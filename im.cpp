#include <string>
#include <vector>
#include <map>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
  vector<string> can_strings;
  can_strings.push_back("我");
  can_strings.push_back("婐");
  can_strings.push_back("捰");


  map<string, vector<string> > key_map;
  key_map[string("xoj")] = can_strings;

  can_strings.clear();

  can_strings.push_back("日");
  can_strings.push_back("衵");
  can_strings.push_back("馹");
  can_strings.push_back("鈤");
  can_strings.push_back("囸");
  key_map[string("jk")] = can_strings;

  while(1)
  {
    string key;
    cin >>  key;
    if (key == "q") break;
    //cout << "key:" << key << endl;
    cout << endl;
    map<string, vector<string> >::iterator it = key_map.find(key);
    if (it != key_map.end() )
    {
      vector<string> can_str = (*it).second;
      for (int i=0 ; i < can_str.size() ; ++i)
      {
        cout << can_str[i] << " ";
      }
      cout << endl;
    }
  }

  return 0;
}
