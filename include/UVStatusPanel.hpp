#pragma once
#include "wx/wx.h"
//#include "Kamera.hpp"
//#include "SettingsManager.hpp"

#define UV_STATUS_P_PADDING 7

class UVStatusPanel : public wxPanel
{
 
public:
    UVStatusPanel(wxFrame* parent, int pos);
 
    void paintEvent(wxPaintEvent& evt);
    void paintNow();
	void onClick(wxMouseEvent& WXUNUSED(event));

	bool State(bool state);
	bool State();
 
    DECLARE_EVENT_TABLE()
private:
	bool painting;
	bool state;
	void render(wxDC &dc);
	void DrawLed(wxDC &dc, bool status=false, int x=0, int y=0);
};
