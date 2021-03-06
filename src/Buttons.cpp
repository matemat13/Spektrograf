#include "include/Buttons.hpp"
#include "main.hpp"

QuitButton::QuitButton(wxFrame *parent, int id) : wxButton(parent, id, wxString::FromUTF8("Konec"), wxDefaultPosition, wxSize(24,24), wxBORDER_NONE|wxBU_EXACTFIT|wxBU_NOTEXT)
{
 normal = wxBitmap(wxT("RC_closeicon"), wxBITMAP_TYPE_ICO_RESOURCE);//wxBITMAP_TYPE_PNG
 //normal = wxBitmap(wxT("RC_closeicon"), wxBITMAP_TYPE_PNG_RESOURCE);
 focus = wxBitmap(wxT("RC_closeiconF"), wxBITMAP_TYPE_ICO_RESOURCE);
 press = wxBitmap(wxT("RC_closeiconP"), wxBITMAP_TYPE_ICO_RESOURCE);

 SetCursor(wxCursor(wxCURSOR_HAND));
 SetHelpText(wxString::FromUTF8("Ukon�i aplikaci spektrograf."));
 SetToolTip(wxString::FromUTF8("Ukon�it program"));
 SetBitmap(normal);
 SetBitmapCurrent(focus);
 //SetBitmapFocus(focus);
 SetBitmapPressed(press);
 SetBackgroundColour(APP_STYLE_MAINBG/*wxTransparentColour*/);
 Align();
}
void QuitButton::Align()
{
 int x, y;
 GetSize(&x, &y);
 SetPosition(wxPoint(this->GetParent()->GetSize().x - x -BUT_BORDER, BUT_BORDER));
}


MaxDemaxButton::MaxDemaxButton(wxFrame *parent, int id, bool n_state) : wxButton(parent, id, wxString::FromUTF8("Konec"), wxDefaultPosition, wxSize(24,24), wxBORDER_NONE|wxBU_EXACTFIT|wxBU_NOTEXT)
{
 normal1 = wxBitmap(wxT("RC_maximizeicon"), wxBITMAP_TYPE_ICO_RESOURCE);
 focus1 = wxBitmap(wxT("RC_maximizeiconF"), wxBITMAP_TYPE_ICO_RESOURCE);
 press1 = wxBitmap(wxT("RC_maximizeiconP"), wxBITMAP_TYPE_ICO_RESOURCE);

 normal2 = wxBitmap(wxT("RC_demaximizeicon"), wxBITMAP_TYPE_ICO_RESOURCE);
 focus2 = wxBitmap(wxT("RC_demaximizeiconF"), wxBITMAP_TYPE_ICO_RESOURCE);
 press2 = wxBitmap(wxT("RC_demaximizeiconP"), wxBITMAP_TYPE_ICO_RESOURCE);
 state = n_state;

 SetCursor(wxCursor(wxCURSOR_HAND));
 ToggleState(state);
 SetBackgroundColour(APP_STYLE_MAINBG);
 Align();
}
void MaxDemaxButton::Align()
{
 int x, y;
 GetSize(&x, &y);
 SetPosition(wxPoint(this->GetParent()->GetSize().x - 2*x - 2*BUT_BORDER, BUT_BORDER));
}
void MaxDemaxButton::ToggleState(bool st)
{
 state = st;
 if (state == ST_MAXED)
 {
  SetHelpText(wxString::FromUTF8("Obnov� aplikaci z maximalizace do okna."));
  SetToolTip(wxString::FromUTF8("Obnovit z maximalizace."));
  SetBitmap(normal1);
  SetBitmapHover(focus1);
  SetBitmapPressed(press1);
 } else //state == ST_WINDO
 {
  SetHelpText(wxString::FromUTF8("Maximalizuje aplikaci."));
  SetToolTip(wxString::FromUTF8("Maximalizovat aplikaci."));
  SetBitmap(normal2);
  SetBitmapHover(focus2);
  SetBitmapPressed(press2);
 }
}
void MaxDemaxButton::ToggleState()
{
  ToggleState(!state);
}




