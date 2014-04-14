#include "../include/BasicDrawPane.hpp"

bool detect_UV(short *data, int IR_edge, int UV_edge)
{
 #define THRESHOLD 64
 if (data[UV_edge] > THRESHOLD)
  return true;
 else
  return false;
}


//Konstruktor (v cestine to zni tvvrde)
wxGLCanvasSubClass::wxGLCanvasSubClass(wxFrame *parent, Kamera *n_kamera, SettingsManager *n_SetMan)
:wxGLCanvas(parent, (wxGLCanvas*)(NULL), wxID_ANY, wxDefaultPosition, wxSize(WIDTH + 4, HEIGHT + 4), wxSUNKEN_BORDER)
{
  data = NULL;
  data_prumer = NULL;

  uchar_data = NULL;
  obr_data = NULL;
  data_length = 0;
  img_width = img_height = 0;
  data_to_screen_ratio = 0;
  stav = stav_pred_chybou = Z_GRAF;
  //selected_line = 0;
  //dragged = false;
  drag_button = 0;

  cur_width = GetParent()->GetSize().GetWidth() - 160;
  cur_height = GetParent()->GetSize().GetHeight() - 120;

  kamera = n_kamera;
  m_glRC = new wxGLContext(this);
  SetMan = n_SetMan;
  pamet = NULL;

  //Eventy pro posouvani zdrojove cary
  Connect(wxEVT_LEFT_DOWN, wxMouseEventHandler(wxGLCanvasSubClass::OnMousedown), NULL, this);
  Connect(wxEVT_LEFT_UP, wxMouseEventHandler(wxGLCanvasSubClass::OnMouseup), NULL, this);
  Connect(wxEVT_RIGHT_DOWN, wxMouseEventHandler(wxGLCanvasSubClass::OnMousedown), NULL, this);
  Connect(wxEVT_RIGHT_UP, wxMouseEventHandler(wxGLCanvasSubClass::OnMouseup), NULL, this);
  Connect(wxEVT_MOTION, wxMouseEventHandler(wxGLCanvasSubClass::OnMousemove), NULL, this);
  Connect(wxEVT_LEAVE_WINDOW, wxMouseEventHandler(wxGLCanvasSubClass::OnMouseout), NULL, this);

  Connect(wxEVT_MOUSEWHEEL, wxMouseEventHandler(wxGLCanvasSubClass::OnScroll), NULL, this);
  

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
  glOrtho(0, cur_width, cur_height, 0, 0, 1);
  glDisable(GL_DEPTH_TEST);
  glMatrixMode(GL_MODELVIEW);
  
 /* glShadeModel(GL_FLAT);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glViewport(0, 0, 640, 480);*/
  Align();
}
 
wxGLCanvasSubClass::~wxGLCanvasSubClass()
{
 delete m_glRC;
}

void wxGLCanvasSubClass::setMemory(GraphMemoryMan*nmem) {
	pamet = nmem;
}

void wxGLCanvasSubClass::SetZoom()
{
 switch (stav)
 {
  case Z_CHYBA: glPixelZoom(cur_width / (double) 640, cur_height / (double) 480); glViewport(0, 0, cur_width, cur_height); break;
  case Z_OBRAZ: glPixelZoom(cur_width / (double) img_width, cur_height / (double) img_height); glViewport(0, 0, cur_width, cur_height); break;
  case Z_GRAF:
  case Z_GRAF_BAR: glPixelZoom(1.0, 1.0); glViewport(0, 0, cur_width, cur_height); break;
 }
}

void wxGLCanvasSubClass::Align()
{
 cur_width = GetParent()->GetSize().GetWidth() - 160;
 cur_height = GetParent()->GetSize().GetHeight() - 120;
 SetZoom();
 SetSize(cur_width +4, cur_height +4);  //Nastaveni nejakejch zobrazovacich sracek
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
  SetZoom();
  stav = type;
 }
}

