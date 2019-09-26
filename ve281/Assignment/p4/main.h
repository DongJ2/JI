#ifndef PROJECT_4_MARKET_H
#define PROJECT_4_MARKET_H

struct client{
    int time, type, price, quantity, duration, order;
    std::string name, symbol;
};

struct compare{
    bool operator()(client a, client b)
    {
        if (a.type==0)//buy
            if (a.price<b.price) return true;
            else if (a.price>b.price) return false;
            else return a.order>b.order;
        else if (a.price>b.price) return true;
            else if (a.price<b.price) return false;
            else return a.order>b.order;
    }
};
struct transfer{
    int number_buy, number_sell, net;
};

struct traveler{
    std::string symbol;
    int buy_time, sell_time, buy_price, sell_price, order, lowest_time, lowest_price;
};

typedef std::priority_queue<client, std::vector<client>, compare> client_heap;
typedef std::map<std::string, client_heap> type_map;
typedef std::map<std::string, std::priority_queue<int> > trade_max;
typedef std::map<std::string, std::priority_queue<int, std::vector<int>, std::greater<int>>> trade_min;
typedef std::map<std::string, transfer> map_transfer;
typedef std::map<int, traveler> map_traveler;
typedef std::map<std::string, traveler> map_string_traveler;

#endif // PROJECT_4_MARKET_H
