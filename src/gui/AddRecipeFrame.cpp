// AddRecipeFrame.cpp
//

#include "AddRecipeFrame.hpp"


AddRecipeFrame::AddRecipeFrame(wxFrame* frame_ptr) : wxFrame(frame_ptr, wxID_ANY, "Add a Recipe", wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE & ~wxRESIZE_BORDER & ~wxMAXIMIZE_BOX){
    SetClientSize(500,500);
    Center();
    main_panel = new wxPanel(this);
    box_sizer = new wxBoxSizer(wxVERTICAL);
    
    
    create_controls();
    main_panel->SetSizer(box_sizer);
    Layout();
}


void AddRecipeFrame::create_controls(){

    

    recipe_name_input_box = new wxTextCtrl(main_panel, wxID_ANY, "Name");
    ingredient_name_input_box = new wxTextCtrl(main_panel, wxID_ANY, "Ingredient");
    garnish_input_box = new wxTextCtrl(main_panel, wxID_ANY, "Garnish");
    glass_input_box = new wxTextCtrl(main_panel, wxID_ANY, "Glass");
    extra_notes_input_box = new wxTextCtrl(main_panel, wxID_ANY, "Extra Notes");

    box_sizer->Add(recipe_name_input_box, 10,  wxEXPAND | wxALL, 2);
    box_sizer->Add(ingredient_name_input_box, 10,  wxEXPAND | wxALL, 2);
    box_sizer->Add(garnish_input_box, 10,  wxEXPAND | wxALL, 2);
    box_sizer->Add(glass_input_box, 10,  wxEXPAND | wxALL, 2);
    box_sizer->Add(extra_notes_input_box, 10,  wxEXPAND | wxALL, 2);

    ingredient_list_display;

    save_button;
    cancel_button;
}