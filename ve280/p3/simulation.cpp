#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <cassert>
#include "simulation.h"

using namespace std;

bool initWorld(world_t &world, const string &speciesFile, const string &worldFile)
{
    ifstream sFile,wFile;
    sFile.open(speciesFile.c_str());
    if (!sFile) {cout<<"Error: Cannot open file "<<speciesFile<<"!"<<endl;exit(0);}
    wFile.open(worldFile.c_str());
    if (!wFile) {cout<<"Error: Cannot open file "<<worldFile<<"!"<<endl;exit(0);}
    wFile>>world.grid.height;
    if ((world.grid.height>MAXHEIGHT)||(world.grid.height<1)) {cout<<"Error: The grid height is illegal!"<<endl;exit(0);}
    wFile>>world.grid.width;
    if ((world.grid.width>MAXWIDTH)||(world.grid.width<1)) {cout<<"Error: The grid width is illegal!"<<endl;exit(0);}
    char c;
    for (int i=0;i<world.grid.height;i++)
        {for (int j=0;j<world.grid.width;j++)
            {
                wFile>>c;
                switch (c)
                {
                    case 'P':world.grid.terrain[i][j]=PLAIN;break;
                    case 'L':world.grid.terrain[i][j]=LAKE;break;
                    case 'F':world.grid.terrain[i][j]=FOREST;break;
                    case 'H':world.grid.terrain[i][j]=HILL;break;
                    default: cout<<"Error: Terrain square ("<<c<<" "<<i<<" "<<j<<") is invalid!"<<endl;exit(0);
                }
                world.grid.squares[i][j]=NULL;
            }
        }
    int t=0;
    int k;
    bool f;
    string summary;
    string s1,s2,s3,s4,s5,s6,s7;
    istringstream iStream;
    istringstream iStream1;
    int sum,go;
    getline(sFile,summary);
    iStream.str(summary);
    iStream>>summary;
    iStream.clear();
    while (getline(sFile,s1))
    {       
	t++;
        if (t>MAXSPECIES) {cout<<"Error: Too many species!\nMaximal number of species is "<<MAXSPECIES<<"."<<endl;exit(0);}
	iStream.str(s1);
	iStream>>world.species[t-1].name;
	iStream.clear(); 
    }
    world.numSpecies=t;
    for (int i=0;i<world.numSpecies;i++)
    {
        ifstream iFile;
        s1=summary+"/"+world.species[i].name;
        iFile.open(s1.c_str());
	if (!iFile) {cout<<"Error: Cannot open file "<<s1<<"!"<<endl;exit(0);}
        sum=1;
	getline(iFile,s2);
	go=0;
	iStream.str(s2);
	iStream>>s3>>go;
	iStream.clear();
	f=true;
        while ((s3!=""))
        {
            if (sum>MAXPROGRAM+1) {cout<<"Error: Too many instructions for species "<<world.species[i].name<<"!\nMaximal number of instructions is "<<MAXPROGRAM<<"."<<endl;exit(0);}
            world.species[i].program[sum].address=go;
            if (s3=="hop") world.species[i].program[sum].op=HOP;
                else if (s3=="left") world.species[i].program[sum].op=LEFT;
                    else if (s3=="right") world.species[i].program[sum].op=RIGHT;
                        else if (s3=="infect") world.species[i].program[sum].op=INFECT;
                            else if (s3=="ifempty") world.species[i].program[sum].op=IFEMPTY;
                                else if (s3=="ifenemy") world.species[i].program[sum].op=IFENEMY;
                                    else if (s3=="ifsame") world.species[i].program[sum].op=IFSAME;
                                        else if (s3=="ifwall") world.species[i].program[sum].op=IFWALL;
                                            else if (s3=="go") world.species[i].program[sum].op=GO;
                                                else {cout<<"Error: Instruction "<<s3<<" is not recognized!"<<endl;exit(0);}
            sum++;
	    go=0;
	    s3="";
            getline(iFile,s2);
	    iStream.str(s2);
	    iStream>>s3>>go;
            iStream.clear();
        }
        world.species[i].programSize=sum-1;
        sum=0;
        iFile.close();
    }
    sum=0;
getline(wFile,s1);
    while (getline(wFile,s1))
    {      
	iStream1.str(s1);
        s4=" ";
        s5=" ";
        iStream1>>s2>>s3>>world.creatures[sum].location.r>>world.creatures[sum].location.c>>s4;
        k=0;
        if (sum+1>MAXCREATURES) {cout<<"Error: Too many creatures!\nMaximal number of creatures is "<<MAXCREATURES<<".\n";exit(0);}
        for (int i=0;i<world.numSpecies;i++)
        {
            if (s2==world.species[i].name) {world.creatures[sum].species=&world.species[i];k=1;break;}
        }
        if (k==0) {cout<<"Error: Species "<<s2<<" not found!\n";exit(0);};
        if (s3=="east") world.creatures[sum].direction=EAST;
            else if (s3=="south") world.creatures[sum].direction=SOUTH;
                else if (s3=="west") world.creatures[sum].direction=WEST;
                    else if (s3=="north") world.creatures[sum].direction=NORTH;
                        else {cout<<"Error: Direction "<<s3<<" is not recognized!\n";exit(0);}
        if ((world.creatures[sum].location.r<0)||(world.creatures[sum].location.r>=world.grid.height)||(world.creatures[sum].location.c<0)||(world.creatures[sum].location.c>=world.grid.width))
        {
            cout<<"Error: Creature ("<<s2<<" "<<s3<<" "<<world.creatures[sum].location.r<<" "<<world.creatures[sum].location.c<<") is out of bound!\n";
            cout<<"The grid size is "<<world.grid.height<<"-by-"<<world.grid.width<<".\n";
            exit(0);
        }
        if (world.grid.squares[world.creatures[sum].location.r][world.creatures[sum].location.c]==NULL) world.grid.squares[world.creatures[sum].location.r][world.creatures[sum].location.c]=&world.creatures[sum];
            else
                {
                    cout<<"Error: Creature ("<<s2<<" "<<s3<<" "<<world.creatures[sum].location.r<<" "<<world.creatures[sum].location.c<<") overlaps with creature (";
                    cout<<world.grid.squares[world.creatures[sum].location.r][world.creatures[sum].location.c]->species->name<<" ";
                    switch (world.grid.squares[world.creatures[sum].location.r][world.creatures[sum].location.c]->direction)
                        {
                            case EAST:cout<<"east";break;
                            case SOUTH:cout<<"south";break;
                            case WEST:cout<<"west";break;
                            case NORTH:cout<<"north";break;
                        }
                    cout<<" "<<world.creatures[sum].location.r<<" "<<world.creatures[sum].location.c<<")!\n";
                    exit(0);
                }
        world.creatures[sum].programID=1;
        world.creatures[sum].ability[ARCH]=false;
        world.creatures[sum].ability[FLY]=false;
        world.creatures[sum].hillActive=true;
        while (s4!=" ")
	{
            if (s4=="a") world.creatures[sum].ability[ARCH]=true;
                else if (s4=="f") world.creatures[sum].ability[FLY]=true;
                    else {cout<<"Error: Creature ("<<s2<<" "<<s3<<" "<<world.creatures[sum].location.r<<" "<<world.creatures[sum].location.c<<") has an invalid ability "<<s4<<"!\n";exit(0);}
	    s4=" ";
	    iStream1>>s4;
	}        
	if ((world.grid.terrain[world.creatures[sum].location.r][world.creatures[sum].location.c]==LAKE)&&(world.creatures[sum].ability[FLY]==false))
        {
            cout<<"Error: Creature ("<<s2<<" "<<s3<<" "<<world.creatures[sum].location.r<<" "<<world.creatures[sum].location.c<<") is in a lake square!\n";
            cout<<"The creature cannot fly!\n";
            exit(0);
        }
	if ((world.creatures[sum].ability[FLY]==false)&&(world.grid.terrain[world.creatures[sum].location.r][world.creatures[sum].location.c]==HILL)) world.creatures[sum].hillActive=false;
        sum++;
	iStream1.clear();
    }
    world.numCreatures=sum;
    sFile.close();
    wFile.close();
}
void printGrid(const grid_t &grid)
{
    for (int i=0;i<grid.height;i++)
    {
        for (int j=0;j<grid.width;j++)
        {
            if (grid.squares[i][j]==NULL) cout<<"____ ";
                else
                {
                    cout<<grid.squares[i][j]->species->name[0]<<grid.squares[i][j]->species->name[1]<<"_";
                    switch (grid.squares[i][j]->direction)
                    {
                        case EAST:cout<<"e ";break;
                        case SOUTH:cout<<"s ";break;
                        case WEST:cout<<"w ";break;
                        case NORTH:cout<<"n ";break;
                    }
                }
        }
        cout<<endl;
    }
}
instruction_t getInstruction(const creature_t &creature)
{
    return creature.species->program[creature.programID];
}

