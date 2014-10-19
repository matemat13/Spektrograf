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

//#include "include/debug_exit.hpp"
#include "include/SettingsManager.hpp"

#define ERROR_STILL_IMGS 100
#define FPS 30
#define FRAME_CLOCK CLOCKS_PER_SEC/FPS

#define UV_TRESHOLD 20


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
  //Vrati true, pokud je kamera pripravena vracet data
	bool isReady();
  //Vrati pocet hodnot, zapsanych do bufferu nebo nulu, pokud je kamera v chybnem stavu
	int Sample(short *&buffer);
  //Vrati pocet bytu, zapsanych do bufferu nebo nulu, pokud je kamera v chybnem stavu
	int Radek(unsigned char *&buffer);
  //Zprumeruje data, pak je vrati
	int Sample_Kalman(short *&buffer);
  //Nastavi zdrojovou caru
  	void SetSourceLine(int x, int y);
  //Najde UV spike, jeho maximalni hodnotu (a jeji pozici) a prumerny jas v oblasti UV, vraci true, pokud je UV detekovano, jinak false
	bool findUVSpike(int &maxf, float &avg, unsigned short &max_pos);
  //Vrati vlnovou delku na danem pixelu (pocita se z nastaveni krajnich hodnot)
	double Kamera::WavelengthAt(const int pos);
  //Vrati error, jako cstring
	const char *GetError() {return error_buf;};
	int GetWidth() {return iWidth;};
	int GetHeight() {return iHeight;};

private:
	//Zpracovani dat
	static short PrumerOkenko(short *&buffer, unsigned short buffsize,unsigned short range, unsigned short pos);
	
	//Moje fce
	HRESULT EnumerateDevices(REFGUID category, IEnumMoniker **ppEnum);
	void UvolniKameru();
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
 unsigned char *avgBuffer;
};

#endif
