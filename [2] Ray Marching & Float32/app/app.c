#include "sim.h"
#include "../float32/float32.h"
#include "../float32/float32_math.h"

// Colors
#define COLOR_T int
#define MASK_R 0xFF0000
#define MASK_G 0x00FF00
#define MASK_B 0x0000FF

#define NONE_COLOR (-1)
#define BG_COLOR 0xBBBBBB
#define FG_COLOR 0xFFFFFF

// Params
#define FOCUS 200
#define MAX_REFLS 10
#define MAX_STEPS 20
#define X_SIZE_HALF (SIM_X_SIZE / 2)
#define Y_SIZE_HALF (SIM_Y_SIZE / 2)

// Data
#define SPHERE_CNT 3

F32_FLOAT_T sqr(F32_FLOAT_T a) {
  return f32_mul(a, a);
}

F32_FLOAT_T dot_prod(F32_FLOAT_T x1, F32_FLOAT_T y1, F32_FLOAT_T z1, F32_FLOAT_T x2, F32_FLOAT_T y2, F32_FLOAT_T z2) {
  return f32_add(f32_add(f32_mul(x1, x2), f32_mul(y1, y2)), f32_mul(z1, z2));
}

F32_FLOAT_T dist2(F32_FLOAT_T x, F32_FLOAT_T y, F32_FLOAT_T z) {
  return dot_prod(x, y, z, x, y, z);
}

F32_FLOAT_T qrsqrt(F32_FLOAT_T number) {	
	F32_FLOAT_T x2 = f32_div(number, F32_2);
	F32_FLOAT_T threehalfs = f32_div(F32_3, F32_2);
	number = 0x5f3759df - (number >> 1);    //as integer
	return f32_mul(number, f32_sub(threehalfs, f32_mul(x2, sqr(number))));
}

COLOR_T combine(COLOR_T c1, COLOR_T c2, F32_FLOAT_T prop) {
  F32_FLOAT_T prop2 = f32_sub(F32_1, prop);
  COLOR_T r = f32_to_ll(f32_add(f32_mul(f32_from_ll(c1 & MASK_R), prop), f32_mul(f32_from_ll(c2 & MASK_R), prop2)));
  COLOR_T g = f32_to_ll(f32_add(f32_mul(f32_from_ll(c1 & MASK_G), prop), f32_mul(f32_from_ll(c2 & MASK_G), prop2)));
  COLOR_T b = f32_to_ll(f32_add(f32_mul(f32_from_ll(c1 & MASK_B), prop), f32_mul(f32_from_ll(c2 & MASK_B), prop2)));
  return (r & MASK_R) | (g & MASK_G) | (b & MASK_B);
}

COLOR_T shadow(COLOR_T color, F32_FLOAT_T cos_) {
  return combine(color, BG_COLOR, cos_);
}

COLOR_T reflection(COLOR_T base, COLOR_T target, F32_FLOAT_T coeff) {
  if (target == NONE_COLOR) return base;
  COLOR_T r = MASK_R & f32_to_ll(f32_div(f32_mul(f32_mul(f32_from_ll(target & MASK_R), f32_from_ll(base & MASK_R)), coeff), f32_from_ll(MASK_R)));
  COLOR_T g = MASK_G & f32_to_ll(f32_div(f32_mul(f32_mul(f32_from_ll(target & MASK_G), f32_from_ll(base & MASK_G)), coeff), f32_from_ll(MASK_G)));
  COLOR_T b = MASK_B & f32_to_ll(f32_div(f32_mul(f32_mul(f32_from_ll(target & MASK_B), f32_from_ll(base & MASK_B)), coeff), f32_from_ll(MASK_B)));
  return combine(base, r | g | b, coeff);
}

