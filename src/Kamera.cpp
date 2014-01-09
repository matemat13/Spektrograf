#include "../include/Kamera.hpp"

int Kamera::Sample(short *&buffer)
{
 //Na pravidelne obnovovani bufferu s obrazkem
 KeepFPS();

 //Pokud je kamera neinicializovana nebo v chybnem stavu, vratim nulu
 if (stav != STAV_OK) return 0;

 int ret = 0;


 if (img_rotation == 0)
 {
  ret = iWidth;
  buffer = new short[ret];
  for (int i = 0; i < ret; i++)
  {
   buffer[i] = (pBuffer[radek_posun*iWidth*3 + i*3] + pBuffer[radek_posun*iWidth*3 + i*3 +1] + pBuffer[radek_posun*iWidth*3 + i*3 +2]);
  }
 } else if (img_rotation == 1)
 {
  ret = iHeight;
  buffer = new short[ret];
  for (int i = 0; i < ret; i++)	//Prirazuje se po trech, kvuli subpixelum
  {
   buffer[i] = (pBuffer[(radek_posun + i*iWidth)*3] + pBuffer[(radek_posun + i*iWidth)*3 + 1] + pBuffer[(radek_posun + i*iWidth)*3 + 2]);
  }
 } else if (img_rotation == 2)
 {
  ret = iWidth;
  buffer = new short[ret];
  for (int i = ret -1; i >= 0; i--)
  {
   buffer[i] = (pBuffer[radek_posun*iWidth*3 + i*3] + pBuffer[radek_posun*iWidth*3 + i*3 +1] + pBuffer[radek_posun*iWidth*3 + i*3 +2]);
  }
 } else if (img_rotation == 3)
 {
  ret = iHeight;
  buffer = new short[ret];
  for (int i = ret -1; i >= 0; i--)	//Prirazuje se po trech, kvuli subpixelum
  {
   buffer[i] = (pBuffer[(radek_posun + i*iWidth)*3] + pBuffer[(radek_posun + i*iWidth)*3 + 1] + pBuffer[(radek_posun + i*iWidth)*3 + 2]);
  }
 }
 return ret;
}

bool Kamera::Obrazek(unsigned char *&img)
{
 //Na pravidelne obnovovani bufferu s obrazkem
 KeepFPS();

 if (stav != STAV_OK) return false;
 
 img = new unsigned char[iWidth*iHeight*3];

 memcpy(img, pBuffer, iWidth*iHeight*3);

 
 //Nakresleni cary, ze ktere se bere radek
 if (img_rotation == 0)
 {
  int length = iWidth*3;
  for (int i = 0; i < length; i++)
  {
   img[radek_posun*iWidth*3 + i] = 255;
  }
 } else if (img_rotation == 1)
 {
  for (int i = 0; i < iHeight; i++)	//Prirazuje se po trech, kvuli subpixelum
  {
   img[(radek_posun + i*iWidth)*3] = 255;	//Red
   img[(radek_posun + i*iWidth)*3 + 1] = 255;	//Green
   img[(radek_posun + i*iWidth)*3 + 2] = 255;	//Blue
  }
 } else if (img_rotation == 2)
 {
  int length = iWidth*3;
  for (int i = length -1; i >= 0; i--)
  {
   img[radek_posun*iWidth*3 + i] = 255;
  }
 } else if (img_rotation == 3)
 {
  for (int i = iHeight -1; i > 0; i--)	//Prirazuje se po trech, kvuli subpixelum
  {
   img[(radek_posun + i*iWidth)*3] = 255;	//Red
   img[(radek_posun + i*iWidth)*3 + 1] = 255;	//Green
   img[(radek_posun + i*iWidth)*3 + 2] = 255;	//Blue
  }
 }

 return true;
}

