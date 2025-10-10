// AddRecipeFrame.cpp
//

#include "AddRecipeFrame.hpp"


AddRecipeFrame::AddRecipeFrame(wxFrame* frame_ptr) : wxFrame(frame_ptr, wxID_ANY, "Add a Recipe", wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE & ~wxRESIZE_BORDER & ~wxMAXIMIZE_BOX){
    SetClientSize(500,500);
    Center();
    main_panel = new wxPanel(this);
    create_controls();
}


void AddRecipeFrame::create_controls(){
    
}