ScreenshotButton::ScreenshotButton(wxFrame *parent, int id, wxGLCanvasSubClass *grafn) : wxButton(parent, id, wxString::FromUTF8("Ukon�it"), wxDefaultPosition, wxSize(24,24), wxBORDER_NONE|wxBU_EXACTFIT|wxBU_NOTEXT)
{
 normal = wxBitmap(wxT("RC_screenshoticon"), wxBITMAP_TYPE_PNG_RESOURCE);//wxBITMAP_TYPE_PNG
 focus = wxBitmap(wxT("RC_screenshoticonF"), wxBITMAP_TYPE_PNG_RESOURCE);
 press = wxBitmap(wxT("RC_screenshoticonP"), wxBITMAP_TYPE_PNG_RESOURCE);

 graf = grafn;

 SetCursor(wxCursor(wxCURSOR_HAND));
 SetHelpText(wxString::FromUTF8("Ulo�� aktu�ln� stav okna jako obr�zek."));
 SetToolTip(wxString::FromUTF8("Ulo�it screenshot"));
 SetBitmap(normal);
 SetBitmapHover(focus);
 SetBitmapPressed(press);
 SetBackgroundColour(APP_STYLE_MAINBG);
 Align();
 //wxEVT_COMMAND_RIGHT_DCLICK
 Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(ScreenshotButton::onClick), NULL, this);
 //Connect(wxEVT_LEFT_UP, wxMouseEventHandler(ScreenshotButton::onClick));
}
void ScreenshotButton::Align()
{
 SetSize(60,60);
 int x, y;
 GetSize(&x, &y);
 SetPosition(wxPoint(this->GetParent()->GetSize().x - x -BUT_BIG_BORDER, 60));
}
void ScreenshotButton::onClick(wxCommandEvent& WXUNUSED(event)) {
   SetBitmapPressed(normal);  //nechci aby na screenshotu vypadal zmacknuty
   Refresh();
   wxBitmap screenshot;
   GetScreenshot(screenshot);
   //screenshot.ClearAlpha();
   SetBitmapPressed(press);
   /**Ulozeni dp souboru**/
   wxFileDialog fileDialog(this, _("Save a screenshot"), wxT(""), wxT("spektrograf.bmp"), wxT("Rastr (*.bmp) | *.bmp|Obr�zek PNG (nedoporu�uje se) (*.png) | *.png|JPEG form�t (*.jpg) | *.jpeg;*.jpg"), wxFD_SAVE);
   if(fileDialog.ShowModal() == wxID_OK) {
          wxFileName namePath(fileDialog.GetPath());
          int fileType = wxBITMAP_TYPE_BMP;
          if( namePath.GetExt().CmpNoCase(wxT("jpeg")) == 0 ) fileType = wxBITMAP_TYPE_JPEG;
          if( namePath.GetExt().CmpNoCase(wxT("jpg")) == 0 )  fileType = wxBITMAP_TYPE_JPEG;
          if( namePath.GetExt().CmpNoCase(wxT("png")) == 0 )  fileType = wxBITMAP_TYPE_PNG;
		  if( namePath.GetExt().CmpNoCase(wxT("bmp")) == 0 )  fileType = wxBITMAP_TYPE_BMP;
		  wxImage tosave(screenshot.ConvertToImage());
		  if(tosave.HasAlpha())
		    tosave.ClearAlpha();

		  if(wxFileExists(fileDialog.GetPath())) 
		  {
			  wxMessageDialog potvrd(this, _("Soubor existuje! Chcete jej p�epsat?"), _("Soubor existuje"), wxYES_NO|wxNO_DEFAULT|wxICON_WARNING);
			  if(potvrd.ShowModal()==wxID_YES)
				  tosave.SaveFile(fileDialog.GetPath(),(wxBitmapType)fileType);

		  }
		  else 
		    tosave.SaveFile(fileDialog.GetPath(),(wxBitmapType)fileType);
   }
   return;
}
void ScreenshotButton::GetScreenshot(wxBitmap &screenshot) {

   //Create a DC for the main window
   wxClientDC dcScreen(GetParent());

   //Get the size of the screen/DC
   wxCoord screenWidth, screenHeight;

   //Size of the image
   int width, height;
   //The pixel array
   byte* graph;
   //Fill the pixel array
   graf->getPixels(graph, width, height);
   
   dcScreen.GetSize(&screenWidth, &screenHeight);

   //Create a Bitmap that will later on hold the screenshot image
   //Note that the Bitmap must have a size big enough to hold the screenshot
   //-1 means using the current default colour depth
   screenshot.Create(screenWidth, screenHeight,-1);
   //screenshot.Create(width, height,-1);

   //Create a memory DC that will be used for actually taking the screenshot
   wxMemoryDC memDC;
   //Tell the memory DC to use our Bitmap
   //all drawing action on the memory DC will go to the Bitmap now
   memDC.SelectObject(screenshot);
   //Blit (in this case copy) the actual screen on the memory DC
   //and thus the Bitmap
   memDC.Blit( 0, //Copy to this X coordinate
            0, //Copy to this Y coordinate
            screenWidth, //Copy this width
            screenHeight, //Copy this height
            &dcScreen, //From where do we copy?
            0, //What's the X offset in the original DC?
            0  //What's the Y offset in the original DC?
         );
   //Draw the graph on the screenshot


   //Temporary color
   wxColour color = wxColor(255,0,0);
   //Temporary position in pixel array
   int pos;

   //Loop through pixel array
   for(int y=0; y<height; y++) {
	   for(int x=0; x<width; x++) {
		   pos = (x+(height-y)*width)*3;
		   color.Set(graph[pos], graph[pos+1], graph[pos+2]);
		   memDC.SetBrush(color);
		   memDC.SetPen(color);
		   memDC.DrawPoint(x+79, y+59);
	   }
   }

   
   //Select the Bitmap out of the memory DC by selecting a new
   //uninitialized Bitmap
   memDC.SelectObject(wxNullBitmap);

   

   return;
}



