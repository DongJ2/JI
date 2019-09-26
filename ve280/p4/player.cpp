#include "player.h"

class Simple: public Player
{
    int bet(unsigned int bankroll, unsigned int minimum);
    bool draw(Card dealer, const Hand &player);
    void expose(Card c);
    void shuffled();
};

class Counting: public Player
{
    int bet(unsigned int bankroll, unsigned int minimum);
    bool draw(Card dealer, const Hand &player);
    void expose(Card c);
    void shuffled();
    int counting;
};

int Simple::bet(unsigned int bankroll, unsigned int minimum)
{
    return minimum;
}

bool Simple::draw(Card dealer, const Hand &player)
{
    HandValue h;
    h=player.handValue();
    if (h.soft)
    {
        if (h.count<=17) return true;
        if (h.count==18)
            if ((dealer.spot==TWO)||(dealer.spot==SEVEN)||(dealer.spot==EIGHT)) return false;
            else return true;
        if (h.count>=19) return false;
    }
    if (!h.soft)
    {
        if (h.count<=11) return true;
        if (h.count==12)
            if ((dealer.spot==FOUR)||(dealer.spot==FIVE)||(dealer.spot==SIX)) return false;
            else return true;
        if ((h.count>=13)&&(h.count<=16))
            if ((dealer.spot==TWO)||(dealer.spot==THREE)||(dealer.spot==FOUR)||(dealer.spot==FIVE)||(dealer.spot==SIX)) return false;
            else return true;
        if (h.count>=17) return false;
    }
}

void Simple::expose(Card c)
{
}

void Simple::shuffled()
{
}

int Counting::bet(unsigned int bankroll, unsigned int minimum)
{
    if ((bankroll>=2*minimum)&&(counting>=2)) return 2*minimum;
    else return minimum;
}

bool Counting::draw(Card dealer, const Hand &player)
{
    HandValue h;
    h=player.handValue();
    if (h.soft)
    {
        if (h.count<=17) return true;
        if (h.count==18)
            if ((dealer.spot==TWO)||(dealer.spot==SEVEN)||(dealer.spot==EIGHT)) return false;
            else return true;
        if (h.count>=19) return false;
    }
    if (!h.soft)
    {
        if (h.count<=11) return true;
        if (h.count==12)
            if ((dealer.spot==FOUR)||(dealer.spot==FIVE)||(dealer.spot==SIX)) return false;
            else return true;
        if ((h.count>=13)&&(h.count<=16))
            if ((dealer.spot==TWO)||(dealer.spot==THREE)||(dealer.spot==FOUR)||(dealer.spot==FIVE)||(dealer.spot==SIX)) return false;
            else return true;
        if (h.count>=17) return false;
    }
}

void Counting::expose(Card c)
{
    if ((c.spot==TEN)||(c.spot==JACK)||(c.spot==QUEEN)||(c.spot==KING)||(c.spot==ACE)) counting--;
    if ((c.spot==TWO)||(c.spot==THREE)||(c.spot==FOUR)||(c.spot==SIX)||(c.spot==FIVE)) counting++;
}

void Counting::shuffled()
{
    counting=0;
}

static Simple simple;

Player *get_Simple()
{
    return &simple;
}

static Counting counting;

Player *get_Counting()
{
    return &counting;
}












