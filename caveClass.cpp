#include"caveClass.h"
using namespace std;

//Default Constructor
Cave::Cave(){
  m_randomWumpus();
  m_death = false;
  
  m_allGold = 1000;
  m_randomGold();

  m_randomPits(1);
}

//Reset the cave
void Cave::m_reset(){}

pair<int, int> Cave::m_getWumpus(){
  return m_wumpus;
}//Get Wumpus' location

int Cave::m_checkAdj(pair<int, int> player){
  return 0;
} //Check what the player is adjacent to

void Cave::m_adjustGold(int change){
  m_allGold += change;
} //Adjust the amount of gold available

int Cave::m_getGold(){
  return m_allGold;
} //Get the amount of gold available

bool Cave::m_getDeath(){
  return m_death;
} //Check whether the Wumpus is dead or not

void Cave::m_randomWumpus(){} //Randomize the location of the Wumpus

void Cave::m_randomPits(int amount){} //Randomize the location of the pits

void Cave::m_randomGold(){} //Randomize the location of the gold
