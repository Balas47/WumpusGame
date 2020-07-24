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

  cout << testPlayer.m_getLocation().first << ", " << testPlayer.m_getLocation().second << endl;

  pair<int, int> changeLoc = make_pair(3, 4);

  testPlayer.m_setLocation(changeLoc);

  cout << testPlayer.m_getLocation().first << endl;

  testPlayer.m_adjustJavelins(-2);

  cout << testPlayer.m_getJavelins() << endl;
  
  return 0;
}
