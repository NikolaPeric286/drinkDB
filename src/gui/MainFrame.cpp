// MainFrame.cpp
//
#include "MainFrame.hpp"
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif




MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE & ~wxRESIZE_BORDER & ~wxMAXIMIZE_BOX){
    CreateStatusBar();
    create_panels();
    create_menus();
    create_images();
    create_list();
    create_recipe_display();
}



void MainFrame::create_menus(){
    menuBar = new wxMenuBar;

    fileMenu = new wxMenu;
    fileMenu->Append(ID_Load_Receipts, "&Load Receipts");
    fileMenu->Append(ID_Load_Stock, "&Load Stock");
    fileMenu->Append(ID_Clear, "&Clear Data");
    fileMenu->AppendSeparator();
    fileMenu->Append(wxID_EXIT);

    menuBar->Append(fileMenu, "&File");

    SetMenuBar(menuBar);

    Bind(wxEVT_MENU, &MainFrame::OnExit, this, wxID_EXIT);
    Bind(wxEVT_MENU, &MainFrame::OnLoadReceipts, this,ID_Load_Receipts);
    Bind(wxEVT_MENU, &MainFrame::OnLoadStock, this,ID_Load_Stock);
    Bind(wxEVT_MENU, &MainFrame::OnClear, this, ID_Clear);
    
}

void MainFrame::create_list(){
    recipe_list = new wxListCtrl(list_panel, ID_Recipe_List, wxPoint(0,35), wxSize(400,700), wxLC_REPORT | wxLC_HRULES | wxLC_VRULES);
    
    recipe_list->InsertColumn(1, "Availablity", 0, 200);
    recipe_list->InsertColumn(0, "Name", 0, 200);
    recipe_list->SetDoubleBuffered(true);

    search = new wxTextCtrl(list_panel, wxID_ANY, wxString("search a recipe..."), wxPoint(0,0), wxSize(200,-1));
    
    fav_button = new wxButton(list_panel, wxID_ANY, "",wxPoint(202,3), wxSize(29,29) );
    available_box = new wxCheckBox(list_panel, ID_Available, "Available", wxPoint(230,4), wxSize(-1,15) );
    not_available_box = new wxCheckBox(list_panel, ID_Not_Available, "Not Available", wxPoint(230,19), wxSize(-1,15));

    available_box->SetValue(true);
    not_available_box->SetValue(true);

    Bind(wxEVT_TEXT, &MainFrame::OnSearch, this);
    Bind(wxEVT_CHECKBOX, &MainFrame::OnCheckBox, this, ID_Available);
    Bind(wxEVT_CHECKBOX, &MainFrame::OnCheckBox, this, ID_Not_Available);
    Bind(wxEVT_LIST_ITEM_SELECTED, &MainFrame::OnSelectRecipe, this, ID_Recipe_List);
    search->Bind(wxEVT_LEFT_DOWN, &MainFrame::OnClickSearch, this);

}

