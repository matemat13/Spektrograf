#include "main.hpp"
//adsad

enum
{
 BUTTON_Quit = wxID_EXIT,
 TIMER_NewImage = wxID_HIGHEST,
 BUTTON_Max,
 BUTTON_Screenshot
};

class AppMain;
class FrameMain : public wxFrame
{
public:
	//Constructor
    FrameMain(const wxString& title);

    // event handlers (these functions should _not_ be virtual)
    void OnQuit(wxCommandEvent& event);
    void OnMax(wxCommandEvent& event);
	void OnMousemove(wxMouseEvent& event);
	void OnMousedown(wxMouseEvent& event);
	void OnMouseup(wxMouseEvent& event);
	void OnMouseout(wxMouseEvent& event);

	/**Layout initialisation**/
	void Align(wxCommandEvent& WXUNUSED(event));

private:
	BasicDrawPane *drawPane;
	GraphPanel *graf;
	UVStatusPanel *uvbut;
	bool drawing;


	QuitButton *quitBut;
	MaxDemaxButton *maxBut;
	ScreenshotButton *scrBut;
	GraphButton *grBut;

	/**Window status**/
	bool dragged;
	wxPoint dragPoint;
	/**Application reference**/
	AppMain application;

	/**Moar events**/
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
	/**Command line parameter parsing**/
	void OnInitCmdLine(wxCmdLineParser& parser);
	bool OnCmdLineParsed(wxCmdLineParser &parser);
    virtual bool OnInit();
private:
	FrameMain *frame;
	SettingsManager *setMgr;
	/**Window status**/
	bool start_maximized;
	bool locked;
	std::string password;
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

BEGIN_EVENT_TABLE(GraphPanel, wxPanel)
 EVT_PAINT(GraphPanel::paintEvent)
END_EVENT_TABLE()

IMPLEMENT_APP(AppMain)




// frame constructor
FrameMain::FrameMain(const wxString& title)
       : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(800,600), 0)
{
 SetFont(wxFont(11, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
 SetFocus();

 //Zarovnat okno pri maximalizaci
 Connect(wxEVT_MAXIMIZE, wxCommandEventHandler(FrameMain::Align), NULL, this);
 //Eventy pro posouvani
 Connect(wxEVT_LEFT_DOWN, wxMouseEventHandler(FrameMain::OnMousedown), NULL, this);
 Connect(wxEVT_LEFT_UP, wxMouseEventHandler(FrameMain::OnMouseup), NULL, this);
 Connect(wxEVT_MOTION, wxMouseEventHandler(FrameMain::OnMousemove), NULL, this);
 Connect(wxEVT_LEAVE_WINDOW, wxMouseEventHandler(FrameMain::OnMouseout), NULL, this);

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

  scrBut = new ScreenshotButton(this, BUTTON_Screenshot);
  
  /*drawPane = new BasicDrawPane(this, SetMan);
  timer = new RenderTimer(drawPane);
  timer->start();
  drawPane->Refresh();*/
  /**HLAVNI NADPIS**/
  //wxFont ;
  wxStaticText *t = new wxStaticText(this, wxID_ANY, wxT("Spektrograf"), wxPoint(APP_LOGO_PADDING*2+32,APP_LOGO_PADDING));
  t->SetForegroundColour(wxColor(0,122,204));
  t->SetFont(wxFont(20, wxDEFAULT, wxNORMAL, wxBOLD));
  /**OBRAZEK**/
  new wxStaticBitmap(this, wxID_ANY, wxBitmap(wxT("aaaa"), wxBITMAP_TYPE_ICO_RESOURCE), wxPoint(APP_LOGO_PADDING,APP_LOGO_PADDING));

  
  /**UV panely**/
  uvbut = new UVStatusPanel(this, 100);
  //UVStatusPanel *uvB = new UVStatusPanel(this, this->GetSize().GetWidth()-200);
  /**Graf**/
  graf =  new GraphPanel(this, SetMan);
  grBut = new GraphButton(this, wxID_ANY, &(graf->drawMode));
  //graf->Hide();
  timer = new RenderTimer(graf);
  timer->start();
  /*
  wxClientDC dc(this);
  dc.DrawBitmap(wxBitmap("./oko.gif", wxBITMAP_TYPE_GIF_RESOURCE),0,0, false);*/
  Centre();
  SetIcon(wxICON(aaaa));

  dragged = false;
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
void FrameMain::OnMousemove(wxMouseEvent& event) {
	if(dragged) 
	{
		wxPoint pos = GetPosition();
		SetPosition(wxPoint(pos.x+event.GetX()-dragPoint.x, pos.y+event.GetY()-dragPoint.y));
	}
}
void FrameMain::OnMousedown(wxMouseEvent& event) {
	if(!IsMaximized(GetHWND()))
	{
        dragged = true;
        dragPoint = wxPoint(event.GetX(), event.GetY());
	}
}
void FrameMain::OnMouseup(wxMouseEvent& WXUNUSED(event)) {
    dragged = false;
}

void FrameMain::OnMouseout(wxMouseEvent& WXUNUSED(event)) {
	dragged = false;
}

void FrameMain::OnMax(wxCommandEvent& WXUNUSED(event))
{
 timer->Stop();
 graf->Hide();
 if (IsMaximized(GetHWND()))
 {
  Maximize(false);
  Centre();
 } 
 else
 {
  Maximize(true);
 }
 Align((wxCommandEvent)NULL);
}
void FrameMain::Align(wxCommandEvent& WXUNUSED(event)) {
 if(graf->IsShownOnScreen()) 
 {
   timer->Stop();
   graf->Hide();
 }
 uvbut->Align();
 graf->Align();
 quitBut->Align();
 maxBut->Align();
 maxBut->ToggleState(!IsMaximized(GetHWND()));
 grBut->Align();
 scrBut->Align();

 graf->Show();
 timer->Start();
 graf->SetFocus();
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
	wxImage::AddHandler(new wxJPEGHandler);
    // create the main application window
    frame = new FrameMain("Spektrograf");

	password = std::string("heslo");
    // and show it (the frames, unlike simple controls, are not shown when
    // created initially)
  
            //wxInitAllImageHandlers();
 
            //wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
 
            // then simply create like this
            //drawPane = new wxImagePanel( frame, wxT("image.jpg"), wxBITMAP_TYPE_JPEG);
            //sizer->Add(drawPane, 1, wxEXPAND);
 
            //frame->SetSizer(sizer);
    frame->Show(true);
	if(start_maximized)
		frame->Maximize(true);
	
	//kamera = new Kamera();
	
    //kamera->Obrazek(img);
    // success: wxApp::OnRun() will be called which will enter the main message
    // loop and the application will run. If we returned false here, the
    // application would exit immediately.
    return true;
}
void AppMain::OnInitCmdLine(wxCmdLineParser& parser)
{
	static const wxCmdLineEntryDesc g_cmdLineDesc [] =
    {

        { wxCMD_LINE_SWITCH, (const char*)wxT("m"), (const char*)wxT("maximized"), (const char*)wxT("Program will start in full window.") },
        { wxCMD_LINE_SWITCH, (const char*)wxT("l"), (const char*)wxT("locked"), (const char*)wxT("Program will start locked.") },
        { wxCMD_LINE_SWITCH, (const char*)wxT("c"), (const char*)wxT("config"), (const char*)wxT("Configuration mode") },
 	   
        { wxCMD_LINE_NONE }
    };
    parser.SetDesc (g_cmdLineDesc);
    // must refuse '/' as parameter starter or cannot use "/path" style paths
    parser.SetSwitchChars (wxT("-"));
}

bool AppMain::OnCmdLineParsed(wxCmdLineParser& parser)
{

	start_maximized = parser.Found(wxT("m"));
    return true;
}