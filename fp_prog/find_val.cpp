#include <iostream>

using namespace std;

int element_0(const int *arr, int len, int val, int index)
{
  if (index >= len)
  {
    // not found
    return -1;
  }
  if (arr[index]  == val)
    return index;
  else
    element_0(arr, len, val, index+1);
}

int find_elem(const int *arr, int len, int val, int index)
{
  return element_0(arr, len, val, index);
}

int main(int argc, char *argv[])
{
  int arr[]={0, 1,2,3,4,5,6,7,8,9,10};
  auto arr_size = sizeof(arr)/sizeof(int);

  int index = find_elem(arr, arr_size, 50, 0);
  cout << "index: " << index << endl;
  
  return 0;
}
