#include "include/GraphPanel.hpp"

GraphPanel::GraphPanel(wxFrame* parent, SettingsManager *n_SetMan) :
wxPanel(parent)
{
 painting = false;
 SetBackgroundColour(wxColor(80,100,255));
 SetDoubleBuffered(true);
 SetBackgroundStyle(wxBG_STYLE_PAINT);
 SetSize(640, 480);
 Centre();
 kamera = new Kamera(n_SetMan);
 kamObr = new wxImage();
 
}
 
 
void GraphPanel::paintEvent(wxPaintEvent& WXUNUSED(evt))
{
 //if (!painting)
 //{
  wxPaintDC dc(this);
  render(dc);
 //}
}
 
void GraphPanel::paintNow()
{
 //if (!painting)
 //{
  wxClientDC dc(this);
  render(dc);
 //}
}

void GraphPanel::render(wxDC& dc)
{
 bool painted = false; 
 //image->Mirror(true);
 //(image->Rotate180())
  
  
 if (kamera->Obrazek(kamObr) && kamObr->IsOk())
 {
  wxSize imageSize = kamObr->GetSize();
  bitmap = wxBitmap(*kamObr);
  if (bitmap.IsOk())
  {
     



     painted = true;
  }
 }
 if (!painted)
 {
  renderError(dc);
 }
}

void GraphPanel::DrawGraph(wxDC& dc, wxImage &img) {
 dc.SetBackgroundMode(wxBG_STYLE_PAINT);
 dc.SetBackground(*wxBLACK_BRUSH);


 wxSize sz = GetSize();
 wxCoord x,y;  //Budou se pouzivat opakovane
 /**Ramecek**/
 dc.SetBrush(wxColor(0,0,0));
 dc.SetPen(wxColor(255,255,255));
 dc.DrawRectangle(0,0,sz.GetWidth(), sz.GetHeight());

 //dc.SetPen(wxPen(wxColor(255,255,255), 0, wxDOT_DASH));

 /**Zahlavi**/
 wxString text = wxT("Vlnová délka:");
 dc.GetMultiLineTextExtent (text, &x, &y);
 dc.DrawText(text, 2, 2);

 /**Oddeleni**/
 dc.SetPen(wxPen(wxColor(255,255,255), 0, wxDOT_DASH));
 dc.DrawLine(0, x+4, sz.GetWidth(), x+4);
}
void GraphPanel::renderError(wxDC& dc)
{
	
 dc.SetBackgroundMode(wxBG_STYLE_PAINT);
 dc.SetBackground(*wxBLACK_BRUSH);
 dc.SetTextBackground(*wxBLACK);
 dc.SetTextForeground(*wxWHITE);
 dc.Clear();
 wxString text = wxT("Nastal problém s kamerou.\nZkontrolujte, jestli není vypojená.");
 wxCoord x,y;
 dc.GetMultiLineTextExtent (text, &x, &y);//, (wxCoord *)NULL, (wxFont*)NULL
 wxSize size = dc.GetSize();
 dc.DrawText(text, (size.GetX()-x)/2, (size.GetY()-y)/2);

 wxBitmap usbdis = wxBitmap(wxT("RC_USBdiscon"), wxBITMAP_TYPE_ICO_RESOURCE);

 dc.DrawBitmap(usbdis,(size.GetX()-x)/2-usbdis.GetSize().GetX(),(size.GetY()-usbdis.GetSize().GetY())/2);
	/*
 dc.SetBackground(*wxWHITE_BRUSH);
 dc.Clear();
 
 wxBitmap bmp(wxT("RC_closeicon"), wxBITMAP_TYPE_ICO_RESOURCE);
 wxBitmap bmp2(wxT("RC_demaximizeicon"), wxBITMAP_TYPE_ICO_RESOURCE);
 wxBitmap bmp3(wxT("RC_maximizeicon"), wxBITMAP_TYPE_ICO_RESOURCE);
 wxBitmap bmp4(wxT("RC_USBdiscon"), wxBITMAP_TYPE_ICO_RESOURCE);
 
  dc.DrawText("BMP from resources", 30, 128);
    if ( bmp.IsOk() )
        dc.DrawBitmap(bmp, 30, 160, true);
    if ( bmp2.IsOk() )
        dc.DrawBitmap(bmp2, 30, 256, true);
    if ( bmp3.IsOk() )
        dc.DrawBitmap(bmp3, 30, 384, true);
    if ( bmp4.IsOk() )
        dc.DrawBitmap(bmp4, 30, 412, true);
		*/
}