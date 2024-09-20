#include "float32_math.h"

F32_FLOAT_T f32_sin(F32_FLOAT_T f) {
    F32_FLOAT_T res = F32_0;
    F32_FLOAT_T step = f;
    f = f32_mul(f, f);
    F32_FLOAT_T f_index = F32_1;
    for (int i = 0; i < F32_TRIG_PRES; ++i) {
        res = f32_add(res, step);
        step = f32_mul(step, f);
        f_index = f32_add(f_index, F32_1);
        step = f32_div(step, f_index);
        f_index = f32_add(f_index, F32_1);
        step = f32_div(step, f_index);
        step = f32_negate(step);
    }
    return res;
}

F32_FLOAT_T f32_cos(F32_FLOAT_T f) {
    F32_FLOAT_T res = F32_0;
    F32_FLOAT_T step = F32_1;
    f = f32_mul(f, f);
    F32_FLOAT_T f_index = F32_0;
    for (int i = 0; i < F32_TRIG_PRES; ++i) {
        res = f32_add(res, step);
        step = f32_mul(step, f);
        f_index = f32_add(f_index, F32_1);
        step = f32_div(step, f_index);
        f_index = f32_add(f_index, F32_1);
        step = f32_div(step, f_index);
        step = f32_negate(step);
    }
    return res;
}

F32_FLOAT_T f32_tan(F32_FLOAT_T f) {
    return f32_div(f32_sin(f), f32_cos(f));
}