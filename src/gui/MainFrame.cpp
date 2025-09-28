#include "MainFrame.hpp"
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif


MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title){
    CreateStatusBar();
    create_menus();
    create_controls();
}

void MainFrame::OnExit(wxCommandEvent& event){
    Close(true);
}

void MainFrame::create_menus(){
    menuBar = new wxMenuBar;

    fileMenu = new wxMenu;
    fileMenu->Append(wxID_ANY, "&Test...");
    fileMenu->Append(wxID_EXIT);

    menuBar->Append(fileMenu, "&File");

    SetMenuBar(menuBar);

    Bind(wxEVT_MENU, &MainFrame::OnExit, this, wxID_EXIT);

}
void MainFrame::create_controls(){
    main_panel = new wxPanel(this);

    receipt_panel = new wxPanel(main_panel, wxID_ANY, wxDefaultPosition, wxSize(400,800));

    search = new wxSearchCtrl(receipt_panel, wxID_ANY, "default value", wxPoint(0,20), wxSize(200,-1));
    receipt_list = new wxListCtrl(receipt_panel, wxID_ANY, wxPoint(0,60), wxSize(400,400));

    
    receipt_list->InsertItem(0,"Test Item");
    



    Bind(wxEVT_SEARCH, &MainFrame::OnSearch, this);
}

void MainFrame::OnSearch(wxCommandEvent& event){
    wxString search_string = event.GetString();
    wxLogStatus(search_string);
}

