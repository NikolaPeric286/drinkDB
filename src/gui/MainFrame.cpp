#include "MainFrame.hpp"
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif


enum IDS {
    ID_Load_Receipts = 2


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
    fileMenu->Append(wxID_ANY, "&Load Stock");
    fileMenu->AppendSeparator();
    fileMenu->Append(wxID_EXIT);

    menuBar->Append(fileMenu, "&File");

    SetMenuBar(menuBar);

    Bind(wxEVT_MENU, &MainFrame::OnExit, this, wxID_EXIT);
    Bind(wxEVT_MENU, &MainFrame::OnLoadReceipts, this,ID_Load_Receipts);

}

void MainFrame::create_list(){
    receipt_list = new wxListCtrl(receipt_panel, wxID_ANY, wxPoint(0,35), wxSize(400,700), wxLC_REPORT);

    receipt_list->InsertColumn(0, "Name", 0, 200);
    //receipt_list->InsertItem(0,"Test Item");
    
    


    Bind(wxEVT_TEXT, &MainFrame::OnSearch, this);
}

void MainFrame::update_list(){
    
    std::vector<Recipe> recipe_vector = DataManager::getInstance().GetVector();
    
    wxString temp_string;
    wxListItem temp_item;
    for(unsigned int i = 0; i < recipe_vector.size(); i++){
        
        temp_item = wxListItem();
        temp_string = recipe_vector.at(i).name;
        wxLogStatus("adding " + temp_string);
        
        temp_item.SetText(temp_string);
        temp_item.SetId(i);
        temp_item.SetAlign(wxLIST_FORMAT_LEFT );
        //temp_item.SetMask(wxLIST_MASK_FORMAT);
        receipt_list->InsertItem(temp_item );
    }
    
}
void MainFrame::create_controls(){
    main_panel = new wxPanel(this);

    receipt_panel = new wxPanel(main_panel, wxID_ANY, wxDefaultPosition, wxSize(400,800));

    search = new wxTextCtrl(receipt_panel, wxID_ANY, "default value", wxPoint(0,0), wxSize(400,-1));
    

}

void MainFrame::OnSearch(wxCommandEvent& event){
    wxString search_string = event.GetString();
    
    wxLogStatus(search_string);
}


void MainFrame::OnLoadReceipts(wxCommandEvent& event){
    DataManager::getInstance().LoadRecipes();
    wxLogStatus("Loaded Receipts");
    update_list();
}
void MainFrame::OnLoadStock(wxCommandEvent& event){

}