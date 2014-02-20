/*! \file
 */
 
/*! \fn evaluate   (std::vector<Expression*> )

 * \brief Vyhodnotí všechny parametry.
 *
 * Pro každý parametr zavolá jednou vyhodnocení a návrat vždy smaže.
 * \param param Vektor parametrů.
 */
 
/*! \fn maximum    (std::vector<Expression*> )
 * \brief Vrátí maximum.
 *
 * Vyhodnotí všechny parametry a zjistí, který z nich vrací nejvyšší číselnou hodnotu. Tuto hodnotu vrátí.
 * \param param Vektor parametrů.
 * \return Nejvyšší hodnota.
 */
 
/*! \fn minimum    (std::vector<Expression*> )
 * \brief Vrátí minimum.
 *
 * Vyhodnotí všechny parametry a zjistí, který z nich vrací nejnišší číselnou hodnotu. Tuto hodnotu vrátí.
 * \param param Vektor parametrů.
 * \return Nejnižší hodnota.
 */
 
/*! \fn suma       (std::vector<Expression*> )
 * \brief Vrátí součet.
 *
 * Vyhodnotí všechny parametry a sečte jejich číselné hodnoty, který z nich vrací nejnišší číselnou hodnotu. Tuto hodnotu vrátí.
 * \param param Vektor parametrů.
 * \return Součet parametrů.
 */
 
/*! \fn average    (std::vector<Expression*> )
 * \brief Vrátí průměr.
 *
 * Vyhodnotí všechny parametry a spočte jejich průměr. Tuto hodnotu vrátí.
 * \param param Vektor parametrů.
 * \return Průměr parametrů.
 */
 
/*! \fn modulo     (std::vector<Expression*> )
 * \brief Vrátí modulo prvního vůči ostatním.
 *
 * Vyhodnotí první parametr a použije operátor modulo vůči všem ostatním parametrům. Tuto hodnotu vrátí.
 * \param param Vektor parametrů.
 * \return Modulo prvního parametru.
 */
 
/*! \fn getString  (std::vector<Expression*> )
 * \brief Zadání řetězce uživatelem.
 *
 * Nechá uživatele zadat řetězec, který pak vrátí.
 * \param param Vektor parametrů. (nevyužité).
 * \return Získaný řetězec.
 */
 
/*! \fn getInteger (std::vector<Expression*> )
 * \brief Zadání čísla uživatelem.
 *
 * Nechá uživatele zadat celé číslo, které pak vrátí.
 * \param param Vektor parametrů. (nevyužité)
 * \return Získané celé číslo.
 */
 
/*! \fn condition  (std::vector<Expression*> )
 * \brief Podmínka (IF)
 *
 * Vyhodnotí číselnou hodnotu prvního parametru a pokud je nenulová, tak vyhodnotí a vrátí druhý parametr. Pokud je nulová, tak vyhodnotí a vrátí třetí parametr. Funguje pouze pro dva nebo tři parametry.
 * \param param Vektor parametrů.
 * \return Druhý nebo třetí parametr. NULL pro špatný počet parametrů.
 */
 
/*! \fn options    (std::vector<Expression*> )
 * \brief Podmínka (SWITCH)
 *
 * Vyhodnotí číselnou hodnotu prvního parametru a dále vyhodnotí pouze parametr, jehož poředí odpovídá získanému číslu zvětšeného o jedna. (tj pro získanou 0 vyhodnotí 1. parametr, pro 1 -> 2., atd.). Vyhodnocené hodnoty parametru vrací.
 * \param param Vektor parametrů.
 * \return Hodnoty z vyhodnoceného parametru.
 */
 
/*! \fn equal      (std::vector<Expression*> )
 * \brief Operátor =
 *
 * Porovná dva parametry a vrátí 1 pro shodu a 0 pro neshodu. Funguje pouza pro dva parametry.
 * \param param Vektor parametrů.
 * \return Hodnota 1 pro shodu a 0 pro neshodu. NULL pro špatný počet parametrů.
 */
 
/*! \fn great      (std::vector<Expression*> )
 * \brief Operátor >
 *
 * Porovná dva parametry a vrátí 1 když je první větší než druhý a 0 pro neshodu.
 * \param param Vektor parametrů. NULL pro špatný počet parametrů.
 * \return Hodnota 1 pro větší a 0 pro menší rovno. NULL pro špatný počet parametrů.
 */
 
/*! \fn randomArg  (std::vector<Expression*> )
 * \brief Náhodný návrat.
 *
 * Náhodně vybere jeden z parametrů vyhodnotí ho a vrátí jeho hodnotu.
 * \param param Vektor parametrů.
 * \return Náhodně vybraný parametr.
 */
 
/*! \fn customArg  (std::vector<Expression*> )
 * \brief Vybraný návrat.
 *
 * Vyhodnotí všechny parametry a vrátí parametr, který je na pozici návratové hodnoty prvního parametru.
 * \param param Vektor parametrů.
 * \return Hodnoty vybraného parametru.
 */
 
/*! \fn print      (std::vector<Expression*> )
 * \brief Vypsání na výstup.
 *
 * Vyhodnotí všechny parametry a vypíše jejich návratové hodnoty.
 * \param param Vektor parametrů.
 * \return Vypsaný řetězec.
 */
 
/*! \fn cycle      (std::vector<Expression*> )
 * \brief Cyklus (WHILE)
 *
 * Vyhodnotí první parametr, pokud je nulový, tak se vyhodnotí všechny ostatní parametry a cyklus se opakuje. Vrací počet opakování.
 *
 * Použití se nedoporučuje tam, kde se dá nahradit změnou kontextu menu viz dokumentace Menu.
 * \param param Vektor parametrů.
 * \return Počet opekování cyklu.
 */
 
/*! \fn repeat     (std::vector<Expression*> )
 * \brief Cylkus (FOR)
 *
 * Vyhodnotí první parametr, poté se vyhodnotí všechny ostatní parametry tolikrát, kolik byla hodnota prvního parametru. Vrátí počet opakování.
 * \param param Vektor parametrů.
 * \return Počet opakování cyklu.
 */

#ifndef SCRIPT
#define SCRIPT
typedef ReturnVal *(*funcPtr)(std::vector<Expression*> param);

Expression *addScript(std::string name, std::vector <Expression*> args);
ReturnVal  *evaluate   (std::vector<Expression*> param);
ReturnVal  *maximum    (std::vector<Expression*> param);
ReturnVal  *minimum    (std::vector<Expression*> param);
ReturnVal  *suma       (std::vector<Expression*> param);
ReturnVal  *average    (std::vector<Expression*> param);
ReturnVal  *modulo     (std::vector<Expression*> param);
ReturnVal  *getString  (std::vector<Expression*> param);
ReturnVal  *getInteger (std::vector<Expression*> param);
ReturnVal  *condition  (std::vector<Expression*> param);
ReturnVal  *options    (std::vector<Expression*> param);
ReturnVal  *equal      (std::vector<Expression*> param);
ReturnVal  *great      (std::vector<Expression*> param);
ReturnVal  *randomArg  (std::vector<Expression*> param);
ReturnVal  *customArg  (std::vector<Expression*> param);
ReturnVal  *print      (std::vector<Expression*> param);
ReturnVal  *cycle      (std::vector<Expression*> param);
ReturnVal  *repeat     (std::vector<Expression*> param);

#endif /*SCRIPT*/
