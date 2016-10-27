#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cctype>
using namespace std;

bool is_number(const std::string& s)
{
    return !s.empty() && std::find_if(s.begin(), 
        s.end(), [](char c) { return !std::isdigit(c); }) == s.end();
}

string tree_string(const string &str)
{
    string print_str{str};
    string s1("%");
    string s2("(");
    string s3(")");
    char s4='\n';
    //cout << endl << "XXX:" << print_str << "YYY" << endl;
    if (print_str.find(s1) != string::npos)
    {
      print_str.replace(print_str.find(s1), s1.length(), R"(\%)");
      //cout << endl << "BBB:" << print_str << endl;
    }

    if (print_str.find(s2) != string::npos)
    {
      //cout << endl << "CCC:" << print_str << endl;
      print_str.replace(print_str.find(s2), s2.length(), R"(\()");
    }
    if (print_str.find(s3) != string::npos)
      print_str.replace(print_str.find(s3), s3.length(), R"(\))");
    if (print_str.find(s4) != string::npos)
    {
      print_str.replace(print_str.find(s4), 1, R"(\\n)");
      //cout << endl << "AAA:" << print_str << endl;
    }
  return print_str;
} 

int main(int argc, char *argv[])
{
  vector<string> args;

  string fmt = R"(test %d, %s, %s\n)";
  string p_str = tree_string(fmt);

  args.push_back(fmt);
  args.push_back("123");
  args.push_back("string_test");
  args.push_back("space string");

  string cmd=R"(printf "My name is \"%s\".\nIt's a pleasure to meet you %d.\n" "John" )";
  string cmd_s{"printf "};
  for (auto &i : args)
  {
    cmd_s += "\"";
    cmd_s += i;
    cmd_s += "\"";
    cmd_s += " ";
  }
  cout << "cmd_s: " << cmd_s << endl;

  cmd+="25";
  system(cmd.c_str());
  system(cmd_s.c_str());
  return 0;
}
