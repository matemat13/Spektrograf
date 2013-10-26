#pragma once

#include <iostream>
#include <fstream>
#include "include/debug_exit.hpp"

#define N_SETTINGS 8

enum
{
 SETT_CAM_N,	//cislo zarizeni
 SETT_LINE_POS,	//pozice cary
 SETT_CAM_ROT,	//otoceni
 SETT_CAM_EXP,	//expozice
 SETT_CAM_BRI,	//svetlost
 SETT_CAM_COM,	//kompenzace
 SETT_CAM_WBA,	//white balance
 SETT_CAM_GAI	//gain
};

struct setting
{
 unsigned int fpos;
 int value;
 //int id;
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
	setting sets[N_SETTINGS];
	/*
	setting cislo_kamery;
	setting pozice_vstupni_cary_kamery;
	setting otoceni_kamery;
	setting expozice_kamery;
	setting svetlost_kamery;
	setting kompenzace_kamery;
	setting white_balance_kamery;
	setting gain_kamery;
	*/
public:
	SettingsManager(void);
	~SettingsManager(void);

	bool GetSetting(setting &set);
	bool GetSetting(int id, int &set);
	void SetSetting(setting &set);
	void SetSetting(int id, int &set);
};

