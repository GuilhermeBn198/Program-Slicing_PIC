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
  unsigned int x = (unsigned int)0;
  unsigned int y = __VERIFIER_nondet_uint();
  while (x < (unsigned int)99) 
    if (y % (unsigned int)2 == (unsigned int)0) x += (unsigned int)2;
    else x ++;
  __VERIFIER_assert_slice_1(x % (unsigned int)2 == y % (unsigned int)2);
  return;
}


