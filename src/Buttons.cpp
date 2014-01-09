#include "include/Buttons.hpp"
#include "main.hpp"

QuitButton::QuitButton(wxFrame *parent, int id) : wxButton(parent, id, wxString::FromUTF8("Konec"), wxDefaultPosition, wxSize(24,24), wxBORDER_NONE|wxBU_EXACTFIT|wxBU_NOTEXT)
{
 normal = wxBitmap(wxT("RC_closeicon"), wxBITMAP_TYPE_ICO_RESOURCE);//wxBITMAP_TYPE_PNG
 //normal = wxBitmap(wxT("RC_closeicon"), wxBITMAP_TYPE_PNG_RESOURCE);
 focus = wxBitmap(wxT("RC_closeiconF"), wxBITMAP_TYPE_ICO_RESOURCE);
 press = wxBitmap(wxT("RC_closeiconP"), wxBITMAP_TYPE_ICO_RESOURCE);

 SetCursor(wxCursor(wxCURSOR_HAND));
 SetHelpText(wxString::FromUTF8("Ukonèi aplikaci spektrograf."));
 SetToolTip(wxString::FromUTF8("Ukonèit program"));
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
  SetHelpText(wxString::FromUTF8("Obnoví aplikaci z maximalizace do okna."));
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


ScreenshotButton::ScreenshotButton(wxFrame *parent, int id) : wxButton(parent, id, wxString::FromUTF8("Ukonèit"), wxDefaultPosition, wxSize(24,24), wxBORDER_NONE|wxBU_EXACTFIT|wxBU_NOTEXT)
{
 normal = wxBitmap(wxT("RC_screenshoticon"), wxBITMAP_TYPE_PNG_RESOURCE);//wxBITMAP_TYPE_PNG
 focus = wxBitmap(wxT("RC_screenshoticonF"), wxBITMAP_TYPE_PNG_RESOURCE);
 press = wxBitmap(wxT("RC_screenshoticonP"), wxBITMAP_TYPE_PNG_RESOURCE);

 SetCursor(wxCursor(wxCURSOR_HAND));
 SetHelpText(wxString::FromUTF8("Uloží aktuální stav okna jako obrázek."));
 SetToolTip(wxString::FromUTF8("Uložit screenshot"));
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
   wxFileDialog fileDialog(this, _("Save a screenshot"), wxT(""), wxT("spektrograf.bmp"), wxT("Rastr (*.bmp) | *.bmp|Obrázek PNG (nedoporuèuje se) (*.png) | *.png|JPEG formát (*.jpg) | *.jpeg;*.jpg"), wxFD_SAVE);
   if(fileDialog.ShowModal() == wxID_OK) {
          wxFileName namePath(fileDialog.GetPath());
          int fileType = wxBITMAP_TYPE_BMP;
          if( namePath.GetExt().CmpNoCase(wxT("jpeg")) == 0 ) fileType = wxBITMAP_TYPE_JPEG;
          if( namePath.GetExt().CmpNoCase(wxT("jpg")) == 0 )  fileType = wxBITMAP_TYPE_JPEG;
          if( namePath.GetExt().CmpNoCase(wxT("png")) == 0 )  fileType = wxBITMAP_TYPE_PNG;
		  if( namePath.GetExt().CmpNoCase(wxT("bmp")) == 0 )  fileType = wxBITMAP_TYPE_BMP;
		  wxImage tosave(screenshot.ConvertToImage());
		  tosave.ClearAlpha();

		  if(wxFileExists(fileDialog.GetPath())) 
		  {
			  wxMessageDialog potvrd(this, _("Soubor existuje! Chcete jej pøepsat?"), _("Soubor existuje"), wxYES_NO|wxNO_DEFAULT|wxICON_WARNING);
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
   dcScreen.GetSize(&screenWidth, &screenHeight);

   //Create a Bitmap that will later on hold the screenshot image
   //Note that the Bitmap must have a size big enough to hold the screenshot
   //-1 means using the current default colour depth
   screenshot.Create(screenWidth, screenHeight,-1);

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
   //Select the Bitmap out of the memory DC by selecting a new
   //uninitialized Bitmap
   memDC.SelectObject(wxNullBitmap);
   return;
}



GraphButton::GraphButton(wxFrame *parent, int id, bool *n_state) : wxButton(parent, id, wxString::FromUTF8("Ukonèit"), wxDefaultPosition, wxSize(24,24), wxBORDER_NONE|wxBU_EXACTFIT|wxBU_NOTEXT)
{
 normal1 = wxBitmap(wxT("RC_graphicon"), wxBITMAP_TYPE_PNG_RESOURCE);
 hover1 = wxBitmap(wxT("RC_graphiconF"), wxBITMAP_TYPE_PNG_RESOURCE);

 normal2 = wxBitmap(wxT("RC_bitmapicon"), wxBITMAP_TYPE_PNG_RESOURCE);
 hover2 = wxBitmap(wxT("RC_bitmapiconF"), wxBITMAP_TYPE_PNG_RESOURCE);
 state = n_state;
 Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(GraphButton::onClick), NULL, this);
 SetCursor(wxCursor(wxCURSOR_HAND));
 ToggleState(*state);
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
void GraphButton::ToggleState(bool st)
{
 *state = st;
 if (*state == true)
 {
  SetHelpText(wxString::FromUTF8("Zobrazit obraz."));
  SetToolTip(wxString::FromUTF8("Zobrazit obraz."));
  SetBitmap(normal1);
  SetBitmapHover(hover1);
 } else //state == ST_WINDO
 {
  SetHelpText(wxString::FromUTF8("Zobrazit graf."));
  SetToolTip(wxString::FromUTF8("Zobrazit graf."));
  SetBitmap(normal2);
  SetBitmapHover(hover2);
 }
}
void GraphButton::ToggleState()
{
    ToggleState(!*state);
}
void GraphButton::onClick(wxCommandEvent& WXUNUSED(event)) {
	ToggleState();
}