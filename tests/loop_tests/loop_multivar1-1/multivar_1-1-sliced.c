/* Generated by Frama-C */
void reach_error_slice_1(void)
{
  return;
}

extern unsigned int __VERIFIER_nondet_uint(void);

void __VERIFIER_assert_slice_1(int cond)
{
  if (! cond) reach_error_slice_1();
  return;
}

void main(void)
{
  unsigned int x = __VERIFIER_nondet_uint();
  unsigned int y = x;
  while (x < (unsigned int)1024) {
    x ++;
    y ++;
  }
  __VERIFIER_assert_slice_1(x == y);
  return;
}

