/* File: rt_roundf.c */

#include "rtwtypes.h"
#include <math.h>
#include "rt_roundf.h"

real32_T rt_roundf(real32_T u)
{
  real32_T y;
  if ((real32_T)fabs(u) < 8.388608E+6F)
  {
    if (u >= 0.5F)
    {
      y = (real32_T)floor(u + 0.5F);
    }
    else if (u > -0.5F)
    {
      y = 0.0F;
    }
    else
    {
      y = (real32_T)ceil(u - 0.5F);
    }
  }
  else
  {
    y = u;
  }

  return y;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