int Kamera::Radek(unsigned char *&buffer)
{
 int ret = 0;
 if (buffer != NULL) delete buffer;

 //Na pravidelne obnovovani bufferu s obrazkem
 KeepFPS();
 //Pokud je kamera neinicializovana nebo v chybnem stavu, vratim nulu
 if (stav != STAV_OK) return ret;

 if (img_rotation == 0)
 {
  ret = iWidth*3;
  buffer = new unsigned char[ret];
  for (int i = 0; i < ret; i++)
  {
   buffer[i] = pBuffer[radek_posun*iWidth*3 + i];
  }
 } else if (img_rotation == 1)
 {
  ret = iHeight*3;
  buffer = new unsigned char[ret];
  for (int i = 0; i < iHeight; i++)	//Prirazuje se po trech, kvuli subpixelum
  {
   buffer[i*3] = pBuffer[(radek_posun + i*iWidth)*3];	//Red
   buffer[i*3 + 1] = pBuffer[(radek_posun + i*iWidth)*3 + 1];	//Green
   buffer[i*3 + 2] = pBuffer[(radek_posun + i*iWidth)*3 + 2];	//Blue
  }
 } else if (img_rotation == 2)
 {
  ret = iWidth*3;
  buffer = new unsigned char[ret];
  for (int i = ret -1; i >= 0; i--)
  {
   buffer[i] = pBuffer[radek_posun*iWidth*3 + i];
  }
 } else if (img_rotation == 3)
 {
  ret = iHeight*3;
  buffer = new unsigned char[ret];
  for (int i = iHeight -1; i > 0; i--)	//Prirazuje se po trech, kvuli subpixelum
  {
   buffer[i*3] = pBuffer[(radek_posun + i*iWidth)*3];	//Red
   buffer[i*3 + 1] = pBuffer[(radek_posun + i*iWidth)*3 + 1];	//Green
   buffer[i*3 + 2] = pBuffer[(radek_posun + i*iWidth)*3 + 2];	//Blue
  }
 }
 return ret;
}


HRESULT Kamera::EnumerateDevices(REFGUID category, IEnumMoniker **ppEnum)
{
    // Create the System Device Enumerator.
    ICreateDevEnum *pDevEnum;
    HRESULT hr = CoCreateInstance(CLSID_SystemDeviceEnum, NULL,  
        CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pDevEnum));

    if (SUCCEEDED(hr))
    {
        // Create an enumerator for the category.
        hr = pDevEnum->CreateClassEnumerator(category, ppEnum, 0);
        if (hr == S_FALSE)
        {
            hr = VFW_E_NOT_FOUND;  // The category is empty. Treat as an error.
        }
        pDevEnum->Release();
    }
    return hr;
}

