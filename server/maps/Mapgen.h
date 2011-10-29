//Jeremy Daugherty
//Sig-Game, Megaminer8,
//Map Generator header file

#ifndef MAPGEN
#define MAPGEN

#include<iostream>
using namespace std;

#include<cstdlib>
#include<ctime>
#include<cmath>

const char empty = '.';
const char wall = 'x';
const char base = '0';
const int mapbase_height = 20;
const int mapbase_width = 20;
const int fullmap_width = 40;
//These are for modifying the ammount of walls in a map
const float max_walls = 100;
const float max_empty = mapbase_height * mapbase_width - max_walls;

//pre: a 2d char array, max_wall, max_empty variables 
//post: the 2d array completed into a map.
//desc: generates a random map
void mapgen_random(char basemap[][mapbase_width], const float max_wall, const float max_empty);

/*
//pre: the 2d map array, and the max_wall and max_empty bariables.
//post: the corrected 2d map array
//desc: generates the map based off of modified probability.
void mapgen_building(char basemap[][mapbase_width] const float max_wall, const float max_empty);
*/

//pre: map, the totatl walls left and empty left.
//post: the check that for all empty squares connected to another.
//desc: the loop to check the map.
void continuitycheck_loop(char basemap[][mapbase_width], float& walls_left, float& empty_left);

//void continuity check( char basemap[][mapbase_width], const int& change_height, const int& change_width);

//void swap(char basemap[][mapbase_width], int height_change, int width_change);

#endif