/* Generated by Frama-C */
#include "errno.h"
#include "stdarg.h"
#include "stddef.h"
#include "stdio.h"
/*@ requires valid_read_string(format);
    assigns \result, __fc_stdout->__fc_FILE_data;
    assigns \result
      \from (indirect: __fc_stdout->__fc_FILE_id),
            (indirect: __fc_stdout->__fc_FILE_data),
            (indirect: *(format + (0 ..))), (indirect: param0);
    assigns __fc_stdout->__fc_FILE_data
      \from (indirect: __fc_stdout->__fc_FILE_id),
            __fc_stdout->__fc_FILE_data, (indirect: *(format + (0 ..))),
            param0;
 */
int printf_va_1(char const * restrict format, int param0);

/*@ requires valid_read_string(format);
    assigns \result, __fc_stdout->__fc_FILE_data;
    assigns \result
      \from (indirect: __fc_stdout->__fc_FILE_id),
            (indirect: __fc_stdout->__fc_FILE_data),
            (indirect: *(format + (0 ..))), (indirect: param0);
    assigns __fc_stdout->__fc_FILE_data
      \from (indirect: __fc_stdout->__fc_FILE_id),
            __fc_stdout->__fc_FILE_data, (indirect: *(format + (0 ..))),
            param0;
 */
int printf_va_2(char const * restrict format, int param0);

/*@ requires valid_read_string(format);
    assigns \result, __fc_stdout->__fc_FILE_data;
    assigns \result
      \from (indirect: __fc_stdout->__fc_FILE_id),
            (indirect: __fc_stdout->__fc_FILE_data),
            (indirect: *(format + (0 ..))), (indirect: param0);
    assigns __fc_stdout->__fc_FILE_data
      \from (indirect: __fc_stdout->__fc_FILE_id),
            __fc_stdout->__fc_FILE_data, (indirect: *(format + (0 ..))),
            param0;
 */
int printf_va_3(char const * restrict format, int param0);

int main(void)
{
  int __retres;
  int x = 0;
  int y = 1;
  int z = 2;
  printf("x: %d\n",x); /* printf_va_1 */
  printf("y: %d\n",y); /* printf_va_2 */
  printf("z: %d\n",z); /* printf_va_3 */
  __retres = 0;
  return __retres;
}