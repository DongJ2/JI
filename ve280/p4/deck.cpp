#include "deck.h"

Deck::Deck()
{
    next=0;
    int m,n;
    for (int i=0;i<52;i++)
    {
        m=i/13;
        n=i%13;
        switch (m)
        {
            case 0: deck[i].suit=SPADES;break;
            case 1: deck[i].suit=HEARTS;break;
            case 2: deck[i].suit=CLUBS;break;
            case 3: deck[i].suit=DIAMONDS;break;
        }
        switch (n)
        {
            case 0: deck[i].spot=TWO;break;
            case 1: deck[i].spot=THREE;break;
            case 2: deck[i].spot=FOUR;break;
            case 3: deck[i].spot=FIVE;break;
            case 4: deck[i].spot=SIX;break;
            case 5: deck[i].spot=SEVEN;break;
            case 6: deck[i].spot=EIGHT;break;
            case 7: deck[i].spot=NINE;break;
            case 8: deck[i].spot=TEN;break;
            case 9: deck[i].spot=JACK;break;
            case 10: deck[i].spot=QUEEN;break;
            case 11: deck[i].spot=KING;break;
            case 12: deck[i].spot=ACE;break;
        }
    }
}

void Deck::reset()
{
    next=0;
    /*int m,n;
    for (int i=0;i<52;i++)
    {
        m=i/13;
        n=i%13;
        switch (m)
        {
            case 0: deck[i].suit=SPADES;break;
            case 1: deck[i].suit=HEARTS;break;
            case 2: deck[i].suit=CLUBS;break;
            case 3: deck[i].suit=DIAMONDS;break;
        }
        switch (n)
        {
            case 0: deck[i].spot=TWO;break;
            case 1: deck[i].spot=THREE;break;
            case 2: deck[i].spot=FOUR;break;
            case 3: deck[i].spot=FIVE;break;
            case 4: deck[i].spot=SIX;break;
            case 5: deck[i].spot=SEVEN;break;
            case 6: deck[i].spot=EIGHT;break;
            case 7: deck[i].spot=NINE;break;
            case 8: deck[i].spot=TEN;break;
            case 9: deck[i].spot=JACK;break;
            case 10: deck[i].spot=QUEEN;break;
            case 11: deck[i].spot=KING;break;
            case 12: deck[i].spot=ACE;break;
        }
    }*/
}

void Deck::shuffle(int n)
{
    Card s[DeckSize];
    int m=52-n;
    int k=n;
    int i=0;
    while ((m>=0)||(n>=0))
    {
        if (m>0) {s[i]=deck[52-m];i++;}
        if (n>0) {s[i]=deck[k-n];i++;}
        m--;
        n--;
    }
    for (i=0;i<52;i++) deck[i]=s[i];
}

Card Deck::deal()
{
    Card c;
    c=deck[next];
    next++;
    return c;
}

int Deck::cardsLeft()
{
    return 52-next;
}
