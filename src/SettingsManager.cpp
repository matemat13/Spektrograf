#include "../include/SettingsManager.hpp"
bool SettingsManager::LoadSettingsFile()
{

  SettingsFile >> cislo_kamery.value;
  SettingsFile >> pozice_vstupni_cary_kamery.value;
  SettingsFile >> otoceni_kamery.value;
  SettingsFile >> expozice_kamery.value;
  SettingsFile >> svetlost_kamery.value;
  SettingsFile >> kompenzace_kamery.value;
  SettingsFile >> white_balance_kamery.value;
  SettingsFile >> gain_kamery.value;

 return true;
}

bool SettingsManager::OpenSettingsFile()
{
 std::ifstream ifile("settings.bin");
 if (ifile.good())
 {
  ifile.close();

  SettingsFile.open("settings.bin", std::ios::in | std::ios::out | std::ios::binary);
  return true;
 } else
 {
  ifile.close();
  return false;
 }
}

bool SettingsManager::CreateSettingsFile()
{
 SettingsFile.open("settings.bin", std::ios::in | std::ios::out | std::ios::binary | std::ios::trunc);
 if (SettingsFile.good())
 {
  cislo_kamery.fpos = 0*sizeof(setting().value);
  cislo_kamery.value = 0;
  cislo_kamery.id = SETT_CAM_N;
  pozice_vstupni_cary_kamery.fpos = 1*sizeof(setting().value);
  pozice_vstupni_cary_kamery.value = 0;
  pozice_vstupni_cary_kamery.id = SETT_LINE_POS;
  otoceni_kamery.fpos = 2*sizeof(setting().value);
  otoceni_kamery.value = 0;
  otoceni_kamery.id = SETT_CAM_ROT;
  expozice_kamery.fpos = 3*sizeof(setting().value);
  expozice_kamery.value = 0;
  expozice_kamery.id = SETT_CAM_EXP;
  svetlost_kamery.fpos = 4*sizeof(setting().value);
  svetlost_kamery.value = 0;
  svetlost_kamery.id = SETT_CAM_BRI;
  kompenzace_kamery.fpos = 5*sizeof(setting().value);
  kompenzace_kamery.value = 0;
  kompenzace_kamery.id = SETT_CAM_COM;
  white_balance_kamery.fpos = 6*sizeof(setting().value);
  white_balance_kamery.value = 6500;
  white_balance_kamery.id = SETT_CAM_WBA;
  gain_kamery.fpos = 7*sizeof(setting().value);
  gain_kamery.value = 0;
  gain_kamery.id = SETT_CAM_GAI;

  WriteSetting(cislo_kamery);
  WriteSetting(pozice_vstupni_cary_kamery);
  WriteSetting(otoceni_kamery);
  WriteSetting(expozice_kamery);
  WriteSetting(svetlost_kamery);
  WriteSetting(kompenzace_kamery);
  WriteSetting(white_balance_kamery);
  WriteSetting(gain_kamery);

  return true;
 } else
 {
  return false;
 }
}

bool SettingsManager::WriteSetting(setting &set)
{
 SettingsFile.seekp(set.fpos);
 SettingsFile << set.value;
 return SettingsFile.good();
}


SettingsManager::SettingsManager(void)
{
 stav = 0;
 if (!OpenSettingsFile())
 {
  if (!CreateSettingsFile())
  {
   stav = -1;	//Failed to open and failed to create settings file
  } else
  {
   stav = 1;	//Settings file was created
  }
 } else
 {
  stav = 2;		//Settings file exists
 }

 if (stav == 2)
 {
  LoadSettingsFile();
 }
}


SettingsManager::~SettingsManager(void)
{
 if (SettingsFile.is_open())
 {
  SettingsFile.close();
 }
}
