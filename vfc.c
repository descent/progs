// try use c to implement c++ virtual function.
#include <stdio.h>
#include <stdint.h>

typedef struct A_ A;

typedef void VfPtr(A *a);
uintptr_t a_vfptr_table[2];
uintptr_t b_vfptr_table[2];

typedef struct A_
{
  typeof (a_vfptr_table) *vt;
  int k;
}A;

typedef struct B_
{
  typeof (b_vfptr_table) *b_vt;
  int k;
  int h;
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
  a->vt = &a_vfptr_table;
}

void ctor_b(B *b)
{
  b->h = 2;
  b->b_vt = &b_vfptr_table;
}

int main(int argc, char *argv[])
{
  A *pa;  
  A a;
  B b;

  a_vfptr_table[0] = 0;
  a_vfptr_table[1] = (uintptr_t)vf_a;

  b_vfptr_table[0] = 0;
  b_vfptr_table[1] = (uintptr_t)vf_b;

  ctor_a(&a);
  ctor_b(&b);

#if 0
  pa->vf();
  (pa->vf[1])();
#endif

  uintptr_t vt;
  VfPtr *vfp;

  pa = &a;
  //vt = pa->vt;    // get pa virtaul table
  vt = (uintptr_t)(*(int *)pa);    // get pa virtaul table
  vfp = (VfPtr *)*((uintptr_t *)(vt + sizeof(uintptr_t))); // index 1 is vf_a, index 0 put rtti info
  (*vfp)(pa);     // call vf_a the virtual function

  pa = &b;
  //vt = ((B*)pa)->b_vt;    // get pa virtaul table
  vt = (uintptr_t)(*(int *)pa);    // get pa virtaul table
  vfp = (VfPtr *)*((uintptr_t *)(vt + sizeof(uintptr_t))); // index 1 is vf_a, index 0 put rtti info
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
