#include "../include/BasicDrawPane.hpp"

BasicDrawPane::BasicDrawPane(wxFrame* parent) :
wxPanel(parent)
{
  SetBackgroundColour(wxColor(80,100,255));
  SetBackgroundStyle(wxBG_STYLE_PAINT);
  SetSize(640, 480);
  wxClientDC dc(this);
  renderWaiting(dc);
  Centre();
  kamera = new Kamera();
  kamObr = new wxImage();
}
 
 
void BasicDrawPane::paintEvent(wxPaintEvent& WXUNUSED(evt))
{
    wxPaintDC dc(this);
    render(dc);
}
 
void BasicDrawPane::paintNow()
{
    wxClientDC dc(this);
    render(dc);
}
 
void BasicDrawPane::render( wxDC& dc )
{
  kamera->Obrazek(kamObr);
  
  //image->Mirror(true);
  //(image->Rotate180())
  
  
  wxSize imageSize = kamObr->GetSize();
  bitmap = wxBitmap(*kamObr);
  //delete image;
  //dc.SetBackground( *wxWHITE_BRUSH );
  // dc.Clear();
  //dc.DrawBitmap(bitmap,0,0, false);
  //dc.DrawBitmap(wxBitmap("./oko.gif", wxBITMAP_TYPE_GIF),0,0, false);
}

void BasicDrawPane::renderWaiting( wxDC& dc )
{
 int x = GetPosition().x;
 int y = GetPosition().y;
 
 wxStaticText t(this, -1, wxT("Inicializuji kameru, prosím èekejte."), wxPoint(x,y));
 t.Centre();
 dc.SetBackground(*wxWHITE_BRUSH);
 dc.Clear();
 t.Show();

}