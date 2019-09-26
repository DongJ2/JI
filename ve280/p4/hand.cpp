#include "hand.h"

Hand::Hand()
{
    curValue.soft=false;
    curValue.count=0;
}

void Hand::discardAll()
{
    curValue.soft=false;
    curValue.count=0;
}

void Hand::addCard(Card c)
{
    switch (c.spot)
    {
        case TWO:   curValue.count=curValue.count+2;break;
        case THREE: curValue.count=curValue.count+3;break;
        case FOUR:  curValue.count=curValue.count+4;break;
        case FIVE:  curValue.count=curValue.count+5;break;
        case SIX:   curValue.count=curValue.count+6;break;
        case SEVEN: curValue.count=curValue.count+7;break;
        case EIGHT: curValue.count=curValue.count+8;break;
        case NINE:  curValue.count=curValue.count+9;break;
        case TEN:   curValue.count=curValue.count+10;break;
        case JACK:  curValue.count=curValue.count+10;break;
        case QUEEN: curValue.count=curValue.count+10;break;
        case KING:  curValue.count=curValue.count+10;break;
        case ACE:
            if (curValue.count+11<=21) {curValue.count=curValue.count+11;curValue.soft=true;}
                else curValue.count++;
            break;
    }
}

HandValue Hand::handValue() const
{
    HandValue h;
    if ((curValue.soft)&&(curValue.count>21)) {h.count=curValue.count-10;h.soft=false;}
        else h=curValue;
    return h;
}
