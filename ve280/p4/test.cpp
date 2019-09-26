#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cstdlib>
#include "card.h"
#include "deck.h"
#include "hand.h"
#include "player.h"
#include "rand.h"

using namespace std;

void printCard(Card c)
{
    switch (c.spot)
    {
        case TWO:   cout<<"Two of ";break;
        case THREE: cout<<"Three of ";break;
        case FOUR:  cout<<"Four of ";break;
        case FIVE:  cout<<"Five of ";break;
        case SIX:   cout<<"Six of ";break;
        case SEVEN: cout<<"Seven of ";break;
        case EIGHT: cout<<"Eight of ";break;
        case NINE:  cout<<"Nine of ";break;
        case TEN:   cout<<"Ten of ";break;
        case JACK:  cout<<"Jack of ";break;
        case QUEEN: cout<<"Queen of ";break;
        case KING:  cout<<"King of ";break;
        case ACE:   cout<<"Ace of ";break;
    }
    switch (c.suit)
    {
        case SPADES:   cout<<"Spades\n";break;
        case HEARTS:   cout<<"Hearts\n";break;
        case DIAMONDS: cout<<"Diamonds\n";break;
        case CLUBS:    cout<<"Clubs\n";break;
    }
}

int main()
{
	Deck d;
	Card c;
	d.reset();
	d.shuffle(1);
for (int i=0;i<52;i++) {c=d.deal();printCard(c);}
}
