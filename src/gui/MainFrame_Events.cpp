// MainFrame_Events.cpp
//

#include "MainFrame.hpp"
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif


void MainFrame::OnExit(wxCommandEvent& event){
    Close(true);
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

void MainFrame::OnCheckBox(wxCommandEvent& event){
    update_list(search->GetValue()); // passes the search term to preserve searching after checking a box
}