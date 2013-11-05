#include "include/GraphPanel.hpp"

GraphPanel::GraphPanel(wxFrame* parent, SettingsManager *n_SetMan) :
wxPanel(parent)
{
 painting = false;
 SetBackgroundColour(wxColor(80,100,255));
 SetDoubleBuffered(true);
 SetBackgroundStyle(wxBG_STYLE_PAINT);
 Align();
 kamera = new Kamera(n_SetMan);
 kamObr = new wxImage();
 selectedLine = 0;
}

void GraphPanel::Align() {
 wxSize size = GetParent()->GetSize();
 SetSize(size.GetWidth()-160, size.GetHeight()-120);
 Centre();
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
  
  
 

 unsigned char* data = NULL;
 const int width = kamera->Radek(data);
 if(width!=0) 
 {
     DrawGraph(dc,data,width);
     painted=true;
 }
 
 /*if (kamera->Obrazek(kamObr) && kamObr->IsOk())
 {
  wxSize imageSize = kamObr->GetSize();
  bitmap = wxBitmap(*kamObr);
  if (bitmap.IsOk())
  {
     DrawGraph(dc, *kamObr);
     painted = true;
  }
 }*/
 if (!painted)
 {
  renderError(dc);
 }
}
void GraphPanel::DrawGraphUI(wxDC &dc) {
 dc.SetBackgroundMode(wxBG_STYLE_PAINT);
 dc.SetBackground(*wxBLACK_BRUSH);


 wxSize sz = GetSize();
 wxCoord x,y;  //Budou se pouzivat opakovane
 /**Ramecek**/
 dc.SetBrush(wxColor(0,0,0));
 dc.SetPen(wxPen(wxColor(255,255,255),0,wxPENSTYLE_TRANSPARENT));
 dc.DrawRectangle(0,0,sz.GetWidth(), sz.GetHeight());

 //dc.SetPen(wxPen(wxColor(255,255,255), 0, wxDOT_DASH));

 /**Zahlavi**/
 dc.SetFont(wxFont(15, wxDEFAULT, wxNORMAL, wxBOLD));
 dc.SetTextBackground(*wxBLACK);
 dc.SetTextForeground(*wxWHITE);
 wxString text = wxT("Vlnová délka:");
 dc.GetTextExtent (text, &x, &y);
 dc.DrawText(text, 2, 2);

 /**Oddeleni**/
 dc.SetPen(wxPen(wxColor(255,255,255), 0, wxDOT));
 dc.DrawLine(0, y+4, sz.GetWidth(), y+4);
 /**Spodni radek**/
 dc.SetPen(wxPen(wxColor(255,255,255), 2, wxSOLID));
 dc.DrawLine(0, sz.GetHeight()-20, sz.GetWidth(), sz.GetHeight()-20);
}


