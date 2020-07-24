
#ifndef CAVECLASS
#define CAVECLASS

#include<utility>
#include<vector>
#include<iostream>
using namespace std;

class Cave{

private:

  pair<int,int> m_wumpus;        //Location of wumpus
  bool m_death;                  //Whether or not the wumpus is dead
  vector<pair<int, int>> m_pits; //Location of all the pits
  vector<pair<int, int>> m_gold; //All gold locations
  int m_allGold;                 //Amount of gold available

public:

  Cave(); //Default Constructor

  void m_reset(); //Reset the cave

  pair<int, int> m_getWumpus(); //Get Wumpus' location
  int m_checkAdj(pair<int, int> player); //Check what the player is adjacent to
  void m_adjustGold(int change); //Adjust the amount of gold available
  int m_getGold(); //Get the amount of gold available
  bool m_getDeath(); //Check whether the Wumpus is dead or not

  void m_randomWumpus(); //Randomize the location of the Wumpus
  void m_randomPits(int amount); //Randomize the location of the pits
  void m_randomGold(); //Randomize the location of the gold
  
  
};

#endif /* CAVECLASS */
