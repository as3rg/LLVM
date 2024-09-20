/// Partial implementation of IEEE 754

#ifndef F32_
#define F32_

#define F32_FLOAT_T unsigned int

#define F32_SIZE 32

#define F32_E_SIZE 8
#define F32_T_SIZE 23

#define F32_BIAS ((1 << (F32_E_SIZE - 1)) - 1)
#define F32_EMAX F32_BIAS
#define F32_EMIN (1 - F32_EMAX)

#define F32_T_POS 0
#define F32_E_POS F32_T_SIZE
#define F32_S_POS (F32_T_SIZE + F32_E_SIZE)

#define F32_S_MASK (1 << (F32_E_SIZE + F32_T_SIZE))
#define F32_E_MASK (~(-1 << F32_E_SIZE) << F32_T_SIZE)
#define F32_T_MASK (~(-1 << F32_T_SIZE))

#define F32_QNAN (F32_S_MASK | F32_E_MASK | F32_T_MASK)
#define F32_SNAN (F32_E_MASK | F32_T_MASK)

#define F32_POS_INF F32_E_MASK
#define F32_NEG_INF (F32_E_MASK | F32_S_MASK)

F32_FLOAT_T f32_add(F32_FLOAT_T a, F32_FLOAT_T b);

F32_FLOAT_T f32_negate(F32_FLOAT_T a);

F32_FLOAT_T f32_sub(F32_FLOAT_T a, F32_FLOAT_T b);

F32_FLOAT_T f32_mul(F32_FLOAT_T a, F32_FLOAT_T b);

F32_FLOAT_T f32_div(F32_FLOAT_T a, F32_FLOAT_T b);

char f32_is_qnan(F32_FLOAT_T a);

char f32_is_snan(F32_FLOAT_T a);

char f32_is_nan(F32_FLOAT_T a);

char f32_is_inf(F32_FLOAT_T a);

char f32_is_zero(F32_FLOAT_T a);

char f32_is_subnormal(F32_FLOAT_T a);

char f32_less(F32_FLOAT_T a, F32_FLOAT_T b);

char f32_equal(F32_FLOAT_T a, F32_FLOAT_T b);

long long f32_to_ll(F32_FLOAT_T a);

F32_FLOAT_T f32_from_ll(long long a);

#endif

