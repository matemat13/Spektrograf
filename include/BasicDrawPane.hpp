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
//#include "include/XYZtoRGB.h"

#define WIDTH 640
#define HEIGHT 480

class Kamera;
class SettingsManager;
class FrameMain;
class GraphMemoryMan;
class GraphMemory;


class wxGLCanvasSubClass: public wxGLCanvas {
public:
    wxGLCanvasSubClass(wxFrame* parent, Kamera *n_kamera, SettingsManager *n_SetMan);
    void paintEvent(wxPaintEvent& event);
	void paintNow();
	void Align();
	void setMemory(GraphMemoryMan*);

	int getGraph(short*&datap);
	void getPixels(byte*&, int&, int&);

	//Zmenit typ zobrazeni - graf/obraz
	void SetDisplay(int type);
	void ToggleDisplay();
    ~wxGLCanvasSubClass();
    DECLARE_EVENT_TABLE()
private:
  void Graf(short *n_data, short*data_pr, int n_data_length);
  void GrafBarevny(unsigned char *n_data, int n_data_length);
  void Obraz(unsigned char *n_data, short width, short height);
  void Chyba();
  void Render();
  void SetZoom();

  

	//Nakresli graf
	void DrawGraph(short*data, int dataLen, wxColour color = wxColor(255,255,255), float lineWidth = 1.0);
	void DrawVMarker(unsigned short wavelength, wxColour color, float lineWidth);
	void DrawVMarker(double position, wxColour color, float lineWidth);
  //bool initialized;
  Kamera *kamera;
  wxGLContext *m_glRC;
  SettingsManager *SetMan;
  GraphMemoryMan*pamet;
  unsigned char *chyba_obr;

  short* data;
   short* data_prumer;
  unsigned char* uchar_data;
  unsigned char* obr_data;
  int data_length, data_to_screen_ratio;
  short img_width, img_height;
  int stav, stav_pred_chybou;
  int cur_width, cur_height;

  //Line that is being moved - if any
  //unsigned int selected_line;
  unsigned int drag_button;

  //bool dragged;
  
	void OnMousemove(wxMouseEvent& event);
	void OnMousedown(wxMouseEvent& event);
	void OnMouseup(wxMouseEvent& event);
	void OnMouseout(wxMouseEvent& event);
	void OnScroll(wxMouseEvent& event);
};
 

bool detect_UV(short *data, int IR_edge, int UV_edge);


void glCircle(float x, float y, float r, bool filled, int subdivs);