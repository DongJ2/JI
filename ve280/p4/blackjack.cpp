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

int main(int argc, char *argv[])
{
    Player *player;
    int bankroll, minimum, round;
    int cut,i,wager;
    Card c,hole,face;
    Deck d;
    Hand dealer;
    Hand p;
    bankroll=atoi(argv[1]);
    minimum=atoi(argv[2]);
    round=atoi(argv[3]);
    string s;
    s=argv[4];
    d.reset();
    if (s=="simple") player=get_Simple();
    if (s=="counting") {player=get_Counting();player->shuffled();}
    if (argc==6)
    {
        ifstream iFile;
        iFile.open(argv[5]);
	cut=-1;
        iFile>>cut;
        cout<<"# Shuffling the deck\n";
        while (cut!=-1)
        {
            cout<<"cut at "<<cut<<endl;
            d.shuffle(cut);
            cut=-1;
            iFile>>cut;
        }
        player->shuffled();
	iFile.close();
    }
    else
    {
        i=1;
        cout<<"# Shuffling the deck\n";
        while (i<8)
        {
            cut=get_cut();
            cout<<"cut at "<<cut<<endl;
            d.shuffle(cut);
            i++;
        }
        player->shuffled();
    }
    int thishand=1;
    while (thishand<=round)
    {
        if (bankroll<minimum) break;
        cout<<"# Hand "<<thishand<<" bankroll "<<bankroll<<endl;
        if (d.cardsLeft()<20)
        {
	    d.reset();
            i=1;
            cout<<"# Shuffling the deck\n";
            while (i<8)
            {
                cut=get_cut();
                cout<<"cut at "<<cut<<endl;
                d.shuffle(cut);
                i++;
            }
            player->shuffled();
        }
        wager=player->bet(bankroll,minimum);
        cout<<"# Player bets "<<wager<<endl;
        c=d.deal();
        p.addCard(c);
        cout<<"Player dealt ";
        printCard(c);
        player->expose(c);
        face=d.deal();
        dealer.addCard(face);
        cout<<"Dealer dealt ";
        printCard(face);
        player->expose(face);
        c=d.deal();
        p.addCard(c);
        cout<<"Player dealt ";
        printCard(c);
        player->expose(c);
        hole=d.deal();
        dealer.addCard(hole);
        if (p.handValue().count==21)
        {
            cout<<"# Player dealt natural 21\n";
            bankroll=bankroll+3*wager/2;
        }
        else
        {
            while (player->draw(face,p))
            {
                c=d.deal();
                p.addCard(c);
                cout<<"Player dealt ";
                printCard(c);
                player->expose(c);
            }
            if (p.handValue().count>21)
            {
                cout<<"Player's total is "<<p.handValue().count<<endl;
                cout<<"# Player busts\n";
                bankroll=bankroll-wager;
            }
            else
            {
                cout<<"Player's total is "<<p.handValue().count<<endl;
                cout<<"Dealer's hole card is ";
                printCard(hole);
                player->expose(hole);
                while (dealer.handValue().count<17)
                {
                    c=d.deal();
                    dealer.addCard(c);
                    cout<<"Dealer dealt ";
                    printCard(c);
                    player->expose(c);
                }
                cout<<"Dealer's total is "<<dealer.handValue().count<<endl;
                if (dealer.handValue().count>21) {cout<<"# Dealer busts\n";bankroll=bankroll+wager;}
                else
                {
                    if (dealer.handValue().count>p.handValue().count) {cout<<"# Dealer wins\n";bankroll=bankroll-wager;}
                    if (dealer.handValue().count==p.handValue().count) {cout<<"# Push\n";}
                    if (dealer.handValue().count<p.handValue().count) {cout<<"# Player wins\n";bankroll=bankroll+wager;}
                }
            }
        }
        p.discardAll();
        dealer.discardAll();
        thishand++;
    }
    cout<<"# Player has "<<bankroll<<" after "<<thishand-1<<" hands\n";
}


















