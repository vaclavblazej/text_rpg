/*! \file
 */

/*! \class Item
 * \brief Předmět.
 * 
 * Uchovává informace a poskytuje rozhraní práce s předmětem. 
 */
 
/*! \fn Item::AddRef()
 * \brief Přidá referenci.
 */
 
/*! \fn Item::RemRef()
 * \brief Odebere referenci.
 */
 
/*! \fn Item::GetCost()
 * \return Vrací cenu předmětu.
 */
 
/*! \fn Item::GetInfo(int &, int &, int &, int &, bool &) const
 * \brief Zjistí informace.
 * 
 * Získá do parametrů hodnoty z předmětu.
 * \param hp Přidané životy.
 * \param str Přidaná síla.
 * \param agi Přidaná obratnost.
 * \param inl Přidaná inteligence.
 * \param range Jeslti je na dálku.
 */
 
/*! \fn Item::Print() const;
 * \brief Vypíše informace o předmětu.
 *
 * Vypíše na výstup formátované informace o oředmětu.
 */
 
/*! \fn Item::PrintCompact(int ) const;
 * \brief Vypíše informace o předmětu.
 *
 * Vypíše na výstup natěsno formátované informace o oředmětu.
 * \param course Procentuelní kurz ceny předmětu. Při nule se cena nevypíše. Sto je výchozí kurz.
 */
 
/*! \fn Item::Save(std::ofstream &) const
 * \brief Uloží předmět.
 *
 * Uloží předmět do souboru.
 * \param output Výstupní soubur
 */
 
/*! \fn Item::Load(std::ifstream &)
 * \brief Načte předmět.
 *
 * Načte předmět ze souboru.
 * \param input Vstupní soubur
 */
 
#ifndef ITEM
#define ITEM
typedef pair<string, int> t_Done;
class Item {
public:
  Item(std::string name = "", vector<t_Done> attrs = vector<t_Done>());
  void AddRef(){m_Ref++;}
  void RemRef(){if (--m_Ref == 0) delete this;}
  int  GetCost() const;
  void GetInfo(int &hp) const;
  void GetInfo(bool &range) const;
  void GetInfo(string &name) const;
  void GetInfo(int &hp, int &str, int &agi, int &inl) const;
  void GetInfo(int &hp, int &str, int &agi, int &inl, bool &range) const;
  void Print() const;
  void PrintCompact(int course = 0) const;
  void Save(std::ofstream &output) const;
  void Load(std::ifstream &input);
private:
  int         m_Cost;
  std::string m_Name;
  int         m_Ref;
  vector<t_Done> m_Attrs;
};

#endif /*ITEM*/
