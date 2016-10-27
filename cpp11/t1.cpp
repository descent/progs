#include <iostream>
#include <chrono>
#include <vector>
#include <string>

using namespace std;
using namespace std::chrono;

#include <unistd.h>
#include <time.h>

//string to_string(const steady_clock::time_point &tp)
string to_string(const system_clock::time_point &tp)
{
  //time_t t = steady_clock::to_time_t(tp);
  time_t t = system_clock::to_time_t(tp);
}

auto time_start()
{
  return steady_clock::now();
}


long long time_pass(auto start)
{
  auto t2 = steady_clock::now();
  auto dus = duration_cast<microseconds>(t2 - start);
  cout << dus.count() << endl;
  auto tick = dus.count();
  return tick;
}

int main(int argc, char *argv[])
{
  auto t1 = steady_clock::now();
  //auto t1 = time_start();

  sleep(5);
  auto t2 = steady_clock::now();
  auto dms = duration_cast<milliseconds>(t2-t1);
  auto dus = duration_cast<microseconds>(t2-t1);
  cout << "ms: " << dms.count() << endl;
  cout << "us: " << dus.count() << endl;

  //diff = time_pass(t1);
  //cout << "t1: " << t1 << ", diff2: " << diff << endl;

  #if 0
  auto diff = time_pass(t1);

  auto dms = duration_cast<milliseconds>(t2-t1);
  auto dus = duration_cast<microseconds>(t2-t1);
  

  now = std::chrono::system_clock::now();
  now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
  //cout << "b now_ms: " << now_ms << endl;
  #endif

  return 0;
}
