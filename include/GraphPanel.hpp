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
	
 
    DECLARE_EVENT_TABLE()
private:
	bool painting;
    void render(wxDC& dc);
	void renderError(wxDC& dc);
	void DrawGraph(wxDC& dc, wxImage &img);
	

	Kamera *kamera;
	wxImage *kamObr;
	wxBitmap bitmap;
};
