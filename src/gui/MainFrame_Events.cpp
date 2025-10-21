// MainFrame_Events.cpp
//
// This file contains all of the event handlers
// for the MainFrame class
//
//
#include "MainFrame.hpp"
#include "../logic/Logic.hpp"
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif


void MainFrame::OnExit([[maybe_unused]] wxCommandEvent& event){
    Close(true);
}

void MainFrame::OnSearch([[maybe_unused]] wxCommandEvent& event){
    wxString search_string = event.GetString();
    
    update_list(search_string);
    wxLogStatus(search_string);
}


void MainFrame::OnLoadReceipts([[maybe_unused]] wxCommandEvent& event){
    DataManager::getInstance().LoadRecipes();
    wxLogStatus("Loaded Receipts");
    update_list();
}
void MainFrame::OnLoadStock([[maybe_unused]] wxCommandEvent& event){
    DataManager::getInstance().LoadStock();
    wxLogStatus("Loaded Stock");
    update_list();
}

void MainFrame::OnClear([[maybe_unused]] wxCommandEvent& event){
    DataManager::getInstance().Clear();
    update_list();
}

void MainFrame::OnCheckBox([[maybe_unused]] wxCommandEvent& event){
    update_list((search->GetValue() != placeholder_text)? search->GetValue(): ""); // passes the search term to preserve searching after checking a box, but only if the term is not placeholder text
}

void MainFrame::OnSelectRecipe([[maybe_unused]] wxCommandEvent& event){

    

    // gets the index of the first item that is selected 
    long selected_index = recipe_list->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);


    // loads the item data into the temporary selected_item object
    wxListItem selected_item;
    selected_item.SetId(selected_index);
    recipe_list->GetItem(selected_item);

    wxString selected_item_name = selected_item.GetText();

    wxLogStatus("Selected Item: " + selected_item_name);

    //sets the recipe name in the recipe section
    recipe_title->SetLabel(selected_item_name);

    // this code is kind of annoying, the pointer that GetData GetData returns needs to be cast to the actual ptr type 
    wxUIntPtr recipe_data_ptr = selected_item.GetData();
    Recipe* recipe_ptr = reinterpret_cast<Recipe*>(recipe_data_ptr);
    if(recipe_ptr == nullptr){
        std::cout << "nullptr!\n";
    }

    recipe_ptr->printRecipe();
    

    // clears everything each time because the code just redraws everything every time
    // could probably go about it more effeciently but oh well 
    clear_ingredient_list();
    clear_images();


    // index of distance between lines, incremented at end of loop
    unsigned int offset = 0;

    wxString ingredient_line_string;
    
    unsigned int image_offset;
    double quantity;
    std::string quantity_string;

    

    for(auto it = recipe_ptr->ingredient_vector.begin(); it != recipe_ptr->ingredient_vector.end(); it++){
        
        
        ingredient_line_string.Clear();
        
        

        quantity = std::round(it->getQuantity(Ingredient::units::imperial)*100)/100;
        

        // if the quantity is either of these two it means that the quantity read from the json
        // is not a numeric quantity but some other random unit or who knows
        // -0.03 comes from converting -1 from metric to oz somewhere in the backend
        if(quantity != -1 && quantity != -0.03){
            quantity_string = std::to_string(quantity);
            remove_trailing_zeros(quantity_string);
            quantity_string.append("oz ");


            ingredient_line_string = wxString("----- " + quantity_string + " of " + it->getName());
        }
        else{
            
            quantity_string = it->getQuantityString();

            // this if statement is needed to switch the order of the output in the case of 
            // "to top". It would probably be a good idea to write all of this more readibly 
            if(quantity_string == "to top"){
                ingredient_line_string = wxString("----- " + it->getName() + " to top");
            }else{
                ingredient_line_string = wxString("----- " + quantity_string + " of " + it->getName());
            }
        }

        
        
        ingredient_list_vector.push_back( new wxStaticText(recipe_panel, wxID_ANY, ingredient_line_string, wxPoint(20,150 + offset)));
        

        ingredient_line_string.Clear();

        // doesnt draw any images if the stock is not loaded yet
        if(!DataManager::getInstance().GetStockVector().empty()){
            image_offset = ingredient_list_vector.back()->GetSize().GetX() + 10;
            
            // the following gross one liner fills the vector of bitmaps with the corrisponding 
            // image (check or x) depending on wether the ingredient is available
            // and sets the position based on the length of the ingredient line string
            // so that the image is positioned next to the end of the string
            availability_bit_map_vector.emplace_back(new wxStaticBitmap(recipe_panel, wxID_ANY, wxBitmapBundle( (DataManager::getInstance().IsInStock(it->getName()))? *check_mark_image : *x_mark_image), wxPoint(20+image_offset, 154 + offset),wxDefaultSize, wxALIGN_CENTRE ));
        }
        offset += 20;
    }

    std::string glass_string = recipe_ptr->glass;
    std::string garnish_string = recipe_ptr->garnish;
    std::string extra_notes_string = recipe_ptr->extra_notes;

    
    

    offset+=20;
    if(!glass_string.empty()){
        glass->SetLabel(wxString("Glass: " + glass_string));
        glass->SetPosition(wxPoint(20, 150+offset));
        offset+=20;
    }
    else{
        glass->SetLabel("");
    }
   
    if(!garnish_string.empty()){
        garnish->SetLabel(wxString("Garnish: " +  garnish_string));
        garnish->SetPosition(wxPoint(20, 150+offset));
        offset+=20;
    }
    else{
        garnish->SetLabel("");
    }
    
    if(!extra_notes_string.empty()){
        extra_notes->SetLabel(wxString("Extra Notes: " + extra_notes_string));
        extra_notes->SetPosition(wxPoint(20, 150+offset));
    }
    else{
        extra_notes->SetLabel("");
    }
    
    

}


void MainFrame::OnClickSearch([[maybe_unused]] wxMouseEvent& event){
    Freeze();
    if(search->GetValue() == placeholder_text){
        search->Clear();
    }
    event.Skip();
    Thaw();
}

void MainFrame::OnAdd([[maybe_unused]] wxCommandEvent& event){
    wxLogStatus("Opening Add Recipe Menu");

    add_recipe_frame_ptr->Show();

}

void MainFrame::OnSave([[maybe_unused]] wxCommandEvent& event){
    if(!DataManager::getInstance().GetRecipeVector().empty()){
        DataManager::getInstance().PrintToFile();       
    }
}


void MainFrame::OnDelete([[maybe_unused]] wxCommandEvent& event){

    int selected_item_count = recipe_list->GetSelectedItemCount();

    wxString message = wxString::Format( "Are you sure you want to delete %d %s?", selected_item_count, selected_item_count == 1 ? "recipe" : "recipes");
    int response = wxMessageBox(message, "", wxYES_NO | wxICON_QUESTION);

    if (response == wxNO){
        return;
    }



    long item = -1;
    wxUIntPtr item_data;
    while(1){
        item = recipe_list->GetNextItem(item, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);

        if (item == -1) break;

        item_data = recipe_list->GetItemData(item);

        auto it = std::find(DataManager::getInstance().GetRecipeVector().begin(), DataManager::getInstance().GetRecipeVector().end(), *reinterpret_cast<Recipe*>(item_data));
        
        if( it != DataManager::getInstance().GetRecipeVector().end()){
            DataManager::getInstance().GetRecipeVector().erase(it);
        }
    }
    update_list();

    message = wxString::Format("Deleted %d %s.", selected_item_count, selected_item_count == 1 ? "recipe" : "recipes");
    wxMessageBox(message,  "", wxOK);


}
