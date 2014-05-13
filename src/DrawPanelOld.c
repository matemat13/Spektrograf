 
class BasicDrawPane : public wxPanel
{
 
public:
    BasicDrawPane(wxFrame* parent, SettingsManager *n_SetMan);
 
    void paintEvent(wxPaintEvent& evt);
	  void paintNow();
    void paintNow(unsigned char *data, int data_length);
 
    DECLARE_EVENT_TABLE()
private:
	bool painting;
  void render(wxDC& dc);
	void reRender(wxDC& dc);
	void renderError(wxDC& dc);
	void renderData(wxDC& dc, unsigned char* data, int data_length);

  unsigned char *buffer;
	Kamera *kamera;
	wxImage *kamObr;
	wxBitmap bitmap;
};
BasicDrawPane::BasicDrawPane(wxFrame* parent, SettingsManager *n_SetMan) :
wxPanel(parent)
{
 painting = false;
 SetBackgroundColour(wxColor(80,100,255));
 SetDoubleBuffered(true);
 SetBackgroundStyle(wxBG_STYLE_PAINT);
 SetSize(WIDTH, HEIGHT);
 Centre();
 kamera = new Kamera(n_SetMan);
 kamObr = new wxImage();
 buffer = new unsigned char[WIDTH*HEIGHT*3];
}
void BasicDrawPane::paintEvent(wxPaintEvent& WXUNUSED(evt))
{
 if (!painting)
 {
  wxPaintDC dc(this);
  reRender(dc);
 }
}
void BasicDrawPane::paintNow()
{
 if (!painting)
 {
  wxClientDC dc(this);
  render(dc);
 }
}
void BasicDrawPane::paintNow(unsigned char *data, int data_length)
{
 if (!painting)
 {
  wxClientDC dc(this);
  renderData(dc, data, data_length);
 }
}
void BasicDrawPane::renderData(wxDC& dc, unsigned char* data, int data_length)
{
 painting = true;
 bool painted = false; 
 //image->Mirror(true);
 //(image->Rotate180())
 int prumer;

 for (int i = 0; i < WIDTH*HEIGHT*3; i++)
   buffer[i] = 0;

 int pomerX = data_length/WIDTH;
 double pomerY = HEIGHT/255.0;
 if (pomerX == 0)
   pomerX = 1;
 if (pomerY == 0)
   pomerY = 1;

 for (int x = 0; x < WIDTH; x++)
 {
  prumer = 0;
  
  for (int i = 0; i < pomerX; i++)
  {
   prumer += data[x*pomerX + i];
  }
  prumer /= pomerX;
  prumer *= pomerY;
  if (prumer < 0)
    prumer = 0;
  else if (prumer >= HEIGHT)
    prumer = HEIGHT-1;
  //prumer = data[x];
  buffer[(HEIGHT - prumer)*WIDTH + x] = 255;
  buffer[(HEIGHT - prumer)*WIDTH + x+1] = 255;
  buffer[(HEIGHT - prumer)*WIDTH + x+2] = 255;
 }

 //bitmap = wxBitmap((char*)buffer, WIDTH, HEIGHT);
 //kamObr->Create(WIDTH, HEIGHT, buffer, true);
 //if (kamObr->IsOk())
 {
  //wxSize imageSize = kamObr->GetSize();
  //bitmap = wxBitmap(*kamObr);
  //if (bitmap.IsOk())
  {
   dc.DrawBitmap(bitmap = wxBitmap((char*)buffer, WIDTH, HEIGHT),0,0, false);
   painted = true;
  }
 }
 if (!painted)
 {
  renderError(dc);
 }

 painting = false;
}
void BasicDrawPane::reRender(wxDC& dc)
{
 painting = true;
 bool painted = false; 

 if (kamObr->IsOk())
 {
  wxSize imageSize = kamObr->GetSize();
  bitmap = wxBitmap(*kamObr);
  if (bitmap.IsOk())
  {
   dc.DrawBitmap(bitmap,0,0, false);
   painted = true;
  }
 }
 if (!painted)
 {
  renderError(dc);
 }

 painting = false;
}
void BasicDrawPane::render(wxDC& dc)
{
 return;
 painting = true;
 bool painted = false; 
 //image->Mirror(true);
 //(image->Rotate180())
  
  
 if (kamera->Obrazek(kamObr) && kamObr->IsOk())
 {
  wxSize imageSize = kamObr->GetSize();
  bitmap = wxBitmap(*kamObr);
  if (bitmap.IsOk())
  {
   dc.DrawBitmap(bitmap,0,0, false);
   painted = true;
  }
 }
 if (!painted)
 {
  renderError(dc);
 }
 
  

  //delete image;
 //dc.SetBackground( *wxWHITE_BRUSH );
// dc.Clear();
  //dc.DrawBitmap(wxBitmap("./oko.gif", wxBITMAP_TYPE_GIF),0,0, false);
 painting = false;

}
void BasicDrawPane::renderError(wxDC& dc)
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
 dc.DrawText(wxT("Nastal problém s kamerou.\nZkontrolujte, jestli není vypojená."), (size.GetX()-x)/2, (size.GetY()-y)/2);

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