//Author: Balas47
//Purpose: The player class will keep track of all player information, including their position in the
//         cave, the number of javelins they own, and how much gold they have in total.

#ifndef PLAYERCLASS
#define PLAYERCLASS

#include<utility>
#include<iostream>
using namespace std;

class Player{

private:
  pair<int, int> m_location; //Current location of the player
  int m_javelins;            //Number of javelins the player has
  int m_gold;                //Number of gold pieces the player has

public:

  Player(); //Default Constructor
  Player(pair<int, int> location, int javelins, int gold); //Overloaded Constructor

  //Setters and getters
  pair<int, int> m_getLocation();
  void m_setLocation(pair<int, int> location);

  int m_getJavelins();
  void m_setJavelins(int javelins);
  void m_adjustJavelins(int change);

  int m_getGold();
  void m_setGold(int gold);
  void m_adjuostGold(int change);

};

#endif /* PLAYERCLASS */
