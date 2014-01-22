#pragma once

#include <iostream>
#include <fstream>
#include "include/debug_exit.hpp"
#include "include/BasicDrawPane.hpp"

#define VERSION "0.9-22.1.2014"

enum SAVED_SETS
{
 SETT_CAM_N,	//cislo zarizeni
 SETT_CAM_ROT,	//otoceni
 SETT_CAM_EXP,	//expozice
 SETT_CAM_BRI,	//svetlost
 SETT_CAM_COM,	//kompenzace backlightu
 SETT_CAM_WBA,	//white balance
 SETT_CAM_GAI,	//gain
 SETT_LINE_POS,	//pozice cary
 SETT_DIS_TYPE,	//typ zobrazeni - graf/obraz
 S_SETS_LAST,		//toto musi byt vzdy predposledni prvek!
 S_N_SETS = S_SETS_LAST	//pocet ukladanych nastaveni
};

enum UNSAVED_SETS
{
 SETT_GEN_CFG = S_SETS_LAST,	//config mode set
 SETT_CAM_NMAX,	//pocet kamer, pripojenych k pocitaci
 U_SETS_LAST,		//toto musi byt vzdy predposledni posledni prvek!
 U_N_SETS = U_SETS_LAST - S_SETS_LAST	//pocet neukladanych nastaveni
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
	//std::fstream SettingsFile;
	bool CreateSettingsFile();
	bool OpenSettingsFile();
	bool LoadSettingsFile();
	bool WriteSetting(setting &set);
	bool RewriteSetting(setting &set);

	//Setting variables
	setting s_sets[S_N_SETS];	//ukladana nastaveni
	setting u_sets[U_N_SETS];	//neukladana nastaveni
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

	//bool GetSetting(setting &set);
	bool GetSetting(unsigned int id, int &set);
	int GetSetting(unsigned int id);
	//void SetSetting(setting set);
	void SetSetting(unsigned int id, int set);
};

