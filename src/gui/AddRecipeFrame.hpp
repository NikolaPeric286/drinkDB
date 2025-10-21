// AddRecipeFrame.hpp
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
#include <functional>
#include <algorithm>
#include "../logic/Logic.hpp"


class AddRecipeFrame : public wxFrame{

public:
    
    AddRecipeFrame(wxFrame* frame_ptr,  std::function<void(const wxString&)> _cb);

    enum IDs{
        ID_recipe_name_input_box=2,
        ID_ingredient_name_input_box,
        ID_garnish_input_box,
        ID_glass_input_box,
        ID_extra_notes_input_box
    };

    void OnSelectBox([[maybe_unused]] wxMouseEvent& event);

    void OnSave([[maybe_unused]] wxCommandEvent& event);
    
    void OnShow([[maybe_unused]] wxShowEvent& event);

private:

    wxFrame* parent_frame;
    
    std::function<void(const wxString&)> cb;
    
    std::vector<std::string> placeholder_text = {
        "Enter Recipe Name",
        "Enter ingredient, quantity. Separate with ;",
        "Enter Garnish or leave empty",
        "Enter Type of Glass",
        "Enter Extra Notes or leave empty"
    };

    void create_controls();

    wxBoxSizer* box_sizer;
    wxBoxSizer* button_sizer;

    wxPanel* main_panel;
    wxPanel* inputs_panel;
    wxPanel* button_panel;

    wxStaticText* input_box_titles;
    

    wxTextCtrl* recipe_name_input_box;
    wxTextCtrl* ingredient_name_input_box;
    wxTextCtrl* garnish_input_box;
    wxTextCtrl* glass_input_box;
    wxTextCtrl* extra_notes_input_box;

    

    wxButton* save_button;
    wxButton* cancel_button;
    



};

