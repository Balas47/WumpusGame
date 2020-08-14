#include"playerClass.h"
using namespace std;

//Default Constructor
Player::Player(){

  m_location = make_pair(0,0); //Default location is (0,0)
  m_javelins = 3;              //Player starts with 3 javelins
  m_gold = 300;                //Player starts with 300 gold

}

//Overloaded Constructor
Player::Player(pair<int, int> location, int javelins, int gold){

  m_location = location;
  m_javelins = javelins;
  m_gold = gold;
  
}

//Setters and getters
pair<int, int> Player::getLocation(){
  return m_location;
}

void Player::setLocation(pair<int, int> location){
  m_location = location;
}

int Player::getJavelins(){
  return m_javelins;
}

void Player::setJavelins(int javelins){
  m_javelins = javelins;
}

void Player::adjustJavelins(int change){
  m_javelins += change;
}

int Player::getGold(){
  return m_gold;
}

void Player::setGold(int gold){
  m_gold = gold;
}

void Player::adjuostGold(int change){
  m_gold += change;
}
