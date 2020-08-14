//Author: Balas47
//Description: The purpose of this file is for testing the functionality of the
//             individual classes, as well as the game of the whole. When
//             finished, the game will be started and controlled here.


#include<utility>
#include<iostream>
#include"playerClass.h"
#include"caveClass.h"
using namespace std;

int main(){

  Player testPlayer = Player();

  cout << testPlayer.getLocation().first << ", " << testPlayer.getLocation().second << endl;

  pair<int, int> changeLoc = make_pair(3, 4);

  testPlayer.setLocation(changeLoc);

  cout << testPlayer.getLocation().first << endl;

  testPlayer.adjustJavelins(-2);

  cout << testPlayer.getJavelins() << endl;

  Cave testCave = Cave();

  cout << testCave.getWumpus().first << ", " << testCave.getWumpus().second << endl;

  //Puts the player onto the same column as the wumpus
  changeLoc.second = testCave.getWumpus().second;
  testPlayer.setLocation(changeLoc);

  cout << testCave.getGold() << endl;

  cout << testCave.checkAdj(testPlayer.getLocation()) << endl;

  //Should put the player with the wumpus, if not already
  changeLoc.first = testCave.getWumpus().first;
  testPlayer.setLocation(changeLoc);
  
  cout << testCave.checkAdj(testPlayer.getLocation()) << endl;
  
  return 0;
}
