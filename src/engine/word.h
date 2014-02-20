/*! \file
 */

/*! \class Word
 * \brief Slovo pro scriptování.
 * 
 * Přes tento objekt je poskytnuta možnost využívat textové řetězce ve scriptování.
 */
 
/*! \fn Word::Word(std::string )
 * \brief Uložení slova.
 *
 * Uloží slovo, které se dále využívá, při scriptovacím procesu.
 * \param word Uložené slovo.
 */
 
/*! \fn Word::getValue() const
 * \return Uložené slovo.
 */

#ifndef WORD
#define WORD
#include <string>
#include "expression.h"
class Word : public Expression{
public:
  Word(std::string word);
  virtual ~Word();
  virtual ReturnVal *getValue() const;
private:
  std::string m_Word;
};

#endif /*WORD*/
