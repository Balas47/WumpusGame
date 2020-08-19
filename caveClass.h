//Author: Balas47
//Purpose: This class will contain all of the information on the Wumpus cave. That is, it will
//         keep track of the location of Wumpus, the pits, and the pieces of gold. It will also
//         check what the player is adjacent to/with or not. i.e. whether the player is next to
//         Wumpus, in the same location as Wumpus, or not. 


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
  int m_numPits;                 //Total number of pits
  vector<pair<int, int>> m_gold; //All gold locations
  int m_allGold;                 //Amount of gold available
  int m_size;                    //Size of the cave, which will be an nXn square

public:

  Cave(); //Default Constructor

  void reset(); //Reset the cave when needed
  void nextLevel(); //Generate the cave as a higher level

  pair<int, int> getWumpus(); //Get the location of the Wumpus
  int getSize(); //Get the size of the cave
  int checkAdj(pair<int, int> player); //Check what the player is adjacent to
  void adjustGold(int change); //Adjust the amount of gold available
  int getGold(); //Get the amount of gold available
  bool getDeath(); //Check whether the Wumpus is dead or not

  void randomWumpus(); //Randomize the location of the Wumpus
  void randomPits(); //Randomize the location of the pits
  void randomGold(); //Randomize the location of the gold
  
  
};

#endif /* CAVECLASS */
