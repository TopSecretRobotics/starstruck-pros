#ifndef FASTMATH_H_

#define FASTMATH_H_

#include <API.h>

#ifdef __cplusplus
#define cast_uint32_t static_cast<uint32_t>
extern "C" {
#else
#define cast_uint32_t (uint32_t)
#endif

static inline float
fastpow2(float p)
{
	float offset = (p < 0) ? 1.0f : 0.0f;
	float clipp = (p < -126) ? -126.0f : p;
	int w = clipp;
	float z = clipp - w + offset;
	union { uint32_t i; float f; } v = { cast_uint32_t ( (1 << 23) * (clipp + 121.2740575f + 27.7280233f / (4.84252568f - z) - 1.49012907f * z) ) };
	return v.f;
}

static inline float
fastlog2 (float x)
{
	union { float f; uint32_t i; } vx = { x };
	union { uint32_t i; float f; } mx = { (vx.i & 0x007FFFFF) | 0x3f000000 };
	float y = vx.i;
	y *= 1.1920928955078125e-7f;
	return y - 124.22551499f - 1.498030302f * mx.f - 1.72587999f / (0.3520887068f + mx.f);
}

static inline float
fastexp (float p)
{
	return fastpow2(1.442695040f * p);
}

static inline float
fastpow (float x, float p)
{
	return fastpow2(p * fastlog2(x));
}

static inline float
fastlog (float x)
{
	return 0.69314718f * fastlog2(x);
}

#ifdef __cplusplus
}
#endif

#endif