void Kamera::NastavKamery()
{
// HRESULT hr = NULL;
 
 IAMVideoProcAmp *camera = 0;
 n = 0;

 
 // Create filter graph
	hr = CoCreateInstance(CLSID_FilterGraph, NULL,
			CLSCTX_INPROC_SERVER, IID_IGraphBuilder,
			(void**)&pGraph);
	if (hr != S_OK)
	{
	 error_message("Could not create filter graph", 1);
	 return;
	}
	
	// Create capture graph builder.
	hr = CoCreateInstance(CLSID_CaptureGraphBuilder2, NULL,
			CLSCTX_INPROC_SERVER, IID_ICaptureGraphBuilder2,
			(void **)&pBuilder);
	if (hr != S_OK)
	{
	 error_message("Could not create capture graph builder", 1);
	 return;
	}

	// Attach capture graph builder to graph
	hr = pBuilder->SetFiltergraph(pGraph);
	if (hr != S_OK)
	{
	 error_message("Could not attach capture graph builder to graph", 1);
	 return;
	}

	// Create system device enumerator
	hr = CoCreateInstance(CLSID_SystemDeviceEnum, NULL,
			CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pDevEnum));
	if (hr != S_OK)
	{
	 error_message("Could not crerate system device enumerator", 1);
	 return;
	}

	// Video input device enumerator
	hr = pDevEnum->CreateClassEnumerator(
					CLSID_VideoInputDeviceCategory, &pEnum, 0);
	if (hr != S_OK)
	{
	 error_message("No video devices found", 1);
	 return;
	}
	
	VARIANT var;
	n = 0;
	while(1)
	{
		// Access next device
		hr = pEnum->Next(1, &pMoniker, NULL);
		if (hr == S_OK)
		{
			n++; // increment device count
		}
		else
		{
			if (device_number == 0)
			{
				fprintf(stderr,
					"Video capture device %s not found\n",
					device_name);
			}
			else
			{
				fprintf(stderr,
					"Video capture device %d not found\n",
					device_number);
			}
			error_message("Video capture device not found", 1);
			return;
		}
    if (n >= device_number) break;
	}
	
	

	// Get video input device name
	hr = pMoniker->BindToStorage(0, 0, IID_PPV_ARGS(&pPropBag));
	VariantInit(&var);
	hr = pPropBag->Read(L"FriendlyName", &var, 0);
	fprintf(stderr, "Capture device: %ls\n", var.bstrVal);
	VariantClear(&var);
	
	// Create capture filter and add to graph
	hr = pMoniker->BindToObject(0, 0,
					IID_IBaseFilter, (void**)&pCap);
	if (hr != S_OK)
	{
	 error_message("Could not create capture filter", 1);
	 return;
	}
	
    pCap->QueryInterface(IID_IAMVideoProcAmp, (void**)&camera);

	//Wait for camera to init!!
	int tmp;
	Sleep(1000);
	SetMan->GetSetting(SETT_CAM_BRI, tmp);
    hr = camera->Set(VideoProcAmp_Brightness, tmp, VideoProcAmp_Flags_Manual);
 //   if (hr != S_OK) error_message("Could not set brightness", 1);

	SetMan->GetSetting(SETT_CAM_COM, tmp);
    hr = camera->Set(VideoProcAmp_BacklightCompensation, tmp, VideoProcAmp_Flags_Manual);
 //   if (hr != S_OK) error_message("Could not set backlight compensation", 1);

	SetMan->GetSetting(SETT_CAM_WBA, tmp);
    hr = camera->Set(VideoProcAmp_WhiteBalance, tmp, VideoProcAmp_Flags_Manual);
 //   if (hr != S_OK) error_message("Could not set white balance", 1);

    /*hr = camera->Set(VideoProcAmp_WhiteBalance, 6000, VideoProcAmp_Flags_Manual);
    if (hr != S_OK) error_message("Could not set backlight compensation", 1);
    hr = camera->Set(VideoProcAmp_BacklightCompensation, 0, VideoProcAmp_Flags_Manual);
    if (hr != S_OK) error_message("Could not set backlight compensation", 1);*/

	SetMan->GetSetting(SETT_CAM_GAI, tmp);
    hr = camera->Set(VideoProcAmp_Gain, tmp, VideoProcAmp_Flags_Manual);
 //   if (hr != S_OK) error_message("Could not set gain", 1);

	// Add capture filter to graph
	hr = pGraph->AddFilter(pCap, L"Capture Filter");


	if (hr != S_OK)
	{
	 error_message("Could not add capture filter to graph", 1);
	 return;
	}

	// Create sample grabber filter
	hr = CoCreateInstance(CLSID_SampleGrabber, NULL,
		CLSCTX_INPROC_SERVER, IID_IBaseFilter,
		(void**)&pSampleGrabberFilter);
	if (hr != S_OK)
	{
	 error_message("Could not create Sample Grabber filter", 1);
	 return;
	}
	
	// Query the ISampleGrabber interface of the sample grabber filter
	hr = pSampleGrabberFilter->QueryInterface(
			DexterLib::IID_ISampleGrabber, (void**)&pSampleGrabber);
	if (hr != S_OK)
	{
	 error_message("Could not get ISampleGrabber interface to sample grabber filter", 1);
	 return;
	}
	
	// Enable sample buffering in the sample grabber filter
	hr = pSampleGrabber->SetBufferSamples(TRUE);
	if (hr != S_OK)
	{
	 error_message("Could not enable sample buffering in the sample grabber", 1);
	 return;
	}

	// Set media type in sample grabber filter
	
	ZeroMemory(&mt, sizeof(AM_MEDIA_TYPE));
	mt.majortype = MEDIATYPE_Video;
	mt.subtype = MEDIASUBTYPE_RGB24;
	hr = pSampleGrabber->SetMediaType((DexterLib::_AMMediaType *)&mt);
	if (hr != S_OK)
	{
	 error_message("Could not set media type in sample grabber", 1);
	 return;
	}
	
	// Add sample grabber filter to filter graph
	hr = pGraph->AddFilter(pSampleGrabberFilter, L"SampleGrab");
	if (hr != S_OK)
	{
	 error_message("Could not add Sample Grabber to filter graph", 1);
	 return;
	}

	// Create Null Renderer filter
	hr = CoCreateInstance(CLSID_NullRenderer, NULL,
		CLSCTX_INPROC_SERVER, IID_IBaseFilter,
		(void**)&pNullRenderer);
	if (hr != S_OK)
	{
	 error_message("Could not create Null Renderer filter", 1);
	 return;
	}
	
	// Add Null Renderer filter to filter graph
	hr = pGraph->AddFilter(pNullRenderer, L"NullRender");
	if (hr != S_OK)
	{
	 error_message("Could not add Null Renderer to filter graph", 1);
	 return;
	}
	
	// Connect up the filter graph's capture stream
	hr = pBuilder->RenderStream(
		&PIN_CATEGORY_CAPTURE, &MEDIATYPE_Video,
		pCap,  pSampleGrabberFilter, pNullRenderer);
	if (hr != S_OK)
	{
	 error_message("Could not render capture video stream", 1);
	 return;
	}



	// Get media control interfaces to graph builder object
	hr = pGraph->QueryInterface(IID_IMediaControl,
					(void**)&pMediaControl);
	if (hr != S_OK)
	{
	 error_message("Could not get media control interface", 1);
	 return;
	}
	
	// Run graph
	while(1)
	{
		hr = pMediaControl->Run();
		
		// Hopefully, the return value was S_OK or S_FALSE
		if (hr == S_OK) break; // graph is now running
		if (hr == S_FALSE) continue; // graph still preparing to run
		
		// If the Run function returned something else,
		// there must be a problem
		fprintf(stderr, "Error: %u\n", hr);
		error_message("Could not run filter graph", 1);
		return;
	}
	
	// Wait for specified time delay (if any)
	
	// Grab a sample
	// First, find the required buffer size
	
	while(1)
	{
		// Passing in a NULL pointer signals that we're just checking
		// the required buffer size; not looking for actual data yet.
		hr = pSampleGrabber->GetCurrentBuffer(&buffer_size, NULL);
		
		// Keep trying until buffer_size is set to non-zero value.
		if (hr == S_OK && buffer_size != 0) break;
		
		// If the return value isn't S_OK or VFW_E_WRONG_STATE
		// then something has gone wrong. VFW_E_WRONG_STATE just
		// means that the filter graph is still starting up and
		// no data has arrived yet in the sample grabber filter.
		if (hr != S_OK && hr != VFW_E_WRONG_STATE)
		{
		 error_message("Could not get buffer size", 1);
		 return;
		}
	}



	// Allocate buffer for image
	pBuffer = new char[buffer_size];
	oldBuffer = new char[buffer_size];
	if (!pBuffer || !oldBuffer)
	{
	 error_message("Could not allocate data buffer for image", 1);
	 return;
	}

	
	// Get the media type from the sample grabber filter
	hr = pSampleGrabber->GetConnectedMediaType(
			(DexterLib::_AMMediaType *)&mt);
	if (hr != S_OK)
	{
	 exit_message("Could not get media type", 1);
	 return;
	}
	// Retrieve format information
	
	if ((mt.formattype == FORMAT_VideoInfo) && 
		(mt.cbFormat >= sizeof(VIDEOINFOHEADER)) &&
		(mt.pbFormat != NULL)) 
	{
		// Get video info header structure from media type
		pVih = (VIDEOINFOHEADER*)mt.pbFormat;
		iWidth = pVih->bmiHeader.biWidth;
		iHeight = pVih->bmiHeader.biHeight;
	}
	else 
	{
		error_message("Wrong media type", 1);
		return;
	}
 

 stav = STAV_OK;
}


