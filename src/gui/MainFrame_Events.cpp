// MainFrame_Events.cpp
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
    update_list(search->GetValue()); // passes the search term to preserve searching after checking a box
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
    
    clear_ingredient_list();
    unsigned int offset = 0;

    wxString ingredient_line_string;
    
    double quantity;
    std::string quantity_string;
    for(auto it = recipe_ptr->ingredient_vector.begin(); it != recipe_ptr->ingredient_vector.end(); it++){
        //std::cout << it->getName() << "\n";
       
        ingredient_line_string.Clear();
        


        quantity = std::round(it->getQuantity(Ingredient::units::imperial)*100)/100;
       
        if(quantity != -1 && quantity != -0.03){
            quantity_string = std::to_string(quantity);
            remove_trailing_zeros(quantity_string);
            quantity_string.append("oz ");


            ingredient_line_string = wxString("----- " + quantity_string + " of " + it->getName());
        }
        else{
            
            quantity_string = it->getQuantityString();
            if(quantity_string == "to top"){
                ingredient_line_string = wxString("----- " + it->getName() + " to top");
            }else{
                ingredient_line_string = wxString("----- " + quantity_string + " of " + it->getName());
            }
        }

        
        
        ingredient_list_vector.push_back( new wxStaticText(recipe_panel, wxID_ANY, ingredient_line_string, wxPoint(20,150 + offset)));
        offset += 20;

        ingredient_line_string.Clear();
        
    }
    

}