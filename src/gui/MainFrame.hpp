// MainFrame.hpp
// 
#pragma once
#include <wx/wx.h>
#include <wx/listctrl.h>
#include <wx/srchctrl.h>
#include <vector>
#include <iostream>
#include <string>
#include "../logic/Logic.hpp"

/*
This header contains the MainFrame class which encompasses the behavior of the GUI.
The app has a menu bar, a status indicator bar, a List panel on the left side
and a recipe panel on the right side.

TODO: 
*reconsider update_list to make it more readable and compartmentalized




*/


class MainFrame : public wxFrame{

public:
    MainFrame(const wxString& title);


    // MENU EVENTS ----------------------------
    // Exit event handler
    void OnExit( [[maybe_unused]] wxCommandEvent& event )  ; 
    // Loads recipes into DataMangager and imports the recipes from DataManager into the ListCtrl using update_list
    void OnLoadReceipts(wxCommandEvent& event);
    // Loads stock of ingredients into DataMangager and imports the recipes from DataManager into the ListCtrl using update_list
    void OnLoadStock(wxCommandEvent& event);
    // Clears the ListCtrl without changing the data in DataManager
    void OnClear(wxCommandEvent& event);
    
    // LIST PANEL EVENTS --------------------
    // Handles user typing in box menu
    void OnSearch(wxCommandEvent& event);
    // Handles when user selects a recipe from the ListCtrl
    void OnSelect(wxCommandEvent& event);
    // RECIPE PANEL EVENTS -----------------
    

private:

    void create_panels();
    void create_controls();
    void create_menus();
    void create_list();
    
    void update_list(wxString search_term = "");

    // menus
    wxMenuBar* menuBar;
    wxMenu* fileMenu;

    // panels
    wxPanel* main_panel;
    wxPanel* list_panel;
    wxPanel* recipe_panel;
    
    // List controls
    wxTextCtrl* search;
    wxListCtrl* recipe_list;
    wxButton* fav_button;
    wxCheckBox* available_box;
    wxCheckBox* not_available_box;

};