void GraphPanel::DrawGraph(wxDC& dc, wxImage &img) {

 DrawGraphUI(dc);
 /**Graf**/
 
 const int width = img.GetWidth();
 const wxSize sz = GetSize();


 int lastyb = 0;
 int lastyg = 0;
 int lastyr = 0;
 int lastyall = 0;
 unsigned char lastblue = 0;
 unsigned char lastgreen = 0;
 unsigned char lastred = 0;
 unsigned char lastwhite = 0;
 unsigned int lastx = 0;
 for(unsigned int i=0; i<width; i++) {
   int colorsum = img.GetRed(i, selectedLine)+img.GetGreen(i, selectedLine)+img.GetBlue(i, selectedLine);
   int x = sz.GetWidth()*((float)i/((float)img.GetWidth()));

   //int yb = (sz.GetHeight())-(23+(sz.GetHeight()-52)*((float)img.GetBlue(i, selectedLine)/255.0));
   //int yr = (sz.GetHeight())-(23+(sz.GetHeight()-52)*((float)img.GetRed(i, selectedLine)/255.0));
   //int yg = (sz.GetHeight())-(23+(sz.GetHeight()-52)*((float)img.GetGreen(i, selectedLine)/255.0));
   int yall = (sz.GetHeight())-(23+(sz.GetHeight()-52)*((float)(colorsum)/(765.0)));

   //DrawGradientLine(dc, wxPoint(lastx, lastyb), wxPoint(x, yb), wxColour(0,0, 64+(((float)lastblue)/4.0)*3.0) , wxColour(0,0,64+(((float)img.GetBlue(i, selectedLine))/4.0)*3.0));
   //DrawGradientLine(dc, wxPoint(lastx, lastyr), wxPoint(x, yr), wxColour(64+(((float)lastred)/4.0)*3.0,0,0)  , wxColour(64+(((float)img.GetRed(i, selectedLine))/4.0)*3.0,0,0));
   //DrawGradientLine(dc, wxPoint(lastx, lastyg), wxPoint(x, yg), wxColour(0, 64+(((float)lastgreen)/4.0)*3.0,0), wxColour(0,64+(((float)img.GetGreen(i, selectedLine))/4.0)*3.0,0));
   

   unsigned char white_aspect = 64+(((float)colorsum)/12.0)*3.0;
   //DrawGradientLine(dc, wxPoint(lastx, lastyall), wxPoint(x, yall), wxColour(lastwhite, lastwhite, lastwhite), wxColour(white_aspect, white_aspect, white_aspect));
   
   DrawGradientLine(dc, wxPoint(lastx, lastyall), wxPoint(x, yall), wxColour(lastred, lastgreen, lastblue), wxColour(img.GetRed(i, selectedLine), img.GetGreen(i, selectedLine), img.GetBlue(i, selectedLine)));
   //dc.SetPen(wxPen(*wxWHITE));
   //dc.DrawLine(lastx, lastyb, x, yb);

   if(lastblue==0) {
	   //wxMessageBox("TMA!");

   }
   /**SPODNI RADEK**/
   dc.SetBrush(wxBrush(wxColor(img.GetRed(i, selectedLine), img.GetGreen(i, selectedLine), img.GetBlue(i, selectedLine))));
   dc.SetPen(wxPen(*wxRED, 0, wxPENSTYLE_TRANSPARENT));
   dc.DrawRectangle(lastx, sz.GetHeight()-18, x-lastx, 18);
   /**PAMATOVAT SI POSLEDNI HODNOTY**/
   lastx=x;
   lastblue = img.GetBlue(i, selectedLine);
   lastred = img.GetRed(i, selectedLine);
   lastgreen = img.GetGreen(i, selectedLine);
   //lastcolorsum = colorsum;
   lastwhite=white_aspect;
   //lastyb = yb;
   //lastyr = yr;
   //lastyg = yg;
   lastyall = yall;

 }
}
void GraphPanel::DrawGraph(wxDC& dc, const unsigned char* data, const int &length) {


 /**Graf**/
 const wxSize sz = GetSize();

 int lastyb = 0;
 int lastyg = 0;
 int lastyr = 0;
 int lastyall = 0;
 unsigned char lastblue = 0;
 unsigned char lastgreen = 0;
 unsigned char lastred = 0;
 unsigned char lastwhite = 0;
 unsigned int lastx = 0;
 for(unsigned int i=0; i<length; i+=3) {
   int colorsum = data[i]+data[i+1]+data[i+2];
   int x = sz.GetWidth()*((float)i/((float)length));

   

   int yall = (sz.GetHeight())-(23+(sz.GetHeight()-52)*((float)(colorsum)/(765.0)));

   unsigned char white_aspect = 64+(((float)colorsum)/12.0)*3.0;
   DrawGradientLine(dc, wxPoint(lastx, lastyall), wxPoint(x, yall), wxColour(lastred, lastgreen, lastblue), wxColour(data[i], data[i+1], data[i+2]));

   /**SPODNI RADEK**/
   dc.SetBrush(wxBrush(wxColor(data[i], data[i+1], data[i+2])));
   dc.SetPen(wxPen(*wxRED, 0, wxPENSTYLE_TRANSPARENT));
   dc.DrawRectangle(lastx, sz.GetHeight()-18, x-lastx, 18);
   /**PAMATOVAT SI POSLEDNI HODNOTY**/
   lastx=x;
   lastblue = data[i+2];
   lastred = data[i];
   lastgreen = data[i+1];
   //lastcolorsum = colorsum;
   lastwhite=white_aspect;
   //lastyb = yb;
   //lastyr = yr;
   //lastyg = yg;
   lastyall = yall;

 }
}
void swap(int &a, int &b) {
	int c = a;
	a=b;
	b=c;
}

void GraphPanel::DrawGradientLine(wxDC& dc,wxPoint a, wxPoint b, const wxColour &end, const wxColour &start) {
  bool steep= abs(b.y - a.y) > abs(b.x - a.x);
  if(steep) {
      swap(a.x, a.y);
      swap(b.x, b.y);
	  /*int c = a.x;
	  a.x=b.y;
	  a.y=c;

	  c=b.x;
	  b.x=b.y;
	  b.y=c;*/
  }
  /*if(a.x>b.x) {
      swap(a.x, b.x);
      swap(a.y, b.y);
  }*/

  int deltax = b.x-a.x;
  int deltay = abs(b.y-a.y);
  int error = deltax / 2;

  /*char message[20] = {0};
  itoa(deltay,message,10);
  strcat(message, ", ");
  itoa(error,message,10);

  wxMessageBox (wxString(std::String()));*/
  

  int ystep = a.y<b.y?1:-1;
  int increment = a.x<b.x?1:-1;

  int y = a.y;

  for(int x=a.x; (a.x<b.x&&x<=b.x)||(a.x>b.x&&x>=b.x); x+=increment) {
	  float koef = a.x>b.x?1.0-x/(float)a.x:x/(float)b.x;

  /*char message[20] = {0};
  itoa((int)(koef*1000),message,10);
  wxMessageBox (wxString(message));*/

	  dc.SetPen(wxColour(
		   end.Red()+((float)(start.Red()-end.Red()))*koef,
		   end.Green()+((float)(start.Green()-end.Green()))*koef,
	       end.Blue()+((float)(start.Blue()-end.Blue()))*koef
	  ));
	  //dc.SetPen(*wxRED);
      if(steep) {
		  dc.DrawPoint(y,x);
	  }
	  else {
		  dc.DrawPoint(x,y);
	  }
      error -= increment*deltay;
      if((a.x<=b.x&&error<0)||(a.x>=b.x&&error>0)) 
	  {
          y += ystep;
          error += deltax;
	  }
  }
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