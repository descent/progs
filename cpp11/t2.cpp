#include <iostream>
#include <chrono>
#include <vector>
#include <string>

using namespace std;
using namespace std::chrono;

#include <unistd.h>
#include <time.h>

int main(int argc, char *argv[])
{
  //duration<int, ratio<1, 1000>> d{2};
  //cout << d.count() << endl;
  time_point<system_clock> epoch = time_point<system_clock>{};
  time_point<system_clock> tp = system_clock::now();

  time_t t = system_clock::to_time_t(tp);

  string ts = ctime(&t);
  cout << "now: " << ts << endl;

  time_point<steady_clock> tp1 = steady_clock::now();

  time_point<steady_clock> steady_epoch = time_point<steady_clock>{};

  //duration<int, ratio<1,1000000>> d = duration_cast<microseconds>(epoch - tp);
  //duration<int, ratio<1,1000000>> d = duration_cast<microseconds>(tp - epoch);
 
  typedef duration<unsigned long long, ratio<1,1000000>> unit;
  //typedef duration<int, ratio<1,1000000>> unit;
  //typedef microseconds unit;
  unit d = duration_cast<unit>(tp - epoch);
  cout << d.count() << endl;

  return 0;
}