void MainFrame::update_list(wxString search_term){
    recipe_list->DeleteAllItems();


    //loads data from logic singleton
    std::vector<Recipe>* recipe_vector = &DataManager::getInstance().GetRecipeVector();
    std::vector<Ingredient>* stock_vector = &DataManager::getInstance().GetStockVector();

    
    Recipe* temp_recipe;
    wxListItem temp_name;
    wxListItem temp_availability;

    bool is_available = true;

    unsigned int id_index = 0; // id_index tracks the id of the created item, used instead of i which is indexing the loaded recipes

    for(unsigned int i = 0; i < recipe_vector->size(); i++){
        
        temp_name = wxListItem();
        temp_recipe = &recipe_vector->at(i);
        
        if(temp_recipe->name.find(search_term) == std::string::npos){ // checks if the search term is in the name
            continue; // if not skips the recipe
        }
       
        

        wxLogStatus("adding " + temp_recipe->name);

        //column 0 is the name column
        temp_name.SetColumn(0);
        temp_name.SetText(temp_recipe->name);
        temp_name.SetId(id_index);
        temp_name.SetAlign(wxLIST_FORMAT_LEFT );
        temp_name.SetData(temp_recipe);
        
        //inserts the name part of the row
        recipe_list->InsertItem(temp_name );

        //if the stock vector is loaded, checks if the recipe is available
        if(stock_vector->size() > 0){
            //column 1 is the availability column
            temp_availability.SetColumn(1);

            temp_availability.SetAlign(wxLIST_FORMAT_LEFT);
            temp_availability.SetId(id_index);

            //for each ngredient in the recipe, it looks through the entire stock vector
            //and if it doesnt find it it exits and sets the associated bool to set a "No"
            is_available = true;
            for(auto it_recipe = temp_recipe->ingredient_vector.begin(); it_recipe != temp_recipe->ingredient_vector.end(); it_recipe++){
                if(!DataManager::getInstance().IsInStock(it_recipe->getName())){
                    is_available = false;
                    break;
                }
            }


            if(is_available){
                temp_availability.SetText("Yes");
            }
            else{
                temp_availability.SetText("No");
            }

            recipe_list->SetItem(temp_availability);
            
            
            if(is_available && !available_box->GetValue() ){
                recipe_list->DeleteItem(id_index);
                id_index--;
            }
            if(!is_available && !not_available_box->GetValue() ){
                recipe_list->DeleteItem(id_index);
                id_index--;
            }
            
        }   
        
        id_index++;
    }
    
}

void MainFrame::create_panels(){
    main_panel = new wxPanel(this);
    list_panel = new wxPanel(main_panel, wxID_ANY, wxDefaultPosition, wxSize(400,800));
    recipe_panel =  new wxPanel(main_panel, wxID_ANY, wxPoint(400,0), wxSize(400,800));

}

void MainFrame::create_recipe_display(){
    background_rect = new wxRect( wxPoint(0,0), wxSize(400,800));
    
    recipe_title = new wxStaticText(recipe_panel, wxID_ANY, title_header, wxPoint(0,40), wxSize(400,-1), wxALIGN_CENTER);
    
    wxFont title_font = recipe_title->GetFont();
    title_font.SetPointSize(20);
    recipe_title->SetFont(title_font);

    
    ingredients_title  = new wxStaticText(recipe_panel, wxID_ANY, wxString("Ingredients:"), wxPoint(20,100));
    ingredients_title->SetFont(title_font);
    availability_display;
    
}


void MainFrame::clear_ingredient_list(){
    for(size_t i = 0; i < ingredient_list_vector.size(); i++){
        ingredient_list_vector[i]->Destroy();
    }
    ingredient_list_vector.clear();
}

void MainFrame::clear_images(){
    for(size_t i = 0; i < availability_bit_map_vector.size(); i++){
        availability_bit_map_vector[i]->Destroy();
       
        
    }
    availability_bit_map_vector.clear();
}

void MainFrame::remove_trailing_zeros(std::string& str) {

    // ChatGPT Wrote this!

    // Find the index of the last character that is NOT '0'
    size_t last_non_zero = str.find_last_not_of('0');

    // If a non-zero character was found, erase everything after it.
    // If the string is all zeros, last_non_zero will be string::npos.
    // In that case, we clear the string or leave a single '0' if desired.
    if (last_non_zero != std::string::npos) {
        str.erase(last_non_zero + 1);
    } else {
        // Handle cases where the string is "0", "00", etc.
        // You might want to clear it or leave a single "0".
        // For example, to leave "0":
        if (!str.empty()) {
            str = "0";
        }
        // Or to clear it completely:
        // str.clear();
    }


    // I added this to remove the . if the number has no decimal 
    if(str.at(str.size()-1) == '.' ){
        str.pop_back();
    }
}

void MainFrame::create_images(){
    wxInitAllImageHandlers();

    check_mark_image = new wxImage();
    x_mark_image = new wxImage();

    check_mark_image->LoadFile(wxT("files/check_mark.png"), wxBITMAP_TYPE_PNG);
    x_mark_image->LoadFile(wxT("files/x_mark.png"), wxBITMAP_TYPE_PNG);

    check_mark_image->Rescale(wxSize(10,10), wxIMAGE_QUALITY_HIGH);
    x_mark_image->Rescale(wxSize(10,10), wxIMAGE_QUALITY_HIGH);

}