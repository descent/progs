#include <cstdio>
#include <string>
#include <cctype>

#include <iostream>

using namespace std;



int la=-1;

int getchar_la()
{
  if (la != -1)
  {
    int tmp=la;
    la = -1;
    return tmp;
  }
  else
    return getchar();
}

string get_token()
{
  int c;
  string token;

  do
  {
    c = getchar_la();
  }while(isspace(c));

  if (c == EOF)
    return "";
  else if (isdigit(c))
       {
         do
         {
           token.push_back(c); 
           c = getchar_la();
         }while(isdigit(c));
       }
       else if (isalpha(c))
            {
              do
              {
                token.push_back(c); 
                c = getchar_la();
              } while(isalnum(c));
            }
            else if (c == '=')
                 {
                   c = getchar_la();
                   if (c == '=')
                     return "==";
                   else
                   {
                     la = c;
                     return "=";
                   }
                 }
                 else
                 {
                   return "";
                 }
  if (c != EOF)
    la = c;
  return token;
}

int main(int argc, char *argv[])
{
  string token = get_token();

  cout << "token: " << token << endl;
  
  return 0;
}
