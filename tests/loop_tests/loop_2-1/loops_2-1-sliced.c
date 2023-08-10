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

/*@ assigns \result;
    assigns \result \from \nothing; */
extern float __VERIFIER_nondet_float(void);

/*@ assigns \result;
    assigns \result \from \nothing; */
extern int __VERIFIER_nondet_int(void);

void main(void)
{
  int multFactor;
  int temp;
  float x = __VERIFIER_nondet_float();
  /*@ assert Eva: is_nan_or_infinite: \is_finite(x); */
  float oddExp = x;
  float evenExp = (float)1.0;
  float term = x;
  unsigned int count = (unsigned int)2;
  while (1) {
    /*@ assert
        Eva: is_nan_or_infinite:
          \is_finite(\mul_float(term, \div_float(x, (float)count)));
    */
    /*@ assert
        Eva: is_nan_or_infinite: \is_finite(\div_float(x, (float)count));
    */
    term *= x / (float)count;
    if (count >> 1 % 2 == (unsigned int)0) multFactor = 1;
    else multFactor = -1;
    /*@ assert
        Eva: is_nan_or_infinite:
          \is_finite(\add_float(evenExp, \mul_float((float)multFactor, term)));
    */
    evenExp += (float)multFactor * term;
    count ++;
    /*@ assert
        Eva: is_nan_or_infinite:
          \is_finite(\mul_float(term, \div_float(x, (float)count)));
    */
    term *= x / (float)count;
    /*@ assert
        Eva: is_nan_or_infinite:
          \is_finite(\add_float(oddExp, \mul_float((float)multFactor, term)));
    */
    oddExp += (float)multFactor * term;
    count ++;
    temp = __VERIFIER_nondet_int();
    if (temp == 0) break;
  }
  __VERIFIER_assert_slice_1(oddExp >= evenExp);
  return;
}