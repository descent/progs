#include <cstdio>
#include <string>
#include <cctype>

#include <iostream>


using namespace std;

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

int get_token(string &token)
{
  int c;

  do
  {
    c = getchar_la();
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

int get_bcgl(string &token)
{
  int c;

  do
  {
    c = getchar_la();
  }while(isspace(c));

  if (c == 'b')
  {
    token.push_back(c);
    c = getchar_la();
    if (c == 'c')
    {
      token.push_back(c);
      c = getchar_la();
      if (c == 'g')
      {
        token.push_back(c);
        c = getchar_la();
        if (c == 'l')
        {
          token.push_back(c);
          return OK;
        }
        else
          ungetchar_la(c);
      }
      else
        ungetchar_la(c);

    }
    else
    {
      ungetchar_la(c);
    }
  }
  else
  {
    return ERR;
  }


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
            else if (c == '\x1b')
            {
              c = getchar_la();
              if (c == '\x5b')
              {
                c = getchar_la();
                switch (c)
                {
                  case 'A': // up
                  {
                    return UP;
                  }
                  case 'B': // down
                  {
                    return DOWN;
                  }
                  case 'C': // right
                  {
                    return RIGHT;
                  }
                  case 'D': // left
                  {
                    return LEFT;
                  }
                  default:
                  {
                    printf("xx error\n");
                    return ERR;
                  }
                }
              }
              else
              {
                printf("error\n");
                return ERR;
              }
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

// terminal escape sequence
// \x1b[31m
// \x1b[31;41m"

int get_tes_token(string &token)
{
  int c;

  do
  {
    c = getchar_la();
  }while(isspace(c));

  if (c == EOF)
    return EOF;
  else if (c == '\x1b') // ESC
       {
         token.push_back(c);
         c = getchar_la();
         if (c == '[')
         {
           do
           {
             token.push_back(c);
             c = getchar_la();
           } while(isdigit(c));

           if (c == 'm')
           {
             token.push_back(c);
             return OK;
           }
           else if (c == ';')
                {
                   do
                   {
                     token.push_back(c);
                     c = getchar_la();
                   } while(isdigit(c));
                   if (c == 'm')
                   {
                     token.push_back(c);
                     return OK;
                   }
                }
         }
         else if (c == ']')
            {
              // ref: https://www.gnu.org/software/screen/manual/html_node/Control-Sequences.html
              // ESC ] 0 ; string ^G     (A)     Operating System Command (Hardstatus, xterm
              token.push_back(c);

             c = getchar_la();
             if (c == '0')
             {
              token.push_back(c);
               c = getchar_la();
               if (c == ';')
               {
                 do
                 {
                   token.push_back(c);
                   c = getchar_la();
                 } while(c != 0x7);

                 if (c == 0x7) // ^G
                 {
                   token.push_back(c);
                   return OK;
                 }

                 
               }
             }
              
            }
         else // unknown tes
         {
           do
           {
             token.push_back(c);
             c = getchar_la();
           } while(isascii_ex1(c));
           la = c;
           return OK; 
         }

       }
       else
       {
         do
         {
           token.push_back(c);
           c = getchar_la();
         } while(isascii_ex1(c));
         la = c;
         return OK; 
       }

  if (c != EOF)
    la = c;
  return ERR;
}


int main(int argc, char *argv[])
{
  int c;
  #if 0
  while(1)
  {
    c = getchar();
    printf("%x\n", c);
  }
  #endif
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
    int ret = get_bcgl(token);
    //int ret = get_c_comment_token(token);
    //int ret = get_string_token(token);
    //int ret = get_tes_token(token);
    switch (ret)
    {
      case UP:
      {
        cout << "up" << endl;
        break;
      }
      case DOWN:
      {
        cout << "down" << endl;
        break;
      }
      case LEFT:
      {
        cout << "left" << endl;
        break;
      }
      case RIGHT:
      {
        cout << "right" << endl;
        break;
      }
      case OK:
      {
        const char *s = token.c_str();
 
        if (*s == '\x1b')
        {
          cout << "token: ESC " << s+1 << endl;
        }
        else 
          cout << "token: " << token << endl;
        break;
      }

      case EOF:
      {
        cout << endl << "xx eof" << endl;
        return 0;
      }
      case ERR:
      {
        cout << "token error" << endl;
        break;
      }
    }

    token.clear();
  }
#endif
  return 0;
}
