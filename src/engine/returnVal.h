/*! \file
 */

/*! \class ReturnVal
 * \brief Univerzální návratová hodnota.
 * 
 * Může uchovávat řetězec i celé číslo a při vyžádání hodnoty vrací uloženou hodnotu nebo výchozí hodnotu.
 */
 
/*! \fn ReturnVal::ReturnVal(int )
 * \brief Uloží celé číslo.
 *
 * \param arg Ukládané celé číslo.
 */
 
/*! \fn ReturnVal::ReturnVal(std::string )
 * \brief Uloží řetězec.
 *
 * \param arg Ukládaný řetězec.
 */
 
/*! \fn ReturnVal::getInt() const
 * \return Uložené celé číslo nebo výchozí hodnota.
 */
 
/*! \fn ReturnVal::getStr() const
 * \return Uložený řetězec nebo výchozí hodnota.
 */

#ifndef RETURN_VAL
#define RETURN_VAL
#include <string>

class ReturnVal{
public:
  ReturnVal(int arg):ing(arg),str(""){}
  ReturnVal(std::string arg):ing(2147483647),str(arg){}
  int         getInt() const {return ing;}
  std::string getStr() const {return str;}
private:
  int         ing;
  std::string str;
};

#endif /*RETURN_VAL*/
