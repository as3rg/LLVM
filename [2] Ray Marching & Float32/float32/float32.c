#include "float32.h"

#define uint unsigned int
#define ll long long 
#define ull unsigned ll


#define LL_SIZE 64
#define LL_MIN (1ll << (LL_SIZE - 1))
#define LL_MAX (~LL_MIN)

static uint get_s(F32_FLOAT_T a) {
    return (a >> F32_S_POS) & 1;
}

static F32_FLOAT_T set_s(F32_FLOAT_T a, char s) {
    return (a & ~F32_S_MASK) | ((s << F32_S_POS) & F32_S_MASK);
}

static uint get_e(F32_FLOAT_T a) {
    return (a & F32_E_MASK) >> F32_E_POS;
}

static F32_FLOAT_T set_e(F32_FLOAT_T a, uint e) {
    return (a & ~F32_E_MASK) | ((e << F32_E_POS) & F32_E_MASK);
}

static uint get_t(F32_FLOAT_T a) {
    return (a & F32_T_MASK) >> F32_T_POS;
}

static F32_FLOAT_T set_t(F32_FLOAT_T a, uint t) {
    return (a & ~F32_T_MASK) | ((t << F32_T_POS) & F32_T_MASK);
}

// fixed point with F32_T_SIZE bits after a point
static ull get_mantissa(F32_FLOAT_T a) {
    ull res = get_t(a);
    if (!f32_is_subnormal(a) && !f32_is_zero(a)) {
        res |= 1 << F32_T_SIZE;
    }
    return res;
}

static int get_exp(F32_FLOAT_T a) {
    return f32_is_subnormal(a) || f32_is_zero(a) ? F32_EMIN : ((int) get_e(a)) - F32_BIAS;
}

static F32_FLOAT_T build_float(char s, int exp, ull mantissa, char carry, int ones) {
    while (mantissa >= (2 << F32_T_SIZE) || exp < F32_EMIN) {
        carry = mantissa & 1;
        ones += carry;

        mantissa >>= 1;
        ++exp;
    }

    if (carry && (ones > 1 || (mantissa & 1)))
        mantissa += 1;

    if (mantissa >= (2 << F32_T_SIZE)) {
        mantissa >>= 1;
        ++exp;
    }

    if (exp > F32_EMAX) {
        return set_s(F32_POS_INF, s);
    } else if (mantissa >= (1 << F32_T_SIZE)) {
        return set_s(set_e(set_t(0, mantissa), exp + F32_BIAS), s);
    } else {
        return set_s(set_e(set_t(0, mantissa), 0), s);
    }
}

static uint min(uint a, uint b) {
    return a <= b ? a : b;
}

static uint max(uint a, uint b) {
    return a >= b ? a : b;
}

F32_FLOAT_T f32_add(F32_FLOAT_T a, F32_FLOAT_T b) {
    if (f32_is_nan(a) || f32_is_nan(b)) {
        return F32_QNAN;
    }
    if (f32_is_inf(a) && f32_is_inf(b)) {
        return get_s(a) == get_s(b) ? a : F32_QNAN;
    }
    if (f32_is_inf(a) || f32_is_zero(b)) {
        return a;
    }
    if (f32_is_inf(b) || f32_is_zero(a)) {
        return b;
    }

    if (f32_less(a & ~F32_S_MASK, b & ~F32_S_MASK)) {
        F32_FLOAT_T tmp = a;
        a = b;
        b = tmp;
    }
    ull a_mantissa = get_mantissa(a);
    ull b_mantissa = get_mantissa(b);

    int a_exp = get_exp(a);
    int b_exp = get_exp(b);
    
    char a_s = get_s(a);
    char b_s = get_s(b);

    // |a| >= |b|

    if (a_s == b_s) {
        ull a_shift = a_exp - b_exp;
        ull a_shift_trunc = min(a_shift, F32_T_SIZE + 1);
        ull b_shift = min(a_shift - a_shift_trunc, F32_T_SIZE + 1);

        a_mantissa <<= a_shift_trunc;
        a_exp -= a_shift_trunc;
        a_mantissa += b_mantissa >> b_shift;
        char carry = (b_mantissa >> (b_shift - 1)) & 1;
        uint ones = (b_mantissa & ~(-1 << b_shift)) > (carry << (b_shift - 1));
        return build_float(a_s, a_exp, a_mantissa, carry, ones);
    } else {
        uint a_shift = a_exp - b_exp;
        if (a_shift > F32_T_SIZE + 1) return a;
        a_mantissa <<= a_shift;
        a_exp -= a_shift;
        a_mantissa -= b_mantissa;
        while (a_mantissa < (2 << F32_T_SIZE) && a_exp > F32_EMIN) {
            a_mantissa <<= 1;
            --a_exp;
        }
        return build_float(a_s, a_exp, a_mantissa, 0, 0);
        
    }
    //todo
}

F32_FLOAT_T f32_negate(F32_FLOAT_T a) {
    return f32_is_nan(a) ? a : a ^ F32_S_MASK;
}

F32_FLOAT_T f32_sub(F32_FLOAT_T a, F32_FLOAT_T b) {
    return f32_add(a, f32_negate(b));
}

