#include "UVStatusPanel.h"

UVStatusPanel::UVStatusPanel(wxFrame* parent) :
wxPanel(parent)
{
 painting = false;
 /*SetBackgroundColour(wxColor(80,100,255));
 SetDoubleBuffered(true);
 SetBackgroundStyle(wxBG_STYLE_PAINT);
 SetSize(640, 480);
 Centre();
 kamera = new Kamera(n_SetMan);
 kamObr = new wxImage();*/
 
}
 
 
void UVStatusPanel::paintEvent(wxPaintEvent& WXUNUSED(evt))
{
 if (!painting)
 {
  wxPaintDC dc(this);
  //reRender(dc);
 }
}
 
void UVStatusPanel::paintNow()
{
 if (!painting)
 {
  wxClientDC dc(this);
  //render(dc);
 }
}
