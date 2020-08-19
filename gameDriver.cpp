#include "gameDriver.h"
#include <limits>
using namespace std;

//Constants for menu
const int PLAY = 1;
const int STORE = 2;
const int INFO = 3;
const int EXIT = 4;

//Constants for cave
const int UP = 1;
const int DOWN = 2;
const int LEFT = 3;
const int RIGHT = 4;
const int SHOOT = 5;
const int LEAVE = 6;

Game::Game(){

  //Adding in a default cave and player
  m_cave = Cave();
  m_player = Player();
  
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
      cout << "You have entered the cave, good luck..." << endl;
      cave();
      break;
      
    case STORE:
      cout << "You have gone to the store, make your choice" << endl;
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

void Game::store(){} //Controls the store where the player can buy javelins

int Game::cave(){

  //Start out with a random position in the cave
  srand(time(NULL));
  pair<int, int> startPosition = make_pair(0,0);

  //Start position is random, and player will not start out in or adjacent to a pit or Wumpus
  do{
    startPosition.first = rand() % m_cave.getSize();
    startPosition.second = rand() % m_cave.getSize();
  }while(!m_cave.checkAdj(startPosition));

  //If the start position is valid, make sure that the player is there
  m_player.m_location = startPosition;

  int options = 0;

  while(options != LEAVE){

    cout << "\nWhat are you going to do?" << endl;
    cout << "1: Move Up" << endl
	 << "2: Move Down" << endl
	 << "3: Move Left" << endl
	 << "4: Move Right" << endl
	 << "5: Shoot Javelin" << endl
	 << ((m_player.m_location == startPosition) ?"6: LEAVE CAVE\n" :"");

    while(!(cin >> options) || options <= 0 || options > LEAVE){
      cout << "Please enter a valid number!" << endl;
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    switch(options){

    case UP:
      if(m_player.m_location.first < m_cave.getSize()) m_player.m_location.first += 1;
      else cout << "You cannot move up anymore!" << endl;
      precepts(m_cave.checkAdj(m_player.m_location));
      break;

    case DOWN:
      if(m_player.m_location.first > 0) m_player.m_location.first -= 1;
      else cout << "You cannot move down anymore!" << endl;
      precepts(m_cave.checkAdj(m_player.m_location));
      break;

    case LEFT:
      if(m_player.m_location.second > 0) m_player.m_location.second -= 1;
      else cout << "You cannot move left anymore!" << endl;
      precepts(m_cave.checkAdj(m_player.m_location));
      break;

    case RIGHT:
      if(m_player.m_location.second < m_cave.getSize()) m_player.m_location.second += 1;
      else cout << "You cannot move right anymore!" << endl;
      precepts(m_cave.checkAdj(m_player.m_location));
      break;

    case SHOOT:
      break;

    case LEAVE:
      break;

    default:
      cout << "ERROR: Invalid Option" << endl;
      break;

    }
    
  }
  
  return 0;
} //Controls what happens when the player is in the cave

void Game::printBoard(){} //Print out current location in cave, and what the player perceives

void Game::precepts(int value){

  cout << "You see nothing... or do you?" << endl;
} //Prints out what the player percieves, if anything
