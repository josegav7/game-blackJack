#include <list>
#include <vector>
#include "Hand.h"
#include "Card.h"

Hand::Hand(std::vector<int>initialCards)
{ 
  for (auto i =initialCards.begin();i !=initialCards.end(); i++){
  cards.push_back(Card(*i));
    }
  //Iterate to create a list based on the initial cards
}

Card Hand:: dealACard()
{
  Card c;
  c = cards.front(); //create a copy of the card at the front
  cards.pop_front(); //and remove it
  return c;
  
}

void Hand:: addACard(Card newCard)
{
  cards.push_front(newCard); //Add a new card to the hand
}

int Hand::getPoints()
{
  //Iterate to find out the sum of the values of the cards
  int count = 0;
  for (auto i=cards.begin(); i !=cards.end(); i++)
    {
      count += i->value;
    }
  return count;
  
}

void Hand::printMe()
{
  //Iterate to print each card in the hand (using overloaded ostream method) and the total points by calling getPoints()
  std::cout << "{ ";
  for (auto i =cards.begin(); i !=cards.end(); i++)
  {
    std::cout << *i <<", ";
  }
  std::cout << " } ";
  std::cout << getPoints() << " points" <<std::endl;
}