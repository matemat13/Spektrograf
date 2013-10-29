#ifndef KAMERA_HPP
#define KAMERA_HPP

#include "wx/wx.h"
#include <windows.h>
#include <dshow.h>
#include <strmif.h>
#include <d3d9.h>
#include <Vmr9.h>
#include <vector>
#include <assert.h>
#pragma comment(lib, "strmiids")

#import "qedit.dll" raw_interfaces_only named_guids
EXTERN_C const CLSID CLSID_NullRenderer;
EXTERN_C const CLSID CLSID_SampleGrabber;

#include "include/debug_exit.hpp"
#include "include/SettingsManager.hpp"

#define ERROR_STILL_IMGS 50

class Kamera
{
public:
	Kamera(SettingsManager *n_SetMan);
	~Kamera();
	bool Obrazek(wxImage *img);
	const char *GetError() {return error_buf;};
private:
	//Moje fce
	HRESULT EnumerateDevices(REFGUID category, IEnumMoniker **ppEnum);
	void NastavKamery();
	void error_message(const char* error_message, int error);

	//moje promenny
	int stav;
	SettingsManager *SetMan;

	//IBaseFilter *camera_filter;
	
 int device_number, n, list_devices;
 long buffer_size;
 char device_name[100];
 // Other variables
 char error_buf[100];
 int still_imgs;
 HRESULT hr;
 ICreateDevEnum *pDevEnum;
 IEnumMoniker *pEnum;
 IMoniker *pMoniker;
 IPropertyBag *pPropBag;
 IGraphBuilder *pGraph;
 ICaptureGraphBuilder2 *pBuilder;
 IBaseFilter *pCap;
 IBaseFilter *pSampleGrabberFilter;
 DexterLib::ISampleGrabber *pSampleGrabber;
 IBaseFilter *pNullRenderer;
 IMediaControl *pMediaControl;
 AM_MEDIA_TYPE mt;
 VIDEOINFOHEADER *pVih;
 char *pBuffer;
 char *oldBuffer;
};

#endif