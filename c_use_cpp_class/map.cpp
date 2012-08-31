#include "map.h"

#include <iostream>
#include <map>

using namespace std;

namespace
{
  std::map< std::string, std::string > internal_map;
}

void map_insert( char const * key, char const * value )
{
   internal_map.insert( make_pair(key, value) );
}

void print_map()
{
  std::map< std::string, std::string>::iterator it = internal_map.begin();

  for (it; it != internal_map.end() ; ++it)
    cout << "key: " << it->first << endl << "value: " << it->second << endl;

}