void wxGLCanvasSubClass::Graf(short *n_data, short*data_pr, int n_data_length)
{
 if (data != NULL) {
  delete [] data; //Uvolnim starou pamet
 }
 if(data_prumer != NULL) {
  delete [] data_prumer;
  data_prumer = NULL;
 }


 //Delka dat je dynamicka, muze se zmenit za behu programu
 data_length = n_data_length;  //Aktualizuji delku dat

 //Prekopiruji nova data do interniho bufferu
 data = n_data;

 //Prekopiruju odkaz na prumer 
 data_prumer = data_pr;
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
			   short *data_old;
			   int data_length = kamera->Sample(data_old);
			   kamera->Sample_Kalman(data);
			   if (data_length == 0)
			   {
			    SetDisplay(Z_CHYBA);
			   } else
			   {
			    Graf(data_old, data, data_length);
			   }
			   break;
			  }
 case Z_GRAF_BAR: {
			       unsigned char *data;
			       int data_length = kamera->Radek(data);
			       if (data_length == 0)
			       {
			        SetDisplay(Z_CHYBA);
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
				 SetDisplay(Z_CHYBA);
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
 if (drag_button!=0) 
 {
  int x, y;
  x = event.GetX()*img_width/cur_width;
  y = img_height - event.GetY()*img_height/cur_height;
  kamera->SetSourceLine(x, y);


  SetMan->SetSetting(wxMOUSE_BTN_LEFT!=drag_button ?SETT_LINE_RED:SETT_LINE_UV, y);
  ((FrameMain*)GetParent())->SpectrumBoundsChanged();
  //DODELAT: posouvani horizontalnich car (IR a UV)
  
 }
}
void wxGLCanvasSubClass::OnMousedown(wxMouseEvent& event)
{
 if(stav == Z_OBRAZ)
 {
   drag_button = event.GetButton();
 }
}
void wxGLCanvasSubClass::OnMouseup(wxMouseEvent& event)
{
  drag_button = 0;
}
void wxGLCanvasSubClass::OnMouseout(wxMouseEvent &event)
{
 //dragged = false;
  drag_button = 0;
}
void wxGLCanvasSubClass::OnScroll(wxMouseEvent &event)
{
    /*std::stringstream ss;
    ss << "Delta:" << event.m_wheelDelta;
    wxMessageDialog pokus(GetParent(), (wxString)ss.str().c_str(), "Nasrat");
	pokus.ShowModal();*/
    //selected_line = selected_line==0?1:0;
	
	//Vypis debug

	int max;
	float sum;
	unsigned short max_pos;
    kamera->findUVSpike(max, sum, max_pos);
    std::stringstream ss;
    ss << "Prumer: " << sum<< "\nMax "<<max<<" na pozici " <<(int)max_pos;
    wxMessageDialog pokus(GetParent(), (wxString)ss.str().c_str(), "Nasrat");
	pokus.ShowModal();

	
}

void wxGLCanvasSubClass::Render()
{
  //Sracky, co tu asi musej bejt
 
 wxPaintDC(this);
 SetCurrent(*m_glRC);

 //Stav UV
  float avg;
  int uv_max;
  unsigned short uv_max_pos;
  //unsigned int uv_treshold = SetMan->GetSetting(SETT_UV_TRESHOLD);
  int uv_mid = SetMan->GetSetting(SETT_LINE_UV);

  bool state = kamera->findUVSpike(uv_max, avg, uv_max_pos);
  
  /**Vykopirovat do Kamera()**/
  //bool state = uv_max-avg>uv_treshold;
  static bool last_uv_state = (!state);
  if(last_uv_state != (state)) {
    ((FrameMain*)GetParent())->setUVStatus(!state);
	last_uv_state = state;
  }
  


 
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
	//DODELAT: otaceni obrazu
  glDrawPixels(img_width, img_height, GL_RGB, GL_UNSIGNED_BYTE, obr_data);
  glLineWidth(1.0); 
  
  glColor3f(1.0, 0.0, 0.0);
  //glPixelZoom(cur_width / (double) 640, cur_height / (double) 480);

  glBegin(GL_LINE_STRIP);
  glVertex2d(-1.0, double(2*SetMan->GetSetting(SETT_LINE_RED)/(double)img_height-1.0));//( 1.0/double(SetMan->GetSetting(SETT_LINE_RED))));
  glVertex2d(1.0, double(2*SetMan->GetSetting(SETT_LINE_RED)/(double)img_height-1.0));//( 1.0/double(SetMan->GetSetting(SETT_LINE_RED))));
  glEnd();
  glBegin(GL_LINE_STRIP);
  glColor3f(0.0, 0.1, 0.9);
  glVertex2d(-1.0, double(2*SetMan->GetSetting(SETT_LINE_UV)/(double)img_height-1.0));//( 1.0/double(SetMan->GetSetting(SETT_LINE_RED))));
  glVertex2d(1.0, double(2*SetMan->GetSetting(SETT_LINE_UV)/(double)img_height-1.0));//( 1.0/double(SetMan->GetSetting(SETT_LINE_RED))));
  glEnd();
  
/*
  glBegin(GL_LINE_STRIP);
  glColor3f(0.0, 0.5, 0.0);
  glVertex2d(0,0
  glVertex2d(0,1.0);
  glColor3f(0.0, 0.9, 0.0);
  glVertex2d(1.0,1.0);
  glVertex2d(-1.0,-1.0);
  glEnd();
  */
 } else if (stav == Z_GRAF)	//Vykreslit cernobilej graf
 {

  GLdouble x;
  GLdouble y;

  //Barvy dle vlnove delky
  /*double bx, by, bz, r, g, b;
  GLdouble x1, y1, x2, y2;
  x1 = (uv_mid - 10 - data_length/2)/double(data_length)*2;
  y1 = -1;
  x2 = (uv_mid + 10 - data_length/2)/double(data_length)*2;
  y2 = 1;
  //Co je tohle?
  glBegin(GL_POLYGON);
  glColor3f(0.0125, 0.025, 0.1125);
  glVertex2d(x1, y1);
  glVertex2d(x2, y1);
  glVertex2d(x2, y2);
  glVertex2d(x1, y2);
  glEnd();*/


  //Vykreslit data A

  /*
  glBegin(GL_LINE_STRIP);
  glColor3f(0.1, .1, .1);
  for (int i = 0; i < data_length; i++)
  {

   //Vypocet barvy
   //spectrum_to_xyz(kamera->WavelengthAt(i), &bx, &by, &bz);
   //xyz_to_rgb(&HDTVsystem, bx, by, bz, &r, &g, &b);

   //Vypocet pozice
   x = 2.0*double(i - data_length/2)/double(data_length);
   y = 2.0*double(data[i] - SAMPLE_MAX_VALUE/2.0)/SAMPLE_MAX_VALUE;

   glVertex2d(x, y);
  }
  glEnd();*/

   //Vykresleni UV hranice

       glBegin(GL_LINE_STRIP);

	   glColor3f(0.0, 0.2, 0.9);
	   glVertex2d(uv_max_pos, 1.0);
       glVertex2d(uv_max_pos, -1.0);

	   glEnd();

  //DrawGraph(data, data_length, wxColor(26,26,26)); 
  
  

  if(pamet!=NULL) 
  {
    GraphMemory *tmp;
    short* tmp_data;
    int tmp_len;
    for(int i=0,l=pamet->count(); i<l; i++) {
	    tmp = pamet->getMemory(i);
	    tmp_len = tmp->getGraphData(tmp_data);
	    DrawGraph(tmp_data, tmp_len, (wxColour)tmp->getColor(), tmp->isSelected()?1.5:1);
    }
  }
  DrawGraph(data_prumer, data_length, wxColor(255,255,255), 2);//wxColor(26,52,230)
  //TEST prumeru
  /*glBegin(GL_LINE_STRIP);
  glColor3f(0.1, 0.2, 0.9);
  for (int i = 0; i < data_length; i++)
  {
   x = 2.0*double(i - data_length/2)/double(data_length);
   y = 2.0*double(data_prumer[i] - SAMPLE_MAX_VALUE/2.0)/SAMPLE_MAX_VALUE;
   glVertex2d(x, y);
  }
  glEnd();*/
 }

 //Dalsi sracky, co tu musej bejt
 glFlush();
 SwapBuffers();
 //Konec dalsich sracek
}
void wxGLCanvasSubClass::DrawGraph(short*data, int dataLen, wxColour color, float lineWidth) {
	
	GLdouble x,y;
	glLineWidth(lineWidth);
	glBegin(GL_LINE_STRIP);  //_STRIP
    glColor3f(color.Red()/255.0,color.Green()/255.0,color.Blue()/255.0);
    for (int i = 0; i < data_length; i++)
    {
   
     //Vypocet barvy
     //spectrum_to_xyz(kamera->WavelengthAt(i), &bx, &by, &bz);
     //xyz_to_rgb(&HDTVsystem, bx, by, bz, &r, &g, &b);
   
     //Vypocet pozice
     x = 2.0*double(i - data_length/2)/double(data_length);
     y = 2.0*double(data[i] - SAMPLE_MAX_VALUE/2.0)/(float)SAMPLE_MAX_VALUE;
     glVertex2d(x, y);
    }
	glEnd();
}
int wxGLCanvasSubClass::getGraph(short*&data) {
	data = data_prumer;
	return data_length;
}
void wxGLCanvasSubClass::getPixels(byte*&dst, int &width, int&height) {
	int size = 3 * cur_width * cur_height;
	width = cur_width;
	height = cur_height;

	dst = new byte[size];
	glReadPixels(0, 0, cur_width, cur_height, GL_RGB, GL_UNSIGNED_BYTE, dst);
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

void glCircle(float x, float y, float r, bool filled, int subdivs) 
{ 
    if( filled ) {
        glBegin( GL_TRIANGLE_FAN );
        glVertex2f( x, y );
    } else {
        glBegin( GL_LINE_STRIP );
    }

    for( unsigned int i = 0; i <= subdivs; ++i ) {
        float angle = i * ((2.0f * 3.14159f) / subdivs);
        glVertex2f( x + r * cos(angle), y + r * sin(angle) );
    }

    glEnd();
}
