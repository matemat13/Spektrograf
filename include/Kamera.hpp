#ifndef KAMERA_HPP
#define KAMERA_HPP

#include "wx/wx.h"
#include <ctime>
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
#define FPS 30
#define FRAME_CLOCK CLOCKS_PER_SEC/FPS

class SettingsManager;

enum
{
 STAV_NEINICIALIZOVANO,
 STAV_CHYBA,
 STAV_OK,
 STAV_ODPOJENO
};

class Kamera
{
public:
	Kamera(SettingsManager *n_SetMan);
	~Kamera();
  //Vrati true, pokud se podarilo vytvorit obrazek do argumentu img, jinak false
	bool Obrazek(wxImage *img);
  //Vrati true, pokud se podarilo ziskat data obrazku, jinak false
	bool Obrazek(unsigned char *&img);
  //Vrati pocet hodnot, zapsanych do bufferu nebo nulu, pokud je kamera v chybnem stavu
	int Sample(short *&buffer);
  //Vrati pocet bytu, zapsanych do bufferu nebo nulu, pokud je kamera v chybnem stavu
	int Radek(unsigned char *&buffer);
  //Nastavi zdrojovou caru
  	void SetSourceLine(int x, int y);
  //Vrati error, jako cstring
	const char *GetError() {return error_buf;};
	int GetWidth() {return iWidth;};
	int GetHeight() {return iHeight;};
private:
	//Moje fce
	HRESULT EnumerateDevices(REFGUID category, IEnumMoniker **ppEnum);
	void NastavKamery();
	void error_message(const char* error_message, int error);
  bool KeepFPS();

	//moje promenny
	int stav;
  clock_t last_frame_update;
	SettingsManager *SetMan;

	//IBaseFilter *camera_filter;
	
 int device_number, n, list_devices, img_rotation, iWidth, iHeight, radek_posun;
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
 unsigned char *pBuffer;
 unsigned char *oldBuffer;
};

#endif
