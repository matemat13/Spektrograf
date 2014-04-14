#pragma once
#include "wx/wx.h"
#include "include/design.hpp"

#define PERCENTAGE_BIG_MARK_SIZE 25
#define PERCENTAGE_SMALL_MARK_SIZE 15
#define PERCENTAGE_H_MARGIN 8

class PercentagePanel : public wxPanel
{
public:
    PercentagePanel(wxFrame* parent);
 
    void paintEvent(wxPaintEvent& evt);
    void paintNow();
	void Align();

	void onClick(wxMouseEvent& WXUNUSED(event));

	//bool State(bool state);
	//bool State();
	//Size
	int cur_width;
	int cur_height;
    //Size without margin
	int ruler_height;

    DECLARE_EVENT_TABLE()
private:
	bool painting;

	//bool state;
	//int xpos;
	void render(wxDC &dc);
	void insetLine(wxDC &dc, const wxColour &color, int width,  const wxPoint &from, const wxPoint &to);
	void markLineAt(wxDC &dc, float percent, int length,  const wxPen &pen = wxPen(wxColor(0,0,0), 1, wxSOLID));
	void markLineAt(wxDC &dc, float percent, int length, const std::string &label, const wxPen &pen = wxPen(wxColor(0,0,0), 1, wxSOLID));
	void markLineAt(wxDC &dc, float percent, int length, const bool do_label, const wxPen &pen = wxPen(wxColor(0,0,0), 1, wxSOLID));
};

