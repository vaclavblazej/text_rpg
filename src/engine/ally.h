/*! \file
 */

/*! \class Ally
 * \brief Spřátelená jednotka.
 * 
 * Uchovává informace o spřátelené jednotce se kterou může hráč interagovat.
 */
 
/*! \fn Ally::Ally(std::string , int , int , int , bool );
 * \brief Vytvoří spřátelenou jednotku.
 *
 * Vytvoří spřátelenou jednotku. Nastaví jméno, informace o jejím umístění a jestli jednotka může zadávat úkoly hráči.
 * \param name Jméno spřátelené jednotky.
 * \param X Souřadnice umístění jednotky.
 * \param Y Souřadnice umístění jednotky.
 * \param L Vrstva, ve které jednotka je.
 * \param quests Pokud je True, tak může jednotka zadávat úkoly.
 */
 
/*! \fn Ally::Paint() const
 * \brief Vykreslí jednotku.
 *
 * Vykreslí reprezentaci jednotky na výstup daný parametrem. Vykreslí barevně nebo černobíle podle parametru color.
 */
 
/*! \fn Ally::Course() const
 * \brief Zjistí směnný kurz.
 *
 * Zjistí směnný kurz spřátelené jednotky v procentech.
 * \return Směnný kurz.
 */
 
/*! \fn Ally::GetInfo(string &name, int &X, int &Y, int &L, int &Q) const
 * \brief Zjistí informace o jednotce.
 *
 * Zjistí lokaci jednotky a její postavení vůči úkolům.
 * \param name 
 * \param X Souřadnice spřátelené jednotky.
 * \param Y Souřadnice spřátelené jednotky.
 * \param L Vrstva, ve které jednotka je.
 * \param Q Zjistí stav vzhledem o dávání úkolu. Je rovno 0=nedává, 1=dává nebo 2=očekává odevzdání.
 */
 
/*! \fn World::Save(std::ofstream &) const
 * \brief Uloží svět.
 *
 * Uloží svět do souboru.
 * \param output Výstupní soubur
 */
 
/*! \fn World::Load(std::ifstream &)
 * \brief Načte svět.
 *
 * Načte svět ze souboru.
 * \param input Vstupní soubur
 */
 
#ifndef ALLY
#define ALLY
class Item;
class Quest;
#include "unit.h"
class Ally : public Unit{
public:
  Ally(std::string name = "UNKNOWN", int X = 0, int Y = 0, int L = 0,
       bool quests = false);
  ~Ally();
  int Paint() const;
  int Course() const;
  void GetInfo(string &name, int &X, int &Y, int &L, int &Q) const;
  void Save(std::ofstream &output) const;
  void Load(std::ifstream &input);
private:
};

#endif /*ALLY*/
