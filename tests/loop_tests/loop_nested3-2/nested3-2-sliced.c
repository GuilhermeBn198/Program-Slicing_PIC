/* Generated by Frama-C */
void reach_error() { assert(0); }

void reach_error_slice_1(void){
  ERROR: {reach_error();}
  return;
}

void __VERIFIER_assert_slice_1(void)
{
  reach_error_slice_1();
  return;
}

void main(void)
{
  __VERIFIER_assert_slice_1();
  return;
}