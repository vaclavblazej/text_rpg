#include <fstream>
#include <vector>
#include <cstdlib>
#include <iostream>
using namespace std;
#include "creature.h"
#include "creaBP.h"

//------------------------------------------------------------------------CreaBP
CreaBP::CreaBP(string name, string folder)
              :m_Name("NAMELESS")
{
  //atoi(arg.c_str());
  m_HealthLow   = m_HealthHigh   = 0;
  m_StrengthLow = m_StrengthHigh = 0;
  m_AgilityLow  = m_AgilityHigh  = 0;
  m_IntelectLow = m_IntelectHigh = 0;
  m_GoldLow     = m_GoldHigh     = 0;
  m_Flying = m_Haste = m_Trample = m_Vigilance = m_FirstStrike = false;
  string line, arg;
  int min, max;
  folder.append(name);
  ifstream file;
  file.open (folder.c_str(), ios::in);
  file >> line;
  while (file.good()){
         if (line == "name"        ){ file >> arg; m_Name        = arg;}
    else if (line == "flying"      ){ m_Flying      = true;}
    else if (line == "haste"       ){ m_Haste       = true;}
    else if (line == "trample"     ){ m_Trample     = true;}
    else if (line == "vigilance"   ){ m_Vigilance   = true;}
    else if (line == "firststrike" ){ m_FirstStrike = true;}
    else{
      file >> min >> max;
      //getline(file, arg); //new _ was there 5 times
         if (line == "health"  ){ m_HealthLow   = min; m_HealthHigh   = max;}
    else if (line == "strength"){ m_StrengthLow = min; m_StrengthHigh = max;}
    else if (line == "agility" ){ m_AgilityLow  = min; m_AgilityHigh  = max;}
    else if (line == "intelect"){ m_IntelectLow = min; m_IntelectHigh = max;}
    else if (line == "gold"    ){ m_GoldLow     = min; m_GoldHigh     = max;}
    }
    file >> line;
  }
  /*cout << m_Name << endl;
  cout << m_StrengthLow << " - " << m_StrengthHigh << endl;
  cout << m_AgilityLow  << " - " << m_AgilityHigh  << endl;
  cout << m_IntelectLow << " - " << m_IntelectHigh << endl;*/
  file.close();
}
//-----------------------------------------------------------------------~CreaBP
CreaBP::~CreaBP(){}
//---------------------------------------------------------------------------New
Creature *CreaBP::New(int X, int Y, int L) const
{
  return new Creature(m_Name, X, Y, L, rand()%7,
                      m_HealthLow   + rand()%(m_HealthHigh   - m_HealthLow   + 1),
                      m_StrengthLow + rand()%(m_StrengthHigh - m_StrengthLow + 1),
                      m_AgilityLow  + rand()%(m_AgilityHigh  - m_AgilityLow  + 1),
                      m_IntelectLow + rand()%(m_IntelectHigh - m_IntelectLow + 1),
                      m_GoldLow     + rand()%(m_GoldHigh     - m_GoldLow     + 1),
                      m_Flying, m_Haste, m_Trample, m_Vigilance, m_FirstStrike);
}
