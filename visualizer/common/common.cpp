#include "common.h"

#if __DEBUG_NEW__
#include <list>
using namespace std;
list< ALLOC_INFO > allocMap;


void AddTrack(long int addr,  long int asize,  const char *fname, long int lnum)
{
  ALLOC_INFO info;

  info.address = addr;
  strncpy(info.file, fname, 63);
  info.line = lnum;
  info.size = asize;
  allocMap.push_back( info );
};

void RemoveTrack( long int addr )
{
  cout << allocMap.size() << endl;
  for
    ( 
    list< ALLOC_INFO >::iterator i = allocMap.begin();
    i != allocMap.end();
    i++
    )
  {
    if( addr == i->address )
    {
      allocMap.erase( i );
      return;
    }
  }


};

#endif

#if __DEBUG__
void DumpUnfreed()
{
  long int totalSize = 0;

  cout << "UNFREEDS -----------------------------------------------------" << endl;
  for
    (
    list< ALLOC_INFO >::iterator i = allocMap.begin();
    i != allocMap.end();
    i++
    )
  {
    cout << "File: " << i->file << ", Line: " << i->line << " unfreed." << endl;
    totalSize += i->size;
  }

  cout << "UNFREEDS -----------------------------------------------------" << endl;
  cout << "Total Unfreed: " << totalSize << " bytes." << endl;

};
#endif
