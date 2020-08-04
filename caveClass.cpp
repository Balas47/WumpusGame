#include"caveClass.h"
#include <cstdlib>
#include<ctime>
using namespace std;

//Default Constructor
Cave::Cave(){

  m_size = 10; //Start out with a 10X10 cave.
  
  m_randomWumpus();
  m_death = false;

  m_allGold = 400; //Start out with 400 gold pieces available
  m_randomGold();

  m_numPits = 1;
  m_randomPits(); //Start out with one pit
}

//Reset the cave when needed
//When the cave resets, it becomes a default cave, so this function
//is exactly like the default constructor.
void Cave::m_reset(){
  
  m_size = 10;

  m_randomWumpus();
  m_death = false;

  m_allGold = 400;
  m_randomGold();
  
  m_numPits = 1;
  m_randomPits();
  
}

//Generate the cave at a higher level
//When the player goes "down" a level, twice the gold is available, but there
//is also twice the number of pits, and the cave becomes twice as large
void Cave::m_nextLevel(){

  m_size *= 2;

  m_randomWumpus();
  m_death = false;

  m_allGold *= 2;
  m_randomGold();

  m_numPits *= 2;
  m_randomPits();

}

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

void Cave::m_randomWumpus(){
  //Initialize random seed
  srand(time(NULL));

  //The coordinates of Wumpus are randomly chosen
  m_wumpus.first = rand() % m_size;
  m_wumpus.second = rand() % m_size;
} //Randomize the location of the Wumpus

void Cave::m_randomPits(){
  //Initialize random seed
  srand(time(NULL));

  //Temporary pair to be put into list of pits
  pair<int, int> temp;
  
  //For all of the pits in the cave, randomize its location
  for(int i=0;i<m_numPits;i++){
    temp.first = rand() % m_size;
    temp.second = rand() % m_size;
    m_pits.push_back(temp);
  }

} //Randomize the location of the pits

void Cave::m_randomGold(){
  //Initialize random seed
  srand(time(NULL));

  //Each pile of gold will have 100 pieces
  int numPiles = m_allGold / 100;

  //Temporary pair to be put into list of gold piles
  pair<int, int> temp;
  
  //Gold piles will be randomly placed
  for(int i=0;i<numPiles;i++){
    temp.first = rand() % m_size;
    temp.second = rand() % m_size;
    m_gold.push_back(temp);
  }
  
} //Randomize the location of the gold
