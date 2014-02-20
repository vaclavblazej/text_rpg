#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <vector>
using namespace std;
#include "item.h"
#include "itemBP.h"

//------------------------------------------------------------------------ItemBP
ItemBP::ItemBP(string name, string fileName, t_Type attrs)
              :m_Name("NAMELESS"),
               m_HealthLow  (0), m_HealthHigh  (0),
               m_StrengthLow(0), m_StrengthHigh(0),
               m_AgilityLow (0), m_AgilityHigh (0),
               m_IntelectLow(0), m_IntelectHigh(0),
               m_Range(false)
  
{
  string line, arg, comm;
  int min, max;
  //cout << name << endl;
  ifstream file;
  file.open (fileName.c_str(), ios::in);
  if (!file.good()){
    cout << "Error: Item blueprint file not found!" << endl;
  }else{
    getline(file, line);
    while (file.good()){
      min = max = 1;
      istringstream is(line);
      getline(is, comm, '=');
      if (comm == "name"    ){is >> arg;        m_Name        = arg;}
      for (t_Type::const_iterator it = attrs.begin(); it != attrs.end(); ++it){
        if (comm == (*it).second){
          t_Duo tmp(min, max);
          m_Attrs.push_back(t_Elem(comm, tmp));
          //cout << comm << " " << min << " " << max << endl;
          t_Elem test = m_Attrs[m_Attrs.size()-1];
          //cout << test.first << " " << test.second.first << " " << test.second.second << endl;
        }
      }
      getline(file, line);
    }
    file.close();
  }
}
//-----------------------------------------------------------------------~ItemBP
ItemBP::~ItemBP(){}
//---------------------------------------------------------------------------New
Item *ItemBP::New() const
{
  vector<t_Done> tmp;
  for (vector<t_Elem>::const_iterator it = m_Attrs.begin();
       it != m_Attrs.end(); ++it){
    t_Duo range = (*it).second;
    tmp.push_back(t_Done((*it).first,
                  range.first + rand()%(range.second - range.first + 1)));
    //cout << tmp[tmp.size()-1].first << " " << tmp[tmp.size()-1].second << endl;
  }
  Item * it = new Item(m_Name, tmp);
  //it->PrintCompact();
  //cout << endl;
  return it;
}
