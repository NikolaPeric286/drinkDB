#include "MainFrame.hpp"
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif


enum IDS {
    ID_Load_Receipts = 2,
    ID_Load_Stock,
    ID_Clear

};

MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title){
    CreateStatusBar();
    create_menus();
    create_controls();
    create_list();
}

void MainFrame::OnExit(wxCommandEvent& event){
    Close(true);
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
    recipe_list = new wxListCtrl(receipt_panel, wxID_ANY, wxPoint(0,35), wxSize(400,700), wxLC_REPORT | wxLC_HRULES | wxLC_VRULES);
    
    recipe_list->InsertColumn(1, "Availablity", 0, 200);
    recipe_list->InsertColumn(0, "Name", 0, 200);
    
    Bind(wxEVT_TEXT, &MainFrame::OnSearch, this);
}

void MainFrame::update_list(wxString search_term){
    recipe_list->DeleteAllItems();


    //loads data from logic singleton
    std::vector<Recipe> recipe_vector = DataManager::getInstance().GetRecipeVector();
    std::vector<Ingredient> stock_vector = DataManager::getInstance().GetStockVector();

    
    Recipe temp_recipe;
    wxListItem temp_name;
    wxListItem temp_availability;

    bool is_available = true;

    unsigned int id_index = 0; // id_index tracks the id of the created item, used instead of i which is indexing the loaded recipes

    for(unsigned int i = 0; i < recipe_vector.size(); i++){
        
        temp_name = wxListItem();
        temp_recipe = recipe_vector.at(i);

        if(temp_recipe.name.find(search_term) == std::string::npos){ // checks if the search term is in the name
            continue; // if not skips the recipe
        }

        wxLogStatus("adding " + temp_recipe.name);

        //column 0 is the name column
        temp_name.SetColumn(0);
        temp_name.SetText(temp_recipe.name);
        temp_name.SetId(id_index);
        temp_name.SetAlign(wxLIST_FORMAT_LEFT );
        
        //inserts the name part of the row
        recipe_list->InsertItem(temp_name );


        //if the stock vector is loaded, checks if the recipe is available
        if(stock_vector.size() > 0){
            //column 1 is the availability column
            temp_availability.SetColumn(1);

            temp_availability.SetAlign(wxLIST_FORMAT_LEFT);
            temp_availability.SetId(id_index);

            //for each ngredient in the recipe, it looks through the entire stock vector
            //and if it doesnt find it it exits and sets the associated bool to set a "No"
            is_available = true;
            for(auto it_recipe = temp_recipe.ingredient_vector.begin(); it_recipe != temp_recipe.ingredient_vector.end(); it_recipe++){
                for(auto it_stock = stock_vector.begin(); it_stock != stock_vector.end(); it_stock++){
                    if(it_recipe->getName() == it_stock->getName() && !it_stock->present){
                        is_available = false;
                        break;
                    }
                }
                if(!is_available) { break;}
            }


            if(is_available){
                temp_availability.SetText("Yes");
            }
            else{
                temp_availability.SetText("No");
            }
            
            
            recipe_list->SetItem(temp_availability);
        }   
        
        id_index++;
    }
    
}
void MainFrame::create_controls(){
    main_panel = new wxPanel(this);

    receipt_panel = new wxPanel(main_panel, wxID_ANY, wxDefaultPosition, wxSize(400,800));

    search = new wxTextCtrl(receipt_panel, wxID_ANY, "default value", wxPoint(0,0), wxSize(400,-1));
    

}

void MainFrame::OnSearch(wxCommandEvent& event){
    wxString search_string = event.GetString();
    
    update_list(search_string);
    

    wxLogStatus(search_string);
}


void MainFrame::OnLoadReceipts(wxCommandEvent& event){
    DataManager::getInstance().LoadRecipes();
    wxLogStatus("Loaded Receipts");
    update_list();
}
void MainFrame::OnLoadStock(wxCommandEvent& event){
    DataManager::getInstance().LoadStock();
    wxLogStatus("Loaded Stock");
    update_list();
}

void MainFrame::OnClear(wxCommandEvent& event){
    DataManager::getInstance().Clear();
    update_list();
}