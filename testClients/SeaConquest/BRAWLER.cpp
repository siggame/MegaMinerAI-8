#include "BRAWLER.h"
void Individual::load(string populationFile,vector<Individual>& pop,int popSize, int geneSize,int geneRange)
{
  ifstream in(populationFile.c_str());
  int readPop, readGene;
  if(in.is_open())
  {
    in>>readPop>>readGene;
  }
  // if the file opened and it contains the desired information
  if(in.is_open() && readPop == popSize && readGene==geneSize)
  {
    // read in the population
    pop.resize(popSize);
    for(unsigned int i=0;i<pop.size();i++)
    {
      cout<<"Reading in "<<i<<endl;
      in>>pop[i].played;
      in>>pop[i].score;
      pop[i].gene.resize(geneSize);
      for(int g=0;g<geneSize;g++)
      {
        in>>pop[i].gene[g];
      }
    }
  }
  else // no file found or file contained incorrect stuff
  {
    pop.resize(popSize);
    for(unsigned int i=0;i<pop.size();i++)
    {
      pop[i].played=0;
      pop[i].score=0;
      pop[i].gene.resize(geneSize);
      
      for(unsigned int g=0;g<geneSize;g++)
      {
        pop[i].gene[g]=rand()%geneRange;
      }
    }
  }
  in.close();
}

void Individual::save(string populationFile,vector<Individual>& pop)
{
  cout<<"STARTING SAVE"<<endl;
  ofstream out(populationFile.c_str());
  if(!out.is_open())
  {
    cout<<"SHIT, didn't open!"<<endl;
  }
  out<<pop.size()<<" "<<pop[0].gene.size()<<endl;

  for(unsigned int i=0;i<pop.size();i++)
  {
 //   cout<<"SAVING "<<i<<"/"<<pop.size()<<endl;
    out<<pop[i].played<<" ";
    out<<pop[i].score<<" ";
    for(unsigned int g=0;g<pop[i].gene.size();g++)
    {
      out<<pop[i].gene[g]<<" ";
    }
    out<<endl;
  }
  cout<<"DONE"<<endl;
  out.close();
}
bool descending(const Individual&lhs, const Individual&rhs)
{
  return lhs.score>rhs.score;
}
void BRAWLER::putInInit(string populationFile,int popSize, int geneSize, int geneRange)
{
  info = populationFile;
  Individual::load(info,pop,popSize,geneSize,geneRange);
  vector<int> canPlay;
  for(size_t i=0;i<pop.size();i++)
  {
    // if it hasn't played enough games
    if(pop[i].played < GAMESPEREVAL)
    {
      canPlay.push_back(i);
    }
  }
  // if everyone has played
  if(canPlay.size()==0)
  {
    sort(pop.begin(),pop.end(),descending);
    // do some really nasty (and bad) EA stuff
    int children = pop.size()/OFFRATE;
    int survivors = pop.size()-children;
    for(int i=0;i<children;i++)
    {
      // select a second parent randomly from the survivors
      int second = rand()%survivors;
      // performs uniform crossover
      for(int g=0;g<pop[i].gene.size();g++)
      {
        pop[pop.size()-i-1].gene[g] = pop[i+rand()%2].gene[g];
        // performs a really nasty random reset mutation
        if(static_cast<double>(rand())/RAND_MAX < 0.5/pop[i].gene.size())
        {
          pop[pop.size()-i-1].gene[g] = rand()%geneRange;
        }
      }
    }
    // put everyone in the can play vector
    canPlay.resize(pop.size());
    for(size_t i=0;i<pop.size();i++)
    {
      pop[i].played=0;
      pop[i].score=0;
      canPlay.push_back(i);
    }
  }
  inUse = canPlay[rand()%canPlay.size()];
}
void BRAWLER::putInEnd(int brawlerScore)
{
  pop[inUse].score+=brawlerScore;
  pop[inUse].played++;
  Individual::save(info, pop);
}
