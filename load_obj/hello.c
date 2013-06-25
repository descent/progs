int i=0x1234;

void func(int *j)
{
  *j = 0x5678;
  while(1);
}

void hello()
{
  //puts("hello");
  func(&i);
}

