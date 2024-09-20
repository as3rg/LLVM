#include "float32.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "float32_math.h"

F32_FLOAT_T f2F(float f) {
    return *((F32_FLOAT_T*) (&f));
}

float F2f(F32_FLOAT_T f) {
  return *((float*) (&f));
}

static void print(F32_FLOAT_T a) {
    for (unsigned long long i = 1ll << 63; i; i >>= 1) {
        printf("%d", a & i ? 1 : 0);
    }
    printf("(%f)\n", F2f(a));
}

char test_mul(F32_FLOAT_T a_, F32_FLOAT_T b_) {
    float a = F2f(a_);
    float b = F2f(b_);
    print(a_);
    printf(" * ");
    print(b_);
    printf(":\nexpected ");
    F32_FLOAT_T expected = f2F(a * b);
    print(expected);
    printf("\nreal ");
    F32_FLOAT_T real = f32_mul(a_, b_);
    print(real);
    if (expected == real 
      || f32_is_inf(expected) && f32_is_inf(real) && (expected & F32_S_MASK) == (real & F32_S_MASK)
      || f32_is_nan(expected) && f32_is_nan(real)
      || f32_is_zero(expected) && f32_is_zero(real)) {
        printf("\nOK\n");
        return 1;
    } else {
        printf("\nWRONG\n");
        return 0;
    }
}

char test_div(F32_FLOAT_T a_, F32_FLOAT_T b_) {
    float a = F2f(a_);
    float b = F2f(b_);
    print(a_);
    printf(" / ");
    print(b_);
    printf(":\nexpected ");
    F32_FLOAT_T expected = f2F(a / b);
    print(expected);
    printf("\nreal ");
    F32_FLOAT_T real = f32_div(a_, b_);
    print(real);
    if (expected == real 
      || f32_is_inf(expected) && f32_is_inf(real) && (expected & F32_S_MASK) == (real & F32_S_MASK)
      || f32_is_nan(expected) && f32_is_nan(real)
      || f32_is_zero(expected) && f32_is_zero(real)) {
        printf("\nOK\n");
        return 1;
    } else {
        printf("\nWRONG\n");
        return 0;
    }
}

char test_add(F32_FLOAT_T a_, F32_FLOAT_T b_) {
    float a = F2f(a_);
    float b = F2f(b_);
    print(a_);
    printf(" + ");
    print(b_);
    printf(":\nexpected ");
    F32_FLOAT_T expected = f2F(a + b);
    print(expected);
    printf("\nreal ");
    F32_FLOAT_T real = f32_add(a_, b_);
    print(real);
    if (expected == real 
      || f32_is_inf(expected) && f32_is_inf(real) && (expected & F32_S_MASK) == (real & F32_S_MASK)
      || f32_is_nan(expected) && f32_is_nan(real)
      || f32_is_zero(expected) && f32_is_zero(real)) {
        printf("\nOK\n");
        return 1;
    } else {
        printf("\nWRONG\n");
        return 0;
    }
}

char test_sub(F32_FLOAT_T a_, F32_FLOAT_T b_) {
    float a = F2f(a_);
    float b = F2f(b_);
    print(a_);
    printf(" - ");
    print(b_);
    printf(":\nexpected ");
    F32_FLOAT_T expected = f2F(a - b);
    print(expected);
    printf("\nreal ");
    F32_FLOAT_T real = f32_sub(a_, b_);
    print(real);
    if (expected == real 
      || f32_is_inf(expected) && f32_is_inf(real) && (expected & F32_S_MASK) == (real & F32_S_MASK)
      || f32_is_nan(expected) && f32_is_nan(real)
      || f32_is_zero(expected) && f32_is_zero(real)) {
        printf("\nOK\n");
        return 1;
    } else {
        printf("\nWRONG\n");
        return 0;
    }
}

char test_neg(F32_FLOAT_T a_) {
    float a = F2f(a_);
    printf("-");
    print(a_);
    printf(":\nexpected ");
    F32_FLOAT_T expected = f2F(-a);
    print(expected);
    printf("\nreal ");
    F32_FLOAT_T real = f32_negate(a_);
    print(real);
    if (expected == real 
      || f32_is_inf(expected) && f32_is_inf(real) && (expected & F32_S_MASK) == (real & F32_S_MASK)
      || f32_is_nan(expected) && f32_is_nan(real)
      || f32_is_zero(expected) && f32_is_zero(real)) {
        printf("\nOK\n");
        return 1;
    } else {
        printf("\nWRONG\n");
        return 0;
    }
}

