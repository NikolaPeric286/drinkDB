#include <fstream>
#include <iostream>
#include <wx/wx.h>
#include <nlohmann/json.hpp>
#include "logic/Recipe.hpp"
#include "logic/Ingredient.hpp"
#include "logic/DataManager.hpp"


 
class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};
 
class MyFrame : public wxFrame
{
public:
    MyFrame();
 
private:
    void OnHello(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnTest(wxCommandEvent& event);
    void OnLoadRecipes(wxCommandEvent& event){
        DataManager::getInstance().LoadRecipes();
    }
    void OnLoadStock(wxCommandEvent& event){
        DataManager::getInstance().LoadStock();
    }
    void OnPrint(wxCommandEvent& event){
        DataManager::getInstance().PrintAvailableRecipes();
    }
};
 
enum
{
    ID_Hello =1,
    ID_Test,
    ID_Load_Recipts,
    ID_Load_stock,
    ID_Print
};
 
wxIMPLEMENT_APP(MyApp);
 
bool MyApp::OnInit()
{
    MyFrame *frame = new MyFrame();
    frame->Show(true);
    return true;
}
 
MyFrame::MyFrame()
    : wxFrame(NULL, wxID_ANY, "Hello World")
{
    wxMenu *menuFile = new wxMenu;
    menuFile->Append(ID_Hello, "&Hello...\tCtrl-H",
                     "Help string shown in status bar for this menu item");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);
    menuFile->AppendSeparator();
    menuFile->Append(ID_Test, "This is a test...");
 
    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);
 
    wxMenuBar *menuBar = new wxMenuBar;

    wxMenu *menuDrinks = new wxMenu;
    menuDrinks->Append(ID_Load_Recipts, "Load Recipts...");
    menuDrinks->Append(ID_Load_stock, "Load Stock...");
    menuDrinks->AppendSeparator();
    menuDrinks->Append(ID_Print, "Print..."); 
        
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuHelp, "&Help");
    menuBar->Append(menuDrinks, "&Drinks");
 
    SetMenuBar( menuBar );
 
    CreateStatusBar();
    SetStatusText("Welcome to wxWidgets!");
 
    Bind(wxEVT_MENU, &MyFrame::OnHello, this, ID_Hello);
    Bind(wxEVT_MENU, &MyFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &MyFrame::OnExit, this, wxID_EXIT);
    Bind(wxEVT_MENU, &MyFrame::OnTest, this, ID_Test);
    Bind(wxEVT_MENU, &MyFrame::OnLoadRecipes, this, ID_Load_Recipts);
    Bind(wxEVT_MENU, &MyFrame::OnLoadStock, this, ID_Load_stock);
    Bind(wxEVT_MENU, &MyFrame::OnPrint, this, ID_Print);

}

void MyFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}

void MyFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox("This is a wxWidgets Hello World example",
                 "About Hello World", wxOK | wxICON_INFORMATION);
}
 
void MyFrame::OnHello(wxCommandEvent& event)
{
    wxLogMessage("Hello world from wxWidgets!");
}

void MyFrame::OnTest(wxCommandEvent& event){
    std::cout << "This is a test \n";
}
//DataManager::getInstance().LoadRecipes();
//DataManager::getInstance().LoadStock();
//DataManager::getInstance().PrintAvailableRecipes();


    


