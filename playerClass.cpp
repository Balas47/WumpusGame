#include"playerClass.h"
using namespace std;

//Default Constructor
Player::Player(){

  m_location = make_pair(0,0);
  m_javelins = 3;
  m_gold = 300;

}

//Overloaded Constructor
Player::Player(pair<int, int> location, int javelins, int gold){

  m_location = location;
  m_javelins = javelins;
  m_gold = gold;
  
}

//Setters and getters
pair<int, int> Player::m_getLocation(){
  return m_location;
}

void Player::m_setLocation(pair<int, int> location){
  m_location = location;
}

int Player::m_getJavelins(){
  return m_javelins;
}

void Player::m_setJavelins(int javelins){
  m_javelins = javelins;
}

void Player::m_adjustJavelins(int change){
  m_javelins += change;
}

int Player::m_getGold(){
  return m_gold;
}

void Player::m_setGold(int gold){
  m_gold = gold;
}

void Player::m_adjuostGold(int change){
  m_gold += change;
}
