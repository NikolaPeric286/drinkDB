#pragma once
#include <wx/wx.h>
#include <wx/listctrl.h>
#include <wx/srchctrl.h>
#include <vector>
#include <iostream>
#include "../logic/Logic.hpp"



class MainFrame : public wxFrame{

public:
    MainFrame(const wxString& title);

    void OnExit( [[maybe_unused]] wxCommandEvent& event )  ;
    void OnSearch(wxCommandEvent& event);
    void OnLoadReceipts(wxCommandEvent& event);
    void OnLoadStock(wxCommandEvent& event);
    void OnClear(wxCommandEvent& event);

private:
    void create_controls();
    void create_menus();
    void create_list();
    
    void update_list();


    wxMenuBar* menuBar;
    wxMenu* fileMenu;

    wxPanel* main_panel;
    wxPanel* receipt_panel;
    
    wxTextCtrl* search;
    wxListCtrl* receipt_list;

};