COLOR_T ray_impl(
          const F32_FLOAT_T *SPHERE_X, 
          const F32_FLOAT_T *SPHERE_Y, 
          const F32_FLOAT_T *SPHERE_Z, 
          const F32_FLOAT_T *SPHERE_R, 
          const F32_FLOAT_T *SPHERE_REFL, 
          const COLOR_T *SPHERE_COLOR,
          F32_FLOAT_T r_x, 
          F32_FLOAT_T r_y, 
          F32_FLOAT_T r_z, 
          F32_FLOAT_T v_x, 
          F32_FLOAT_T v_y, 
          F32_FLOAT_T v_z, 
          int steps, 
          int reflects
        ) {
  while (steps--) {
    // find SDF
    F32_FLOAT_T step = F32_100000;
    int closest = 0;
    for (int s = 0; s < SPHERE_CNT; ++s) {
      F32_FLOAT_T sp_vec_x = f32_sub(SPHERE_X[s], r_x);
      F32_FLOAT_T sp_vec_y = f32_sub(SPHERE_Y[s], r_y);
      F32_FLOAT_T sp_vec_z = f32_sub(SPHERE_Z[s], r_z);
      F32_FLOAT_T dist_sq = dist2(sp_vec_x, sp_vec_y, sp_vec_z);
      F32_FLOAT_T step_new = f32_sub(f32_mul(dist_sq, qrsqrt(dist_sq)), SPHERE_R[s]);
      F32_FLOAT_T scalar = dot_prod(v_x, v_y, v_z, sp_vec_x, sp_vec_y, sp_vec_z);
      if (f32_less(step_new, step) && f32_less(F32_0, scalar)) {
        step = step_new;
        closest = s;
      }
    }

    // move
    r_x = f32_add(r_x, f32_mul(v_x, step));
    r_y = f32_add(r_y, f32_mul(v_y, step));
    r_z = f32_add(r_z, f32_mul(v_z, step));

    //reflect
    if (f32_less(step, f32_div(F32_1, F32_100))) {
      F32_FLOAT_T sp_vec_x = f32_sub(SPHERE_X[closest], r_x);
      F32_FLOAT_T sp_vec_y = f32_sub(SPHERE_Y[closest], r_y);
      F32_FLOAT_T sp_vec_z = f32_sub(SPHERE_Z[closest], r_z);
      F32_FLOAT_T qrsqrt_sp_len = qrsqrt(dist2(sp_vec_x, sp_vec_y, sp_vec_z));
      sp_vec_x = f32_mul(sp_vec_x, qrsqrt_sp_len);
      sp_vec_y = f32_mul(sp_vec_y, qrsqrt_sp_len);
      sp_vec_z = f32_mul(sp_vec_z, qrsqrt_sp_len);
      F32_FLOAT_T cos_ = dot_prod(v_x, v_y, v_z, sp_vec_x, sp_vec_y, sp_vec_z);
      F32_FLOAT_T cos_2 = f32_mul(F32_2, cos_);
      v_x = f32_sub(v_x, f32_mul(cos_2, sp_vec_x));
      v_y = f32_sub(v_y, f32_mul(cos_2, sp_vec_y));
      v_z = f32_sub(v_z, f32_mul(cos_2, sp_vec_z));
      COLOR_T refl = reflects
                      ? ray_impl(
                          SPHERE_X, 
                          SPHERE_Y, 
                          SPHERE_Z, 
                          SPHERE_R, 
                          SPHERE_REFL, 
                          SPHERE_COLOR, 
                          r_x, r_y, r_z, 
                          v_x, v_y, v_z, 
                          steps, reflects - 1
                        )
                      : NONE_COLOR;
      return shadow(reflection(SPHERE_COLOR[closest], refl, SPHERE_REFL[closest]), cos_);
    }
  }
  return NONE_COLOR;
}

COLOR_T ray(
          const F32_FLOAT_T *SPHERE_X, 
          const F32_FLOAT_T *SPHERE_Y, 
          const F32_FLOAT_T *SPHERE_Z, 
          const F32_FLOAT_T *SPHERE_R, 
          const F32_FLOAT_T *SPHERE_REFL, 
          const COLOR_T *SPHERE_COLOR,
          int x, int y
        ) {
  F32_FLOAT_T r_x = F32_0;
  F32_FLOAT_T r_y = F32_0;
  F32_FLOAT_T r_z = F32_0;

  F32_FLOAT_T v_x = f32_from_ll(x - X_SIZE_HALF);
  F32_FLOAT_T v_y = f32_from_ll(Y_SIZE_HALF - y);
  F32_FLOAT_T v_z = f32_from_ll(FOCUS);
  F32_FLOAT_T qrsqrt_len = qrsqrt(dist2(v_x, v_y, v_z));
  v_x = f32_mul(v_x, qrsqrt_len);
  v_y = f32_mul(v_y, qrsqrt_len);
  v_z = f32_mul(v_z, qrsqrt_len);

  COLOR_T res = ray_impl(
                          SPHERE_X, 
                          SPHERE_Y, 
                          SPHERE_Z, 
                          SPHERE_R, 
                          SPHERE_REFL, 
                          SPHERE_COLOR, 
                          r_x, r_y, r_z, 
                          v_x, v_y, v_z, 
                          MAX_STEPS, MAX_REFLS
                        );
  return res != NONE_COLOR ? res : BG_COLOR;
}

void app() {
  const F32_FLOAT_T SPHERE_X[SPHERE_CNT] = {F32_30 | F32_S_MASK, F32_30, F32_0};
  const F32_FLOAT_T SPHERE_Y[SPHERE_CNT] = {F32_0, F32_0, F32_25};
  const F32_FLOAT_T SPHERE_Z[SPHERE_CNT] = {F32_30, F32_30, F32_30};
  const F32_FLOAT_T SPHERE_R[SPHERE_CNT] = {F32_20, F32_20, F32_20};
  const F32_FLOAT_T SPHERE_REFL[SPHERE_CNT] = {f32_div(F32_3, F32_4), f32_div(F32_3, F32_4), f32_div(F32_3, F32_4)};
  const COLOR_T SPHERE_COLOR[SPHERE_CNT] = {0xFF0000, 0xFFFF00, 0x00FF00};


  COLOR_T data[SIM_X_SIZE][SIM_Y_SIZE];
  for (int i = 0; i < SIM_X_SIZE; ++i) {
      for (int j = 0; j < SIM_Y_SIZE; ++j) {
        data[i][j] = 0;
      }
    }


  for (int i = 0; i < SIM_X_SIZE; ++i) {
    for (int j = 0; j < SIM_Y_SIZE; ++j) {
      data[i][j] = ray(SPHERE_X, SPHERE_Y, SPHERE_Z, SPHERE_R, SPHERE_REFL, SPHERE_COLOR, i, j);
    }

    for (int i = 0; i < SIM_X_SIZE; ++i) {
      for (int j = 0; j < SIM_Y_SIZE; ++j) {
        simPutPixel(i, j, data[i][j]);
      }
    }

    simFlush();
  }
}
