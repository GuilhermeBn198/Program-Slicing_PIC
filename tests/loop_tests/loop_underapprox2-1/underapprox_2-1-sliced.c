/* Generated by Frama-C */
/*@ assigns \nothing; */
extern  __attribute__((__nothrow__, __noreturn__)) void __assert_fail
(char const *, char const *, unsigned int, char const *) __attribute__((
__leaf__));

void reach_error_slice_1(void)
{
  __assert_fail("0","underapprox_2-1.c",(unsigned int)3,"reach_error");
  return;
}

void __VERIFIER_assert_slice_1(void)
{
  reach_error_slice_1();
  return;
}

void main(void)
{
  unsigned int x = (unsigned int)0;
  unsigned int y = (unsigned int)1;
  while (x < (unsigned int)6) {
    x ++;
    y *= (unsigned int)2;
  }
  __VERIFIER_assert_slice_1();
  return;
}

