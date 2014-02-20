/*! \file
 */
 
/*! \class Battle
 * \brief Informace a rozhraní bitvy.
 * 
 * Ukládá obě strany bitvy a umožňuje výměnu poškození.
 */
 
/*! \fn Battle::Battle(Creature *, Creature *)
 * \brief Vytvoří bitvu.
 *
 * Zjistí a uloží veškeré informace, potřebné k vedení bitvy.
 * \param first První participant boje.
 * \param second Druhý participant boje.
 */
 
/*! \fn Battle::Fight(int , int , int , bool )
 * \brief Výměna poškození.
 *
 * Výměna poškození mezi participanty boje
 * \param crit Procentuální pravděpodobnost kritického poškození
 * \param block Procentuální pravděpodobnost blokování příchozího poškození.
 * \param dodge Procentuální pravděpodobnost vyhnutí se příchozímu poškození.
 * \param flee True - první participant se pokusí o útěk z bitvy. False - Nic se neděje.
 * \return Vrací 0, pokud se situace nezměnila. Vrací 1, pokud druhá strana vyhrála. Vrací 2, pokud první strana vyhráka. Vrací 3, pro úspěšný útěk.
 */

#ifndef BATTLE
#define BATTLE
class Creature;
class Battle{
public:
  Battle(Creature *first, Creature *second);
  ~Battle();
  int Fight(int crit, int block, int dodge, bool flee);
  Creature *m_First;  //!< První participant boje.
  Creature *m_Second; //!< Druhý participant boje.
private:
  int m_FirstHp;
  int m_SecondHp;
  bool FirstCrit,  FirstBlock,  FirstDodge;
  bool SecondCrit, SecondBlock, SecondDodge;
  bool FRange, FFlying, FHaste, FTrample, FVigilance, FFirststrike;
  bool SRange, SFlying, SHaste, STrample, SVigilance, SFirststrike;
  std::vector <Item*>     m_Loot;
  int m_Advantage;
};

#endif /*BATTLE*/