bool Kamera::KeepFPS()
{
 if (stav != STAV_OK && stav != STAV_ODPOJENO) return false;

 clock_t curClock = clock();
 if (curClock - last_frame_update > FRAME_CLOCK)
 {
  // Retrieve image data from sample grabber buffer
  hr = pSampleGrabber->GetCurrentBuffer(&buffer_size, (long*)pBuffer);
  if (hr != S_OK)
  {
   exit_message("Could not get buffer data from sample grabber", 1);
   return false;
  }
  
  
  //Prohození R a B bytů
  unsigned char rgb = 0;
  unsigned char oldR = 0;
  bool unchanged = true;	//Jestli tohle zůstane true, tak je něco asi špatně
  for (long byte = 0; byte < buffer_size; byte++)
  {
   if (rgb == 0)
   {
    oldR = pBuffer[byte];
    rgb++;
    if (pBuffer[byte +2] != oldBuffer[byte]) unchanged = false;	//Protože oldBuffer je už prohozenej!
   } else if (rgb == 1)
   {
    rgb++;
    if (pBuffer[byte] != oldBuffer[byte]) unchanged = false;
   } else  //rgb == 2
   {
    pBuffer[byte -2] = pBuffer[byte];
    pBuffer[byte] = oldR;
    rgb = 0;
    if (pBuffer[byte] != oldBuffer[byte]) unchanged = false;
   }
  }
  
  //Detekce odpojeny kamery
  if (unchanged)
  {
   if (still_imgs <= ERROR_STILL_IMGS)	//Aby to nepretejkalo
   {
    still_imgs++;
   } else  //Uz je to za hranici
   {
    stav = STAV_ODPOJENO;
    return false;
   }
  }
  else
  {
   still_imgs = 0;
  }
 } else return false;



 stav = STAV_OK;
 memcpy(oldBuffer, pBuffer, buffer_size);
 return true;
}



