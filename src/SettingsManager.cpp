#include "../include/SettingsManager.hpp"

unsigned int CountLines(std::ifstream &file)
{
 file.seekg(std::ifstream::beg);
 std::string s;
 unsigned int ret = 0;
 while (!file.eof())
 {
  std::getline(file, s);
  ret++;
 }
 return ret;
}

unsigned int GoToLine(std::fstream &file, unsigned int line)
{
 file.seekg(std::fstream::beg);
 std::string s;
 for (unsigned int i = 0; i < line; ++i)
 {
  std::getline(file, s);
  //file.ignore((long long)(std::numeric_limits<std::streamsize>::max), '\n');
 }
 return int(file.tellg());
}

bool SettingsManager::GetSetting(unsigned int id, int &set)
{
/*
 switch (id)
 {
 case SETT_CAM_N: set = cislo_kamery.value; break;
 case SETT_LINE_POS: set = otoceni_kamery.value; break;
 case SETT_CAM_ROT: set = cislo_kamery.value; break;
 case SETT_CAM_EXP: set = cislo_kamery.value; break;
 case SETT_CAM_BRI: set = cislo_kamery.value; break;
 case SETT_CAM_COM: set = cislo_kamery.value; break;
 case SETT_CAM_WBA: set = cislo_kamery.value; break;
 case SETT_CAM_GAI: set = cislo_kamery.value; break;
 default: exit_message("Inexistent setting asked for.", 2); return false;
 }
 */
 if (id < S_SETS_LAST)
 {
  set = s_sets[id].value;
  return true;
 } else if (id < U_SETS_LAST)
 {
  set = u_sets[id - S_SETS_LAST].value;
  return true;
 } else
 {
  return false;
 }
}

int SettingsManager::GetSetting(unsigned int id)
{
/*
 switch (id)
 {
 case SETT_CAM_N: set = cislo_kamery.value; break;
 case SETT_LINE_POS: set = otoceni_kamery.value; break;
 case SETT_CAM_ROT: set = cislo_kamery.value; break;
 case SETT_CAM_EXP: set = cislo_kamery.value; break;
 case SETT_CAM_BRI: set = cislo_kamery.value; break;
 case SETT_CAM_COM: set = cislo_kamery.value; break;
 case SETT_CAM_WBA: set = cislo_kamery.value; break;
 case SETT_CAM_GAI: set = cislo_kamery.value; break;
 default: exit_message("Inexistent setting asked for.", 2); return false;
 }
 */
 if (id < S_SETS_LAST)
 {
  return s_sets[id].value;
 } else if (id < U_SETS_LAST)
 {
  return u_sets[id - S_SETS_LAST].value;
 } else
 {
  return -1;
 }
}

void SettingsManager::SetSetting(unsigned int id, int set)
{
 if (id < S_SETS_LAST)
 {
  s_sets[id].value = set;
  //Rovnou se i ulozi
  //RewriteSetting(s_sets[id]);
 } else if (id < U_SETS_LAST)
 {
  u_sets[id - S_SETS_LAST].value = set;
 }
}

bool SettingsManager::LoadSettingsFile()
{
 std::ifstream ifile("settings.bin");
 std::string s;
 std::getline(ifile, s);	//preskocit prvni radek
 for (int i = 0; i < S_N_SETS; i++)
 {
  
  ifile >> s_sets[i].value;
 }


	/*
  SettingsFile >> cislo_kamery.value;
  SettingsFile >> pozice_vstupni_cary_kamery.value;
  SettingsFile >> otoceni_kamery.value;
  SettingsFile >> expozice_kamery.value;
  SettingsFile >> svetlost_kamery.value;
  SettingsFile >> kompenzace_kamery.value;
  SettingsFile >> white_balance_kamery.value;
  SettingsFile >> gain_kamery.value;
  */

 return true;
}

bool SettingsManager::OpenSettingsFile()
{
 std::ifstream ifile("settings.bin");
 if (ifile && ifile.good())
 {
  unsigned line_count = CountLines(ifile);
  ifile.close();
  //Neshoduje se pocet radku s poctem nastaveni
  if (line_count != S_N_SETS +2)
  {
   return false;
  }

  //SettingsFile.open("settings.bin", std::fstream::in | std::fstream::out);
  return true;
 } else
 {
  ifile.close();
  return false;
 }
}

