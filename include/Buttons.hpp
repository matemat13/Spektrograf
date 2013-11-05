#pragma once
#include "wx/wx.h"

#define ST_MAXED true
#define ST_WINDO false
#define BUT_BORDER 0

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