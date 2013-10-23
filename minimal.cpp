
#include "main.hpp"


enum
{
    // menu items
    BUTTON_Quit = wxID_EXIT,

    // it is important for the id corresponding to the "About" command to have
    // this standard value as otherwise it won't be handled properly under Mac
    // (where it is special and put into the "Apple" menu)
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
	Kamera *kamera;
};


class FrameMain : public wxFrame
{
public:
    // ctor(s)
    FrameMain(const wxString& title);

    // event handlers (these functions should _not_ be virtual)
    void OnQuit(wxCommandEvent& event);
	void OnPaint(wxPaintEvent& event);

private:
    // any class wishing to process wxWidgets events must use this macro
	wxButton *QuitBut;
	void DrawImage(wxDC &dc);
	Kamera *kamera;
    DECLARE_EVENT_TABLE()
};


BEGIN_EVENT_TABLE(FrameMain, wxFrame)
    EVT_BUTTON(BUTTON_Quit,  FrameMain::OnQuit)
	EVT_PAINT(FrameMain::OnPaint)
END_EVENT_TABLE()


IMPLEMENT_APP(AppMain)




// frame constructor
FrameMain::FrameMain(const wxString& title)
       : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(640,480), 0)
{
  SetBackgroundColour(wxColor(80,100,255));
  SetBackgroundStyle(wxBG_STYLE_PAINT);
  // set the frame icon
  QuitBut = new wxButton(this, BUTTON_Quit, wxT("Ukonèit"), wxDefaultPosition, wxDefaultSize, wxBORDER_NONE|wxBU_EXACTFIT);
  QuitBut->SetForegroundColour(wxColor(150,150,255));
  int x, y;
  QuitBut->GetSize(&x, &y);
  QuitBut->SetPosition(wxPoint(640-x, 0));


  SetIcon(wxICON(sample));
  Centre();
  kamera = new Kamera();

}

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
  
  
  
  wxSize imageSize = image->GetSize();
  wxBitmap bitmap = wxBitmap((image->Rotate180()));
  //delete image;
  dc.DrawBitmap(bitmap,0,0, false);
}

// event handlers

void FrameMain::OnQuit(wxCommandEvent& WXUNUSED(event))
{
    // true is to force the frame to close
    Close(true);
}


bool AppMain::OnInit()
{
    // call the base class initialization method, currently it only parses a
    // few common command-line options but it could be do more in the future
    if ( !wxApp::OnInit() )
        return false;

    // create the main application window
    FrameMain *frame = new FrameMain("Spektrograf");

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