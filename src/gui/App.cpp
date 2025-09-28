
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
#include "App.hpp"
wxIMPLEMENT_APP(App);

bool App::OnInit() {
    MainFrame* mainFrame = new MainFrame("DrinkDB");
    mainFrame->SetClientSize(800,800);
    mainFrame->Center();
    mainFrame->Show();
    return true;
}