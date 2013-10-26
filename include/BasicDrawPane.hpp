#pragma once
#include "wx/wx.h"
#include "Kamera.hpp"


class BasicDrawPane : public wxPanel
{
 
public:
    BasicDrawPane(wxFrame* parent);
 
    void paintEvent(wxPaintEvent& evt);
    void paintNow();
 
    DECLARE_EVENT_TABLE()
private:
	bool painting;
    void render(wxDC& dc);
	void renderWaiting(wxDC& dc);
	Kamera *kamera;
	wxImage *kamObr;
	wxBitmap bitmap;
};