GraphButton::GraphButton(wxFrame *parent, int id, SettingsManager *n_SetMan) : wxButton(parent, id, wxString::FromUTF8("Ukon�it"), wxDefaultPosition, wxSize(24,24), wxBORDER_NONE|wxBU_EXACTFIT|wxBU_NOTEXT)
{
 SetMan = n_SetMan;
 normal1 = wxBitmap(wxT("RC_graphicon"), wxBITMAP_TYPE_PNG_RESOURCE);
 hover1 = wxBitmap(wxT("RC_graphiconF"), wxBITMAP_TYPE_PNG_RESOURCE);

 normal2 = wxBitmap(wxT("RC_bitmapicon"), wxBITMAP_TYPE_PNG_RESOURCE);
 hover2 = wxBitmap(wxT("RC_bitmapiconF"), wxBITMAP_TYPE_PNG_RESOURCE);

 Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(GraphButton::onClick), NULL, this);
 SetCursor(wxCursor(wxCURSOR_HAND));
 SetMan->GetSetting(SETT_DIS_TYPE, state);
 ToggleState(state);
 SetBackgroundColour(APP_STYLE_MAINBG);
 Align();
}
void GraphButton::Align()
{
 SetSize(60,60);
 int x, y;
 GetSize(&x, &y);
 SetPosition(wxPoint(this->GetParent()->GetSize().x - x -BUT_BIG_BORDER, 2*60+BUT_BIG_BORDER));
}
void GraphButton::ToggleState(int st)
{
 state = st;
 SetMan->SetSetting(SETT_DIS_TYPE, st);
 if (st == Z_GRAF)
 {
  SetHelpText(wxString::FromUTF8("Zobrazit obraz."));
  SetToolTip(wxString::FromUTF8("Zobrazit obraz."));
  SetBitmap(normal1);
  SetBitmapHover(hover1);
 } else //state == Z_OBRAZ
 {
  SetHelpText(wxString::FromUTF8("Zobrazit graf."));
  SetToolTip(wxString::FromUTF8("Zobrazit graf."));
  SetBitmap(normal2);
  SetBitmapHover(hover2);
 }
}
void GraphButton::ToggleState()
{
 if (state == Z_GRAF)
  ToggleState(Z_OBRAZ);
 else //state == Z_OBRAZ
  ToggleState(Z_GRAF);
}
void GraphButton::onClick(wxCommandEvent& WXUNUSED(event)) {
	ToggleState();
}


PreviousButton::PreviousButton(wxFrame *parent, int id, SettingsManager *n_SetMan) : wxButton(parent, id, wxString::FromUTF8("Ukon�it"), wxDefaultPosition, wxSize(24,24), wxBORDER_NONE|wxBU_EXACTFIT|wxBU_NOTEXT)
{
 normal = wxBitmap(wxT("RC_previcon"), wxBITMAP_TYPE_PNG_RESOURCE);//wxBITMAP_TYPE_PNG
 focus = wxBitmap(wxT("RC_previconF"), wxBITMAP_TYPE_PNG_RESOURCE);
 press = wxBitmap(wxT("RC_previconP"), wxBITMAP_TYPE_PNG_RESOURCE);
 SetMan = n_SetMan;

 //Dal doleva uz posouvat nejde
 if (SetMan->GetSetting(SETT_CAM_N) <= 1)
  Enable(false);

 SetCursor(wxCursor(wxCURSOR_HAND));
 SetHelpText(wxString::FromUTF8("Pou�ije p�edchoz� kameru."));
 SetToolTip(wxString::FromUTF8("P�edchoz� kamera"));
 SetBitmap(normal);
 SetBitmapHover(focus);
 SetBitmapPressed(press);
 SetBackgroundColour(APP_STYLE_MAINBG);
 Align();
 //wxEVT_COMMAND_RIGHT_DCLICK
 Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(PreviousButton::onClick), NULL, this);
 //Connect(wxEVT_LEFT_UP, wxMouseEventHandler(ScreenshotButton::onClick));
}
void PreviousButton::Align()
{
 SetSize(60,60);
 int x, y;
 GetSize(&x, &y);
 SetPosition(wxPoint(this->GetParent()->GetSize().x - x -BUT_BIG_BORDER, 3*60+2*BUT_BIG_BORDER));
}
void PreviousButton::onClick(wxCommandEvent& WXUNUSED(event))
{
 int n = SetMan->GetSetting(SETT_CAM_N);
 if (n-- > 0)
 {
  SetMan->SetSetting(SETT_CAM_N, n);
  NextBut->Enable(true);
  if (n == 1)
  {
   Enable(false);
  }
 }
}

