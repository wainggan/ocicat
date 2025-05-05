#ifndef OCI_RNG_H
#define OCI_RNG_H

#include "type.h"

typedef struct OciRng {
	u32 seed0;
	u32 seed1;
	u32 seed2;
} OciRng;

OciRng oci_rng_seed(u32 seed);
f64 oci_rng_next(OciRng *state);
f64 oci_rng_range(OciRng *state, f64 x0, f64 x1);
i64 oci_rng_irange(OciRng *state, i64 x0, i64 x1);


#endif