point_t adjacentPoint(point_t pt, direction_t dir)
{
    point_t point;
    if (dir==EAST) {point.r=pt.r;point.c=pt.c+1;}
    if (dir==WEST) {point.r=pt.r;point.c=pt.c-1;}
    if (dir==NORTH) {point.r=pt.r-1;point.c=pt.c;}
    if (dir==SOUTH) {point.r=pt.r+1;point.c=pt.c;}
    return point;
}
void hop(creature_t &creature, grid_t &grid)
{
    if (creature.direction==EAST)
    {
        if ((creature.location.c+1<grid.width)&&(grid.squares[creature.location.r][creature.location.c+1]==NULL)&&(!((grid.terrain[creature.location.r][creature.location.c+1]==LAKE)&&(creature.ability[FLY]==false))))
        {
            grid.squares[creature.location.r][creature.location.c]=NULL;
            creature.location=adjacentPoint(creature.location,creature.direction);
            grid.squares[creature.location.r][creature.location.c]=&creature;
        }
    }
    if (creature.direction==WEST)
    {
        if ((creature.location.c-1>=0)&&(grid.squares[creature.location.r][creature.location.c-1]==NULL)&&(!((grid.terrain[creature.location.r][creature.location.c-1]==LAKE)&&(creature.ability[FLY]==false))))
        {
            grid.squares[creature.location.r][creature.location.c]=NULL;
            creature.location=adjacentPoint(creature.location,creature.direction);
            grid.squares[creature.location.r][creature.location.c]=&creature;
        }
    }
        if (creature.direction==NORTH)
    {
        if ((creature.location.r-1>=0)&&(grid.squares[creature.location.r-1][creature.location.c]==NULL)&&(!((grid.terrain[creature.location.r-1][creature.location.c]==LAKE)&&(creature.ability[FLY]==false))))
        {
            grid.squares[creature.location.r][creature.location.c]=NULL;
            creature.location=adjacentPoint(creature.location,creature.direction);
            grid.squares[creature.location.r][creature.location.c]=&creature;
        }
    }
        if (creature.direction==SOUTH)
    {
        if ((creature.location.r+1<grid.height)&&(grid.squares[creature.location.r+1][creature.location.c]==NULL)&&(!((grid.terrain[creature.location.r+1][creature.location.c]==LAKE)&&(creature.ability[FLY]==false))))
        {
            grid.squares[creature.location.r][creature.location.c]=NULL;
            creature.location=adjacentPoint(creature.location,creature.direction);
            grid.squares[creature.location.r][creature.location.c]=&creature;
        }
    }
}
direction_t leftFrom(direction_t dir)
{
    direction_t d;
    if (dir==EAST) return NORTH;
    if (dir==NORTH) return WEST;
    if (dir==WEST) return SOUTH;
    if (dir==SOUTH) return EAST;
    return d;
}
direction_t rightFrom(direction_t dir)
{
    if (dir==EAST) return SOUTH;
    if (dir==SOUTH) return WEST;
    if (dir==WEST) return NORTH;
    if (dir=NORTH) return EAST;

}

