#include "gameDriver.h"
#include <limits>
using namespace std;

//Constants for menu
const int PLAY = 1;
const int STORE = 2;
const int EXIT = 3;

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

    cout << "What do you want to do?" << endl;
    
    //Options the player can make
    cout << "1: Enter the Wumpus Cave" << endl
	 << "2: Go to the Javelin Store" << endl
	 << "3: EXIT" << endl;
    
    //Checks whether the input is valid
    while(!(cin >> playerOption) || (0 >= playerOption) || (playerOption >= 4)){
      cout << "Please enter a number from 1-3!" << endl;
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
  return 0;
} //Controls what happens when the player is in the cave

void Game::printBoard(){} //Print out current location in cave, and what the player perceives
