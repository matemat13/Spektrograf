#pragma once
#include "wx/wx.h"

#include <windows.h>
#include "main.hpp"
class FrameMain;
class Kamera;


class WavelengthPanel : public wxPanel
{
 
public:
    WavelengthPanel(wxFrame* parent, SettingsManager *setMan, int pos, Kamera* kam);
 
    void paintEvent(wxPaintEvent& evt);
    void paintNow();
	void Align();

	void onClick(wxMouseEvent& WXUNUSED(event));

	//bool State(bool state);
	//bool State();
	//Size
	int cur_width;
	int cur_height;
 
    DECLARE_EVENT_TABLE()
private:
	bool painting;
	SettingsManager *SetMan; 
	Kamera *kam;
	//bool state;
	//int xpos;
	void render(wxDC &dc);

	void drawWavelengthAt(wxDC &dc, const int offset, int wavelength);
	//void DrawLed(wxDC &dc, bool status=false, int x=0, int y=0);
};
