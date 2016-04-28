#include <cstdio>
#include <string>
#include <cctype>

#include <iostream>

using namespace std;

#define OK 0
#define ERR 1

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

int get_token(string &token)
{
  int c;

  do
  {
    c = getchar_la();
  }while(isspace(c));

  if (c == EOF)
    return EOF;
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
  if (c != EOF)
    la = c;
  return OK;
}

int get_c_comment_token(string &token)
{
  int c;
  int ret = OK;

  do
  {
    c = getchar_la();
  }while(isspace(c));
  if (c == EOF)
    return EOF;
  else if (c == '/')
       {
         token.push_back(c); 
         c = getchar_la();

         if (c == '*')
         {
           token.push_back(c); 
           do
           {
             c = getchar_la();
             token.push_back(c); 
           }while(c != '*');

           c = getchar_la();

           if (c == '/')
           {
             token.push_back(c); 
             return OK;
           }
           else
           {
             return ERR;
             ret = ERR;
           }
         }
         else
         {
           return ERR;
           ret = ERR;
         }
       }
       else
       {
         return ERR;
         ret = ERR;
       }


  if (c != EOF)
    la = c;
  return ret;
}

int get_se_token(string &token)
{
  int c;

  do
  {
    c = getchar_la();
  }while(isspace(c));

  if (c == EOF)
    return EOF;
  else if (c == '(')
       {
         token = '(';
         return OK;
       }
       else if (c == ')')
            {
              token = ')';
              return OK;
            }
            else if (isgraph_ex(c)) // printable ascii, but not (, )
                 {
                   do
                   {
                     token.push_back(c); 
                     c = getchar_la();
                     if (c==EOF)
                     {
                       printf("EOF\n");
                       exit(5);
                     }
                     else
                       printf("c: %c\n", c);


                   }while(isgraph_ex(c));
                 }
                 else
                 {
                   return ERR;
                 }


  if (c != EOF)
    la = c;
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

int main(int argc, char *argv[])
{
  int c;
#if 0
  while(1)
  {
    c = getchar();
    if (c==EOF)
    {
      printf("EOF\n");
      return -1;
    }
    else
    {
      printf("\nc: %c\n", c);
    }
  }
#endif
#if 1
  while(1)
  {
    string token;

    //int ret = get_token(token);
    //int ret = get_se_token(token);
    //int ret = get_c_comment_token(token);
    int ret = get_string_token(token);
    if (ret == EOF)
    {
      break;
    }
    if (ret == OK)
    {
      cout << "token: " << token << endl;
    }
    else
    {
      cout << "token error" << endl;
    }
    token.clear();
  }
#endif
  return 0;
}
