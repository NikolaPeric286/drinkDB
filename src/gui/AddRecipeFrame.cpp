// AddRecipeFrame.cpp
//

#include "AddRecipeFrame.hpp"


AddRecipeFrame::AddRecipeFrame(wxFrame* frame_ptr,  std::function<void(const wxString&)> _cb) : cb(std::move(_cb)), wxFrame(frame_ptr, wxID_ANY, "Add a Recipe", wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE & ~wxRESIZE_BORDER & ~wxMAXIMIZE_BOX){
    parent_frame = frame_ptr;
    SetClientSize(500,250);
    Center();
    main_panel = new wxPanel(this);
    inputs_panel = new wxPanel(main_panel, wxID_ANY, wxPoint(100,0), wxSize(400,200));;
    button_panel = new wxPanel(main_panel, wxID_ANY, wxPoint(0,200),wxSize(500,50));

    box_sizer = new wxBoxSizer(wxVERTICAL);
    button_sizer = new wxBoxSizer(wxHORIZONTAL);
    
    Bind(wxEVT_CLOSE_WINDOW, [this]([[maybe_unused]] wxCloseEvent& event){
        Bind(wxEVT_SHOW, &AddRecipeFrame::OnShow, this);
        Hide();
        //event.Skip();
    });

    create_controls();
    Layout();
    inputs_panel->SetSizerAndFit(box_sizer);
    button_panel->SetSizerAndFit(button_sizer);    
}


void AddRecipeFrame::create_controls(){

    input_box_titles = new wxStaticText(main_panel,wxID_ANY, "Name\n\nIngredients\n\nGarnish\n\nGlass\n\nExtra", wxPoint(3,8), wxDefaultSize);
    
    wxFont myFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    input_box_titles->SetFont(myFont);
    
    recipe_name_input_box = new wxTextCtrl(inputs_panel, wxID_ANY, placeholder_text[0], wxDefaultPosition, wxSize(400,-1));
    ingredient_name_input_box = new wxTextCtrl(inputs_panel, wxID_ANY, placeholder_text[1], wxDefaultPosition, wxSize(400,-1));
    garnish_input_box = new wxTextCtrl(inputs_panel, wxID_ANY, placeholder_text[2], wxDefaultPosition, wxSize(400,-1));
    glass_input_box = new wxTextCtrl(inputs_panel, wxID_ANY, placeholder_text[3], wxDefaultPosition, wxSize(400,-1));
    extra_notes_input_box = new wxTextCtrl(inputs_panel, wxID_ANY, placeholder_text[4], wxDefaultPosition, wxSize(400,-1));

    

    box_sizer->Add(recipe_name_input_box, 0,    wxALL, 2);
    box_sizer->Add(ingredient_name_input_box, 0,   wxALL, 2);
    box_sizer->Add(garnish_input_box, 0,   wxALL, 2);
    box_sizer->Add(glass_input_box, 0,   wxALL, 2);
    box_sizer->Add(extra_notes_input_box, 0,   wxALL, 2);

    recipe_name_input_box->Bind(wxEVT_LEFT_DOWN, &AddRecipeFrame::OnSelectBox, this);
    ingredient_name_input_box->Bind(wxEVT_LEFT_DOWN, &AddRecipeFrame::OnSelectBox, this);
    garnish_input_box->Bind(wxEVT_LEFT_DOWN, &AddRecipeFrame::OnSelectBox, this);
    glass_input_box->Bind(wxEVT_LEFT_DOWN, &AddRecipeFrame::OnSelectBox, this);
    extra_notes_input_box->Bind(wxEVT_LEFT_DOWN, &AddRecipeFrame::OnSelectBox, this);

    save_button = new wxButton(button_panel, wxID_ANY, "SAVE", wxDefaultPosition, wxDefaultSize);
    cancel_button = new wxButton(button_panel, wxID_ANY, "CANCEL", wxDefaultPosition, wxDefaultSize);

    button_sizer->Add(save_button, 10, wxALIGN_CENTER_VERTICAL , 2);
    button_sizer->Add(cancel_button, 10, wxALIGN_CENTER_VERTICAL , 2);

    cancel_button->Bind(wxEVT_BUTTON, [this]([[maybe_unused]] wxCommandEvent& event) {
        Bind(wxEVT_SHOW, &AddRecipeFrame::OnShow, this);
        Hide();
    });
    save_button->Bind(wxEVT_BUTTON, &AddRecipeFrame::OnSave, this);
    
}

