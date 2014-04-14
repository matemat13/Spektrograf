#include "..\include\Percentage.hpp"




#include "include/Wavelength.hpp"


PercentagePanel::PercentagePanel(wxFrame* parent) :
wxPanel(parent)
{
	painting = false;

}
void PercentagePanel::onClick(wxMouseEvent& WXUNUSED(event)) {
	paintNow();
	return;
}
void PercentagePanel::render(wxDC &dc) {
 dc.SetBackground(wxBrush (APP_STYLE_MAINBG));
 dc.Clear();
 //Nahrazeni inset borderu
 /*dc.SetPen(wxPen(wxColor(105,105,105), 1, wxSOLID));
 dc.DrawLine(wxPoint(cur_width-1, PERCENTAGE_H_MARGIN-1), wxPoint(cur_width-1, ruler_height+PERCENTAGE_H_MARGIN));
 dc.SetPen(wxPen(wxColor(160,160,160), 1, wxSOLID));
 dc.DrawLine(wxPoint(cur_width-2, PERCENTAGE_H_MARGIN-2), wxPoint(cur_width-2, ruler_height+PERCENTAGE_H_MARGIN));*/
 //Debug linka
 //dc.SetPen(wxPen(wxColor(255,160,130), 1, wxSOLID));
 //dc.DrawLine(wxPoint(cur_width-3, 0), wxPoint(cur_width-3, cur_height));

 /*insetLine(dc, wxColor(0,0,0),1, wxPoint(cur_width-PERCENTAGE_BIG_MARK_SIZE,5),  wxPoint(cur_width, 5));
 insetLine(dc, wxColor(0,0,0),3, wxPoint(2,30),  wxPoint(cur_width, 30));

 insetLine(dc, wxColor(0,0,0),0, wxPoint(2,50),  wxPoint(cur_width, 50));*/

 //markLineAt(dc, 0.5, 20);
 //markLineAt(dc, 0.75, 25, std::string("75%"));
 //markLineAt(dc, 0.9, 25, true);

 //Draw all marks
 //Length of the mark
 int markSize;
 //How many pixels exuals 1%
 float pixelsPerPercent = ruler_height/100.0;
 //What is the smallest allowed mark density?
 int step = 1;
 if(pixelsPerPercent<5) {
	 if(pixelsPerPercent<=0.1) {
		 step = 25;
	 }
	 else if(pixelsPerPercent<=2) {
		 step = 5;
	 }
	 else {
		 step = 2;
	 }
 }


 for(int i=0; i<=100; i+=step) {
	 //Default mark size
	 markSize = 8;
	 //Larger for *5
	 if(i%5==0)
		 markSize+=3;
	 //Even larger for *10
	 if(i%10==0) {
		 markSize+=5;
	 }
	 markLineAt(dc, ((float)(i))/100.0, markSize, i%10==0);
 }
}

void PercentagePanel::insetLine(wxDC &dc, const wxColour &color, int width, const wxPoint &from, const wxPoint &to) {
 if(width>0) {
   dc.SetPen(wxPen(color, width, wxSOLID));
   dc.DrawLine(from,to);
 }
 
 width = ceil(width/2.0);

 const wxPen darkPen = wxPen(wxColor(105,105,105), 1, wxSOLID);
 const wxPen lightPen = wxPen(wxColor(160,160,160), 1, wxSOLID);
 //Horni
 dc.SetPen(darkPen);
 dc.DrawLine(from-wxPoint(0,width),to-wxPoint(0,width));
 dc.SetPen(lightPen);
 dc.DrawLine(from-wxPoint(1,width+1),to-wxPoint(1,width+1));
 //Levy
 dc.SetPen(darkPen);
 dc.DrawLine(from-wxPoint(0,width),from+wxPoint(0,width));
 dc.SetPen(lightPen);
 dc.DrawLine(from+wxPoint(-1,-width-1),from+wxPoint(-1,width+1));
 //Dolni
 dc.SetPen(darkPen);
 dc.DrawLine(from+wxPoint(0,width),to+wxPoint(0,width));
 dc.SetPen(lightPen);
 dc.DrawLine(from+wxPoint(-1,width+1),to+wxPoint(-1,width+1));
}
void PercentagePanel::markLineAt(wxDC &dc, float percent, int length, const wxPen &pen) {
	float hpos= percent*(float)ruler_height+PERCENTAGE_H_MARGIN;
	dc.SetPen(pen);
	dc.DrawLine(wxPoint(cur_width-2-length, hpos), wxPoint(cur_width-2, hpos));
}
void PercentagePanel::markLineAt(wxDC &dc, float percent, int length, const std::string &label, const wxPen &pen) {
	markLineAt(dc, percent, length, pen);

	float hpos= percent*(float)ruler_height+PERCENTAGE_H_MARGIN;

	const char* label_c = label.c_str();

    dc.SetTextForeground(wxColor(0,0,13));
	wxSize size = dc.GetTextExtent(label_c);
	dc.DrawText(label_c, 0, hpos-size.y/2);
}
void PercentagePanel::markLineAt(wxDC &dc, float percent, int length, const bool do_label, const wxPen &pen) {
	if(do_label) {
       std::string text = toString(100-(int)(percent*100));
       text.append("%");
	   if(text.length()<4) {
		   text.insert(0, std::max(0, (int)(4-text.length())), ' ');
	   }
	   markLineAt(dc, percent, length, text, pen);
	}
	else {
       markLineAt(dc, percent, length, pen);
	}
}



void PercentagePanel::Align() {
 cur_width = 60;
 cur_height = GetParent()->GetSize().GetHeight()-120-1+2*PERCENTAGE_H_MARGIN;

 ruler_height = cur_height - 2*PERCENTAGE_H_MARGIN-1;


 SetSize(cur_width, cur_height);  //nastav velikost
 SetPosition(wxPoint(79-cur_width-2, 60-1-PERCENTAGE_H_MARGIN));
 //SetPosition(wxPoint(0,0));
 paintNow();
}

 /**Vykresli objekt kdyz je to treba (treba pri obnoveni z minimalizace)**/
void PercentagePanel::paintEvent(wxPaintEvent& WXUNUSED(evt))
{
 if (!painting)
 {
  wxPaintDC dc(this);
  render(dc);
 }
}
 /*Vykresli objekt na vyzadani programu (treba pri zmene stavu)**/
void PercentagePanel::paintNow()
{
 if (!painting)
 {
  wxClientDC dc(this);
  render(dc);
 }
}