char test_conv(F32_FLOAT_T a_) {
    float a = F2f(a_);
    printf("(ll) ");
    print(a_);

    long long expected = a;
    printf(":\nexpected %lld\n", expected);
    long long real = f32_to_ll(a_);
    printf("real %lld", real);

    if (expected == real) {
        printf("\nOK\n");
        return 1;
    } else {
        printf("\nWRONG\n");
        return 0;
    }
}

char test_conv2(long long a) {
    printf("(float) ");
    print(a);

    printf(":\nexpected ");
    F32_FLOAT_T expected = f2F((float) a);
    print(expected);
    printf("\nreal ");
    F32_FLOAT_T real = f32_from_ll(a);
    print(real);
    if (expected == real 
      || f32_is_inf(expected) && f32_is_inf(real) && (expected & F32_S_MASK) == (real & F32_S_MASK)
      || f32_is_nan(expected) && f32_is_nan(real)
      || f32_is_zero(expected) && f32_is_zero(real)) {
        printf("\nOK\n");
        return 1;
    } else {
        printf("\nWRONG\n");
        return 0;
    }
}

char test_eq(F32_FLOAT_T a_, F32_FLOAT_T b_) {
    float a = F2f(a_);
    float b = F2f(b_);
    print(a_);
    printf(" == ");
    print(b_);
    printf(":\nexpected ");
    char expected = a == b;
    print(expected);
    printf("\nreal ");
    char real = f32_equal(a_, b_);
    print(real);
    if (expected == real) {
        printf("\nOK\n");
        return 1;
    } else {
        printf("\nWRONG\n");
        return 0;
    }
}

char test_less(F32_FLOAT_T a_, F32_FLOAT_T b_) {
    float a = F2f(a_);
    float b = F2f(b_);
    print(a_);
    printf(" < ");
    print(b_);
    printf(":\nexpected ");
    char expected = a < b;
    print(expected);
    printf("\nreal ");
    char real = f32_less(a_, b_);
    print(real);
    if (expected == real) {
        printf("\nOK\n");
        return 1;
    } else {
        printf("\nWRONG\n");
        return 0;
    }
}

F32_FLOAT_T norm() {
	F32_FLOAT_T f;
	do {
		f = rand();
	} while (f32_is_subnormal(f));
  return f | (rand() << F32_S_POS);
}

F32_FLOAT_T denorm() {
	return norm() & ~F32_E_MASK;
}

float sin2(float f) {
    // while (f32_less(f, f32_negate(F32_PI))) {
    //     f = f32_add(f, f32_add(F32_PI, F32_PI));
    // }
    // while (f32_less(F32_PI, f)) {
    //     f = f32_sub(f, f32_add(F32_PI, F32_PI));
    // }
    float res = 0;
    float step = f;
    f *= f;;
    float f_index = 1;
    for (int i = 0; i < M_TRIG_PRES; ++i) {
        res += step;
        step *= f;
        step /= ++f_index;
        step /= ++f_index;
        step = -step;
    }
    return res;
}

int main() {
  while (1) {
    #define DATA_SIZE 8
    F32_FLOAT_T data[DATA_SIZE] = {norm(), denorm(), F32_POS_INF, F32_NEG_INF, F32_QNAN, F32_SNAN, 0, F32_S_MASK};
    F32_FLOAT_T data2[DATA_SIZE] = {norm(), denorm(), F32_POS_INF, F32_NEG_INF, F32_QNAN, F32_SNAN, 0, F32_S_MASK};
    for (int i = 0; i < DATA_SIZE; ++i) {
      for (int j = 0; j < DATA_SIZE; ++j) {
        if (0
            || !test_conv(data[i]) 
            || !test_conv2(data[i]) 
            || !test_neg(data[i]) 
            || !test_add(data[i], data2[j]) 
            || !test_sub(data[i], data2[j]) 
            || !test_mul(data[i], data2[j]) 
            || !test_div(data[i], data2[j]) 
            || !test_eq(data[i], data2[j]) 
            || !test_less(data[i], data2[j])
        ) {
          return 1;
        }
      }
    }
  }
  test_conv2(f2F(1 << 1));
  return 0;
}
