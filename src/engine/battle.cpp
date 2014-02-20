#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;
#include "item.h"
#include "creature.h"
#include "battle.h"
//------------------------------------------------------------------------Battle
Battle::Battle(Creature *first, Creature *second)
              :m_First(first), m_Second(second),
               m_FirstHp  (m_First->GetHp()),
               m_SecondHp (m_Second->GetHp()),
               FirstCrit  (false),
               FirstBlock (false),
               FirstDodge (false),
               SecondCrit (false),
               SecondBlock(false),
               SecondDodge(false),
               m_Advantage(0)
{
  first->GetAbilities(FRange, FFlying, FHaste, FTrample, FVigilance, FFirststrike);
  second->GetAbilities(SRange, SFlying, SHaste, STrample, SVigilance, SFirststrike);
  if (FHaste && !SHaste  && !SFlying && !SVigilance && !SFirststrike) m_Advantage++;
  if (SHaste && !FHaste  && !FFlying && !FVigilance && !FFirststrike) m_Advantage--;
  if (FRange && !SRange  && !SHaste  && !SFlying    && !SFirststrike) m_Advantage++;
  if (SRange && !FRange  && !FHaste  && !FFlying    && !FFirststrike) m_Advantage--;
  if (FTrample && !STrample && !SHaste && !SVigilance)                m_Advantage++;
  if (STrample && !FTrample && !FHaste && !FVigilance)                m_Advantage--;
  if (FFirststrike && !SFirststrike  && !SVigilance)                  m_Advantage++;
  if (SFirststrike && !FFirststrike  && !FVigilance)                  m_Advantage--;
  if (FFlying  && !SFlying  && !SRange)                               m_Advantage++;
  if (SFlying  && !FFlying  && !FRange)                               m_Advantage--;
  /*FHaste     -> výhoda!, vyruší FRange, FHaste a FTrample
  FRange       -> výhoda!, vyruší FRange a FFlying
  FFlying      -> výhoda!, vyruší FFlying, FRange, FHaste a FTrample
  FTrample     -> výhoda!, vyruší FTrample
  FVigilance   ->          vyruší FTrample, FHaste a FFirststrike
  FFirststrike -> výhoda!, vyruší FFirststrike a FHaste*/
}
//-----------------------------------------------------------------------~Battle
Battle::~Battle()
{
  m_First  = NULL;
  m_Second = NULL;
}
//-------------------------------------------------------------------------Fight
int Battle::Fight(int crit, int block, int dodge, bool flee)
{
  //hero attack
  if (rand()%100 < crit)  FirstCrit  = true;
  if (rand()%100 < block) FirstBlock = true;
  if (rand()%100 < dodge) FirstDodge = true;
  
  if (!flee){
    int yourDmg = m_First->GetDmg();
    if (FirstCrit)   yourDmg  = 1.4*yourDmg + 1;
    if (SecondBlock) yourDmg /= 3;
    if (SecondDodge) yourDmg  = 0;
    yourDmg    += m_Advantage;
    m_SecondHp -= (yourDmg>=0)?yourDmg:0;
    cout << "you dealt "   << ((yourDmg>=0)?yourDmg:0)
         << "dmg to enemy" << (FirstCrit   ? " (critical)" : "")
                           << (SecondBlock ? " (blocked)" : "")
                           << (SecondDodge ? " (dodged)" : "") << endl;
  }
  FirstCrit   = false;
  SecondBlock = false;
  SecondDodge = false;
  //enemy attack
  if (rand()%100 < 30) SecondCrit  = true;
  if (rand()%100 < 45) SecondBlock = true;
  if (rand()%100 < 25) SecondDodge = true;
  int enemyDmg = m_Second->GetDmg();
  if (SecondCrit) enemyDmg  = 1.4*enemyDmg + 1;
  if (FirstBlock) enemyDmg /= 2;
  if (FirstDodge) enemyDmg  = 0;
  enemyDmg  -= m_Advantage;
  m_FirstHp -= (enemyDmg>=0)?enemyDmg:0;
  cout << "enemy dealt " << ((enemyDmg>=0)?enemyDmg:0)
       << "dmg to you"   << (SecondCrit ? " (critical)" : "")
                         << (FirstBlock ? " (blocked)" : "")
                         << (FirstDodge ? " (dodged)" : "") << endl;
  SecondCrit = false;
  FirstBlock = false;
  FirstDodge = false;
  //state check
  cout << "your health: "   << m_FirstHp   << ", "
       << "enemys health: " << m_SecondHp << endl;
  if (m_FirstHp <= 0){
    return 1;
  }
  if (m_SecondHp <= 0){
    return 2;
  }
  if (flee) return 3;
  return 0;
}
