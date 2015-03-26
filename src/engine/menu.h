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
#include <string>
class Expression;
class Scenario;
class ReturnVal;
class Menu{
public:
  Menu(std::string gameDirectory, std::string menuDirectory);
  ~Menu();
  bool Good() const;
  void Run(const std::string commandFileName);
private:
  bool good;
  void Simmilar() const;
  void CommandList() const;
  Expression *LoadMethod (std::string name, std::vector<Expression*> &atrs);
  Expression* LoadFunction(std::istringstream & is, char &next, int &len, std::string &errMsg);
  ReturnVal *Commands     (std::vector<Expression*> atr = std::vector<Expression*>());
  ReturnVal *PrintFile    (std::vector<Expression*> atr = std::vector<Expression*>());
  ReturnVal *LoadMenu     (std::vector<Expression*> atr = std::vector<Expression*>());
  ReturnVal *LoadPushMenu (std::vector<Expression*> atr = std::vector<Expression*>());
  ReturnVal *ExitMenu     (std::vector<Expression*> atr = std::vector<Expression*>());
  bool Reserved(std::string line);
  std::string PWD;
  std::string DIR;
  std::string MENU_DIR;
  Scenario *m_Scene;
  std::vector<const char *> lifo;
  std::map<std::string, Expression*> alias;
  std::map<std::string, Expression*> expressions;
};

#endif /*MENU*/
