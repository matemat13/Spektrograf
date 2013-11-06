#pragma once
#include "wx/wx.h"

#define ST_MAXED true
#define ST_WINDO false
#define BUT_BORDER 0
#define BUT_BIG_BORDER 10

class QuitButton : public wxButton
{
public:
 QuitButton(wxFrame *parent, int id);
 void Align();
private:
 wxBitmap normal;
 wxBitmap focus;
 wxBitmap press;
};

class MaxDemaxButton : public wxButton
{
public:
 MaxDemaxButton(wxFrame *parent, int id, bool n_state);
 void ToggleState();
 void ToggleState(bool);
 void Align();
private:
 bool state;
 wxBitmap normal1;
 wxBitmap focus1;
 wxBitmap press1;
 wxBitmap normal2;
 wxBitmap focus2;
 wxBitmap press2;
};
class ScreenshotButton : public wxButton
{
public:
 ScreenshotButton(wxFrame *parent, int id);
 void onClick(wxCommandEvent& WXUNUSED(event));
 void GetScreenshot(wxBitmap &screenshot);
 void Align();
private:
 wxBitmap normal;
 wxBitmap focus;
 wxBitmap press;
};

class GraphButton : public wxButton
{
public:
 GraphButton(wxFrame *parent, int id, bool*);
 void onClick(wxCommandEvent& WXUNUSED(event));
 void ToggleState();
 void ToggleState(bool);
 void Align();
private:
 bool *state;
 wxBitmap normal1;
 wxBitmap hover1;
 wxBitmap normal2;
 wxBitmap hover2;
};