#pragma once
#include "wx/wx.h"
#include "Kamera.hpp"
#include "SettingsManager.hpp"

class BasicDrawPane : public wxPanel
{
 
public:
    BasicDrawPane(wxFrame* parent, SettingsManager *n_SetMan);
 
    void paintEvent(wxPaintEvent& evt);
    void paintNow();
	
 
    DECLARE_EVENT_TABLE()
private:
	bool painting;
    void render(wxDC& dc);
	void reRender(wxDC& dc);
	void renderError(wxDC& dc);
	

	Kamera *kamera;
	wxImage *kamObr;
	wxBitmap bitmap;
};
