#pragma once
#include "wx/wx.h"
#include "Kamera.hpp"
#include "SettingsManager.hpp"

class GraphPanel : public wxPanel
{
 
public:
    GraphPanel(wxFrame* parent, SettingsManager *n_SetMan);
 
    void paintEvent(wxPaintEvent& evt);
    void paintNow();
	void Align();
	unsigned int selectedLine;
	
 
    DECLARE_EVENT_TABLE()
private:
	bool painting;
    void render(wxDC& dc);
	void renderError(wxDC& dc);
	void DrawGraph(wxDC& dc, wxImage &img);
	
	void DrawGradientLine(wxDC& dc,wxPoint a, wxPoint b, const wxColour&, const wxColour&);
	Kamera *kamera;
	wxImage *kamObr;
	wxBitmap bitmap;
};