F32_FLOAT_T f32_mul(F32_FLOAT_T a, F32_FLOAT_T b) {
    if (f32_is_nan(a) || f32_is_nan(b)) {
        return F32_QNAN;
    }

    if ((f32_is_inf(a) || f32_is_inf(b)) && (f32_is_zero(a) || f32_is_zero(b))) {
        return F32_QNAN;
    }

    if (f32_is_inf(a) || f32_is_inf(b)) {
        return set_s(F32_POS_INF, get_s(a) ^ get_s(b));
    }

    if (f32_is_zero(a) || f32_is_zero(b)) {
        return set_s(0, get_s(a) ^ get_s(b));
    }

    char res_s = get_s(a) ^ get_s(b);

    ull a_mantissa = get_mantissa(a);
    ull b_mantissa = get_mantissa(b);
    
    ull res_mantissa = a_mantissa * b_mantissa;
    int res_exp = get_exp(a) + get_exp(b) - F32_T_SIZE;
    
    return build_float(res_s, res_exp, res_mantissa, 0, 0);
}

F32_FLOAT_T f32_div(F32_FLOAT_T a, F32_FLOAT_T b) {
    if (f32_is_nan(a) || f32_is_nan(b)) {
        return F32_QNAN;
    }
    if (f32_is_inf(a) && f32_is_inf(b) || f32_is_zero(a) && f32_is_zero(b)) {
        return F32_QNAN;
    }
    if (f32_is_inf(a) || f32_is_zero(b)) {
        return set_s(F32_POS_INF, get_s(a) ^ get_s(b));
    }

    if (f32_is_zero(a) || f32_is_inf(b)) {
        return set_s(0, get_s(a) ^ get_s(b));
    }

    char res_s = get_s(a) ^ get_s(b);

    ull a_mantissa = get_mantissa(a);
    ull b_mantissa = get_mantissa(b);
    
    int res_exp = get_exp(a) - get_exp(b) + F32_T_SIZE;
    ull res_mantissa = 0;

    while (res_mantissa < (2 << F32_T_SIZE)) {
        a_mantissa  <<= (F32_T_SIZE + 1);
        res_exp -= (F32_T_SIZE + 1);
        res_mantissa <<= (F32_T_SIZE + 1);
        res_mantissa += (a_mantissa / b_mantissa);
        a_mantissa = (a_mantissa % b_mantissa);
    }

    char carry = a_mantissa * 2 >= b_mantissa;
    int ones = (a_mantissa * 2 > b_mantissa) ? 2 : (a_mantissa > 0);
    return build_float(res_s, res_exp, res_mantissa, carry, ones);
}

char f32_is_nan(F32_FLOAT_T a) {
    return get_e(a) == (F32_E_MASK >> F32_E_POS) && get_t(a) != 0;
}

char f32_is_qnan(F32_FLOAT_T a) {
    return f32_is_nan(a) && get_s(a);
}

char f32_is_snan(F32_FLOAT_T a) {
    return f32_is_nan(a) && !get_s(a);
}

char f32_is_inf(F32_FLOAT_T a) {
    return get_e(a) == (F32_E_MASK >> F32_E_POS) && get_t(a) == 0;
}

char f32_is_zero(F32_FLOAT_T a) {
    return get_e(a) == 0 && get_t(a) == 0;
}

char f32_is_subnormal(F32_FLOAT_T a) {
    return get_e(a) == 0 && get_t(a) != 0;
}

char f32_less(F32_FLOAT_T a, F32_FLOAT_T b) {
    if (f32_is_nan(a) || f32_is_nan(b) || f32_equal(a, b)) {
        return 0;
    }

    char a_s = get_s(a);
    char b_s = get_s(b);

    if (a_s != b_s) {
        return a_s > b_s;
    }
    return (a < b) ^ a_s;
}

char f32_equal(F32_FLOAT_T a, F32_FLOAT_T b) {
    if (f32_is_nan(a) || f32_is_nan(b)) {
        return 0;
    }
    if (f32_is_inf(a) && f32_is_inf(b)) {
        return get_s(a) == get_s(b);
    }
    if (f32_is_zero(a) && f32_is_zero(b)) {
        return 1;
    }
    return a == b;
}

ll f32_to_ll(F32_FLOAT_T a) {
    if (f32_is_inf(a) || f32_is_nan(a)) {
        return LL_MIN;
    }
    if (f32_is_zero(a)) {
        return 0;
    }

    ll mantissa = get_mantissa(a);
    int exp = get_exp(a) - F32_T_SIZE;
    char s = get_s(a);

    if (exp <= -LL_SIZE) {
        return 0;
    } if (exp <= 0) {
        ll res = mantissa >> (-exp);
        return s ? -res : res;
    } else if (exp < LL_SIZE - F32_T_SIZE - 1) {
        ll res = mantissa << exp;
        return s ? -res : res;
    } else {
        return LL_MIN;
    }
}

F32_FLOAT_T f32_from_ll(ll a) {
    char s = a < 0;
    if (a == LL_MIN) {
        return build_float(1, -(LL_SIZE - 1), 1, 0, 0);
    }
    if (a == 0) {
        return 0;
    }
    ull mantissa = a < 0 ? -a : a;
    int exp = F32_T_SIZE;
    
    if (mantissa < (2 << F32_T_SIZE)) {
        mantissa <<= (F32_T_SIZE + 1);
        exp -= (F32_T_SIZE + 1);
    }

    return build_float(a < 0, exp, mantissa, 0, 0);
}