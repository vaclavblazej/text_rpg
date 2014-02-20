/*! \file
 */

/*! \class CreaBP
 * \brief Vzor jednotky.
 * 
 * Slouží k uchování obecných informací o jednotce, ze kterých je možné danou jednotku vygenerovat.
 */
 
/*! \fn CreaBP::CreaBP(std::string , std::string )
 * \brief Vytvoří vzor jednotky.
 *
 * Vytvoří vzor pro vytváření předmětů.
 * \param name Jméno jednotky.
 * \param folder Složka ve které se informace o jednotce nachází.
 */
 
/*! \fn CreaBP::New(int , int , int ) const
 * \brief Vytvoří jednotku.
 *
 * Vytvoří a vrátí jednotku podle vzoru. 
 * \param X Souřadnice, na které se jednotka vygeneruje.
 * \param Y Souřadnice, na které se jednotka vygeneruje.
 * \param L Vrstva, do které se jednotka vygeneruje.
 * \return Vytvořená jednotka.
 */
 
#ifndef CREABP
#define CREABP
class Creature;
class CreaBP {
public:
  CreaBP(std::string name, std::string folder);
  ~CreaBP();
  Creature *New(int X, int Y, int L) const;
private:
  std::string m_Name;
  int m_HealthLow,   m_HealthHigh;
  int m_StrengthLow, m_StrengthHigh;
  int m_AgilityLow,  m_AgilityHigh;
  int m_IntelectLow, m_IntelectHigh;
  int m_GoldLow,     m_GoldHigh;
  bool m_Flying, m_Haste, m_Trample, m_Vigilance, m_FirstStrike;
};

#endif /*CREABP*/
