#include "../include/BasicDrawPane.hpp"

//Konstruktor (v cestine to zni tvvrde)
wxGLCanvasSubClass::wxGLCanvasSubClass(wxFrame *parent, Kamera *n_kamera, SettingsManager *n_SetMan)
:wxGLCanvas(parent, (wxGLCanvas*)(NULL), wxID_ANY, wxDefaultPosition, wxSize(WIDTH + 4, HEIGHT + 4), wxSUNKEN_BORDER)
{
  data = NULL;
  uchar_data = NULL;
  obr_data = NULL;
  data_length = 0;
  img_width = img_height = 0;
  data_to_screen_ratio = 0;
  stav = stav_pred_chybou = Z_GRAF;
  dragged = false;

  kamera = n_kamera;
  m_glRC = new wxGLContext(this);
  SetMan = n_SetMan;

  //Eventy pro posouvani zdrojove cary
  Connect(wxEVT_LEFT_DOWN, wxMouseEventHandler(wxGLCanvasSubClass::OnMousedown), NULL, this);
  Connect(wxEVT_LEFT_UP, wxMouseEventHandler(wxGLCanvasSubClass::OnMouseup), NULL, this);
  Connect(wxEVT_MOTION, wxMouseEventHandler(wxGLCanvasSubClass::OnMousemove), NULL, this);
  Connect(wxEVT_LEAVE_WINDOW, wxMouseEventHandler(wxGLCanvasSubClass::OnMouseout), NULL, this);
  
  
  wxBitmap img(640, 480, 24);
  wxMemoryDC temp_dc;
  temp_dc.SelectObject(img);
  
  temp_dc.SetBackground(*wxBLACK_BRUSH);
  temp_dc.SetTextBackground(*wxBLACK);
  temp_dc.SetTextForeground(*wxWHITE);
  temp_dc.Clear();


  wxString text = wxT("Nastal problém s kamerou.\nZkontrolujte, jestli není vypojená.");
  wxCoord x,y;
  temp_dc.GetMultiLineTextExtent (text, &x, &y);//, (wxCoord *)NULL, (wxFont*)NULL
  wxSize size = temp_dc.GetSize();
  temp_dc.DrawText(wxT("Nastal problém s kamerou.\nZkontrolujte, jestli není vypojená."), (size.GetX()-x)/2, (size.GetY()-y)/2);
  wxBitmap usbdis = wxBitmap(wxT("RC_USBdiscon"), wxBITMAP_TYPE_ICO_RESOURCE);
  temp_dc.DrawBitmap(usbdis,(size.GetX()-x)/2-usbdis.GetSize().GetX(),(size.GetY()-usbdis.GetSize().GetY())/2);
  temp_dc.SelectObject(wxNullBitmap);

  img.SaveFile("test.png", wxBITMAP_TYPE_PNG);

  chyba_obr = new unsigned char[(640*480*3)];
  wxNativePixelData data(img);
  
  wxNativePixelData::Iterator p(data);
  for (int y = 479; y >= 0; --y)
  {
   wxNativePixelData::Iterator rowStart = p;
   for (int x = 0; x < 640; ++x, ++p)
   {
    chyba_obr[(x + y*640)*3] = p.Red();
    chyba_obr[(x + y*640)*3 +1] = p.Green();
    chyba_obr[(x + y*640)*3 +2] = p.Blue();
   }
   p = rowStart;
   p.OffsetY(data, 1);
  }
  

  //Nastaveni nejakejch zobrazovacich sracek
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, WIDTH, HEIGHT, 0, 0, 1);
  glDisable(GL_DEPTH_TEST);
  glMatrixMode(GL_MODELVIEW);
  
 /* glShadeModel(GL_FLAT);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glViewport(0, 0, 640, 480);*/
}
 
wxGLCanvasSubClass::~wxGLCanvasSubClass()
{
 delete m_glRC;
}

void wxGLCanvasSubClass::Align()
{
 Centre();
}

void wxGLCanvasSubClass::ToggleDisplay()
{
 if (stav == Z_CHYBA)
 {
  if (stav_pred_chybou == Z_GRAF)
  {
   stav_pred_chybou = Z_OBRAZ;
  } else
  {
   stav_pred_chybou = Z_GRAF;
  }
 } else
 {
  if (stav == Z_GRAF)
  {
   stav = Z_OBRAZ;
  } else
  {
   stav = Z_GRAF;
  }
 }
}

void wxGLCanvasSubClass::SetDisplay(int type)
{
 if (stav == Z_CHYBA)
 {
  stav_pred_chybou = type;
 } else
 {
  stav = type;
 }
}

void wxGLCanvasSubClass::Graf(short *n_data, int n_data_length)
{
 if (data != NULL)
  delete [] data; //Uvolnim starou pamet

 //Delka dat je dynamicka, muze se zmenit za behu programu
 data_length = n_data_length;  //Aktualizuji delku dat

 //Prekopiruji nova data do interniho bufferu
 data = n_data;

 //Vykreslit (pravdepodobne zavola paintEvent)
 Refresh(false);
}

