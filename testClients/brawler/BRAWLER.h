/////////////////////////////////////////////////////////
/// @file .h
///
/// @author Brian Goldman
///
/// @language C++
///
/// @compiler g++ 4.43
///
/// @project 
///
/// @description 
///
/////////////////////////////////////////////////////////
#ifndef BRAWLER_H
#define BRAWLER_H

const int GAMESPEREVAL = 3;
const int OFFRATE = 4;
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
using namespace std;
struct Individual
{
  int played;
  int score;
  vector<int> gene;

  static void load(string populationFile, vector<Individual>& pop,int popSize, int geneSize, int geneRange);
  static void save(string populationFile, vector<Individual>& pop);
};


class BRAWLER
{
  public:
    void putInInit(string populationFile, int popSize, int geneSize, int geneRange);
    void putInEnd(int brawlerScore);
    
    int operator()(int i){return pop[inUse].gene[i];}
  private:
    vector<Individual> pop;
    string info;
    int inUse;
};


#endif
