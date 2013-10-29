#pragma once
#include "wx/wx.h"
//#include "Kamera.hpp"
//#include "SettingsManager.hpp"

class UVStatusPanel : public wxPanel
{
 
public:
    UVStatusPanel(wxFrame* parent, int pos);
 
    void paintEvent(wxPaintEvent& evt);
    void paintNow();
 
    DECLARE_EVENT_TABLE()
private:
	bool painting;
	void render(wxDC &dc);
};
