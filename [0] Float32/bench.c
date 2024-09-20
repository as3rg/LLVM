#include "float32.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "float32_math.h"
#include "time.h"

F32_FLOAT_T f2F(float f) {
    return *((F32_FLOAT_T*) (&f));
}

float F2f(F32_FLOAT_T f) {
  return *((float*) (&f));
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

#define ITERS (1ull << 29)
#define ull unsigned long long

int main() {
  {
    ull start = time(NULL);
    float acc = F2f(norm());
    for (ull i = 0; i < ITERS; ++i) {
      acc += F2f(norm());
    }
    printf("float %lld\n", time(NULL) - start);
  }

  {
    ull start = time(NULL);
    F32_FLOAT_T acc = norm();
    for (ull i = 0; i < ITERS; ++i) {
      acc = f32_add(acc, norm());
    }
    printf("FLOAT32 %lld\n", time(NULL) - start);
  }
  return 0;
}
