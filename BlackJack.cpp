#include<iostream>
#include "Card.h"
#include "Hand.h"
#include "BlackJack.h"

//
// PLAY
//

// the method below has been written for you to help you understand how your methods will be used
  void BlackJack :: play() {
    std::cout << "Let's Play BlackJack!" << std::endl;

    bool gameOver = false; // Bust means >21
    this->printInstructions(); // print instructions
    this->printBoard(); // print the board

    while( !gameOver ) { // keep playing as long as the game is not won by either player
    
      gameOver = this->takePlayerTurn(); // current player takes a turn

      if (gameOver){
        break;
      }

      this->printBoard(); // print the board if that was a good move


      gameOver = this->takeDealerTurn(); // AI takes a turn

      if (gameOver)
        break;

    } // end while: game over

    // note below that the winning player is who we want, not the current player
    if (getWinningPlayerId() != -1)
      std::cout << "Congratulations: " << playerNames[getWinningPlayerId()] << " has won the game!" << std::endl;
    else 
      std::cout << "Looks like the game was a tie" << std::endl;

    std::cout << "Goodbye!" << std::endl;

  } // end play()

BlackJack::BlackJack(std::vector<std::string> _playerNames,std::vector<int>cardID) : playerNames(_playerNames), deck(cardID) 
{}

void BlackJack::printInstructions()
{
  std::cout << "The game starts with  a full deck and a empty hand for both the dealer and the player.Each hand is scored based on the following point values: Aces are treated as 1, 2 through 9 are treated as their representative numbers, Jack, King, and Queen will always have a value of 10, and Joker is not of value.\n\n The player goes first, and then the Dealer\n -The player can take as many cards as he/she wants, but if the player goes over 21 points, Dealer wins automatially\n -If the Dealer's cards have a total value of 21, the Dealer wins\n -If the Dealer's cards exceed 21, and the player's cards are <= 21, the player wins\n -If the Dealer's and Player's score are both equal, the Dealer wins.\n" << std::endl;
}

void BlackJack::printBoard()
{
  //Call printMe() from the Hand class
  std::cout << "Dealer's Hand: "; 
  dealerHand.printMe();
  std::cout << "Player's Hand: ";
  playerHand.printMe();
  std::cout << std::endl;
}

int BlackJack::getWinningPlayerId()
{
  return winningPlayerId;
}

bool BlackJack::takePlayerTurn()
{
  char hintOrStand;

  while (getPlayerPoints() < 21){ //If the player doesn't "bust"
    
  std::cout << "Player's turn: Enter (h) for 'hit'(take a card) or (s) for 'stand'(pass the turn to the dealer)\n";
    
  std::cin >> hintOrStand;

  if (hintOrStand == 'h') //If the player chooses to hit
  {
    
    playerHand.addACard(deck.dealACard()); 
    //Deal a card and add it to the player hand 
    if (getPlayerPoints() > 21) // If player "busts", set the winning player ID equal to 1, which represents the dealer
    {
      winningPlayerId = 1;
      return true;
    }
    if (getPlayerPoints() == 21)
    {
      //turn passes to the dealer, so we don't go through the while loop anymore
      winningPlayerId = -1; //No winner yet
      return false;
    }
  }
    
  if (hintOrStand == 's') //If player chooses to stand, there is no winner yet
  {
   winningPlayerId = -1;
  return false;
  }
    printBoard();
}
 return false; 
}

bool BlackJack::takeDealerTurn()
{
    while(getDealerPoints() <=16) //Dealer hits while he has less than 16 points
    {
       std::cout << "Dealer's turn...\n";
      dealerHand.addACard(deck.dealACard());
      //deal a card and add it to dealers hand
      printBoard();
    }
    if (getDealerPoints() > 21) //If dealer "busts"
    {
      winningPlayerId = 0; 
      //Set the winning player ID equal to 0, which represents 
      //the player
      return true;
    }
    else if (getDealerPoints() >= getPlayerPoints())
      //If the dealer doesn't "bust" and if he has equal or greater points than the player...
    {
      winningPlayerId = 1; // Dealer wins 
      return true;
    }
      winningPlayerId = 0; //Otherwise, player wins  
      return true;
}

int BlackJack::getPlayerPoints()
 {
  return (playerHand.getPoints()); //Call getPoints() from the hand class to get player points
 }

int BlackJack::getDealerPoints()
 {
  return (dealerHand.getPoints()); //Call getPoints() from the hand class to get dealer points
 }
