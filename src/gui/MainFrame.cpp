// MainFrame.cpp
//
// Implementation for MainFrame functions, except 
// event handlers which are in MainFrame_Events.cpp
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
    create_add_recipe_window();

    
    DataManager::getInstance().LoadRecipes();
    wxLogStatus("Loaded Receipts");
    update_list();


    DataManager::getInstance().LoadStock();
    wxLogStatus("Loaded Stock");
    update_list();


}



void MainFrame::create_menus(){
    menu_bar = new wxMenuBar;

    file_menu = new wxMenu;
    file_menu->Append(ID_Load_Receipts, "&Load Receipts");
    file_menu->Append(ID_Load_Stock, "&Load Stock");
    file_menu->Append(ID_Clear, "&Clear Data");
    file_menu->AppendSeparator();
    file_menu->Append(wxID_EXIT);

    edit_menu = new wxMenu;
    edit_menu->Append(ID_Add, "&Add Recipe");
    edit_menu->Append(wxID_ANY, "&Edit Stock");
    edit_menu->Append(wxID_ANY, "&Delete Item");
    edit_menu->Append(ID_Save, "&Save Changes");

    menu_bar->Append(file_menu, "&File");
    menu_bar->Append(edit_menu, "&Edit");

    SetMenuBar(menu_bar);

    Bind(wxEVT_MENU, &MainFrame::OnExit, this, wxID_EXIT);
    Bind(wxEVT_MENU, &MainFrame::OnLoadReceipts, this,ID_Load_Receipts);
    Bind(wxEVT_MENU, &MainFrame::OnLoadStock, this,ID_Load_Stock);
    Bind(wxEVT_MENU, &MainFrame::OnClear, this, ID_Clear);
    Bind(wxEVT_MENU, &MainFrame::OnAdd, this, ID_Add);
    Bind(wxEVT_MENU, &MainFrame::OnSave, this, ID_Save);    
}

void MainFrame::create_list(){
    recipe_list = new wxListCtrl(list_panel, ID_Recipe_List, wxPoint(0,35), wxSize(400,700), wxLC_REPORT | wxLC_HRULES | wxLC_VRULES);
    recipe_list->SetDoubleBuffered(1);
    recipe_list->InsertColumn(1, "Availablity", 0, 200);
    recipe_list->InsertColumn(0, "Name", 0, 200);
    recipe_list->SetDoubleBuffered(true);

    search = new wxTextCtrl(list_panel, ID_Search, wxString("search a recipe..."), wxPoint(0,0), wxSize(200,35));
    
    fav_button = new wxButton(list_panel, wxID_ANY, "",wxPoint(202,3), wxSize(29,29) );
    available_box = new wxCheckBox(list_panel, ID_Available, "Available", wxPoint(230,4), wxSize(-1,15) ); //////
    not_available_box = new wxCheckBox(list_panel, ID_Not_Available, "Not Available", wxPoint(230,19), wxSize(-1,15)); /////////

    available_box->SetValue(true);
    not_available_box->SetValue(true);

    Bind(wxEVT_TEXT, &MainFrame::OnSearch, this, ID_Search);
    Bind(wxEVT_CHECKBOX, &MainFrame::OnCheckBox, this, ID_Available);
    Bind(wxEVT_CHECKBOX, &MainFrame::OnCheckBox, this, ID_Not_Available);
    Bind(wxEVT_LIST_ITEM_SELECTED, &MainFrame::OnSelectRecipe, this, ID_Recipe_List);
    search->Bind(wxEVT_LEFT_DOWN, &MainFrame::OnClickSearch, this);

}

void MainFrame::create_add_recipe_window(){
    std::function<void(const wxString&)> cb = std::bind(&MainFrame::update_list, this, std::placeholders::_1);
    add_recipe_frame_ptr = new AddRecipeFrame(this , std::move(cb));
    add_recipe_frame_ptr->Hide();
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
    
    list_panel->SetDoubleBuffered(true);
    main_panel->Bind(wxEVT_ERASE_BACKGROUND, [](wxEraseEvent&){ /* swallow */ });    
    list_panel->Bind(wxEVT_ERASE_BACKGROUND, [](wxEraseEvent&){ /* swallow */ });
    recipe_panel =  new wxPanel(main_panel, wxID_ANY, wxPoint(400,0), wxSize(400,800));

}

void MainFrame::create_recipe_display(){
    
    
    recipe_title = new wxStaticText(recipe_panel, wxID_ANY, title_header, wxPoint(0,40), wxSize(400,-1), wxALIGN_CENTER);
    
    wxFont title_font = recipe_title->GetFont();
    title_font.SetPointSize(20);
    recipe_title->SetFont(title_font);

    
    ingredients_title  = new wxStaticText(recipe_panel, wxID_ANY, wxString("Ingredients:"), wxPoint(20,100));
    ingredients_title->SetFont(title_font);
    
    glass = new wxStaticText(recipe_panel, wxID_ANY, "");
    garnish = new wxStaticText(recipe_panel, wxID_ANY, "");
    extra_notes = new wxStaticText(recipe_panel, wxID_ANY, "");
    
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



void MainFrame::create_images(){
    wxInitAllImageHandlers();

    check_mark_image = new wxImage();
    x_mark_image = new wxImage();

    check_mark_image->LoadFile(wxT("files/check_mark.png"), wxBITMAP_TYPE_PNG);
    x_mark_image->LoadFile(wxT("files/x_mark.png"), wxBITMAP_TYPE_PNG);

    check_mark_image->Rescale(wxSize(10,10), wxIMAGE_QUALITY_HIGH);
    x_mark_image->Rescale(wxSize(10,10), wxIMAGE_QUALITY_HIGH);

}