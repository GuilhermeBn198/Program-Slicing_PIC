/* Generated by Frama-C */
void reach_error_slice_1(void)
{
  return;
}

void main(void)
{
  unsigned int a;
  unsigned int b;
  unsigned int c;
  unsigned int d;
  unsigned int e;
  unsigned int uint32_max;
  uint32_max = 0xffffffff;
  a = (unsigned int)0;
  while (a < uint32_max - (unsigned int)1) {
    b = (unsigned int)0;
    while (b < uint32_max - (unsigned int)1) {
      c = (unsigned int)0;
      while (c < uint32_max - (unsigned int)1) {
        d = (unsigned int)0;
        while (d < uint32_max - (unsigned int)1) {
          e = (unsigned int)0;
          while (e < uint32_max - (unsigned int)1) {
            if (a == b)
              if (b == c)
                if (c == d)
                  if (d == e)
                    if (e == uint32_max - (unsigned int)2) reach_error_slice_1
                                                           ();
            e ++;
          }
          d ++;
        }
        c ++;
      }
      b ++;
    }
    a ++;
  }
  return;
}