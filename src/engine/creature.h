/*! \file
 */
 
/*! \class Creature
 * \brief Běžná jednotka.
 * 
 * Reprezentuje jak hráče, tak znepřátelené jednotky. Uchovává veškeré informace o jednotce tj. předměty, vlastnosti, aj.
 */
 
/*! \fn Creature::Creature(std::string name ,
           int , int , int , int , int , int , int , int , int ,
           bool , bool , bool , bool , bool );
 * \brief Vytvoří jednotku.
 *
 * Vytvoří jednotku s danými vlastnostmi.
 * \param name Jméno jednotky.
 * \param X Vodorovná pozice jednotky na mapě.
 * \param Y Svislá pozice jednotky na mapě.
 * \param L Vrstva ve které jednotka je.
 * \param m_class Povolání jednotky.
 * \param hp Počet životů.
 * \param str Síla jednotky.
 * \param agl Obratnost jednotky.
 * \param inl Inteligence jednotky.
 * \param gold Množství zlata.
 * \param fly Ovlivňuje chování v bitvě.
 * \param hst Ovlivňuje chování v bitvě.
 * \param tpl Ovlivňuje chování v bitvě.
 * \param vig Ovlivňuje chování v bitvě.
 * \param frs Ovlivňuje chování v bitvě.
 */
 
/*! \fn Creature::MoveBy(int , int , int , int )
 * \brief Změna pozice hráče.
 *
 * Změní pozici hráče na mapě a zarovná tuto tak, aby hráč nevyšel z mapy, ale vyšel na druhém konci.
 * \param X Změna pozice ve vodorovné ose.
 * \param Y Změna pozice svislé ose.
 * \param cutX Definuje šířku pro zarovnání.
 * \param cutY Definuje výšku pro zarovnání.
 */
 
/*! \fn Creature::MoveTo(int , int )
 * \brief Nastavení pozice hráče.
 *
 * Nastaví pozici hráče na danou hodnotu.
 * \param X Nastavení ve vodorovné ose.
 * \param Y Nastavení ve svislé ose.
 */
 
/*! \fn Creature::GetAbilities(bool &, bool &, bool &, bool &, bool &, bool &) const;
 * \brief Zjistí vlastnisti jednotky.
 *
 * Zjistí jaké vlastnosti jednotka má. Tyto vlastnosti ovlivňují průběh soubojů.
 * \param Rng Nastaví na hodnotu podle valstnosti střelba.
 * \param Fly Nastaví na hodnotu podle valstnosti létání.
 * \param Hst Nastaví na hodnotu podle valstnosti spěch.
 * \param Tpl Nastaví na hodnotu podle valstnosti průraz.
 * \param Vig Nastaví na hodnotu podle valstnosti ostražitost.
 * \param Frs Nastaví na hodnotu podle valstnosti první rána.
 */
 
/*! \fn Creature::GetHp() const
 * \return Počet životů jednotky.
 */
 
/*! \fn Creature::GetDmg() const
 * \return Běžné poškození, které jednotka uděluje.
 */
 
/*! \fn Creature::GetBlock() const
 * \return mohutnost obrany jednotky proti poškození.
 */
 
/*! \fn Creature::PrintStats() const
 * \brief Vypíše informace o jednotce.
 *
 * Vypíše podrobné informace o jednotce vč. jména, poškození, síly, atd.
 */
 
/*! \fn Creature::Save(std::ofstream &) const
 * \brief Uloží jednotku.
 *
 * Uloží jednotku do souboru.
 * \param output Výstupní soubur
 */
 
/*! \fn Creature::Load(std::ifstream &)
 * \brief Načte jednotku.
 *
 * Načte jednotku ze souboru.
 * \param input Vstupní soubur
 */

#ifndef CREATURE
#define CREATURE
class Item;
#include "unit.h"
class Creature : public Unit {
public:
  Creature(std::string name = "UNKNOWN",
           int X = 0, int Y = 0, int L = 0,
           int m_class = 0, int hp = 0,
           int str = 0, int agl = 0, int inl = 0, int gold = 0,
           bool fly = false, bool hst = false, bool tpl = false,
           bool vig = false, bool frs = false);
  ~Creature();
  void  MoveBy(int X, int Y, int cutX = 2147483647, int cutY = 2147483647);
  void  MoveTo(int X, int Y);
  void  GetAbilities(bool &Rng, bool &Fly, bool &Hst,
                     bool &Tpl, bool &Vig, bool &Frs) const;
  int   GetHp() const;
  int   GetDmg() const;
  int   GetBlock() const;
  void  PrintStats() const;
  void  Save(std::ofstream &output) const;
  void  Load(std::ifstream &input);
private:
  int         m_Class;
  int         m_CurHp;
  int         m_Health;
  int         m_Strength;
  int         m_Agility;
  int         m_Intelect;
  bool        m_Flying;
  bool        m_Haste;
  bool        m_Trample;
  bool        m_Vigilance;
  bool        m_FirstStrike;
  //bool        m_DoubleStrike;
};

#endif /*CREATURE*/
