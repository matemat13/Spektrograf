#include "main.hpp"
//adsad

enum
{
 BUTTON_Quit = wxID_EXIT,
 TIMER_NewImage = wxID_HIGHEST,
 BUTTON_Max
};


class FrameMain : public wxFrame
{
public:
    // ctor(s)
    FrameMain(const wxString& title);

    // event handlers (these functions should _not_ be virtual)
    void OnQuit(wxCommandEvent& event);
    void OnMax(wxCommandEvent& event);
	/*void OnPaint(wxPaintEvent& event);
	void OnProgressTimer(wxTimerEvent& event);*/
private:
    // any class wishing to process wxWidgets events must use this macro
	BasicDrawPane *drawPane;
	bool drawing;
	QuitButton *quitBut;
	MaxDemaxButton *maxBut;
	//void DrawImage(wxDC &dc);
	RenderTimer *timer;
    DECLARE_EVENT_TABLE()
};

class AppMain : public wxApp
{
public:
    // override base class virtuals
    // ----------------------------

    // this one is called on application startup and is a good place for the app
    // initialization (doing it here and not in the ctor allows to have an error
    // return: if OnInit() returns false, the application terminates)
    virtual bool OnInit();
private:
	FrameMain *frame;
	SettingsManager *setMgr;

	//void activateRenderLoop(bool on);
};




BEGIN_EVENT_TABLE(FrameMain, wxFrame)
 EVT_BUTTON(BUTTON_Quit,  FrameMain::OnQuit)
 EVT_BUTTON(BUTTON_Max,  FrameMain::OnMax)
END_EVENT_TABLE()


BEGIN_EVENT_TABLE(BasicDrawPane, wxPanel)
 EVT_PAINT(BasicDrawPane::paintEvent)
END_EVENT_TABLE()

BEGIN_EVENT_TABLE(UVStatusPanel, wxPanel)
 EVT_PAINT(UVStatusPanel::paintEvent)
END_EVENT_TABLE()

IMPLEMENT_APP(AppMain)




// frame constructor
FrameMain::FrameMain(const wxString& title)
       : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(800,600), 0)
{
 SetFont(wxFont(11, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
 SetFocus();

 //wxImage::AddHandler( new wxPNGHandler );  //Neco hrozne dulezityho pro png...
 /*wxBitmap *bmp2 = new wxBitmap(wxT("RC_demaximizeicon"), wxBITMAP_TYPE_ICO_RESOURCE);
 wxBitmap *bmp3 = new wxBitmap(wxT("RC_maximizeicon"), wxBITMAP_TYPE_ICO_RESOURCE);
 wxBitmap *bmp4 = new wxBitmap(wxT("RC_USBdiscon"), wxBITMAP_TYPE_ICO_RESOURCE);*/
 
  /*char *res = wxLoadUserResource(wxString::FromUTF8("WINICON"));
  SetIcon(wxIcon(res));
  //wxBitmap close = wxBITMAP_PNG(CLOSEICON);*/
  //Maximize(true);
  SetBackgroundColour(APP_STYLE_MAINBG);
  //Png pokus
  //wxStaticBitmap *ikona2 = new wxStaticBitmap(this, wxID_ANY, wxBitmap(wxT("pokus"), wxBITMAP_TYPE_PNG_RESOURCE), wxPoint(0,0));
  //Inicializace nastaveni
  SettingsManager *SetMan = new SettingsManager();
  //Maximize();

  quitBut = new QuitButton(this, BUTTON_Quit);
  maxBut = new MaxDemaxButton(this, BUTTON_Max, ST_MAXED);
  drawPane = new BasicDrawPane(this, SetMan);
  timer = new RenderTimer(drawPane);
  timer->start();
  drawPane->Refresh();
  /**HLAVNI NADPIS**/
  //wxFont ;
  wxStaticText *t = new wxStaticText(this, wxID_ANY, wxT("Spektrograf"), wxPoint(BUT_BORDER*2+32,BUT_BORDER));
  t->SetForegroundColour(wxColor(0,122,204));
  t->SetFont(wxFont(20, wxDEFAULT, wxNORMAL, wxBOLD));
  /**OBRAZEK**/
  wxStaticBitmap *ikona = new wxStaticBitmap(this, wxID_ANY, wxBitmap(wxT("aaaa"), wxBITMAP_TYPE_ICO_RESOURCE), wxPoint(BUT_BORDER,BUT_BORDER));

  
  /**UV panely**/
  UVStatusPanel *uvA = new UVStatusPanel(this, 100);


  /*
  wxClientDC dc(this);
  dc.DrawBitmap(wxBitmap("./oko.gif", wxBITMAP_TYPE_GIF_RESOURCE),0,0, false);*/
  Centre();
  SetIcon(wxICON(aaaa));
  /*
  static const int INTERVAL = 300; // milliseconds
  timer = new wxTimer(this, TIMER_NewImage);
  timer->Start(INTERVAL);*/
}
/*
void FrameMain::OnPaint(wxPaintEvent& event)
{
   wxAutoBufferedPaintDC dc(this);
   dc.SetBackground(wxBrush(this->GetBackgroundColour()));
   dc.Clear();
   DrawImage(dc);
   
}


void FrameMain::DrawImage(wxDC &dc)
{
 
  wxImage *image = new wxImage();
  kamera->Obrazek(image);
  
  //image->Mirror(true);
  //(image->Rotate180())
  
  
  wxSize imageSize = image->GetSize();
  wxBitmap bitmap = wxBitmap(*image);
  //delete image;
  dc.DrawBitmap(bitmap,0,0, false);
}*/

// event handlers
void FrameMain::OnMax(wxCommandEvent& WXUNUSED(event))
{
 if (IsMaximized(GetHWND()))
 {
  drawPane->Hide();
  Maximize(false);
  Centre();
  drawPane->Centre();
  quitBut->Align();
  maxBut->Align();
  maxBut->ToggleState();
  drawPane->Show();
 } else
 {
  drawPane->Hide();
  Maximize(true);
  drawPane->Centre();
  quitBut->Align();
  maxBut->Align();
  maxBut->ToggleState();
  drawPane->Show();
 }
 drawPane->SetFocus();
}

void FrameMain::OnQuit(wxCommandEvent& WXUNUSED(event))
{
 timer->Stop();
 delete timer;
 Close(true);
}


bool AppMain::OnInit()
{
    // call the base class initialization method, currently it only parses a
    // few common command-line options but it could be do more in the future
    if ( !wxApp::OnInit() )
        return false;
    //Aditional image handlers
    wxImage::AddHandler(new wxBMPHandler); 
    wxImage::AddHandler(new wxPNGHandler);
    // create the main application window
    frame = new FrameMain("Spektrograf");

    // and show it (the frames, unlike simple controls, are not shown when
    // created initially)
  
            //wxInitAllImageHandlers();
 
            //wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
 
            // then simply create like this
            //drawPane = new wxImagePanel( frame, wxT("image.jpg"), wxBITMAP_TYPE_JPEG);
            //sizer->Add(drawPane, 1, wxEXPAND);
 
            //frame->SetSizer(sizer);
    frame->Show(true);
	
	//kamera = new Kamera();
	
    //kamera->Obrazek(img);
    // success: wxApp::OnRun() will be called which will enter the main message
    // loop and the application will run. If we returned false here, the
    // application would exit immediately.
    return true;
}
