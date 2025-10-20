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

