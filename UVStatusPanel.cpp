#include "UVStatusPanel.h"

UVStatusPanel::UVStatusPanel(wxFrame* parent, int pos) :
wxPanel(parent)
{
 painting = false;
 const int padding = 8;

 SetBackgroundColour(wxColor(80,100,255));
 SetDoubleBuffered(true);
 SetBackgroundStyle(wxBG_STYLE_PAINT);
 SetSize(200, 48);
 SetPosition(wxPoint(pos, parent->GetSize().GetHeight()-padding-(this->GetSize().GetHeight())));
}
 
 /**Vykresli objekt kdyz je to treba (treba pri obnoveni z minimalizace)**/
void UVStatusPanel::paintEvent(wxPaintEvent& WXUNUSED(evt))
{
 if (!painting)
 {
  wxPaintDC dc(this);
  render(dc);
 }
}
 /*Vykresli objekt na vyzadani programu (treba pri zmene stavu)**/
void UVStatusPanel::paintNow()
{
 if (!painting)
 {
  wxClientDC dc(this);
  render(dc);
 }
}

void UVStatusPanel::render(wxDC &dc) 
{
	dc.SetBrush(wxBrush (wxColor(128,128,128)));
	dc.DrawRectangle(0,0,this->GetSize().GetWidth(), this->GetSize().GetHeight());


}

