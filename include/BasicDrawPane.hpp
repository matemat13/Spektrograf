#pragma once
#include "wx/wx.h"
#include "wx/glcanvas.h"


/*
#ifdef __WXMAC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
*/
#include <windows.h>
#include "Kamera.hpp"
#include "SettingsManager.hpp"
#include "main.hpp"

#define WIDTH 640
#define HEIGHT 480

class CBitmapFont;

class wxGLCanvasSubClass: public wxGLCanvas {
public:
    wxGLCanvasSubClass(wxFrame* parent);
    void Paintit(wxPaintEvent& event);
    void Graf(const short *n_data, int n_data_length);
    void Obraz(const unsigned char *n_data, short width, short height);
	void Chyba();
    ~wxGLCanvasSubClass();
    DECLARE_EVENT_TABLE()
private:
  //bool initialized;
  wxGLContext *m_glRC;
  unsigned char *chyba_obr;
  void Render();
  short* data;
  unsigned char* obr_data;
  int data_length, data_to_screen_ratio;
  short img_width, img_height;
  int stav;
};
 
 

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


// COutlineFont is a class which encapsulates the details necessary
// to draw outline font text in OpenGL on the Windows platform.

