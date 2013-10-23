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

#include <stdio.h>

class Kamera
{
public:
	Kamera();
	void Obrazek(wxImage *img);
private:
	//Moje fce
	HRESULT EnumerateDevices(REFGUID category, IEnumMoniker **ppEnum);
	void NastavKamery();

	//moje promenny
	int stav;
	//IBaseFilter *camera_filter;
	IBaseFilter *camera_filter;
	
 int device_number, n, list_devices;
 long buffer_size;
 char device_name[100];
 // Other variables
 char char_buffer[100];
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
 char *pBuffer;
};

#endif