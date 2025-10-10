
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
#include "App.hpp"
wxIMPLEMENT_APP(App);  // entry point is in here


// the conditional compilation here is bad and i will be changing this

#ifdef __UNIX__

bool App::OnInit() {
    MainFrame* mainFrame = new MainFrame("DrinkDB");
    mainFrame->SetClientSize(800,800);
    mainFrame->Center();
    mainFrame->Show();
    //wxImage::AddHandler(new wxPNGHandler);
    
    

    
    return true;
}

#endif

#ifdef _WIN32

    bool App::OnInit() {
    MainFrame* mainFrame = new MainFrame("DrinkDB");
    mainFrame->SetClientSize(700,700);
    mainFrame->Center();
    mainFrame->Show();
    //wxImage::AddHandler(new wxPNGHandler);
    
    
    return true;
}

#endif