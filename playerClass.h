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
  int m_javelins;            //Number of javelins the player has
  int m_gold;                //Number of gold pieces the player has

public:

  Player(); //Default Constructor
  Player(pair<int, int> location, int javelins, int gold); //Overloaded Constructor

  pair<int, int> m_location; //Current location of the player

  //Setters and getters
  pair<int, int> getLocation();
  void setLocation(pair<int, int> location);

  int getJavelins();
  void setJavelins(int javelins);
  void adjustJavelins(int change);

  int getGold();
  void setGold(int gold);
  void adjustGold(int change);

};

#endif /* PLAYERCLASS */
