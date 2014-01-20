#pragma once

#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

// for all others, include the necessary headers (this file is usually all you
// need because it includes almost all "standard" wxWidgets headers)
#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

// ----------------------------------------------------------------------------
// resources
// ----------------------------------------------------------------------------

// the application icon (under Windows and OS/2 it is in resources and even
// though we could still include the XPM here it would be unused)
/*
#ifndef wxHAS_IMAGES_IN_RESOURCES
    #include "./sample.xpm"
#endif
	*/

#if !wxUSE_THREADS
    #error "This sample requires thread support!"
#endif // wxUSE_THREADS


#include "wx/thread.h"
#include "wx/event.h"
#include "wx/image.h"
#include "wx/file.h"
#include "wx/filename.h"
#include "wx/graphics.h"
#include "wx/mstream.h"
#include "wx/wfstream.h"
#include "wx/quantize.h"
#include "wx/scopedptr.h"
#include "wx/stopwatch.h"
#include "wx/versioninfo.h"
#include "wx/dcbuffer.h"
#include "wx/timer.h"
#include <ctime>

#include "wx/wxprec.h"
#include "wx/cmdline.h"

#if wxUSE_CLIPBOARD
    #include "wx/dataobj.h"
    #include "wx/clipbrd.h"
#endif // wxUSE_CLIPBOARD

#if defined(__WXMSW__)
    #ifdef wxHAVE_RAW_BITMAP
    #include "wx/rawbmp.h"
    #endif
#endif

#if defined(__WXMAC__) || defined(__WXGTK__)
    #define wxHAVE_RAW_BITMAP
    #include "wx/rawbmp.h"
#endif

#include "include/Kamera.hpp"
#include "include/BasicDrawPane.hpp"
#include "include/GraphPanel.hpp"
#include "include/UVStatusPanel.hpp"
#include "include/RenderTimer.hpp"
#include "include/SettingsManager.hpp"
#include "include/Buttons.hpp"

#include <String>
#include <math.h>


//Definice vzhledu a textu:
#define APP_STYLE_MAINBG wxColor(230,230,246)
#define APP_LOGO_PADDING 10

//Definice samplovani:
#define DEFAULT_SAMPLE_LENGTH 1024
#define SAMPLING_PERIOD (1000/20)
#define SAMPLE_MAX_VALUE (255.0*3.0)




/*Sampling thread*/

//definice typu zobrazeni
#define Z_CHYBA 0
#define Z_OBRAZ 1
#define Z_GRAF 2
#define Z_GRAF_BAR 3

class FrameMain;
class Kamera;
class SettingsManager;

class SamplingThread : public wxThread
{
private:
	//state change crit section
	wxCriticalSection state_CS;
	int state, lastState;
public:
    SamplingThread(FrameMain *frame, SettingsManager *n_SetMan);
    //virtual ~SamplingThread();

    // thread execution starts here
    virtual void *Entry();
    virtual void OnExit();
	//Slouzi ke zmene zobrazovani z grafu do obrazu a zpet
	void setState(int n_state)
	{
	 wxCriticalSectionLocker lock(state_CS);
  	 state = n_state;
	};
	//Musi to byt pres Critical Section kvuli multithreadingu
	int getState() {wxCriticalSectionLocker lock(state_CS); return state;};
    ~SamplingThread();
private:
    FrameMain *m_frame;
	Kamera *zdroj;
	SettingsManager *n_SetMan;
	
    int sample_length;
	
    bool getSample();
    bool getImage();
    short *buffer;
	unsigned char *imgData;
};


enum
{
 BUTTON_Quit = wxID_EXIT,
 TIMER_NewImage = wxID_HIGHEST,
 BUTTON_Max,
 BUTTON_Screenshot,
 STHREAD_EVENT
};