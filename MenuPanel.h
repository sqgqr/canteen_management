#pragma once
#include <wx/wx.h>
#include "menu.h"

class MenuPanel : public wxPanel
{
public:
    MenuPanel(wxWindow* parent);
    void OnButtonHoverEnter(wxMouseEvent& event);
    void OnButtonHoverLeave(wxMouseEvent& event);
    void OnDelete(wxMouseEvent& event);
private:
    Menu* m_menu;
    wxListBox* m_itemList;
};