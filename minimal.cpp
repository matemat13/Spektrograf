#include "main.hpp"
//adsad

enum
{
 BUTTON_Quit = wxID_EXIT,
 TIMER_NewImage = wxID_HIGHEST
};


class FrameMain : public wxFrame
{
public:
    // ctor(s)
    FrameMain(const wxString& title);

    // event handlers (these functions should _not_ be virtual)
    void OnQuit(wxCommandEvent& event);
	/*void OnPaint(wxPaintEvent& event);
	void OnProgressTimer(wxTimerEvent& event);*/
private:
    // any class wishing to process wxWidgets events must use this macro
	BasicDrawPane *drawPane;
	bool drawing;
	wxButton *QuitBut;
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
END_EVENT_TABLE()


BEGIN_EVENT_TABLE(BasicDrawPane, wxPanel)
 EVT_PAINT(BasicDrawPane::paintEvent)
END_EVENT_TABLE()

IMPLEMENT_APP(AppMain)




// frame constructor
FrameMain::FrameMain(const wxString& title)
       : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(800,600), 0)
{
  SetFont(wxFont(11, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));


  /*char *res = wxLoadUserResource(wxString::FromUTF8("WINICON"));
  SetIcon(wxIcon(res));
  //wxBitmap close = wxBITMAP_PNG(CLOSEICON);*/
  //Maximize(true);
  SetBackgroundColour(wxColor(80,100,255));
  // set the frame icon
  QuitBut = new wxButton(this, BUTTON_Quit, wxString::FromUTF8("Ukončit"), wxDefaultPosition, wxDefaultSize, wxBORDER_NONE|wxBU_EXACTFIT);
  QuitBut->SetForegroundColour(wxColor(150,150,255));
  QuitBut->SetBackgroundColour(wxColor(255,0,0));
  QuitBut->SetCursor(wxCursor(wxCURSOR_HAND));
  QuitBut->SetHelpText(wxString::FromUTF8("Ukonči aplikaci spektrograf."));
  QuitBut->SetToolTip(wxString::FromUTF8("Ukončit program"));
  //QuitBut->SetAuthNeeded(true);
  
  SettingsManager *SetMan = new SettingsManager();

  int x, y;
  QuitBut->GetSize(&x, &y);
  QuitBut->SetPosition(wxPoint(800-x, 0));
  drawPane = new BasicDrawPane(this, SetMan);
  timer = new RenderTimer(drawPane);
  timer->start();
  drawPane->Refresh();
  
  /*
  wxClientDC dc(this);
  dc.DrawBitmap(wxBitmap("./oko.gif", wxBITMAP_TYPE_GIF_RESOURCE),0,0, false);*/
  Centre();
  SetIcon(wxICON(sample));
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
