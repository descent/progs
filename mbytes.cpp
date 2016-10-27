// ref: http://www.cplusplus.com/reference/cstdlib/mblen/
// ref: http://en.cppreference.com/w/cpp/locale/setlocale

#if 0
/* mblen example */
#include <cstdio>      /* printf */
#include <cstdlib>     /* mblen, mbtowc, wchar_t(C) */
#include <clocale>

using namespace std;

void printbuffer (const char* pt, size_t max)
{
  int length;
  wchar_t dest;

  mblen (NULL, 0);         /* reset mblen */
  mbtowc (NULL, NULL, 0);  /* reset mbtowc */

  while (max>0) 
  {
    length = mblen (pt, max);
    printf("length: %d\n", length);
    if (length<1) break;
    mbtowc(&dest,pt,length);
    printf ("[%lc]",dest);
    pt+=length; 
    max-=length;
  }
  printf ("\n");
}

int main()
{
  std::setlocale(LC_ALL, "en_US.UTF-8");
  //const char str [] = "test string";
  const char str [] = "中文";

  printbuffer (str,sizeof(str));

  return 0;
}
#endif

#include <clocale>
#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
  string str(argv[1]);
  unsigned int strLen = str.length();
  cout << "Length (char-values): " << strLen << '\n';
  setlocale(LC_ALL, "en_EN.UTF-8");
  unsigned int u = 0;
  const char *c_str = str.c_str();
  unsigned int charCount = 0;
  while(u < strLen)
  {
    u += mblen(&c_str[u], strLen - u);
    charCount += 1;
  }
  cout << "Length (characters): " << charCount << endl; 
}