bool SettingsManager::CreateSettingsFile()
{
 std::ofstream ofile("settings.bin", std::ofstream::trunc);
 if (ofile && ofile.good())
 {
  ofile << VERSION_STR << '\n';
  for (int i = 0; i < S_N_SETS; i++)
  {
   ofile << s_sets[i].value << '\n';
   //WriteSetting(s_sets[i]);
  }
  ofile << "Spektrometr";
  ofile.close();
	 /*
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
  */

	 /*
  WriteSetting(cislo_kamery);
  WriteSetting(pozice_vstupni_cary_kamery);
  WriteSetting(otoceni_kamery);
  WriteSetting(expozice_kamery);
  WriteSetting(svetlost_kamery);
  WriteSetting(kompenzace_kamery);
  WriteSetting(white_balance_kamery);
  WriteSetting(gain_kamery);
  */

  return true;
 } else
 {
  return false;
 }
}

bool SettingsManager::RewriteSetting(setting &set)
{
 /*if (set.fpos > S_N_SETS +2)
  return false;
 static std::fstream file;
 static std::string buffer[S_N_SETS +2];
 static int filepos, fileend;

 file.open("settings.bin", std::ios::out | std::ios::in);

 for (unsigned int i = 0; i < S_N_SETS +2; i++)
 {
  if (i == set.fpos)
  {
   filepos = file.tellg();	//zapamatuju si misto v souboru
  }
  std::getline(file, buffer[i]);
  if (i != S_N_SETS +1)	//Za poslednim radkem uz \n nebude
   buffer[i] += '\n';
 }

 //Nahrazeni radku
 std::stringstream a;
 a << (set.value);
 buffer[set.fpos] = a.str() + std::string("\n");

 //Zapsani do souboru
 file.seekp(filepos, std::fstream::beg);
 for (int i = set.fpos; i < S_N_SETS +2; i++)
  file << buffer[i];

 //Kontrola, jestli neprebyvaji nejaka data
 filepos = file.tellp();
 file.seekp(0, std::fstream::end);
 fileend = file.tellp();
 file.seekp(filepos, std::fstream::beg);
 file.(filepos - file.tellp())*/
 return true;
}

bool SettingsManager::WriteSetting(setting &set)
{
/*
 SettingsFile.seekp(GoToLine(SettingsFile, set.fpos), std::fstream::beg);
 int a = SettingsFile.tellp();*/
 //SettingsFile << set.value << '\n';
 //return SettingsFile.good();
	return false;
}


SettingsManager::SettingsManager(void)
{
 stav = 0;

 //Inicializace ukladanych nastaveni na defaultni hodnoty
 for (int i = 0; i < S_N_SETS; i++)
 {
  s_sets[i].fpos = i+1;
  switch (i)
  {
   case SETT_CAM_N: s_sets[i].value = 1;	break;
   case SETT_CAM_ROT: s_sets[i].value = 3;	break;
   case SETT_CAM_EXP: s_sets[i].value = 0;	break;
   case SETT_CAM_BRI: s_sets[i].value = 0;	break;
   case SETT_CAM_COM: s_sets[i].value = 0;	break;
   case SETT_CAM_WBA: s_sets[i].value = 6000;	break;
   case SETT_CAM_GAI: s_sets[i].value = 0;	break;
   case SETT_LINE_POS: s_sets[i].value = 359;	break;
   case SETT_LINE_RED: s_sets[i].value = 25;	break;
   case SETT_LINE_UV: s_sets[i].value = 416;	break;
   case SETT_MARKER_UV: s_sets[i].value = 400; break;
   case SETT_DIS_TYPE: s_sets[i].value = Z_GRAF; break;
   case SETT_UV_TRESHOLD: s_sets[i].value = 20; break;
  }
 }
 
 //Inicializace neukladanych nastaveni
 for (int set = S_SETS_LAST, i = 0; set < U_SETS_LAST; set++, i++)
 {
  switch (set)
  {
   case SETT_GEN_CFG: u_sets[i].value = 0;	break;
   case SETT_CAM_NMAX: u_sets[i].value = 0;	break;
  }
 }

 //Pokus o otevreni souboru s ulozenymi nastavenimi
 if (!OpenSettingsFile())
 {
  //Pokus o vytvoreni souboru
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

 //Nacteni ulozenych nastaveni
 if (stav == 2)
 {
  LoadSettingsFile();
 }
}


SettingsManager::~SettingsManager()
{
 //Ulozeni nastaveni
 std::ofstream ofile("settings.bin", std::fstream::trunc);
 ofile << VERSION_STR << '\n';
 for (int i = 0; i < S_N_SETS; i++)
 {
  ofile << s_sets[i].value << '\n';
 }
 ofile << "Spektrometr";
 ofile.close();
 /*if (SettingsFile.is_open())
 {
  SettingsFile.close();
 }*/
}

