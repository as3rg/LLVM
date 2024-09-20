#include "float32.h"

#ifndef F32_MATH_
#define F32_MATH_

#define F32_PI 1078530011

#define F32_0 0
#define F32_1 1065353216
#define F32_2 1073741824
#define F32_3 1077936128
#define F32_4 1082130432
#define F32_5 1084227584
#define F32_6 1086324736
#define F32_7 1088421888
#define F32_8 1090519040
#define F32_9 1091567616
#define F32_10 1092616192
#define F32_11 1093664768
#define F32_12 1094713344
#define F32_13 1095761920
#define F32_14 1096810496
#define F32_15 1097859072
#define F32_16 1098907648
#define F32_17 1099431936
#define F32_18 1099956224
#define F32_19 1100480512
#define F32_20 1101004800
#define F32_21 1101529088
#define F32_22 1102053376
#define F32_23 1102577664
#define F32_24 1103101952
#define F32_25 1103626240
#define F32_26 1104150528
#define F32_27 1104674816
#define F32_28 1105199104
#define F32_29 1105723392
#define F32_30 1106247680
#define F32_31 1106771968
#define F32_32 1107296256
#define F32_33 1107558400
#define F32_34 1107820544
#define F32_35 1108082688
#define F32_36 1108344832
#define F32_37 1108606976
#define F32_38 1108869120
#define F32_39 1109131264
#define F32_40 1109393408
#define F32_41 1109655552
#define F32_42 1109917696
#define F32_43 1110179840
#define F32_44 1110441984
#define F32_45 1110704128
#define F32_46 1110966272
#define F32_47 1111228416
#define F32_48 1111490560
#define F32_49 1111752704
#define F32_50 1112014848
#define F32_51 1112276992
#define F32_52 1112539136
#define F32_53 1112801280
#define F32_54 1113063424
#define F32_55 1113325568
#define F32_56 1113587712
#define F32_57 1113849856
#define F32_58 1114112000
#define F32_59 1114374144
#define F32_60 1114636288
#define F32_61 1114898432
#define F32_62 1115160576
#define F32_63 1115422720
#define F32_64 1115684864
#define F32_65 1115815936
#define F32_66 1115947008
#define F32_67 1116078080
#define F32_68 1116209152
#define F32_69 1116340224
#define F32_70 1116471296
#define F32_71 1116602368
#define F32_72 1116733440
#define F32_73 1116864512
#define F32_74 1116995584
#define F32_75 1117126656
#define F32_76 1117257728
#define F32_77 1117388800
#define F32_78 1117519872
#define F32_79 1117650944
#define F32_80 1117782016
#define F32_81 1117913088
#define F32_82 1118044160
#define F32_83 1118175232
#define F32_84 1118306304
#define F32_85 1118437376
#define F32_86 1118568448
#define F32_87 1118699520
#define F32_88 1118830592
#define F32_89 1118961664
#define F32_90 1119092736
#define F32_91 1119223808
#define F32_92 1119354880
#define F32_93 1119485952
#define F32_94 1119617024
#define F32_95 1119748096
#define F32_96 1119879168
#define F32_97 1120010240
#define F32_98 1120141312
#define F32_99 1120272384

#define F32_1 1065353216
#define F32_10 1092616192
#define F32_100 1120403456
#define F32_1000 1148846080
#define F32_10000 1176256512
#define F32_100000 1203982336
#define F32_1000000 1232348160
#define F32_10000000 1259902592
#define F32_100000000 1287568416
#define F32_1000000000 1315859240

#define M_TRIG_PRES 100

F32_FLOAT_T m_sin(F32_FLOAT_T f) {
    F32_FLOAT_T res = F32_0;
    F32_FLOAT_T step = f;
    f = f32_mul(f, f);
    F32_FLOAT_T f_index = F32_1;
    for (int i = 0; i < M_TRIG_PRES; ++i) {
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

F32_FLOAT_T m_cos(F32_FLOAT_T f) {
    F32_FLOAT_T res = F32_0;
    F32_FLOAT_T step = F32_1;
    f = f32_mul(f, f);
    F32_FLOAT_T f_index = F32_0;
    for (int i = 0; i < M_TRIG_PRES; ++i) {
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

F32_FLOAT_T m_tan(F32_FLOAT_T f) {
    return f32_div(m_sin(f), m_cos(f));
}

#endif