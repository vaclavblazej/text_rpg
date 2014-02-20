/*! \file
 */
 
/*! \class Unit
 * \brief Třída reprezentující jednotku.
 * 
 * Třída uchovává veškeré informace o jednotce tj. předměty, vlastnosti, aj.
 */
 
/*! \fn Unit::Unit(std::string name , int , int , int , int );
 * \brief Vytvoří jednotku.
 *
 * Vytvoří jednotku se záznamem o její pozici, zlatě a předmětech.
 * \param name Jméno jednotky.
 * \param X Vodorovná pozice jednotky na mapě.
 * \param Y Svislá pozice jednotky na mapě.
 * \param L Vrstva ve které jednotka je.
 * \param gold Množství zlata.
 */
 
/*! \fn Unit::GetItems() const
 * \return Všechny předměty, které jednotka má.
 */
 
/*! \fn Unit::GetInfo(string &name, int &X, int &, int &) const
 * \brief Zjistí informace o jednotce.
 *
 * Zjistí jméno a přesnou pozici jednotky.
 * \param name Jméno jednotky
 * \param X Se nastaví na vodorovnou pozici jednotky.
 * \param Y Se nastaví na svislou pozici jednotky.
 * \param L Se nastaví na vrstvu, ve které jednotka je.
 */
 
/*! \overload Unit::GetInfo(int &X, int &Y, int &L) const
 *
 */

/*! \fn Unit::GiveItem(Item *)
 * \brief Dá jednotce předmět.
 *
 * Předá jednotce předmět.
 * \param item Předaný předmět.
 * \return Počet předmětů, které jednotka má.
 */
 
/*! \fn Unit::DelItem(int )
 * \brief Odebrání předmět.
 *
 * Jednotce odebere předmět na daném indexu. Předmět je zničen.
 * \param index Index odebíraného předmětu.
 * \return Jestli byl item odebrán.
 */
 
/*! \fn Unit::ChangeGold(int );
 * \brief Změna množství zlata.
 *
 * Pokud je to možné, tak změní množství zlata, které jednotka má o danou hodnotu.
 * \param amount Množstevní změna zlata.
 * \return Jestli bylo množství zlata změněno. False při pokusu o odebrání zlata, které jednotka nemá.
 */
 
/*! \fn Unit::HandItem(int )
 * \brief Předání předmětu.
 *
 * Odebere jednotce předmět a předá ho návratvou hodnotou. Předmět není zničen.
 * \param index Index
 * \return Odebraný předmět
 */
 
/*! \fn Unit::PrintItems(int ) const
 * \brief Vytisknout předměty.
 *
 * V kompaktrní formě vytiskne na obrazovku všechny předměty, které jednotka má.
 * \param cost Kurz tisknutého předmětu. Ovlivní tisknutou cenu. 0 cenu vypne.
 */
 
/*! \fn Unit::Save(std::ofstream &) const
 * \brief Uloží jednotku.
 *
 * Uloží jednotku do souboru.
 * \param output Výstupní soubur
 */
 
/*! \fn Unit::Load(std::ifstream &)
 * \brief Načte jednotku.
 *
 * Načte jednotku ze souboru.
 * \param input Vstupní soubur
 */

#ifndef UNIT
#define UNIT
class Item;
class Unit {
public:
  Unit(std::string name = "UNKNOWN",
       int X = 0, int Y = 0,
       int L = 0, int gold = 0);
  ~Unit();
  vector <Item*> GetItems() const;
  void  GetInfo(string &name, int &X, int &Y, int &L) const;
  void  GetInfo(int &X, int &Y, int &L) const;
  bool  IsItem(string str);
  bool  DelByName(string str);
  Item *HandItem(int index);
  void  PrintItems(int cost = 0) const;
  int   GiveItem(Item *item);
  bool  DelItem(int index);
  bool  ChangeGold(int amount);
  void  Save(std::ofstream &output) const;
  void  Load(std::ifstream &input);
protected:
  std::string m_Name; //<! Jméno jednotky
  int         m_X;    //<! Vodorovná souřadnice jednotky
  int         m_Y;    //<! Svislá souřadnice jednotky
  int         m_L;    //<! Vrstevní souřadnice jednotky
  int         m_Gold; //<! Zlato jednotky
  std::vector <Item*> m_Items;
  //bool        m_DoubleStrike;
};

#endif /*UNIT*/
