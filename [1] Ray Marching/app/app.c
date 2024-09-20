#include "sim.h"

#include <math.h>
#include <assert.h>
#include <stdint.h>

// Colors
#define COLOR_T int
#define MASK_R 0xFF0000
#define MASK_G 0x00FF00
#define MASK_B 0x0000FF

#define NONE_COLOR (-1)
#define BG_COLOR 0xBBBBBB

// Params
#define FOCUS 200
#define MAX_REFLS 10
#define MAX_STEPS 1000
#define X_SIZE_HALF (SIM_X_SIZE / 2)
#define Y_SIZE_HALF (SIM_Y_SIZE / 2)

// Data
#define SPHERE_CNT 3

float dist2(float x, float y, float z) {
  return x * x + y * y + z * z;   
}

float dot_prod(float x1, float y1, float z1, float x2, float y2, float z2) {
  return x1 * x2 + y1 * y2 + z1 * z2;   
}

float qrsqrt(float number) {
  return 1 / sqrt(number);
}

COLOR_T combine(COLOR_T c1, COLOR_T c2, float prop) {
  COLOR_T r = (c1 & MASK_R) * prop + (c2 & MASK_R) * (1 - prop);   
  COLOR_T g = (c1 & MASK_G) * prop + (c2 & MASK_G) * (1 - prop);   
  COLOR_T b = (c1 & MASK_B) * prop + (c2 & MASK_B) * (1 - prop);   
  return (r & MASK_R) | (g & MASK_G) | (b & MASK_B);
}

COLOR_T shadow(COLOR_T color, float cos_) {
  return combine(color, BG_COLOR, cos_);
}

COLOR_T reflection(COLOR_T base, COLOR_T target, float coeff) {
  if (target == NONE_COLOR) return base;
  COLOR_T r = (target & MASK_R) * coeff * (base & MASK_R) / MASK_R;   
  COLOR_T g = (target & MASK_G) * coeff * (base & MASK_G) / MASK_G;   
  COLOR_T b = (target & MASK_B) * coeff * (base & MASK_B) / MASK_B;   
  return combine(base, (r & MASK_R) | (g & MASK_G) | (b & MASK_B), coeff);
}

COLOR_T ray_impl(
          const float *SPHERE_X, 
          const float *SPHERE_Y, 
          const float *SPHERE_Z, 
          const float *SPHERE_R, 
          const float *SPHERE_REFL, 
          const COLOR_T *SPHERE_COLOR,
          float r_x, 
          float r_y, 
          float r_z, 
          float v_x, 
          float v_y, 
          float v_z, 
          int steps, 
          int reflects
        ) {
  while (steps--) {
    // find SDF
    float step = 1000000;   
    int closest = 0;
    for (int s = 0; s < SPHERE_CNT; ++s) {
      float sp_vec_x = SPHERE_X[s] - r_x;   
      float sp_vec_y = SPHERE_Y[s] - r_y;   
      float sp_vec_z = SPHERE_Z[s] - r_z;   
      float dist_sq = dist2(sp_vec_x, sp_vec_y, sp_vec_z);
      float step_new = dist_sq * qrsqrt(dist_sq) - SPHERE_R[s];   
      float scalar = dot_prod(v_x, v_y, v_z, sp_vec_x, sp_vec_y, sp_vec_z);
      if (step > step_new && scalar > 0) {   
        step = step_new;
        closest = s;
      }
    }

    // move
    r_x += v_x * step;   
    r_y += v_y * step;   
    r_z += v_z * step;   

    //reflect
    if (step < 0.005) {   
      float sp_vec_x = SPHERE_X[closest] - r_x;   
      float sp_vec_y = SPHERE_Y[closest] - r_y;   
      float sp_vec_z = SPHERE_Z[closest] - r_z;   
      float qrsqrt_sp_len = qrsqrt(dist2(sp_vec_x, sp_vec_y, sp_vec_z));
      sp_vec_x *= qrsqrt_sp_len;   
      sp_vec_y *= qrsqrt_sp_len;   
      sp_vec_z *= qrsqrt_sp_len;   
      float cos_ = dot_prod(v_x, v_y, v_z, sp_vec_x, sp_vec_y, sp_vec_z);   
      v_x -= 2 * cos_ * sp_vec_x;   
      v_y -= 2 * cos_ * sp_vec_y;   
      v_z -= 2 * cos_ * sp_vec_z;   
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
          const float *SPHERE_X, 
          const float *SPHERE_Y, 
          const float *SPHERE_Z, 
          const float *SPHERE_R, 
          const float *SPHERE_REFL, 
          const COLOR_T *SPHERE_COLOR,
          int x, int y
        ) {
  float r_x = 0;   
  float r_y = 0;   
  float r_z = 0;   

  float v_x = x - X_SIZE_HALF;   
  float v_y = Y_SIZE_HALF - y;   
  float v_z = FOCUS;   
  float qrsqrt_len = qrsqrt(dist2(v_x, v_y, v_z));
  v_x *= qrsqrt_len;   
  v_y *= qrsqrt_len;   
  v_z *= qrsqrt_len;   

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
  const float SPHERE_X[SPHERE_CNT] = {-30, 30, 0};   
  const float SPHERE_Y[SPHERE_CNT] = {0, 0, 25};   
  const float SPHERE_Z[SPHERE_CNT] = {50, 50, 50};   
  const float SPHERE_R[SPHERE_CNT] = {20, 20, 20};   
  const float SPHERE_REFL[SPHERE_CNT] = {0.5, 0.5, 0.5};   
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
