/* Generated by Frama-C */
void reach_error_slice_1(void)
{
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
  /*@ assert Eva: initialization: \initialized(&A[1023]); */
  __VERIFIER_assert_slice_1(A[1023] != 1023);
  return;
}