bool Kamera::Obrazek(wxImage *img)
{

 //Na pravidelne obnovovani bufferu s obrazkem
 KeepFPS();

 if (stav != STAV_OK) return false;

 //Nakresleni cary, ze ktere se bere radek
 if (img_rotation == 0)
 {
  int length = iWidth*3;
  for (int i = 0; i < length; i++)
  {
   pBuffer[radek_posun*iWidth*3 + i] = 255;
  }
 } else if (img_rotation == 1)
 {
  for (int i = 0; i < iHeight; i++)	//Prirazuje se po trech, kvuli subpixelum
  {
   pBuffer[(radek_posun + i*iWidth)*3] = 255;	//Red
   pBuffer[(radek_posun + i*iWidth)*3 + 1] = 255;	//Green
   pBuffer[(radek_posun + i*iWidth)*3 + 2] = 255;	//Blue
  }
 } else if (img_rotation == 2)
 {
  int length = iWidth*3;
  for (int i = length -1; i >= 0; i--)
  {
   pBuffer[radek_posun*iWidth*3 + i] = 255;
  }
 } else if (img_rotation == 3)
 {
  for (int i = iHeight -1; i > 0; i--)	//Prirazuje se po trech, kvuli subpixelum
  {
   pBuffer[(radek_posun + i*iWidth)*3] = 255;	//Red
   pBuffer[(radek_posun + i*iWidth)*3 + 1] = 255;	//Green
   pBuffer[(radek_posun + i*iWidth)*3 + 2] = 255;	//Blue
  }
 }

 img->Destroy();
 img->Create(pVih->bmiHeader.biWidth, pVih->bmiHeader.biHeight, (unsigned char*)pBuffer, true);


 return true;			
}

Kamera::Kamera(SettingsManager *n_SetMan)
{
 SetMan = n_SetMan;
 stav = STAV_NEINICIALIZOVANO;
 still_imgs = iWidth = iHeight = 0;
 last_frame_update = clock();
 pDevEnum = NULL;
 pEnum = NULL;
 pMoniker = NULL;
 pPropBag = NULL;
 pGraph = NULL;
 pBuilder = NULL;
 pCap = NULL;
 pSampleGrabberFilter = NULL;
 pSampleGrabber = NULL;
 pNullRenderer = NULL;
 pMediaControl = NULL;
 pVih = NULL;
 pBuffer = NULL;
 oldBuffer = NULL;
 SetMan->GetSetting(SETT_CAM_N, device_number);
 SetMan->GetSetting(SETT_CAM_ROT, img_rotation);
 SetMan->GetSetting(SETT_LINE_POS, radek_posun);
 NastavKamery();
}

Kamera::~Kamera()
{
 //Stop the graph
 pMediaControl->Stop();
 
	// Free the format block
	if (mt.cbFormat != 0)
	{
		CoTaskMemFree((PVOID)mt.pbFormat);
		mt.cbFormat = 0;
		mt.pbFormat = NULL;
	}
	if (mt.pUnk != NULL)
	{
		// pUnk should not be used.
		mt.pUnk->Release();
		mt.pUnk = NULL;
	}
 // Clean up DirectShow / COM stuff
 if (pBuffer != NULL) delete[] pBuffer;
 if (pBuffer != NULL) delete[] oldBuffer;
 if (pMediaControl != NULL) pMediaControl->Release();	
 if (pNullRenderer != NULL) pNullRenderer->Release();
 if (pSampleGrabber != NULL) pSampleGrabber->Release();
 if (pSampleGrabberFilter != NULL)
 		pSampleGrabberFilter->Release();
 if (pCap != NULL) pCap->Release();
 if (pBuilder != NULL) pBuilder->Release();
 if (pGraph != NULL) pGraph->Release();
 if (pPropBag != NULL) pPropBag->Release();
 if (pMoniker != NULL) pMoniker->Release();
 if (pEnum != NULL) pEnum->Release();
 if (pDevEnum != NULL) pDevEnum->Release();
 CoUninitialize();
}

void Kamera::error_message(const char* error_message, int error)
{
 stav = STAV_CHYBA;
 strcpy(error_buf, error_message);
 exit_message(error_message, error);
}
