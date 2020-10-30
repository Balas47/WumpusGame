#include "gameDriver.h"
#include <limits>
#include <iomanip>
using namespace std;

//Constants for menu
enum MenuThings{PLAY=1, STORE, INFO, EXIT};
/*
const int PLAY = 1;
const int STORE = 2;
const int INFO = 3;
const int EXIT = 4;
*/

//Constants for cave
enum CaveThings{UP=1, DOWN, LEFT, RIGHT, SHOOT, LEAVE, DEEPER};
/*
const int UP = 1;
const int DOWN = 2;
const int LEFT = 3;
const int RIGHT = 4;
const int SHOOT = 5;
const int LEAVE = 6;
const int DEEPER = 7;
*/

//Constants for store
enum StoreThings{ONE=1, ALL, NONE};
const int PRICE = 100;

//Constants for precepts
const int CWUMPUS = 100;
const int CPIT = 10;

//Information concerning return value for checkAdj()
const int ADJWUMPUS = 100; //Adjacent to the wumpus
const int WWUMPUS   = 200; //With the wumpus

const int ADJPIT = 10;
const int WPIT   = 20;

const int ADJGOLD = 1;
const int WGOLD   = 2;

const int EMPTY = 0; //Not adjacent to anything

//Constants for leaving the cave
const int ALIVE = 1;
const int DEAD = 2;

Game::Game(){

  //Adding in a default cave and player
  m_cave = Cave();
  m_player = Player();
  m_tempGold = 0;
  
} //Default Constructor

void Game::menu(){

  cout << "Welcome to the Wumpus Game!" << endl;
  cout << "Put your senses to the test and see if you have what it takes to survive." << endl;

  //The player will choose an option from the menu
  int playerOption = 0;

  //Continue the menu unless the player wants to exit
  while(playerOption != EXIT){

    cout << "\nWhat do you want to do?" << endl;
    
    //Options the player can make
    cout << "1: Enter the Wumpus Cave" << endl
	 << "2: Go to the Javelin Store" << endl
	 << "3: Check your gold and javelins" << endl
	 << "4: EXIT" << endl;
    
    //Checks whether the input is valid
    while(!(cin >> playerOption) || (0 >= playerOption) || (playerOption > EXIT)){
      cout << "Please enter a number from 1-4!" << endl;
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
    };
    
    switch(playerOption){
      
    case PLAY:
      //Reset the cave is necessary, and enter
      m_cave.reset();
      cout << "You have entered the cave, good luck..." << endl;
      {
	int rewards = cave();

	//Check whether the player gets the gold that they collected
	if(rewards == ALIVE){
	  cout << "You have come out of the cave alive... this time..." << endl
	       << "You have collected " << m_tempGold << " gold pieces" << endl;
	  m_player.adjustGold(m_tempGold);
	}else{
	  cout << "You died and lost " << m_tempGold << " gold pieces" << endl;
	}
      }
      
      m_tempGold = 0;
      break;
      
    case STORE:
      store();
      break;

    case INFO:
      cout << "You have " << m_player.getGold() << " gold pieces and "
	   << m_player.getJavelins() << " javelins." << endl;
      break;

    case EXIT:
      cout << "Goodbye! See you soon :)" << endl;
      break;
      
    default:
      cout << "ERROR: invalid input" << endl;
      break;
    }
  }
  
} //Controls the menu section of the game

