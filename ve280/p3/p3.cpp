#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <cassert>
#include "simulation.h"
#include "world_type.h"
using namespace std;

int main(int argc, char *argv[])
{
    if (argc<4)
        {
            cout<<"Error: Missing arguments!\n";
            cout<<"Usage: ./p3 <species-summary> <world-file> <rounds> [v|verbose]"<<endl;;
            exit(0);
        }
    int round;
    round=atoi(argv[3]);
    if (round<0) {cout<<"Error: Number of simulation rounds is negative!\n";exit(0);}
    world_t world;
    initWorld(world,argv[1],argv[2]);
    cout<<"Initial state"<<endl;
    printGrid(world.grid);
    bool v;
    bool active;
    string ver;
    if (argc==5) 
	{
		ver=argv[4];
		if ((ver=="v")||(ver=="verbose")) v=true;
		else v=false;
        }
    else v=false;
    for (int i=1;i<=round;i++)
    {
        cout<<"Round "<<i<<endl;
        for (int j=0;j<world.numCreatures;j++)
        {
            active=simulateCreature(world.creatures[j],world.grid,v);
            if ((v)&&(active)) printGrid(world.grid);
	    if ((!v)&&(j==world.numCreatures-1)) printGrid(world.grid);
        }
    }
}
