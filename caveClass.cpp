#include"caveClass.h"
#include <cstdlib>
#include<ctime>
using namespace std;

//Information concerning return value for checkAdj()
const int ADJWUMPUS = 100; //Adjacent to the wumpus
const int WWUMPUS   = 200; //With the wumpus

const int ADJPIT = 10; //Adjacent to a pit
const int WPIT   = 20; //With a pit

const int ADJGOLD = 1; //Adjacent to gold
const int WGOLD   = 2; //With a gold pile

const int EMPTY = 0; //Not adjacent to anything

//Default Constructor
Cave::Cave(){

  m_size = 10; //Start out with a 10X10 cave.
  
  randomWumpus();
  m_death = false;

  m_allGold = 400; //Start out with 400 gold pieces available
  randomGold();

  m_numPits = 1;
  randomPits(); //Start out with one pit
}

//Reset the cave when needed
//When the cave resets, it becomes a default cave, so this function
//is exactly like the default constructor.
void Cave::reset(){
  
  m_size = 10;

  randomWumpus();
  m_death = false;

  m_allGold = 400;
  randomGold();
  
  m_numPits = 1;
  randomPits();
  
}

//Generate the cave at a higher level
//When the player goes "down" a level, twice the gold is available, but there
//is also twice the number of pits, and the cave becomes twice as large
void Cave::nextLevel(){

  //Everything doubles going to a higher level
  
  m_size *= 2;

  randomWumpus();
  m_death = false;

  m_allGold *= 2;
  randomGold();

  m_numPits *= 2;
  randomPits();

}

pair<int, int> Cave::getWumpus(){
  return m_wumpus;
} //Get the location of the Wumpus


int Cave::getSize(){
  return m_size;
}//Get the size of the cave

int Cave::checkAdj(pair<int, int> player){
					    
  int checks = EMPTY;

  //Check if the player is next to the Wumpus
  if(player.first == m_wumpus.first){

    if(player.second == m_wumpus.second){
      return WWUMPUS; //Player is with the wumpus

      //Player is on the same row, so now we check if the player is on a column adjacent
      //to the Wumpus.
    }else if((player.second == m_wumpus.second + 1) | (player.second == m_wumpus.second - 1)){
      checks += ADJWUMPUS; //Player is adjacent to the wumpus

    }
    
  }else if(player.second == m_wumpus.second){

    //Player is on the same column, so now we check if the player is on a row adjacent
    //to the Wumpus
    if((player.first == m_wumpus.first + 1) | (player.first == m_wumpus.first - 1)){
      checks += ADJWUMPUS; //Player is adjacent to the wumpus

    }
  }

  //Check if the player is next to a pit, using an iterator for the pits
  for(vector<pair<int, int>>::iterator it=m_pits.begin(); it!=m_pits.end(); ++it){
    
    //Check if the player is in the same row as a pit
    if(player.first == it->first){
      
      if(player.second == it->second){
	return WPIT; //Player is in a pit
	
	//Check if the player is also on a column adjacent to the pit
      }else if((player.second == it->second + 1) | (player.second == it->second - 1)){
	checks += ADJPIT; //Player is adjacent to a pit
	break;
      }
      
      //Check if the player is in the same column as a pit
    }else if(player.second == it->second){
      
      //Check if the player is in the same row as a pit
      if((player.first == it->first + 1) | (player.first == it->first - 1)){
	checks += ADJPIT; //Player is adjacent to a pit
	break;
      }
    }
  }
  
  //Check if the player is on a gold pile
  for(vector<pair<int, int>>::iterator it=m_gold.begin(); it!=m_gold.end(); ++it){
    
    //Check if the player is in the same row as a gold pile
    if(player.first == it->first){
      
      if(player.second == it->second){
        return WGOLD; //Player is in a gold pile
	
        //Check if the player is also on a column adjacent to a gold pile
      }else if((player.second == it->second + 1) | (player.second == it->second - 1)){
        checks += ADJGOLD; //Player is adjacent to a gold pile
	break;
      }
      
      //Check if the player is in the same column as a gold pile
    }else if(player.second == it->second){
      
      //Check if the player is in the same row as a gold pile
      if((player.first == it->first + 1) | (player.first == it->first - 1)){
        checks += ADJGOLD; //Player is adjacent to a gold pile
	break;
      }
    }
  }
  
  return checks;
} //Check what the player is adjacent to

void Cave::adjustGold(int change){
  m_allGold += change;
} //Adjust the amount of gold available

int Cave::getGold(){
  return m_allGold;
} //Get the amount of gold available

bool Cave::getDeath(){
  return m_death;
} //Check whether the Wumpus is dead or not

void Cave::randomWumpus(){
  //Initialize random seed
  srand(time(NULL));

  //The coordinates of Wumpus are randomly chosen
  m_wumpus.first = rand() % m_size;
  m_wumpus.second = rand() % m_size;
} //Randomize the location of the Wumpus

void Cave::randomPits(){
  //Initialize random seed
  srand(time(NULL));

  //Temporary pair to be put into list of pits
  pair<int, int> temp;

  //Clear the previous pits if they exist
  if(m_pits.empty()) m_pits.clear();
  
  //For all of the pits in the cave, randomize its location
  for(int i=0;i<m_numPits;i++){
    temp.first = rand() % m_size;
    temp.second = rand() % m_size;

    //Only add the pit if it isn't adjacent to or with something that already exists
    if(checkAdj(temp) == 0) m_pits.push_back(temp);
    else i--;
  }
} //Randomize the location of the pits

void Cave::randomGold(){
  //Initialize random seed
  srand(time(NULL));

  //Clear the previous gold piles if they exist
  if(m_gold.empty()) m_gold.clear();
  
  //Each pile of gold will have 100 pieces
  int numPiles = m_allGold / 100;

  //Temporary pair to be put into list of gold piles
  pair<int, int> temp;
  
  //Gold piles will be randomly placed
  for(int i=0;i<numPiles;i++){
    temp.first = rand() % m_size;
    temp.second = rand() % m_size;

    //Only add the gold pile if it isnt adjacent to or with something that already exists
    if(checkAdj(temp) == 0) m_gold.push_back(temp);
    else i--;
  }
  
} //Randomize the location of the gold
