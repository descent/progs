#include <cstdio>
#include <string>
#include <cctype>

#include <iostream>
#include <vector>

using namespace std;

#define END_STATE 255
#define NO_MATCH 254


#define OK 0
#define ERR 1

#define UP 2
#define DOWN 3
#define RIGHT 4
#define LEFT 5

int isgraph_ex1(int c)
{
  if (c == ' ')
    return 1;
  else
    return isgraph(c);
}

static inline int isascii_ex1(int c) 
{
  if (c == '\x1b')
    return 0;
  else
    return isascii(c);
}

static inline int isascii_ex(int c) 
{
  if (c == '"')
    return 0;
  else
    return isascii(c);
}

// printable ascii, but not (, )
static inline int isgraph_ex(int c) 
{
#if 1
  if (c == '(')
    return 0;
  if (c == ')')
    return 0;
#endif
  return isgraph(c);
}

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

int ungetchar_la(int c)
{
  la = c;
}


int get_token(int c, int &state)
{
  switch (state)
  {
    case 0:
    {
      state = NO_MATCH;
      if (isspace(c))
      {
        state = 0;
      }
      else if (isdigit(c))
           {
             state = 1;
           }
           else if (isalpha(c))
                {
                  state = 2;
                }

      break;
    }
    case 1:
    {
      state = NO_MATCH;
      if (isdigit(c))
      {
        state = 1;
      }
      else
      {
        state = END_STATE;
      }
      break;
    }
    case 2:
    {
      state = NO_MATCH;
      if(isalnum(c))
      {
        state = 2;
      }
      else
      {
        state = END_STATE;
      }
      break;
    }
  }

#if 0
  do
  {
    state = 0;
  }while(isspace(c));

  if (c == EOF)
  {
    cout << endl << "eof" << endl;
    return EOF;
  }
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
                   {
                     token = "==";
                   }
                   else
                   {
                     la = c;
                     token = "=";
                   }
                   return OK;
                 }
                 else
                 {
                   return ERR;
                 }
#endif
  return OK;
}



// " asdf "
int get_string_token(string &token)
{
  int c;

  do
  {
    c = getchar_la();
  }while(isspace(c));

  if (c == EOF)
    return EOF;
  else if (c == '"')
       {
         do
         {
           token.push_back(c); 
           c = getchar_la();
         }while (isascii_ex(c));
         if (c=='"')
         {
           token.push_back(c); 
           return OK;
         }
         else
         {
           printf("should \"\n");
           return ERR;
         }

         
       }
  
}

int segment_lex(const string input_data, int &state, vector<string> &tokens, bool last = false)
{
  static string token;
  int i=0;
  auto len = input_data.size();

  while(i < len)
  {
    int ret = get_token(input_data[i], state);
    if (state == NO_MATCH)
    {
      cout << input_data[i] << " xx no match" << endl;
      return ERR;
    }
    cout << "i: " << i << ", input_data[i]: " << input_data[i] << ", state: " << state << ", ret: " << ret << endl;

    if (state != END_STATE)
    {
      token.push_back(input_data[i]);
      ++i;
    }
    else
    {
    }

    if (ret == OK && state == END_STATE)
    {
      cout << "token: " << token << endl;
      tokens.push_back(token);
      token.clear();
      state=0;
    }
  }
  if (last == true)
  {
    cout << "last token: " << token << endl;
    tokens.push_back(token);
  }
  
  return OK;
}

int main(int argc, char *argv[])
{
  int c;
  string pat = "abc";
  if (argc >= 2)
  {
    pat = argv[1];
  }
#if 1
  int state=0;
  int i=0;
  int begin_index = 0;
  int end_index = 0;
  //string input_data = {"int i=9"};
  string input_data[] = {"123int-", "abc789"};
  vector<string> tokens;

  int input_size = sizeof(input_data)/sizeof(string);
  cout << "org input string:" << endl;
  for (int i=0 ; i < input_size ; ++i)
  {
    cout << input_data[i] << endl;
  }

  for (int i=0 ; i < input_size ; ++i)
  {
    int ret;
    if (i == (input_size-1))
      ret = segment_lex(input_data[i], state, tokens, true);
    else
      ret = segment_lex(input_data[i], state, tokens);
    if (state == NO_MATCH)
    {
      cout << input_data[i] << " yy no match" << endl;
      break;
    }
  }
  for (auto &i : tokens)
  {
    cout << i << endl;
  }
#endif
  return 0;
}
