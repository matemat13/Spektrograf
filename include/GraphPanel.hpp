#pragma once
#include "wx/wx.h"
#include "Kamera.hpp"
#include "SettingsManager.hpp"
#include <sstream>
#include <math.h>

#include <algorithm>

	 
class GraphPanel : public wxPanel
{
 
public:
    GraphPanel(wxFrame* parent, SettingsManager *n_SetMan);
 
    void paintEvent(wxPaintEvent& evt);
    void paintNow();
	void Align();
	unsigned int selectedLine;

	bool drawMode;
	
 
    DECLARE_EVENT_TABLE()
private:
	bool painting;
    void render(wxDC& dc);
	void renderError(wxDC& dc);
	void DrawGraph(wxDC& dc, wxImage &img);
	void DrawGraph(wxDC& dc, const unsigned char*data, const int &length);
	void DrawGraphUI(wxDC& dc);

	void DrawGradientLine(wxDC& dc,wxPoint a, wxPoint b, const wxColour&, const wxColour&);
	Kamera *kamera;
	wxImage *kamObr;
	wxBitmap bitmap;

	unsigned long render_time;
	unsigned int render_count;
	unsigned short fps;

};
