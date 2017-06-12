#include <stdio.h>


typedef struct A_ A;

typedef void VfPtr(A *a);
VfPtr *vfptr[2];

typedef struct A_
{
  int k;
  typeof (vfptr) *vt;
}A;

typedef struct B_
{
  int k;
  int h;
  typeof (vfptr) *vt;
}B;


void vf_a(A *a)
{
  printf("k: %d\n", a->k);
}

void vf_b(A *a)
{
  B *b = (B*)a;
  printf("h: %d\n", b->h);
}

void ctor_a(A *a)
{
  a->k = 1;
  a->vt = &vfptr;
}

void ctor_b(B *b)
{
  b->h = 2;
  b->vt = &vfptr;
}

int main(int argc, char *argv[])
{
  A *pa;  
  A a;
  B b;

  vfptr[0] = vf_a;
  vfptr[1] = vf_b;

  ctor_a(&a);
  ctor_b(&b);

#if 0
  pa->vf();
#endif

  typeof (vfptr) *vt;
  VfPtr *vfp;

  pa = &a;
  vt = pa->vt;    // get pa virtaul table
  vfp = (*vt)[0]; // index 0 is vf_a
  (*vfp)(pa);     // call vf_a the virtual function

  pa = &b;
  vt = pa->vt;    // get pa virtaul table
  vfp = (*vt)[1]; // index 1 is vf_b
  (*vfp)(pa);     // call vf_b the virtual function

#if 0
  VfPtr *avfp = (*vt)[0];
  VfPtr *bvfp = (*vt)[1];

  printf("vf_a: %p\n", vf_a);
  printf("vf_b: %p\n", vf_b);
  printf("avfp: %p\n", avfp);
  printf("bvfp: %p\n", bvfp);
#endif

  //(*(pa->vt[1]))(pa);

  return 0;
}
