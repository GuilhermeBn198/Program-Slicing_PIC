/* Generated by Frama-C */
/*@ assigns \nothing; */
extern  __attribute__((__nothrow__, __noreturn__)) void __assert_fail
(char const *, char const *, unsigned int, char const *) __attribute__((
__leaf__));

void reach_error_slice_1(void)
{
  __assert_fail("0","array_1-2.c",(unsigned int)3,"reach_error");
  return;
}

void __VERIFIER_assert_slice_1(int cond)
{
  if (! cond) reach_error_slice_1();
  return;
}

void main(void)
{
  int A[2048];
  int i;
  i = 0;
  while (i < 1024) {
    A[i] = i;
    i ++;
  }
  __VERIFIER_assert_slice_1(A[1023] == 1023);
  return;
}

