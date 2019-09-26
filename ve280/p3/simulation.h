#ifndef SIMULATION_H
#define SIMULATION_H

#include <string>
#include "world_type.h"

bool initWorld(world_t &world, const string &speciesFile,
 const string &worldFile);
// MODIFIES: world
//
// EFFECTS: Initialize "world" given the species summary file
// "speciesFile" and the world description file
// "worldFile". This initializes all the components of
// "world". Returns true if initialization is successful.

bool simulateCreature(creature_t &creature, grid_t &grid, bool
verbose);
// REQUIRES: creature is inside the grid.
//
// MODIFIES: creature, grid, cout.
//
// EFFECTS: Simulate one turn of "creature" and update the creature,
// the infected creature, and the grid if necessary.
// The creature programID is always updated. The function
// also prints to the stdout the procedure. If verbose is
// true, it prints more information.

void printGrid(const grid_t &grid);
// MODIFIES: cout.
//
// EFFECTS: print a grid representation of the creature world.

point_t adjacentPoint(point_t pt, direction_t dir);
// EFFECTS: Returns a point that results from moving one square
// in the direction "dir" from the point "pt".

direction_t leftFrom(direction_t dir);
// EFFECTS: Returns the direction that results from turning
// left from the given direction "dir".

direction_t rightFrom(direction_t dir);
// EFFECTS: Returns the direction that results from turning
// right from the given direction "dir".

instruction_t getInstruction(const creature_t &creature);
// EFFECTS: Returns the current instruction of "creature".

void hop(creature_t &creature, grid_t &grid);
// EFFECTS: Let the creature hop if it can.

bool ifempty(const grid_t &grid, const creature_t &creature);
// EFFECTS: Return true if the creature is facing a square without creatures or the creature is not facing the boundary.

bool ifenemy(const grid_t &grid, const creature_t &creature);
// EFFECTS: Return true if the creature is facing a square with a creature of other species and the square is not forest.

bool ifsame(const grid_t &grid, const creature_t &creature);
// EFFECTS: Return true if the creature is facing a square with a creature of same specie and the square is not forest.
 
bool ifwall(const grid_t &grid, const creature_t &creature);
// EFFECTS: Return true is the creature is facing the boundary or a creature without ability of fly is facing a lake.

void infectArch(grid_t &grid, creature_t &creature);
// EFFECTS: Infect the nearest creature of other species in the direction, including the creature in the forest.

void infectnoArch(grid_t &grid, creature_t &creature);
// EFFECTS: Infect the creature in the facing sqaure. if the square is forest, do nothing.
#endif // SIMULATION_H
