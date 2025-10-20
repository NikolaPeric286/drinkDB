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


class AddRecipeFrame : public wxFrame{

public:
    AddRecipeFrame(wxFrame* frame_ptr);

    enum IDs{
        ID_recipe_name_input_box=2,
        ID_ingredient_name_input_box,
        ID_garnish_input_box,
        ID_glass_input_box,
        ID_extra_notes_input_box
    };

    void OnSelectBox([[maybe_unused]] wxMouseEvent& event);

private:

    void create_controls();

    wxBoxSizer* box_sizer;

    wxPanel* main_panel;

    wxTextCtrl* recipe_name_input_box;
    wxTextCtrl* ingredient_name_input_box;
    wxTextCtrl* garnish_input_box;
    wxTextCtrl* glass_input_box;
    wxTextCtrl* extra_notes_input_box;

    wxListCtrl* ingredient_list_display;

    wxButton* save_button;
    wxButton* cancel_button;
    



};

