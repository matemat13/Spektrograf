#include "include/Buttons.hpp"

QuitButton::QuitButton(wxFrame *parent, int id) : wxButton(parent, id, wxString::FromUTF8("Ukonèit"), wxDefaultPosition, wxSize(32,32), wxBORDER_NONE|wxBU_EXACTFIT|wxBU_NOTEXT)
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
 Align();
}
void QuitButton::Align()
{
 int x, y;
 GetSize(&x, &y);
 SetPosition(wxPoint(this->GetParent()->GetSize().x - x -BUT_BORDER, BUT_BORDER));
}


MaxDemaxButton::MaxDemaxButton(wxFrame *parent, int id, bool n_state) : wxButton(parent, id, wxString::FromUTF8("Ukonèit"), wxDefaultPosition, wxSize(32,32), wxBORDER_NONE|wxBU_EXACTFIT|wxBU_NOTEXT)
{
 normal1 = wxBitmap(wxT("RC_maximizeicon"), wxBITMAP_TYPE_ICO_RESOURCE);
 focus1 = wxBitmap(wxT("RC_maximizeiconF"), wxBITMAP_TYPE_ICO_RESOURCE);
 press1 = wxBitmap(wxT("RC_maximizeiconP"), wxBITMAP_TYPE_ICO_RESOURCE);

 normal2 = wxBitmap(wxT("RC_demaximizeicon"), wxBITMAP_TYPE_ICO_RESOURCE);
 focus2 = wxBitmap(wxT("RC_demaximizeiconF"), wxBITMAP_TYPE_ICO_RESOURCE);
 press2 = wxBitmap(wxT("RC_demaximizeiconP"), wxBITMAP_TYPE_ICO_RESOURCE);
 state = n_state;

 SetCursor(wxCursor(wxCURSOR_HAND));
 if (state == ST_MAXED)
 {
  SetHelpText(wxString::FromUTF8("Minimalizuje aplikaci."));
  SetToolTip(wxString::FromUTF8("Minimalizovat aplikaci."));
  SetBitmap(normal1);
  SetBitmapCurrent(focus1);
  //SetBitmapFocus(focus1);
  SetBitmapPressed(press1);
 } else //state == ST_WINDO
 {
  SetHelpText(wxString::FromUTF8("Maximalizuje aplikaci."));
  SetToolTip(wxString::FromUTF8("Maximalizovat aplikaci."));
  SetBitmap(normal2);
  SetBitmapCurrent(focus2);
  //SetBitmapFocus(focus2);
  SetBitmapPressed(press2);
 }
 Align();
}
void MaxDemaxButton::Align()
{
 int x, y;
 GetSize(&x, &y);
 SetPosition(wxPoint(this->GetParent()->GetSize().x - 2*x - 2*BUT_BORDER, BUT_BORDER));
}
void MaxDemaxButton::ToggleState()
{
 state = !state;
 if (state == ST_MAXED)
 {
  SetHelpText(wxString::FromUTF8("Minimalizuje aplikaci."));
  SetToolTip(wxString::FromUTF8("Minimalizovat aplikaci."));
  SetBitmap(normal1);
  SetBitmapCurrent(focus1);
  SetBitmapFocus(focus1);
  SetBitmapPressed(press1);
 } else //state == ST_WINDO
 {
  SetHelpText(wxString::FromUTF8("Maximalizuje aplikaci."));
  SetToolTip(wxString::FromUTF8("Maximalizovat aplikaci."));
  SetBitmap(normal2);
  SetBitmapCurrent(focus2);
  SetBitmapFocus(focus2);
  SetBitmapPressed(press2);
 }
}