/*! \file
 */

/*! \class Scenario
 * \brief Poskytuje rozhraní skriptování.
 * 
 * Uchovává informace o hře a poskytuje rozhraní mezi naskriptovanými funkcemi a herní implementací.
 */
 
/*! \fn Scenario::Scenario (string )
 * \param gameDirectory Nastaví potřebná metadata pro načítání dat.
 */
 
/*! \fn Scenario::LoadMethod (string , vector<Expression*> &)
 * \brief Vrátí metodu odpovídající názvu.
 *
 * Pokud název odpovídá názvu metody ve skriptovacím jazyce, tak vrátí objekt, který je schopen metodu zavolat s danými parametry.
 * \param name Název funkce ve scriptovacím jazyce.
 * \param atrs Parametry předávané metodě při zavolání.
 * \return Objekt zařizující obsluho volání metody s argumenty.
 */

#ifndef SCENARIO
#define SCENARIO
typedef pair<std::vector<string>, std::vector<string> > t_Planes;
class World;
class Item;
class Creature;
class Ally;
class Battle;
class Container;
class Scenario {
public:
  Scenario(std::string gameDirectory);
  ~Scenario();
  Expression* LoadMethod (string name, vector<Expression*> &atrs);
private:
  ReturnVal *Set           (vector<Expression*> atr = vector<Expression*>());
  ReturnVal *Increase      (vector<Expression*> atr = vector<Expression*>());
  ReturnVal *ResetVars     (vector<Expression*> atr = vector<Expression*>());
  ReturnVal *Print         (vector<Expression*> atr = vector<Expression*>());
  ReturnVal *CreateWorld   (vector<Expression*> atr = vector<Expression*>());
  ReturnVal *DestroyWorld  (vector<Expression*> atr = vector<Expression*>());
  ReturnVal *CreateChar    (vector<Expression*> atr = vector<Expression*>());
  ReturnVal *DestroyChar   (vector<Expression*> atr = vector<Expression*>());
  ReturnVal *GiveItem      (vector<Expression*> atr = vector<Expression*>());
  ReturnVal *GiveCustItem  (vector<Expression*> atr = vector<Expression*>());
  ReturnVal *RemoveItem    (vector<Expression*> atr = vector<Expression*>());
  ReturnVal *ListItems     (vector<Expression*> atr = vector<Expression*>());
  ReturnVal *DelItem       (vector<Expression*> atr = vector<Expression*>());
  ReturnVal *ListSaves     (vector<Expression*> atr = vector<Expression*>());
  ReturnVal *SaveScenario  (vector<Expression*> atr = vector<Expression*>());
  ReturnVal *LoadScenario  (vector<Expression*> atr = vector<Expression*>());
  ReturnVal *PrintWorld    (vector<Expression*> atr = vector<Expression*>());
  ReturnVal *DiscoverWorld (vector<Expression*> atr = vector<Expression*>());
  ReturnVal *PrintStats    (vector<Expression*> atr = vector<Expression*>());
  ReturnVal *PrintXY       (vector<Expression*> atr = vector<Expression*>());
  ReturnVal *FightEnemy    (vector<Expression*> atr = vector<Expression*>());
  ReturnVal *MovePlayer    (vector<Expression*> atr = vector<Expression*>());
  ReturnVal *PortPlayer    (vector<Expression*> atr = vector<Expression*>());
  ReturnVal *CreateQuest   (vector<Expression*> atr = vector<Expression*>());
  ReturnVal *ListQuest     (vector<Expression*> atr = vector<Expression*>());
  ReturnVal *CheckQuests   (vector<Expression*> atr = vector<Expression*>());
  ReturnVal *EnterEnc      (vector<Expression*> atr = vector<Expression*>());
  ReturnVal *PrintFight    (vector<Expression*> atr = vector<Expression*>());
  ReturnVal *FightAttack   (vector<Expression*> atr = vector<Expression*>());
  ReturnVal *ShowLoot      (vector<Expression*> atr = vector<Expression*>());
  ReturnVal *TakeLoot      (vector<Expression*> atr = vector<Expression*>());
  ReturnVal *FlushLoot     (vector<Expression*> atr = vector<Expression*>());
  ReturnVal *Buy           (vector<Expression*> atr = vector<Expression*>());
  ReturnVal *Sell          (vector<Expression*> atr = vector<Expression*>());
  ReturnVal *FrCourse      (vector<Expression*> atr = vector<Expression*>());
  ReturnVal *Goods         (vector<Expression*> atr = vector<Expression*>());
  ReturnVal *TakeGold      (vector<Expression*> atr = vector<Expression*>());
  ReturnVal *Craft         (vector<Expression*> atr = vector<Expression*>());
  ReturnVal *Quit          (vector<Expression*> atr = vector<Expression*>());
  World      *m_World;
  Creature   *m_Character;
  Ally       *ally;
  int m_Width, m_Height;
  std::string saveDir;
  std::string creaDir;
  std::string itemDir;
  std::string mapsDir;
  std::vector <Creature*> encounter;
  std::vector <Ally*>     alliesMet;
  std::vector <Item*>     m_Loot;
  vector<t_Planes> m_Planes;
  map <std::string, int>  m_Variables;
  map <std::string, int>  m_Options;
  Container *m_Quests;
  Battle *m_Battle;
};

#endif /*SCENARIO*/
