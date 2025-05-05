
#include "../rng.h"

inline OciRng oci_rng_seed(u32 seed) {
	return (OciRng) {
		.seed0 = seed,
		.seed1 = seed + 1,
		.seed2 = seed + 2,
	};
}

inline f64 oci_rng_next(OciRng *state) {
	state->seed0 = (state->seed0 * 171) % 30269;
	state->seed1 = (state->seed1 * 172) % 30307;
	state->seed2 = (state->seed2 * 170) % 30323;
	f64 x = state->seed0 / 30269.0 + state->seed1 / 30307.0 + state->seed2 / 30323.0;
	return x - (i64)x;
}

inline f64 oci_rng_range(OciRng *state, f64 x0, f64 x1) {
	return x0 + oci_rng_next(state) * (x1 - x0);
}

inline i64 oci_rng_irange(OciRng *state, i64 x0, i64 x1) {
	return (i64)oci_rng_range(state, x0, x1);
}

