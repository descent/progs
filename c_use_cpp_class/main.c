#include "map.h"

int main(void) 
{
  map_insert("key0", "value0" );
  map_insert("key1", "value1" );
  map_insert("key2", "value2" );
  print_map();

  return 0;
}
