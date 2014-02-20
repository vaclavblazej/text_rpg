#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
using namespace std;
#include "menu.h"

//==========================================================================MAIN
int main (int argc, char *argv[]){
  bool editor = false;
  //file control...
  string gameDirectory = "./", menumenu = "", playmenu = "", editmenu = "";
  {
    ifstream input;
    input.open ("./src/config.txt", ios::in);
    if (!input.good()){
      cout << "ERROR: Config file is missing!" << endl;
      return 0;
    }else{
      cout << ">> Loading config file..." << endl;
      string command, parameter;
      getline(input, command, '=');
      while(input.good()){
        getline(input, parameter);
        if (command == "GAME_DIRECTORY") gameDirectory.append(parameter).append("/");
        getline(input, command, '=');
      }
      input.close();
    }
    if (gameDirectory == "./"){
      cout << "ERROR: Game directory not defined! (in ./src/config.txt)" << endl;
      return 0;
    }
    cout << ">> Config file ok" << endl;
    string structureFile = gameDirectory;
    structureFile.append("structure.txt");
    input.open (structureFile.c_str(), ios::in);
    string command;
    getline(input, command, '=');
    bool item, crea, menu, save, play, edit;
    item = crea = menu = save = play = edit = false;
    if (!input.good()){
      cout << "ERROR: Structure file is missing!" << endl;
      return 0;
    }
    while(input.good()){
      if (command == "ITEM_DIRECTORY")     item = true;
      if (command == "CREATURE_DIRECTORY") crea = true;
      if (command == "MENU_DIRECTORY"){    menu = true; input >> menumenu;}
      if (command == "SAVE_DIRECTORY")     save = true;
      if (command == "START_PLAY"){        play = true; input >> playmenu;}
      if (command == "START_EDIT"){        edit = true; input >> editmenu;}
      getline(input, command);
      getline(input, command, '=');
    }
    input.close();
    if(item == false || crea == false || menu == false ||
       save == false || play == false || edit == false){
      cout << "ERROR: Directory with";
      if (item == false) cout << " items";
      if (crea == false) cout << " creatures";
      if (menu == false) cout << " menu";
      if (save == false) cout << " saves";
      if (play == false) cout << " play_menu";
      if (edit == false) cout << " edit_menu";
      cout << " was not defined in structure.txt file in game directory!" << endl;
      return 0;
    }
    cout << ">> Structure file ok" << endl;
    string scriptFile = gameDirectory;
    scriptFile.append("scripts.txt");
    input.open (scriptFile.c_str(), ios::in);
    if (!input.good()){
      cout << "ERROR: Script file is missing!" << endl;
      return 0;
    }
    input.close();
    cout << ">> Script file ok" << endl;
  }
  if(argc > 1){
    string help = "--help";
    string seditor = "-e";
    if (argv[1] == help){
      cout << "Usage: " << argv[0] << "[option]" << endl;
      ifstream input;
      input.open ("./src/helpfile.txt", ios::in);
      if(input.good()){
        string line;
        getline(input, line);
        while(input.good()){
          cout << line << endl;
          getline(input, line);
        }
        input.close();
      }else{
        cout << "ERROR: Help file not found!" << endl;
      }
      return 0;
    }else if (argv[1] == seditor){
      cout << "edit mode:" << endl;
      editor = true;
    }else{
      cout << "Usage: " << argv[0] << "[option]" << endl;
      cout << argv[0] << ": error: no such option: -" << argv[1] << endl;
      cout << "Use `" << argv[0] << " --help' for a complete list of options." << endl;
      return 0;
    }
  }
  string tmp = gameDirectory;
  tmp.append(menumenu).append("/");
  Menu mainMenu(gameDirectory, tmp);
  if(!mainMenu.Good()) return 0;
  cout << ">> Loading scripts ok" << endl;
  if(editor){
    mainMenu.Run(editmenu.c_str());
  }else{
    mainMenu.Run(playmenu.c_str());
  }
	return 0;
}
