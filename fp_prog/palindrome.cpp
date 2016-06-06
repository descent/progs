#include <iostream>
#include <cstring>

using namespace std;

bool is_palindrome(const char *str, size_t len)
{
  if (len <= 1)
    return true;
  else
  {
    if (str[0] == str[len-1])
    {
      return is_palindrome(str+1, len - 2);    
    }
  }
  return false;
}

int main(int argc, char *argv[])
{
  const char *str = "abba";
  if (argc > 1)
    str = argv[1];

  cout << str << " is " << (is_palindrome(str, strlen(str)) == true ? "palindrome" : "not palindrome") << endl;
  return 0;
}
