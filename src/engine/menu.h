/*! \file
 */

/*! \class Menu
 * \brief Správa menu.
 * 
 * Provádí hlavní cyklus programu, kde se opakovaně čeká vstup uživatele.
 * 
 * Poskytuje rozhraní správy uživatelského menu pro scriptování.
 */
 
/*! \fn Menu::Menu(std::string, std::string )
 * \brief Uloží metadata.
 *
 * \param gameDirectory Složka se hrou.
 * \param menuDirectory Složka se meny.
 */
 
/*! \fn Menu::Good() const
 * \return Jestli se všechno načetlo v pořádku.
 */
 
/*! \fn Menu::Run(const char * );
 * \brief Hlavní funkce programu.
 *
 * Obsahuje v sobě cyklus, který opakoveně čeká na uživatelův vstup
 * \param commandFileName Název souboru prvního načteného menu.
 */
 
#ifndef MENU
#define MENU
#include <vector>
#include <map>
class Expression;
class Scenario;
class ReturnVal;
class Menu{
public:
  Menu(std::string gameDirectory, string menuDirectory);
  ~Menu();
  bool Good() const;
  void Run(const char * commandFileName);
private:
  bool good;
  void Simmilar() const;
  void CommandList() const;
  Expression *LoadMethod (string name, vector<Expression*> &atrs);
  Expression* LoadFunction(istringstream & is, char &next, int &len, std::string &errMsg);
  ReturnVal *Commands        (vector<Expression*> atr = vector<Expression*>());
  ReturnVal *PrintFile       (vector<Expression*> atr = vector<Expression*>());
  ReturnVal *LoadMenu        (vector<Expression*> atr = vector<Expression*>());
  ReturnVal *LoadPushMenu    (vector<Expression*> atr = vector<Expression*>());
  ReturnVal *ExitMenu        (vector<Expression*> atr = vector<Expression*>());
  bool Reserved(string line);
  std::string PWD;
  std::string DIR;
  std::string MENU_DIR;
  Scenario *m_Scene;
  std::vector<const char *> lifo;
  std::map<std::string, Expression*> alias;
  std::map<std::string, Expression*> expressions;
};

#endif /*MENU*/
