#include "main.h"

/*
 * Public API
 */

double fabsmax(int argc, ...) {
  va_list argv;
  double max = 0.0;
  double cur = 0.0;
  int i;

  /* initialize `argv` for `argc` number of arguments */
  va_start(argv, argc);

  /* access all the arguments assigned to `argv` */
  for (i = 0; i < argc; i++) {
    cur = va_arg(argv, double);
    if (fabs(cur) > fabs(max)) {
      max = cur;
    }
  }

  /* clean up `argv` */
  va_end(argv);

  return max;
}

double fabsmin(int argc, ...) {
  va_list argv;
  double min = 0.0;
  double cur = 0.0;
  int i;

  /* initialize `argv` for `argc` number of arguments */
  va_start(argv, argc);

  /* access all the arguments assigned to `argv` */
  for (i = 0; i < argc; i++) {
    cur = va_arg(argv, double);
    if (fabs(cur) < fabs(min)) {
      min = cur;
    }
  }

  /* clean up `argv` */
  va_end(argv);

  return min;
}
