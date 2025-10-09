// MainFrame.hpp
// 
#pragma once
#include <wx/wx.h>
#include <wx/listctrl.h>
#include <wx/statbmp.h>
#include <wx/srchctrl.h>
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include "../logic/Logic.hpp"

/*
This header contains the MainFrame class which encompasses the behavior of the GUI.
The app has a menu bar, a status indicator bar, a List panel on the left side
and a recipe panel on the right side.

TODO: 
----- reconsider update_list to make it more readable and compartmentalized




*/


enum IDS {
    ID_Load_Receipts = 2,
    ID_Load_Stock,
    ID_Clear,
    ID_Available,
    ID_Not_Available,
    ID_Recipe_List
};

class MainFrame : public wxFrame{

public:
    MainFrame(const wxString& title);


    // MENU EVENTS ----------------------------

    // Exit event handler
    void OnExit( [[maybe_unused]] wxCommandEvent& event )  ; 

    // Loads recipes into DataMangager and imports the recipes from DataManager into the ListCtrl using update_list
    void OnLoadReceipts([[maybe_unused]] wxCommandEvent& event);

    // Loads stock of ingredients into DataMangager and imports the recipes from DataManager into the ListCtrl using update_list
    void OnLoadStock([[maybe_unused]] wxCommandEvent& event);

    // Clears the ListCtrl without changing the data in DataManager
    void OnClear([[maybe_unused]] wxCommandEvent& event);
    
    // LIST PANEL EVENTS --------------------
    // Handles user typing in box menu
    void OnSearch([[maybe_unused]] wxCommandEvent& event);

    // Handles when user selects a recipe from the ListCtrl
    void OnSelect([[maybe_unused]] wxCommandEvent& event);

    // Handles either of the 2 check box events
    void OnCheckBox([[maybe_unused]] wxCommandEvent& event);

    // Handles when the user clicks on a recipe, displays it on the recipe display side
    void OnSelectRecipe([[maybe_unused]] wxCommandEvent& event);

    // clears the placeholder text in the search bar when the user clicks on it
    void OnClickSearch([[maybe_unused]] wxMouseEvent& event);
    

    // RECIPE PANEL EVENTS -----------------
    

private:
    // loads the images from the file and stores them as images to be converted to bitmaps later
    void create_images();

    // instantiates the panels 
    void create_panels();

    // instantiates the menus
    void create_menus();

    // creates the wxListCtrl as well as all of the supporting buttons, all on the list_panel
    void create_list();

    // creates all of the controlls and text on the recipe_panel
    void create_recipe_display();
    
    // updates the wxListCtrl search to display the information that the user is expecting
    void update_list(wxString search_term = ""); // this function does way to much and should probably be split up and made more readable

    // clears the wxStaticText strings that corrispond to the selected recipe ingredients
    void clear_ingredient_list();

    // clears the images displayed that are stored in the availability_bit_map_vector
    void clear_images();
    
    // does what the title is
    void remove_trailing_zeros(std::string& str);

    // menus

    wxMenuBar* menu_bar;
    wxMenu* file_menu;
    wxMenu* edit_menu;

    // panels

    wxPanel* main_panel;
    wxPanel* list_panel;
    wxPanel* recipe_panel;
    
    // List controls

    wxTextCtrl* search;
    wxListCtrl* recipe_list;
    wxButton* fav_button;    // TODO
    wxCheckBox* available_box;
    wxCheckBox* not_available_box;

    // Recipe Display
    
    wxStaticText* recipe_title;
    wxStaticText* ingredients_title;
    
    // vector of text corrisponding to an ingredient in the selected recipe
    std::vector<wxStaticText*> ingredient_list_vector;
    // vector of images corrisponding to the x or check for each ingredient
    std::vector<wxStaticBitmap*> availability_bit_map_vector;

    wxStaticText* extra_notes;
    wxStaticText* glass_title;
    wxStaticText* garnish_title;
    // Images 

    wxImage* check_mark_image;
    wxImage* x_mark_image;

    // Constant strings

    const wxString title_header = wxString("       "); // idk why this is like this but i dont feel like changing it
    const wxString placeholder_text = wxString("search a recipe...");

    
};