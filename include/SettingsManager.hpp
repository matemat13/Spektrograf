#pragma once

#include <iostream>
#include <fstream>

#define SETT_CAM_N 0;	//cislo zarizeni
#define SETT_LINE_POS 1;	//pozice cary
#define SETT_CAM_ROT 2;	//otoceni
#define SETT_CAM_EXP 3;	//expozice
#define SETT_CAM_BRI 4;	//svetlost
#define SETT_CAM_COM 5;	//kompenzace
#define SETT_CAM_WBA 6;	//white balance
#define SETT_CAM_GAI 7;	//gain

struct setting
{
 unsigned int fpos;
 int value;
 int id;
};

class SettingsManager
{
private:
	int stav;
	std::fstream SettingsFile;
	bool CreateSettingsFile();
	bool OpenSettingsFile();
	bool LoadSettingsFile();
	bool WriteSetting(setting &set);

	//Setting variables
	setting cislo_kamery;
	setting pozice_vstupni_cary_kamery;
	setting otoceni_kamery;
	setting expozice_kamery;
	setting svetlost_kamery;
	setting kompenzace_kamery;
	setting white_balance_kamery;
	setting gain_kamery;
public:
	SettingsManager(void);
	~SettingsManager(void);


};