bool ifempty(const grid_t &grid, const creature_t &creature)
{
    bool f=false;
    switch (creature.direction)
    {
        case EAST: if ((creature.location.c+1<grid.width)&&(grid.squares[creature.location.r][creature.location.c+1]==NULL)) f=true;break;
        case WEST: if ((creature.location.c-1>=0)&&(grid.squares[creature.location.r][creature.location.c-1]==NULL)) f=true;break;
        case SOUTH: if ((creature.location.r+1<grid.height)&&(grid.squares[creature.location.r+1][creature.location.c]==NULL)) f=true;break;
        case NORTH: if ((creature.location.r-1>=0)&&(grid.squares[creature.location.r-1][creature.location.c]==NULL)) f=true;break;
    }
    return f;
}
bool ifenemy(const grid_t &grid, const creature_t &creature)
{
    bool f=false;
    switch (creature.direction)
    {
        case EAST: if ((creature.location.c+1<grid.width)&&(grid.squares[creature.location.r][creature.location.c+1]!=NULL)&&(grid.squares[creature.location.r][creature.location.c+1]->species->name!=creature.species->name)&&(grid.terrain[creature.location.r][creature.location.c+1]!=FOREST)) f=true;break;
        case WEST: if ((creature.location.c-1>=0)&&(grid.squares[creature.location.r][creature.location.c-1]!=NULL)&&(grid.squares[creature.location.r][creature.location.c-1]->species->name!=creature.species->name)&&(grid.terrain[creature.location.r][creature.location.c-1]!=FOREST)) f=true;break;
        case SOUTH: if ((creature.location.r+1<grid.height)&&(grid.squares[creature.location.r+1][creature.location.c]!=NULL)&&(grid.squares[creature.location.r+1][creature.location.c]->species->name!=creature.species->name)&&(grid.terrain[creature.location.r+1][creature.location.c]!=FOREST)) f=true;break;
        case NORTH: if ((creature.location.r-1>=0)&&(grid.squares[creature.location.r-1][creature.location.c]!=NULL)&&(grid.squares[creature.location.r-1][creature.location.c]->species->name!=creature.species->name)&&(grid.terrain[creature.location.r-1][creature.location.c]!=FOREST)) f=true;break;
    }
    return f;
}
bool ifsame(const grid_t &grid, const creature_t &creature)
{
    bool f=false;
    switch (creature.direction)
    {
        case EAST: if ((creature.location.c+1<grid.width)&&(grid.squares[creature.location.r][creature.location.c+1]!=NULL)&&(grid.squares[creature.location.r][creature.location.c+1]->species->name==creature.species->name)&&(grid.terrain[creature.location.r][creature.location.c+1]!=FOREST)) f=true;break;
        case WEST: if ((creature.location.c-1>=0)&&(grid.squares[creature.location.r][creature.location.c-1]!=NULL)&&(grid.squares[creature.location.r][creature.location.c-1]->species->name==creature.species->name)&&(grid.terrain[creature.location.r][creature.location.c-1]!=FOREST)) f=true;break;
        case SOUTH: if ((creature.location.r+1<grid.height)&&(grid.squares[creature.location.r+1][creature.location.c]!=NULL)&&(grid.squares[creature.location.r+1][creature.location.c]->species->name==creature.species->name)&&(grid.terrain[creature.location.r+1][creature.location.c]!=FOREST)) f=true;break;
        case NORTH: if ((creature.location.r-1>=0)&&(grid.squares[creature.location.r-1][creature.location.c]!=NULL)&&(grid.squares[creature.location.r-1][creature.location.c]->species->name==creature.species->name)&&(grid.terrain[creature.location.r-1][creature.location.c]!=FOREST)) f=true;break;
    }
    return f;
}
bool ifwall(const grid_t &grid, const creature_t &creature)
{
    bool f=false;
    switch (creature.direction)
    {
        case EAST: if ((creature.location.c+1==grid.width)||((grid.terrain[creature.location.r][creature.location.c+1]==LAKE)&&(creature.ability[FLY]==false))) f=true;break;
        case WEST: if ((creature.location.c==0)||((grid.terrain[creature.location.r][creature.location.c-1]==LAKE)&&(creature.ability[FLY]==false))) f=true;break;
        case SOUTH: if ((creature.location.r+1==grid.height)||((grid.terrain[creature.location.r+1][creature.location.c]==LAKE)&&(creature.ability[FLY]==false))) f=true;break;
        case NORTH: if ((creature.location.r==0)||((grid.terrain[creature.location.r-1][creature.location.c]==LAKE)&&(creature.ability[FLY]==false))) f=true;break;
    }
    return f;
}
void infectArch(grid_t &grid, creature_t &creature)
{
    if ((creature.direction==EAST)&&(creature.location.c!=grid.width-1))
    {
        for (int i=creature.location.c+1;i<grid.width;i++)
        {
            if ((grid.squares[creature.location.r][i]!=NULL)&&(grid.squares[creature.location.r][i]->species->name!=creature.species->name))
            {
                grid.squares[creature.location.r][i]->programID=1;
                grid.squares[creature.location.r][i]->species=creature.species;
                break;
            }
        }
    }
    if ((creature.direction==WEST)&&(creature.location.c!=0))
    {
        for (int i=creature.location.c-1;i>=0;i--)
        {
            if ((grid.squares[creature.location.r][i]!=NULL)&&(grid.squares[creature.location.r][i]->species->name!=creature.species->name))
            {
                grid.squares[creature.location.r][i]->programID=1;
                grid.squares[creature.location.r][i]->species=creature.species;
                break;
            }
        }
    }
    if ((creature.direction==NORTH)&&(creature.location.r!=0))
    {
        for (int i=creature.location.r-1;i>=0;i--)
        {
            if ((grid.squares[i][creature.location.c]!=NULL)&&(grid.squares[i][creature.location.c]->species->name!=creature.species->name))
            {
                grid.squares[i][creature.location.c]->programID=1;
                grid.squares[i][creature.location.c]->species=creature.species;
                break;
            }
        }
    }
    if ((creature.direction==SOUTH)&&(creature.location.r!=grid.height-1))
    {
        for (int i=creature.location.r+1;i<grid.height;i++)
        {
            if ((grid.squares[i][creature.location.c]!=NULL)&&(grid.squares[i][creature.location.c]->species->name!=creature.species->name))
            {
                grid.squares[i][creature.location.c]->programID=1;
                grid.squares[i][creature.location.c]->species=creature.species;
                break;
            }
        }
    }
}
void infectnoArch(grid_t &grid, creature_t &creature)
{
    if ((creature.direction==EAST)&&(creature.location.c!=grid.width-1))
    {
        if ((grid.squares[creature.location.r][creature.location.c+1]!=NULL)&&(grid.terrain[creature.location.r][creature.location.c+1]!=FOREST)&&(grid.squares[creature.location.r][creature.location.c+1]->species->name!=creature.species->name))
        {
            grid.squares[creature.location.r][creature.location.c+1]->programID=1;
            grid.squares[creature.location.r][creature.location.c+1]->species=creature.species;
        }
    }
    if ((creature.direction==WEST)&&(creature.location.c!=0))
    {
        if ((grid.squares[creature.location.r][creature.location.c-1]!=NULL)&&(grid.terrain[creature.location.r][creature.location.c-1]!=FOREST)&&(grid.squares[creature.location.r][creature.location.c-1]->species->name!=creature.species->name))
        {
            grid.squares[creature.location.r][creature.location.c-1]->programID=1;
            grid.squares[creature.location.r][creature.location.c-1]->species=creature.species;
        }
    }
    if ((creature.direction==NORTH)&&(creature.location.r!=0))
    {
        if ((grid.squares[creature.location.r-1][creature.location.c]!=NULL)&&(grid.terrain[creature.location.r-1][creature.location.c]!=FOREST)&&(grid.squares[creature.location.r-1][creature.location.c]->species->name!=creature.species->name))
        {
            grid.squares[creature.location.r-1][creature.location.c]->programID=1;
            grid.squares[creature.location.r-1][creature.location.c]->species=creature.species;
        }
    }
    if ((creature.direction==SOUTH)&&(creature.location.r!=grid.height-1))
    {
        if ((grid.squares[creature.location.r+1][creature.location.c]!=NULL)&&(grid.terrain[creature.location.r+1][creature.location.c]!=FOREST)&&(grid.squares[creature.location.r+1][creature.location.c]->species->name!=creature.species->name))
        {
            grid.squares[creature.location.r+1][creature.location.c]->programID=1;
            grid.squares[creature.location.r+1][creature.location.c]->species=creature.species;
        }
    }
}
bool simulateCreature(creature_t &creature, grid_t &grid, bool verbose)
{
    instruction_t ins;
    string dir;
    bool over=false;
    int r,c;
    r=creature.location.r;
    c=creature.location.c;
    switch (creature.direction)
    {
        case EAST:dir="east";break;
        case WEST:dir="west";break;
        case NORTH:dir="north";break;
        case SOUTH:dir="south";break;
    }
    if (creature.hillActive==false) {creature.hillActive=true;return false;}
        else
        {
            cout<<"Creature ("<<creature.species->name<<" "<<dir<<" "<<r<<" "<<c<<") takes action:";
            if (verbose) cout<<endl;
            while (!over)
            {
                ins=getInstruction(creature);
                switch (ins.op)
                {
                    case HOP:
                        {
                            if (verbose) cout<<"Instruction "<<creature.programID<<": hop\n";
                                else cout<<" hop\n";
                            hop(creature,grid);
                            over=true;
                            creature.programID++;
                            if ((grid.terrain[creature.location.r][creature.location.c]==HILL)&&(creature.ability[FLY]==false))
                                creature.hillActive=false;
                            break;
                        }
                    case LEFT:
                        {
                            if (verbose) cout<<"Instruction "<<creature.programID<<": left\n";
                                else cout<<" left\n";
                            creature.direction=leftFrom(creature.direction);
                            over=true;
                            creature.programID++;
                            if ((grid.terrain[creature.location.r][creature.location.c]==HILL)&&(creature.ability[FLY]==false))
                                creature.hillActive=false;
                            break;
                        }
                    case RIGHT:
                        {
                            if (verbose) cout<<"Instruction "<<creature.programID<<": right\n";
                                else cout<<" right\n";
                            creature.direction=rightFrom(creature.direction);
                            over=true;
                            creature.programID++;
                            if ((grid.terrain[creature.location.r][creature.location.c]==HILL)&&(creature.ability[FLY]==false))
                                creature.hillActive=false;
                            break;
                        }
                    case INFECT:
                        {
                            if (verbose) cout<<"Instruction "<<creature.programID<<": infect\n";
                                else cout<<" infect\n";
                            if (creature.ability[ARCH]) infectArch(grid,creature);
                                else infectnoArch(grid,creature);
                            over=true;
                            creature.programID++;
                            if ((grid.terrain[creature.location.r][creature.location.c]==HILL)&&(creature.ability[FLY]==false))
                                creature.hillActive=false;
                            break;
                        }
                    case IFEMPTY:
                        {
                            if (verbose) cout<<"Instruction "<<creature.programID<<": ifempty "<<ins.address<<endl;
                            if (ifempty(grid,creature)) creature.programID=ins.address;
                                else creature.programID++;
                            break;
                        }
                    case IFENEMY:
                        {
                            if (verbose) cout<<"Instruction "<<creature.programID<<": ifenemy "<<ins.address<<endl;
                            if (ifenemy(grid,creature)) creature.programID=ins.address;
                                else creature.programID++;
                            break;
                        }
                    case IFSAME:
                        {
                            if (verbose) cout<<"Instruction "<<creature.programID<<": ifsame "<<ins.address<<endl;
                            if (ifsame(grid,creature)) creature.programID=ins.address;
                                else creature.programID++;
                            break;
                        }
                    case IFWALL:
                        {
                            if (verbose) cout<<"Instruction "<<creature.programID<<": ifwall "<<ins.address<<endl;
                            if (ifwall(grid,creature)) creature.programID=ins.address;
                                else creature.programID++;
                            break;
                        }
                    case GO:
                        {
                            if (verbose) cout<<"Instruction "<<creature.programID<<": go "<<ins.address<<endl;
                            creature.programID=ins.address;
                            break;
                        }
                }
            }
            return true;
        }
}
