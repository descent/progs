
void my_func1(int fruit[2][3][5]){;}
void my_func2(int fruit[][3][5]){;}
void my_func3(int (*fruit)[3][5]){;}

int main(int argc, const char *argv[])
{
  int apricot[2][3][5];
  my_func1(apricot);
  my_func2(apricot);
  my_func3(apricot);

  int (*p)[3][5] = apricot;
  my_func1(p);
  my_func2(p);
  my_func3(p);

  int (*q)[2][3][5] = &apricot;
  my_func1(*q);
  my_func2(*q);
  my_func3(*q);
  return 0;
}
