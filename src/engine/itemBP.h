/*! \file
 */

/*! \class ItemBP
 * \brief Vzor předmětu.
 * 
 * Slouží k uchování obecných informací o předmětu, ze kterých je možné daný předmět vygenerovat.
 */
 
/*! \fn ItemBP::ItemBP(std::string , std::string )
 * \brief Vytvoří vzor předmětu.
 *
 * Vytvoří vzor pro vytváření předmětů.
 * \param name Název předmětu.
 * \param folder Složka ve které se informace o předmětu nachází.
 */
 
/*! \fn ItemBP::New() const
 * \brief Vytvoří předmět.
 *
 * Vytvoří a vrátí předmět podle vzoru. 
 * \return Vytvořený předmět.
 */
 
#ifndef ITEMBP
#define ITEMBP
typedef vector<pair<string, string> > t_Type;
typedef pair<int, int>                t_Duo;
typedef pair<string, t_Duo>           t_Elem;
typedef pair<string, int>             t_Done;
class Item;
class ItemBP {
public:
  ItemBP(std::string name, std::string fileName, t_Type attrs);
  ~ItemBP();
  Item *New() const;
private:
  std::string m_Name;
  vector<t_Elem> m_Attrs;
  int m_HealthLow, m_HealthHigh;
  int m_StrengthLow, m_StrengthHigh;
  int m_AgilityLow, m_AgilityHigh;
  int m_IntelectLow, m_IntelectHigh;
  bool m_Range;
};

#endif /*ITEMBP*/