NextButton::NextButton(wxFrame *parent, int id, PreviousButton *n_PrevBut, SettingsManager *n_SetMan) : wxButton(parent, id, wxString::FromUTF8("Ukon�it"), wxDefaultPosition, wxSize(24,24), wxBORDER_NONE|wxBU_EXACTFIT|wxBU_NOTEXT)
{
 normal = wxBitmap(wxT("RC_nexticon"), wxBITMAP_TYPE_PNG_RESOURCE);//wxBITMAP_TYPE_PNG
 focus = wxBitmap(wxT("RC_nexticonF"), wxBITMAP_TYPE_PNG_RESOURCE);
 press = wxBitmap(wxT("RC_nexticonP"), wxBITMAP_TYPE_PNG_RESOURCE);
 SetMan = n_SetMan;
 PrevBut = n_PrevBut;
 
 //Dal doprava uz posouvat nejde
 if (SetMan->GetSetting(SETT_CAM_N) >= SetMan->GetSetting(SETT_CAM_NMAX))
  Enable(false);

 SetCursor(wxCursor(wxCURSOR_HAND));
 SetHelpText(wxString::FromUTF8("Pou�ije dal�� kameru."));
 SetToolTip(wxString::FromUTF8("Dal�� kamera"));
 SetBitmap(normal);
 SetBitmapHover(focus);
 SetBitmapPressed(press);
 SetBackgroundColour(APP_STYLE_MAINBG);
 Align();
 //wxEVT_COMMAND_RIGHT_DCLICK
 Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(NextButton::onClick), NULL, this);
 //Connect(wxEVT_LEFT_UP, wxMouseEventHandler(ScreenshotButton::onClick));
}
void NextButton::Align()
{
 SetSize(60,60);
 int x, y;
 GetSize(&x, &y);
 SetPosition(wxPoint(this->GetParent()->GetSize().x - x -BUT_BIG_BORDER, 4*60+2*BUT_BIG_BORDER));
}
void NextButton::onClick(wxCommandEvent& WXUNUSED(event))
{
 int n = SetMan->GetSetting(SETT_CAM_N);
 int maxn = SetMan->GetSetting(SETT_CAM_NMAX);
 if (n < maxn)
 {
  n++;
  SetMan->SetSetting(SETT_CAM_N, n);
  PrevBut->Enable(true);
  if (n == maxn)
  {
   Enable(false);
  }
 }
}



PauseButton::PauseButton(wxFrame *parent, int id, GraphMemoryMan* gMem) : wxButton(parent, id, wxString::FromUTF8("Pauza"), wxDefaultPosition, wxSize(24,24), wxBORDER_NONE|wxBU_EXACTFIT|wxBU_NOTEXT)
{
 normal = wxBitmap(wxT("RC_pause"), wxBITMAP_TYPE_PNG_RESOURCE);//wxBITMAP_TYPE_PNG
 focus = wxBitmap(wxT("RC_pauseF"), wxBITMAP_TYPE_PNG_RESOURCE);
 press = wxBitmap(wxT("RC_pauseP"), wxBITMAP_TYPE_PNG_RESOURCE);

 graphMemory = gMem;

 SetCursor(wxCursor(wxCURSOR_HAND));
 SetHelpText(wxString::FromUTF8("Ulo�� a zobraz� pozastavenou stopu grafu."));
 SetToolTip(wxString::FromUTF8("Ulo�it pozastaven� graf"));
 SetBitmap(normal);
 SetBitmapHover(focus);
 SetBitmapPressed(press);
 SetBackgroundColour(APP_STYLE_MAINBG);
 Align();

 //wxEVT_COMMAND_RIGHT_DCLICK
 Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(PauseButton::onClick), NULL, this);
 //Connect(wxEVT_LEFT_UP, wxMouseEventHandler(ScreenshotButton::onClick));
}
void PauseButton::Align()
{
 SetSize(60,60);
 int x, y;
 GetSize(&x, &y);
 SetPosition(wxPoint(this->GetParent()->GetSize().x - x -BUT_BIG_BORDER, 5*60+2*BUT_BIG_BORDER));
}
void PauseButton::onClick(wxCommandEvent& WXUNUSED(event))
{
	graphMemory->createNew();
}