#ifndef CLA_COMMONUNITS_H
#define CLA_COMMONUNITS_H


#include <stdint.h>

#include <stddef.h>

#include <stdbool.h>



#ifdef __cplusplus
extern "C" {
#endif

#define ms_to_s_any(val)((val) / 1000)
#define s_to_ms_any(val)((val) * 1000)
#define deg_to_rad_double(val)((val) * 3.14159265358979 / 180)
#define rad_to_deg_double(val)((val) * 180 / 3.14159265358979)
#define deg_to_rev_double(val)((val) / 360)
#define rad_to_rev_double(val)((val) / 6.28318530717959)
#define rev_to_deg_double(val)((val) * 360)
#define rev_to_rad_double(val)((val) * 6.28318530717959)
#define min_to_s_double(val)((val) * 60)
#define s_to_min_double(val)((val) / 60)
#define rpm_to_radps_double(val)((val) * 3.14159265358979 / 30)
#define radps_to_rpm_double(val)((val) * 30 / 3.14159265358979)
#define degC_to_K_double(val)((val) * 1 / 1 + 273.15)
#define K_to_degC_double(val)(((val) - 273.15) * 1 / 1)
#define W_to_kW_double(val)((val) / 1000)
#define kW_to_W_double(val)((val) * 1000)
#define W_to_MW_double(val)((val) / 1000 / 1000)
#define MW_to_W_double(val)((val) * 1000 * 1000)
#define Pa_to_kPa_double(val)((val) / 1000)
#define Pa_to_MPA_double(val)((val) / 1000 / 1000)
#define kPa_to_Pa_double(val)((val) * 1000)
#define kPa_to_MPA_double(val)((val) / 1000)
#define MPA_to_Pa_double(val)((val) * 1000 * 1000)
#define MPA_to_kPa_double(val)((val) * 1000)

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