void Game::store(){

  //Basically the player will have three choices, buy one javelin, buy as many javelins as they
  //can, or leave

  int options = 0;

  cout << "Welcome to the Store!" << endl;
  
  while(options != NONE){
    cout << "\n The price per javelin is 100 gold pieces, how many do ya want?" << endl;

    cout << "1. Buy a Javelin" << endl
	 << "2. Buy as many Javelins as I Have Gold" << endl
	 << "3. Leave the Store" << endl;

    //Input validation loop
    while(!(cin >> options) || options <= 0 || options > NONE){
      cout << "Please enter a valid number!" << endl;
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    switch(options){

    case ONE:
      if(m_player.getGold() != 0){
	m_player.adjustGold(-PRICE);
	m_player.adjustJavelins(1);
      }
      else cout << "You don't have enough gold!" << endl;
      break;

    case ALL:
      cout << "You have bought " << m_player.getGold()/PRICE << " javelins! " << endl;
      m_player.adjustJavelins(m_player.getGold()/PRICE);
      m_player.setGold(0);
      break;

    case NONE:
      cout << "Alrighty, good bye!" << endl;
      break;
      
    }
  }
} //Controls the store where the player can buy javelins

int Game::cave(){

  //Start out with a random position in the cave
  srand(time(NULL));
  pair<int, int> startPosition = make_pair(0,0);

  //Start position is random, and player will not start out in or adjacent to a pit or Wumpus
  do{
    startPosition.first = rand() % m_cave.getSize();
    startPosition.second = rand() % m_cave.getSize();
  }while(m_cave.checkAdj(startPosition) != 0);

  //If the start position is valid, make sure that the player is there
  m_player.m_location = startPosition;

  int options = 0;
  int status = ALIVE;
  
  int direction = 0;
  
  while(options != LEAVE && status == ALIVE){

    //Player can choose what to do while in the cave
    printBoard();
    cout << "\nWhat are you going to do?" << endl;
    cout << "1: Move Up" << endl
	 << "2: Move Down" << endl
	 << "3: Move Left" << endl
	 << "4: Move Right" << endl
	 << "5: Shoot Javelin" << endl
    	 << ((m_player.m_location == startPosition) ?"6: LEAVE CAVE\n7: Go to a Deeper Cave\n" :"");

    //Make sure that player input is valid
    while(!(cin >> options) || options <= 0 || options > DEEPER){
      cout << "Please enter a valid number!" << endl;
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    switch(options){

    case UP:
      //Check that the player is not at the top of the cave
      if(m_player.m_location.first < m_cave.getSize()) m_player.m_location.first += 1;
      else cout << "You cannot move up anymore!" << endl;
      status = precepts(m_cave.checkAdj(m_player.m_location));
      break;

    case DOWN:
      //Check that the player is not at the bottom of the cave
      if(m_player.m_location.first > 0) m_player.m_location.first -= 1;
      else cout << "You cannot move down anymore!" << endl;
      status = precepts(m_cave.checkAdj(m_player.m_location));
      break;

    case LEFT:
      //Check that the player is not at the left edge of the cave
      if(m_player.m_location.second > 0) m_player.m_location.second -= 1;
      else cout << "You cannot move left anymore!" << endl;
      status = precepts(m_cave.checkAdj(m_player.m_location));
      break;

    case RIGHT:
      //Check that the player is not at the right edge of the cave
      if(m_player.m_location.second < m_cave.getSize()) m_player.m_location.second += 1;
      else cout << "You cannot move right anymore!" << endl;
      status = precepts(m_cave.checkAdj(m_player.m_location));
      break;

    case SHOOT:

      //Can only shoot if you have a javelin
      if(m_player.getJavelins() == 0){
	cout << "You have no javelins left!" << endl;
	break;
      }

      cout << "\nWhat direction did you want to shoot?" << endl
	   << "1: Shoot Up" << endl
	   << "2: Shoot Down" << endl
	   << "3: Shoot Left" << endl
	   << "4: Shoot Right" << endl;

      //Make sure that player input is valid
      while(!(cin >> direction) || options <= 0 || options > LEAVE){
	cout << "Please enter a valid number!" << endl;
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
      }

      //Check if the javelin hits the Wumpus or not
      if(direction == UP){
	if((m_player.m_location.first < m_cave.getWumpus().first)
	   && m_player.m_location.second == m_cave.getWumpus().second){
	  cout << "You killed the Wumpus!" << endl;
	  m_cave.setDeath(true); //Indicate that Wumpus has died
	}else{
	  cout << "You missed the Wumpus!" << endl;
	}
      }else if(direction == DOWN){
	if(m_player.m_location.first > m_cave.getWumpus().first
	   && m_player.m_location.second == m_cave.getWumpus().second){
	  cout << "You killed the Wumpus!" << endl;
	  m_cave.setDeath(true);
	}else{
	  cout << "You missed the Wumpus!" << endl;
	}
      }else if(direction == LEFT){
	if(m_player.m_location.second > m_cave.getWumpus().second
	   && m_player.m_location.first == m_cave.getWumpus().first){
	  cout << "You killed the Wumpus!" << endl;
	  m_cave.setDeath(true);
	}else{
	  cout << "You missed the Wumpus!" << endl;
	}
      }else if(direction == RIGHT){
	if(m_player.m_location.second < m_cave.getWumpus().second
	   && m_player.m_location.first == m_cave.getWumpus().first){
	  cout << "You killed the Wumpus!" << endl;
	  m_cave.setDeath(true);
	}else{
	  cout << "You missed the Wumpus!" << endl;
	}
      }else{
	cout << "ERROR: Invalid Option!" << endl;
      }

      //Take away one of the players javelins
      m_player.adjustJavelins(-1);
      break;

    case LEAVE:

      //Make sure that the player is actually able to leave
      if(m_player.m_location != startPosition){
	cout << "You can't leave yet!" << endl;
	options = 0; //Have to change option so that we dont exit the while loop
      }
      else cout << "Please come again :)" << endl;
      break;

    case DEEPER:

      //Make sure that the player is actually able to descend
      if(m_player.m_location != startPosition) cout << "You can't leave yet!" << endl;
      else{
	m_cave.nextLevel();
	cout << "Beware, there are more pits... but there is also more gold!" << endl;
      }
      break;

    default:
      cout << "ERROR: Invalid Option" << endl;
      break;

    }
    
  }
  
  return status;
} //Controls what happens when the player is in the cave

void Game::printBoard(){
  
  //Print out the board with player location
  for(int i=m_cave.getSize();i>=0;i--){
    for(int j=0;j<m_cave.getSize();j++){
      
      //Prints out an X where the player is, and a "_" otherwise
      //setw used to make the output nicer
      pair<int, int> testLocation = make_pair(i, j);
      if(testLocation == m_player.m_location) cout << setw(2) << "X";
      else cout << setw(2) << "_";
    }
    cout << endl;
  }

} //Print out current location

int Game::precepts(int value){

  //First check if the player is with the Wumpus, or in a pit
  if(value == WWUMPUS && !m_cave.getDeath()){
    cout << "THE WUMPUS HAS EATEN YOU" << endl
	 << "Better Luck Next Time" << endl;
    return DEAD; //The player has died
  }else if(value == WPIT){
    cout << "YOU HAVE FALLEN INTO A PIT" << endl
	 << "Better Luck Next Time" << endl;
    return DEAD; //The player has died
  }else if(value == WGOLD){
    cout << "You see some gold specks in the air" << endl
	 << "You have collected 100 gold pieces!" << endl;
    m_tempGold += 100;
  }
  
  //Check whether the player is adjacent to the Wumpus
  if(value/CWUMPUS == ADJWUMPUS/CWUMPUS){ //Isolates the Wumpus(100's) digit
    cout << "You smell a terrible stench... the Wumpus is near..." << endl;

    //Check whether the player is adjacent to a pit
  }else if(((value/CPIT) % CPIT) == ADJPIT/CPIT){ //Isolates the Pits(10's) digit
    cout << "You feel a gust of wind... there is a pit nearby..." << endl;
  }else{
    cout << "There is nothing nearby... hopefully" << endl;
  }
  
  return ALIVE; //The player is still alive
} //Prints out what the player percieves, if anything
