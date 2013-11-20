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
