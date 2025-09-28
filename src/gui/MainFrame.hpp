#pragma once
#include <wx/wx.h>
#include <wx/listctrl.h>
#include <wx/srchctrl.h>



class MainFrame : public wxFrame{

public:
    MainFrame(const wxString& title);

    void OnExit(wxCommandEvent& event);
    void OnSearch(wxCommandEvent& event);

private:
    void create_controls();
    void create_menus();


    wxMenuBar* menuBar;
    wxMenu* fileMenu;

    wxPanel* main_panel;
    wxPanel* receipt_panel;
    
    wxSearchCtrl* search;
    wxListCtrl* receipt_list;

};