void AddRecipeFrame::OnSelectBox([[maybe_unused]] wxMouseEvent& event){
    
    
    wxTextCtrl* textCtrl = wxDynamicCast(event.GetEventObject(), wxTextCtrl);
    
    if (std::find(placeholder_text.begin(), placeholder_text.end(), textCtrl->GetValue().ToStdString()) !=  placeholder_text.end() ){
        textCtrl->SetValue("");
    }
    
    

    event.Skip();
    
}

void AddRecipeFrame::OnSave([[maybe_unused]] wxCommandEvent& event){
    Recipe temp_recipe;

    temp_recipe.name = recipe_name_input_box->GetValue().ToStdString();
    temp_recipe.garnish = garnish_input_box->GetValue().ToStdString();
    temp_recipe.glass = glass_input_box->GetValue().ToStdString();
    temp_recipe.extra_notes = extra_notes_input_box->GetValue().ToStdString();
    
    std::string ingredients_string = ingredient_name_input_box->GetValue().ToStdString();

    
    std::stringstream ss(ingredients_string);
    std::string item;

   
    while (std::getline(ss, item, ';')) {
        // Trim leading/trailing spaces
        auto trim = [](std::string& s) {
            s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch){ return !std::isspace(ch); }));
            s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch){ return !std::isspace(ch); }).base(), s.end());
        };

        trim(item);
        if (item.empty()) continue;

        // Split by ',' to separate name and quantity
        std::stringstream part(item);
        std::string name, quantity;
        double temp_amount;
        if (std::getline(part, name, ',') && std::getline(part, quantity)) {
            trim(name);
            trim(quantity);

            if(quantity.find("oz") != std::string::npos){
                temp_amount = OZ_TO_ML * std::stod(quantity.erase(quantity.length() - 2));
            }
            else if (quantity.find("ml") != std::string::npos){
                temp_amount = std::stod(quantity.erase(quantity.length() - 2));
            }
            else{
                temp_recipe.ingredient_vector.emplace_back(name, quantity);
                continue;
            }

            temp_recipe.ingredient_vector.emplace_back(name,temp_amount, Ingredient::units::metric);
        }
    }

    DataManager::getInstance().AddRecipe(temp_recipe);
    
    if (cb) cb("");

    Bind(wxEVT_SHOW, &AddRecipeFrame::OnShow, this);
    Hide();
}

void AddRecipeFrame::OnShow([[maybe_unused]] wxShowEvent& event){

    /*
    recipe_name_input_box->SetValue("");
    ingredient_name_input_box->SetValue("");
    garnish_input_box->SetValue("");
    glass_input_box->SetValue("");
    extra_notes_input_box->SetValue("");
    */
    
    if(recipe_name_input_box->GetValue() != placeholder_text[0]){
        recipe_name_input_box->SetValue(placeholder_text[0]);
    }
    if(ingredient_name_input_box->GetValue() != placeholder_text[1]){
        ingredient_name_input_box->SetValue(placeholder_text[1]);
    }
    if(garnish_input_box->GetValue() != placeholder_text[2]){
        garnish_input_box->SetValue(placeholder_text[2]);
    }
    if(glass_input_box->GetValue() != placeholder_text[3]){
        glass_input_box->SetValue(placeholder_text[3]);
    }
    if(extra_notes_input_box->GetValue() != placeholder_text[4]){
        extra_notes_input_box->SetValue(placeholder_text[4]);
    }
   
    
}