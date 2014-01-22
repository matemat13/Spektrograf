#pragma once
#include "wx/wx.h"

#define ST_MAXED true
#define ST_WINDO false
#define BUT_BORDER 0
#define BUT_BIG_BORDER 10

class SettingsManager;

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
 GraphButton(wxFrame *parent, int id, SettingsManager*);
 void onClick(wxCommandEvent& WXUNUSED(event));
 void ToggleState();
 void ToggleState(int);
 void Align();
private:
 SettingsManager *SetMan;
 int state;
 wxBitmap normal1;
 wxBitmap hover1;
 wxBitmap normal2;
 wxBitmap hover2;
};

class NextButton;

class PreviousButton : public wxButton
{
public:
 PreviousButton(wxFrame *parent, int id, SettingsManager*);
 void SetNextBut(NextButton *n_NextBut) {NextBut = n_NextBut;};
 void onClick(wxCommandEvent& WXUNUSED(event));
 void Align();
private:
 SettingsManager *SetMan;
 NextButton *NextBut;
 int state;
 wxBitmap normal;
 wxBitmap focus;
 wxBitmap press;
};

class NextButton : public wxButton
{
public:
 NextButton(wxFrame *parent, int id, PreviousButton*, SettingsManager*);
 void onClick(wxCommandEvent& WXUNUSED(event));
 void Align();
private:
 SettingsManager *SetMan;
 PreviousButton *PrevBut;
 int state;
 wxBitmap normal;
 wxBitmap focus;
 wxBitmap press;
};