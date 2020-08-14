
#ifndef GAMEDRIVER
#define GAMEDRIVER

#include <iostream>
#include <utility>
#include "playerClass.h"
#include "caveClass.h"
using namespace std;

class Game{

 private:

  //Player and Cave members
  Player m_player;
  Cave  m_cave;

  //Start/Exit location
  pair<int, int> m_exit;
  
 public:
  Game(); //Default Constructor

  void menu(); //Controls the menu section of the game
  void store(); //Controls the store where the player can buy javelins
  int cave(); //Controls what happens when the player is in the cave
  void printBoard(); //Print out current location in cave, and what the player perceives 

};

#endif //GAMEDRIVER