void wxGLCanvasSubClass::GrafBarevny(unsigned char *n_data, int n_data_length)
{
 if (data != NULL)
  delete [] data; //Uvolnim starou pamet

 //Delka dat je dynamicka, muze se zmenit za behu programu
 data_length = n_data_length;  //Aktualizuji delku dat

 //Prekopiruji nova data do interniho bufferu
 uchar_data = n_data;

 //Vykreslit (pravdepodobne zavola paintEvent)
 Refresh(false);
}

void wxGLCanvasSubClass::Obraz(unsigned char *n_data, short width, short height)
{
 //Delka dat je dynamicka, muze se zmenit za behu programu
 if (obr_data != NULL)
  delete [] obr_data; //Uvolnim starou pamet
 img_width = width;  //Aktualizuji sirku obrazku
 img_height = height;  //Aktualizuji delku dat

 //Prekopiruji nova data do interniho bufferu
 obr_data = n_data;

 //Vykreslit (pravdepodobne zavola paintEvent)
 Refresh(false);
}

void wxGLCanvasSubClass::Chyba()
{
 Refresh(false);
}


void wxGLCanvasSubClass::paintEvent(wxPaintEvent& WXUNUSED(event))
{
 Render();
}

void wxGLCanvasSubClass::paintNow()
{
 //Nacteni aktualniho nastaveni zobrazeni
 int set;
 SetMan->GetSetting(SETT_DIS_TYPE, set);
 SetDisplay(set);
 switch (stav)
 {
 case Z_CHYBA: Chyba(); break;
 case Z_GRAF: {
			   short *data;
			   int data_length = kamera->Sample(data);
			   if (data_length == 0)
			   {
			    stav = Z_CHYBA;
			   } else
			   {
			    Graf(data, data_length);
			   }
			   break;
			  }
 case Z_GRAF_BAR: {
			       unsigned char *data;
			       int data_length = kamera->Radek(data);
			       if (data_length == 0)
			       {
			        stav = Z_CHYBA;
			       } else
			       {
			        GrafBarevny(data, data_length);
			       }
			       break;
			      }
 case Z_OBRAZ: {
				unsigned char *data;
				if (!kamera->Obrazek(data))
				{
				 stav = Z_CHYBA;
				} else
				{
				 Obraz(data, kamera->GetWidth(), kamera->GetHeight());
				}
				break;
			   }
 }
}

// event handlers
void wxGLCanvasSubClass::OnMousemove(wxMouseEvent& event)
{
 if(dragged) 
 {
  kamera->SetSourceLine(event.GetX(), event.GetY());
 }
}
void wxGLCanvasSubClass::OnMousedown(wxMouseEvent& event)
{
 if(stav == Z_OBRAZ)
 {
  dragged = true;
 }
}
void wxGLCanvasSubClass::OnMouseup(wxMouseEvent& WXUNUSED(event))
{
 dragged = false;
}

void wxGLCanvasSubClass::OnMouseout(wxMouseEvent& WXUNUSED(event))
{
 dragged = false;
}

void wxGLCanvasSubClass::Render()
{
  //Sracky, co tu asi musej bejt
 
 wxPaintDC(this);
 SetCurrent(*m_glRC);

 
 //if (!initialized)
 //{
 //    InitGL();
 //    ResetProjectionMode();
 //    initialized = true;
 //}

 glClearColor(0.0, 0.0, 0.0, 0.0);
 glClear(GL_COLOR_BUFFER_BIT);
 //glViewport(0, 0, (GLint)GetSize().x, (GLint)GetSize().y);
 
 /*glClearColor(1.0, 0.0, 1.0, 0.5);
 glClear(GL_COLOR_BUFFER_BIT);*/
 //glViewport(0, 0, WIDTH, HEIGHT);
 //Konec sracek
 
 //Jeste jsme nedostali zadna data
 //if (data_to_screen_ratio == 0)
 //  return;
 

 if (stav == Z_CHYBA) //Vykreslit chybovou hlasku
 {
  //Vykresleni obrazku z pameti
  glDrawPixels(640, 480, GL_RGB, GL_UNSIGNED_BYTE, chyba_obr);
 } else if (stav == Z_OBRAZ) //Vykreslit obraz z kamery
 {
  glDrawPixels(img_width, img_height, GL_RGB, GL_UNSIGNED_BYTE, obr_data);
 } else if (stav == Z_GRAF)	//Vykreslit cernobilej graf
 {

  GLdouble x;
  GLdouble y;

  glBegin(GL_LINE_STRIP);
  glColor3f(1.0, 1.0, 1.0);
  
  for (int i = 0; i < data_length; i++)
  {
   x = 2.0*double(i - data_length/2)/double(data_length);
   y = 2.0*double(data[i] - SAMPLE_MAX_VALUE/2.0)/SAMPLE_MAX_VALUE;
   glVertex2d(x, y);
  }
  glEnd();
 }

 //Dalsi sracky, co tu musej bejt
 glFlush();
 SwapBuffers();
 //Konec dalsich sracek
}

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


