#include "map.h"

#include <iostream>
#include <map>

using namespace std;

std::map<
         std::string,
         std::string
        > internal_map;

extern "C" {

void map_insert( char const * key,
                 char const * value )
{
   cout << "key: " << key << endl
        << "value: " << value << endl;

   internal_map.insert( make_pair(key, value) );
}
