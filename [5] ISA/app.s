;;;;;;;
; App ;
;;;;;;;

#sqr(1):
mv ex1, ex0
call #f32_mul(2)
ret

#dot_prod(6):
    swp ex3, ex1
    call #f32_mul(2)
    swp ex0, ex2
    mv ex1, ex5
    call #f32_mul(2)
    swp ex0, ex3
    mv ex1, ex4
    call #f32_mul(2)
    mv ex1, ex2
    call #f32_add(2)
    mv ex1, ex3
    call #f32_add(2)
    ret

#dist2(3):
    mv ex3, ex0
    mv ex4, ex1
    mv ex5, ex2
    call #dot_prod(6)
    ret

#qrsqrt(1):
    mv ex2, ex0
    mv ex1, (w32) 1073741824
    call #f32_div(2)
    swp ex2, ex0
    rshl ex0, ex0, (w32) 1
    sub ex0, (w32) 1597463007, ex0
    mv ex1, ex0
    swp ex1, ex2
    call #sqr(1)
    call #f32_mul(2)
    mv ex1, ex0
    mv ex0, (w32) 1069547520
    call #f32_sub(2)
    mv ex1, ex2
    call #f32_mul(2)
    ret

#combine(3):
    mv ex4, ex0
    mv ex5, ex1

    mv ex1, ex2
    mv ex0, (w32) 1065353216
    call #f32_sub(2)
    mv ex3, ex0

    mv ex7, (w32) 0

    and ex0, ex4, (w32) 16711680
    call #f32_from_ll(1)
    mv ex1, ex2
    call #f32_mul(2)
    mv ex6, ex0
    and ex0, ex5, (w32) 16711680
    call #f32_from_ll(1)
    mv ex1, ex3
    call #f32_mul(2)
    mv ex1, ex6
    call #f32_add(2)
    call #f32_to_ll(1)
    and ex0, ex0, (w32) 16711680
    or ex7, ex7, ex0

    and ex0, ex4, (w32) 65280
    call #f32_from_ll(1)
    mv ex1, ex2
    call #f32_mul(2)
    mv ex6, ex0
    and ex0, ex5, (w32) 65280
    call #f32_from_ll(1)
    mv ex1, ex3
    call #f32_mul(2)
    mv ex1, ex6
    call #f32_add(2)
    call #f32_to_ll(1)
    and ex0, ex0, (w32) 65280
    or ex7, ex7, ex0

    and ex0, ex4, (w32) 255
    call #f32_from_ll(1)
    mv ex1, ex2
    call #f32_mul(2)
    mv ex6, ex0
    and ex0, ex5, (w32) 255
    call #f32_from_ll(1)
    mv ex1, ex3
    call #f32_mul(2)
    mv ex1, ex6
    call #f32_add(2)
    call #f32_to_ll(1)
    and ex0, ex0, (w32) 255
    or ex7, ex7, ex0

    mv ex0, ex7
    ret

#shadow(2):
    mv ex2, ex1
    mv ex1, (w32) 12303291
    call #combine(3)
    ret

#reflection(3):
    neq l5, ex1, (w32) -1
    jpc l5, %lbl1
    ret
%lbl1:

    mv ex3, ex0
    mv ex4, ex1
    mv ex5, (w32) 0
    
    and ex0, ex3, (w32) 16711680
    call #f32_from_ll(1)
    mv ex1, ex0
    and ex0, ex4, (w32) 16711680
    call #f32_from_ll(1)
    call #f32_mul(2)
    mv ex1, ex2
    call #f32_mul(2)
    mv ex1, (w32) 1266614272
    call #f32_div(2)
    call #f32_to_ll(1)
    and ex0, ex0, (w32) 16711680
    or ex5, ex5, ex0
    
    and ex0, ex3, (w32) 65280
    call #f32_from_ll(1)
    mv ex1, ex0
    and ex0, ex4, (w32) 65280
    call #f32_from_ll(1)
    call #f32_mul(2)
    mv ex1, ex2
    call #f32_mul(2)
    mv ex1, (w32) 1199505408
    call #f32_div(2)
    call #f32_to_ll(1)
    and ex0, ex0, (w32) 65280
    or ex5, ex5, ex0
    
    and ex0, ex3, (w32) 255
    call #f32_from_ll(1)
    mv ex1, ex0
    and ex0, ex4, (w32) 255
    call #f32_from_ll(1)
    call #f32_mul(2)
    mv ex1, ex2
    call #f32_mul(2)
    mv ex1, (w32) 1132396544
    call #f32_div(2)
    call #f32_to_ll(1)
    and ex0, ex0, (w32) 255
    or ex5, ex5, ex0

    mv ex1, ex5
    mv ex0, ex3
    call #combine(3)
    ret

#ray(8):
    mv rx14, rx0
    mv rx15, rx1
    mv rx16, rx2

    sub ex0, ex6, (w32) 250
    lsh rx0, rx0, (w8) 32
    rsha rx0, rx0, (w8) 32
    call #f32_from_ll(1)
    mv ex9, ex0
    sub ex0, (w32) 250, ex7
    lsh rx0, rx0, (w8) 32
    rsha rx0, rx0, (w8) 32
    call #f32_from_ll(1)
    mv ex10, ex0
    mv ex11, (w32) 1128792064

    mv ex0, ex9
    mv ex1, ex10
    mv ex2, ex11
    call #dist2(3)
    call #qrsqrt(1)
    mv ex17, ex0

    mv ex0, ex9
    mv ex1, ex17
    call #f32_mul(2)
    mv ex9, ex0

    mv ex0, ex10
    mv ex1, ex17
    call #f32_mul(2)
    mv ex10, ex0

    mv ex0, ex11
    mv ex1, ex17
    call #f32_mul(2)
    mv ex11, ex0
    
    mv ex6, (w32) 0
    mv ex7, (w32) 0
    mv ex8, (w32) 0

    mv ex12, (w32) 20
    mv ex13, (w32) 10

    mv rx0, rx14
    mv rx1, rx15
    mv rx2, rx16

    call #ray_impl(14)
    
    neq l2, ex0, (w32) -1
    jpc l2, %lbl
    mv ex0, (w32) 12303291
    ret
%lbl:
    ret

#init(6):
    mv (w32) *rx0, (w32) -1041235968
    add rx0, rx0, (w64) 4
    mv (w32) *rx0, (w32) 1106247680
    add rx0, rx0, (w64) 4
    mv (w32) *rx0, (w32) 0

    mv (w32) *rx1, (w32) 0
    add rx1, rx1, (w64) 4
    mv (w32) *rx1, (w32) 0
    add rx1, rx1, (w64) 4
    mv (w32) *rx1, (w32) 1103626240

    mv (w32) *rx2, (w32) 1106247680
    add rx2, rx2, (w64) 4
    mv (w32) *rx2, (w32) 1106247680
    add rx2, rx2, (w64) 4
    mv (w32) *rx2, (w32) 1106247680

    mv (w32) *rx3, (w32) 1101004800
    add rx3, rx3, (w64) 4
    mv (w32) *rx3, (w32) 1101004800
    add rx3, rx3, (w64) 4
    mv (w32) *rx3, (w32) 1101004800

    mv (w32) *rx4, (w32) 1061158912
    add rx4, rx4, (w64) 4
    mv (w32) *rx4, (w32) 1061158912
    add rx4, rx4, (w64) 4
    mv (w32) *rx4, (w32) 1061158912

    mv (w32) *rx5, (w32) 16711680
    add rx5, rx5, (w64) 4
    mv (w32) *rx5, (w32) 16776960
    add rx5, rx5, (w64) 4
    mv (w32) *rx5, (w32) 65280
    ret


#ray_impl(14):
; *SPHERE_X
mv rx14, rx0
; *SPHERE_Y
mv rx15, rx1
; *SPHERE_Z
mv rx16, rx2
; *SPHERE_R
mv rx17, rx3
; *SPHERE_REFL
mv rx18, rx4
; *SPHERE_COLOR
mv rx19, rx5

%lbl:

; step
mv ex20, (w32) 1203982336
; closest
mv ex21, (w32) 0
; s
mv ex22, (w32) 0
; s * 4
mv ex23, (w32) 0

;; find SDF
%lbl2:
; sp_vec_x
add rx0, rx14, rx23
mv ex0, (w32) *rx0
mv ex1, ex6
call #f32_sub(2)
mv ex3, ex0
; sp_vec_y
add rx0, rx15, rx23
mv ex0, (w32) *rx0
mv ex1, ex7
call #f32_sub(2)
mv ex4, ex0
; sp_vec_z
add rx0, rx16, rx23
mv ex0, (w32) *rx0
mv ex1, ex8
call #f32_sub(2)
mv ex5, ex0

mv ex0, ex3
mv ex1, ex4
mv ex2, ex5
call #dist2(3)
mv ex1, ex0
call #qrsqrt(1)
call #f32_mul(2)
add rx1, rx17, rx23
mv ex1, (w32) *rx1
call #f32_sub(2)
; step_new
mv ex24, ex0

mv ex0, ex9
mv ex1, ex10
mv ex2, ex11
call #dot_prod(6)
mv ex1, ex0
mv ex0, (w32) 0
call #f32_less(2)
xor l0, l0, (w8) 1
jpc l0, %lbl3
mv ex0, ex24
mv ex1, ex20
call #f32_less(2)
xor l0, l0, (w8) 1
jpc l0, %lbl3
mv ex20, ex24
mv ex21, ex22
%lbl3:

add ex22, ex22, (w32) 1
add ex23, ex23, (w32) 4
lt l0, ex22, (w32) 3
jpc l0, %lbl2

;; move

mv ex0, ex9
mv ex1, ex20
call #f32_mul(2)
mv ex1, ex6
call #f32_add(2)
mv ex6, ex0

mv ex0, ex10
mv ex1, ex20
call #f32_mul(2)
mv ex1, ex7
call #f32_add(2)
mv ex7, ex0

mv ex0, ex11
mv ex1, ex20
call #f32_mul(2)
mv ex1, ex8
call #f32_add(2)
mv ex8, ex0

mul ex21, ex21, (w32) 4

;; reflect

mv ex0, ex20
mv ex1, (w32) 1008981770
call #f32_less(2)
xor l0, l0, (w8) 1
jpc l0, %lbl4

add rx0, rx14, rx21
mv ex0, (w32) *rx0
mv ex1, ex6
call #f32_sub(2)
mv ex3, ex0
; sp_vec_y
add rx0, rx15, rx21
mv ex0, (w32) *rx0
mv ex1, ex7
call #f32_sub(2)
mv ex4, ex0
; sp_vec_z
add rx0, rx16, rx21
mv ex0, (w32) *rx0
mv ex1, ex8
call #f32_sub(2)
mv ex5, ex0

mv ex0, ex3
mv ex1, ex4
mv ex2, ex5
call #dist2(3)
call #qrsqrt(1)
mv ex2, ex0

mv ex0, ex3
mv ex1, ex2
call #f32_mul(2)
mv ex3, ex0
; sp_vec_x
mv ex25, ex0

mv ex0, ex4
mv ex1, ex2
call #f32_mul(2)
mv ex4, ex0
; sp_vec_y
mv ex26, ex0

mv ex0, ex5
mv ex1, ex2
call #f32_mul(2)
mv ex5, ex0
; sp_vec_z
mv ex27, ex0

mv ex0, ex9
mv ex1, ex10
mv ex2, ex11
mv ex3, ex25
mv ex4, ex26
mv ex5, ex27
call #dot_prod(6)
; cos_
mv ex28, ex0

mv ex1, (w32) 1073741824
call #f32_mul(2)
; cos_2
mv ex2, ex0

mv ex0, ex2
mv ex1, ex25
call #f32_mul(2)
mv ex1, ex0
mv ex0, ex9
call #f32_sub(2)
mv ex9, ex0

mv ex0, ex2
mv ex1, ex26
call #f32_mul(2)
mv ex1, ex0
mv ex0, ex10
call #f32_sub(2)
mv ex10, ex0 

mv ex0, ex2
mv ex1, ex27
call #f32_mul(2)
mv ex1, ex0
mv ex0, ex11
call #f32_sub(2)
mv ex11, ex0

mv ex1, (w32) -1
eq l0, ex13, (w32) 0
jpc l0, %lbl5

mv rx0, rx14
mv rx1, rx15
mv rx2, rx16
mv rx3, rx17
mv rx4, rx18
mv rx5, rx19
sub ex13, ex13, (w32) 1
call #ray_impl(14)
mv ex1, ex0

%lbl5:
add rx0, rx19, rx21
mv ex0, (w32) *rx0
add rx2, rx18, rx21
mv ex2, (w32) *rx2
call #reflection(3)

mv ex1, ex28
call #shadow(2) 

ret
%lbl4:

sub ex12, ex12, (w32) 1
lt l0, (w32) 0, ex12
jpc l0, %lbl

mv ex0, (w32) -1
ret

#app(0):
; SPHERE_X
alloc rx8, (w32) 12

; SPHERE_Y
alloc rx9, (w32) 12

; SPHERE_Z
alloc rx10, (w32) 12

; SPHERE_R
alloc rx11, (w32) 12

; SPHERE_REFL
alloc rx12, (w32) 12

; SPHERE_COLOR
alloc rx13, (w32) 12

; DATA
alloc rx14, (w32) 1000000

mv rx0, rx8
mv rx1, rx9
mv rx2, rx10
mv rx3, rx11
mv rx4, rx12
mv rx5, rx13
call #init(6)

mv ex15, (w32) 0
%lbl:
mul rx1, rx15, (w64) 4
add rx1, rx14, rx1
mv (w32) *rx1, (w32) 0
add ex15, ex15, (w32) 1
lt l2, ex15, (w32) 250000
jpc l2, %lbl

mv ex15, (w32) 0
%lbl2:

mv ex16, (w32) 0
%lbl3:

mv rx0, rx8
mv rx1, rx9
mv rx2, rx10
mv rx3, rx11
mv rx4, rx12
mv rx5, rx13
mv rx6, rx15
mv rx7, rx16
call #ray(8)

mul rx1, rx15, (w64) 500
add rx1, rx1, rx16
mul rx1, rx1, (w64) 4
add rx1, rx14, rx1
mv (w32) *rx1, ex0

add ex16, ex16, (w32) 1
lt l2, ex16, (w32) 500
jpc l2, %lbl3

mv ex16, (w32) 0
%lbl4:

mv ex17, (w32) 0
%lbl5:

mul rx2, rx16, (w64) 500
add rx2, rx2, rx17
mul rx2, rx2, (w64) 4
add rx2, rx14, rx2

drw ex16, ex17, (w32) *rx2

add ex17, ex17, (w32) 1
lt l2, ex17, (w32) 500
jpc l2, %lbl5

add ex16, ex16, (w32) 1
lt l2, ex16, (w32) 500
jpc l2, %lbl4

flsh

add ex15, ex15, (w32) 1
lt l2, ex15, (w32) 500
jpc l2, %lbl2


free rx14
free rx13
free rx12
free rx11
free rx10
free rx9
free rx8
ret

;;;;;;;;;;;;
; Float 32 ;
;;;;;;;;;;;;

#get_s(1):
    rshl ex0, ex0, (w8) 31
    ret

#set_s(2):
    and ex0, ex0, (w32) 2147483647
    lsh ex1, ex1, (w8) 31
    or ex0, ex0, ex1
    ret

#get_e(1):
    and ex0, ex0, (w32) 2139095040
    rshl ex0, ex0, (w8) 23
    ret

#set_e(2):
    and ex0, ex0, (w32) -2139095041
    lsh ex1, ex1, (w8) 23
    and ex1, ex1, (w32) 2139095040
    or ex0, ex0, ex1
    ret

#get_t(1):
    and ex0, ex0, (w32) 8388607
    ret

#set_t(2):
    and ex0, ex0, (w32) -8388608
    and ex1, ex1, (w32) 8388607
    or ex0, ex0, ex1
    ret

#get_mantissa(1):
    mv ex1, ex0
    mv ex2, ex0
    call #get_t(1)
    swp ex1, ex0
    call #f32_is_subnormal(1)
    jpc ex0, %lbl
    mv ex0, ex2
    call #f32_is_zero(1)
    jpc ex0, %lbl
    or ex1, ex1, (w32) 8388608
%lbl:
    mv ex0, ex1
    ret

#get_exp(1):
    mv ex1, ex0
    call #f32_is_subnormal(1)
    mv ex2, ex0
    mv ex0, ex1
    call #f32_is_zero(1)
    or ex0, ex0, ex2
    jpc ex0, %lbl
    mv ex0, ex1
    call #get_e(1)
    sub ex0, ex0, (w32) 127
    ret
%lbl:
    mv ex0, (w32) -126
    ret


#build_float(5):
%loop:
    ult l6, rx2, (w64) 16777216
    le l7, (w32) -126, ex1
    and l6, l6, l7
    jpc l6, %loop_end

    and l3, l2, (w8) 1
    add ex4, ex4, ex3

    rshl rx2, rx2, (w8) 1
    add ex1, ex1, (w32) 1
    jp %loop
%loop_end:

    lt l6, (w32) 1, ex4
    and rx7, rx2, (w64) 1
    or l6, l6, l7
    neq l7, l3, (w8) 0 
    and l6, l6, l7
    add rx2, rx2, rx6

    ule l6, (w64) 16777216, rx2
    rshl rx2, rx2, l6
    add ex1, ex1, ex6

    le l6, ex1, (w32) 127
    jpc l6, %lbl
    mv l1, l0
    mv ex0, (w32) 2139095040
    call #set_s(2)
    ret
%lbl: 
    ult l6, rx2, (w64) 8388608

    add ex1, ex1, (w32) 127
    sub ex7, ex1, ex6
    mv l8, l0

    mv ex0, (w32) 0
    mv ex1, ex2
    call #set_t(2)
    mv ex1, ex7
    call #set_e(2)
    mv l1, l8
    call #set_s(2)
    ret

#min(2):
    ule l3, ex0, ex1
    jpc l3, %lbl
    mv ex0, ex1
%lbl
    ret

#f32_negate(1):
    mv ex1, ex0
    call #f32_is_nan(1)
    swp ex0, ex1
    jpc ex1, %lbl
    xor ex0, ex0, (w32) -2147483648
%lbl:
    ret

#f32_sub(2):
    swp ex0, ex1
    call #f32_negate(1)
    swp ex0, ex1
    call #f32_add(2)
    ret

#f32_is_nan(1):
    mv ex1, ex0
    call #get_e(1)
    eq ex0, ex0, (w32) 255
    swp ex0, ex1
    call #get_t(1)
    neq ex0, ex0, (w32) 0
    and ex0, ex0, ex1
    ret

#f32_is_qnan(1):
    mv ex1, ex0
    call #f32_is_nan(1)
    swp ex0, ex1
    call #get_s(1)
    and ex0, ex0, ex1
    ret

#f32_is_snan(1):
    mv ex1, ex0
    call #f32_is_nan(1)
    swp ex0, ex1
    call #get_s(1)
    xor ex0, ex0, (w32) 1
    and ex0, ex0, ex1
    ret

#f32_is_inf(1):
    mv ex1, ex0
    call #get_e(1)
    eq ex0, ex0, (w32) 255
    swp ex0, ex1
    call #get_t(1)
    eq ex0, ex0, (w32) 0
    and ex0, ex0, ex1
    ret

#f32_is_zero(1):
    mv ex1, ex0
    call #get_e(1)
    eq ex0, ex0, (w32) 0
    swp ex0, ex1
    call #get_t(1)
    eq ex0, ex0, (w32) 0
    and ex0, ex0, ex1
    ret

#f32_is_subnormal(1):
    mv ex1, ex0
    call #get_e(1)
    eq ex0, ex0, (w32) 0
    swp ex0, ex1
    call #get_t(1)
    neq ex0, ex0, (w32) 0
    and ex0, ex0, ex1
    ret

#f32_less(2):
    mv ex2, ex0
    mv ex3, ex1
    
    call #f32_is_nan(1)
    jpc l0, %lbl2
    mv ex0, ex1
    call #f32_is_nan(1)
    jpc l0, %lbl2
    mv ex0, ex2
    mv ex1, ex3
    call #f32_equal(2)
    jpc l0, %lbl2

    mv ex0, ex2
    call #get_s(1)
    mv l4, l0

    mv ex0, ex3
    call #get_s(1)
    mv l5, l0

    eq l0, l4, l5
    jpc l0, %lbl
    lt l0, l5, l4
    ret
%lbl:
    lt l0, ex2, ex3
    xor l0, l0, l4
    ret

%lbl2:
    mv l0, (w8) 0
    ret

#f32_equal(2):
    mv ex2, ex0
    mv ex3, ex1
    
    call #f32_is_nan(1)
    jpc l0, %lbl3
    mv ex0, ex1
    call #f32_is_nan(1)
    jpc l0, %lbl3

    mv ex0, ex2
    call #f32_is_inf(1)
    xor l0, l0, (w8) 1
    jpc l0, %lbl
    mv ex0, ex3
    call #f32_is_inf(1)
    xor l0, l0, (w8) 1
    jpc l0, %lbl

    mv ex0, ex2
    call #get_s(1)
    mv l1, l0

    mv ex0, ex3
    call #get_s(1)
    eq l0, l0, l1
    ret
%lbl:
    mv ex0, ex2
    call #f32_is_zero(1)
    xor l0, l0, (w8) 1
    jpc l0, %lbl2
    mv ex0, ex3
    call #f32_is_zero(1)
    xor l0, l0, (w8) 1
    jpc l0, %lbl2

    mv l0, (w8) 1
    ret

%lbl2:
    eq l0, ex2, ex3
    ret

%lbl3:
    mv l0, (w8) 0
    ret

#f32_to_ll(1):
    mv ex1, ex0
    call #f32_is_inf(1)
    jpc l0, %lbl
    mv ex0, ex1
    call #f32_is_nan(1)
    jpc l0, %lbl

    mv ex0, ex1
    call #f32_is_zero(1)
    jpc l0, %lbl2

    mv ex0, ex1
    call #get_mantissa(1)
    mv rx2, rx0

    mv ex0, ex1
    call #get_exp(1)
    sub ex3, ex0, (w32) 23

    mv ex0, ex1
    call #get_s(1)
    mv l4, l0

    le l0, ex3, (w32) -64
    jpc l0, %lbl2

    lt l0, (w32) 0, ex3
    jpc l0, %lbl3

    sub ex3, (w32) 0, ex3
    rsha rx2, rx2, ex3
    jpc l4, %lbl4

    mv rx0, rx2
    ret

%lbl3:
    le l0, (w32) 40, ex3
    jpc l0, %lbl 

    lsh rx2, rx2, ex3
    jpc l4, %lbl4

    mv rx0, rx2
    ret

%lbl4:
    sub rx0, (w64) 0, rx2
    ret

%lbl:
    mv rx0, (w64) -9223372036854775808
    ret

%lbl2:
    mv rx0, (w64) 0
    ret

#f32_from_ll(1):
    eq l1, rx0, (w64) 0
    jpc l1, %lbl

    mv rx2, rx0
    mv ex1, (w32) 23
    
    le l3, (w64) 0, rx2
    jpc l3, %lbl2
    sub rx2, (w64) 0, rx2
%lbl2:

    le l3, (w64) 16777216, rx2
    jpc l3, %lbl3
    lsh rx2, rx2, (w8) 24
    sub ex1, ex1, (w32) 24
%lbl3:

    lt l0, rx0, (w64) 0
    mv l3, (w8) 0
    mv l4, (w8) 0

    call #build_float(5)
%lbl:
    ret


#f32_mul(2):
    mv ex2, ex0
    mv ex3, ex1

    call #f32_is_nan(1)
    jpc l0, %lbl
    mv ex0, ex3
    call #f32_is_nan(1)
    jpc l0, %lbl

    mv ex0, ex2
    call #f32_is_inf(1)
    jpc l0, %lbl2
    mv ex0, ex3
    call #f32_is_inf(1)
    jpc l0, %lbl2
    jp %lbl3
%lbl2:
    mv ex0, ex2
    call #f32_is_zero(1)
    jpc l0, %lbl
    mv ex0, ex3
    call #f32_is_zero(1)
    jpc l0, %lbl
    jp %lbl3
%lbl3:

    mv ex5, (w32) 2139095040
    mv ex0, ex2
    call #f32_is_inf(1)
    jpc l0, %lbl4
    mv ex0, ex3
    call #f32_is_inf(1)
    jpc l0, %lbl4

    mv ex5, (w32) 0
    mv ex0, ex2
    call #f32_is_zero(1)
    jpc l0, %lbl4
    mv ex0, ex3
    call #f32_is_zero(1)
    jpc l0, %lbl4


    mv ex0, ex2
    call #get_s(1)
    mv l1, l0
    mv ex0, ex3
    call #get_s(1)
    xor l5, l1, l0

    mv ex0, ex2
    call #get_mantissa(1)
    mv ex6, ex0
    mv ex0, ex3
    call #get_mantissa(1)
    mul rx6, rx6, rx0

    mv ex0, ex2
    call #get_exp(1)
    mv ex1, ex0
    mv ex0, ex3
    call #get_exp(1)
    add ex1, ex1, ex0
    sub ex1, ex1, (w32) 23

    mv l0, l5
    mv rx2, rx6
    mv l3, (w8) 0
    mv l4, (w8) 0
    call #build_float(5)
    ret

%lbl:
    mv ex0, (w32) 4294967295
    ret

%lbl4:
    mv ex0, ex2
    call #get_s(1)
    mv l1, l0
    mv ex0, ex3
    call #get_s(1)
    xor l1, l1, l0
    mv ex0, ex5
    call #set_s(2)
    ret

#f32_div(2):
    mv ex2, ex0
    mv ex3, ex1

    call #f32_is_nan(1)
    jpc l0, %lbl
    mv ex0, ex3
    call #f32_is_nan(1)
    jpc l0, %lbl

    mv ex0, ex2
    call #f32_is_inf(1)
    jpc l0, %lbl2
    mv ex0, ex3
    call #f32_is_zero(1)
    jpc l0, %lbl2
    jp %lbl3
%lbl2:
    mv ex0, ex2
    call #f32_is_zero(1)
    jpc l0, %lbl
    mv ex0, ex3
    call #f32_is_inf(1)
    jpc l0, %lbl
    jp %lbl3
%lbl3:

    mv ex5, (w32) 2139095040
    mv ex0, ex2
    call #f32_is_inf(1)
    jpc l0, %lbl4
    mv ex0, ex3
    call #f32_is_zero(1)
    jpc l0, %lbl4

    mv ex5, (w32) 0
    mv ex0, ex2
    call #f32_is_zero(1)
    jpc l0, %lbl4
    mv ex0, ex3
    call #f32_is_inf(1)
    jpc l0, %lbl4


    mv ex0, ex2
    call #get_s(1)
    mv l5, l0
    mv ex0, ex3
    call #get_s(1)
    xor l5, l5, l0

    mv ex0, ex2
    call #get_exp(1)
    mv ex1, ex0
    mv ex0, ex3
    call #get_exp(1)
    sub ex1, ex1, ex0
    add ex1, ex1, (w32) 23

    mv ex0, ex2
    call #get_mantissa(1)
    mv ex7, ex0
    mv ex0, ex3
    call #get_mantissa(1)
    mv ex8, ex0

    mv rx2, (w64) 0

%lbl5:
    lsh rx7, rx7, (w8) 24
    sub ex1, ex1, (w32) 24
    lsh rx2, rx2, (w8) 24
    udiv rx9, rx7, rx7, rx8
    add rx2, rx2, rx9
    lt l0, rx2, (w64) 16777216
    jpc l0, %lbl5

    mv l0, l5

    mul rx7, rx7, (w64) 2
    ule l3, rx8, rx7

    ult l4, (w64) 0, rx7
    add l4, l4, l3
    call #build_float(5)
    ret

%lbl:
    mv ex0, (w32) 4294967295
    ret

%lbl4:
    mv ex0, ex2
    call #get_s(1)
    mv l1, l0
    mv ex0, ex3
    call #get_s(1)
    xor l1, l1, l0
    mv ex0, ex5
    call #set_s(2)
    ret

#f32_add(2):
    mv ex2, ex0
    mv ex3, ex1

    call #f32_is_nan(1)
    jpc l0, %lbl
    mv ex0, ex3
    call #f32_is_nan(1)
    jpc l0, %lbl

    mv ex0, ex2
    call #f32_is_inf(1)
    xor l0, l0, (w8) 1
    jpc l0, %lbl2
    mv ex0, ex3
    call #f32_is_inf(1)
    xor l0, l0, (w8) 1
    jpc l0, %lbl2

    mv ex0, ex2
    call #get_s(1)
    mv l1, l0
    mv ex0, ex3
    call #get_s(1)
    neq l0, l0, l1
    jpc l0, %lbl
    mv ex0, ex2
    ret

%lbl2:
    mv ex0, ex2
    call #f32_is_inf(1)
    jpc l0, %lbl3
    mv ex0, ex3
    call #f32_is_zero(1)
    jpc l0, %lbl3

    mv ex0, ex2
    call #f32_is_zero(1)
    jpc l0, %lbl4
    mv ex0, ex3
    call #f32_is_inf(1)
    jpc l0, %lbl4

    and ex0, ex2, (w32) 2147483647
    and ex1, ex3, (w32) 2147483647
    call #f32_less(2)
    xor l0, l0, (w8) 1
    jpc l0, %lbl5
    swp ex2, ex3
%lbl5:
    mv ex0, ex2
    call #get_mantissa(1)
    ; a_mantissa
    mv ex4, ex0
    mv ex0, ex3
    call #get_mantissa(1)
    ; b_mantissa
    mv ex5, ex0

    mv ex0, ex2
    call #get_exp(1)
    ; a_exp
    mv ex6, ex0
    mv ex0, ex3
    call #get_exp(1)
    ; b_exp
    mv ex7, ex0

    mv ex0, ex2
    call #get_s(1)
    ; a_s
    mv l8, l0
    mv ex0, ex3
    call #get_s(1)
    ; b_s
    mv l9, l0

    neq l0, l8, l9
    jpc l0, %lbl6

    ; a_shift
    sub ex11, ex6, ex7
    mv ex0, ex11
    mv ex1, (w32) 24
    call #min(2)
    ; a_shift_trunc
    mv ex10, ex0
    mv ex1, (w32) 24
    sub ex0, ex11, ex10
    call #min(2)
    ; b_shift
    mv ex11, ex0

    lsh rx4, rx4, l10
    sub ex6, ex6, ex10
    rshl rx0, rx5, l11
    add rx2, rx4, rx0

    sub l0, l11, (w8) 1
    rshl rx3, rx5, l0
    and l3, l3, (w8) 1

    lsh ex0, ex3, l0
    lsh ex11, (w32) -1, ex11
    xor ex11, ex11, (w32) 4294967295
    and ex1, ex1, ex11
    lt l4, ex0, ex1

    mv l0, l8
    mv ex1, ex6

    call #build_float(5)
    ret
%lbl6:
    ; a_shift
    sub ex11, ex6, ex7
    lt l0, (w32) 24, ex11
    jpc l0, %lbl3

    lsh rx4, rx4, l11
    sub ex6, ex6, ex11
    sub rx4, rx4, rx5

%lbl7:
    le l0, (w64) 16777216, rx4
    jpc l0, %lbl8
    le l0, ex6, (w32) -126
    jpc l0, %lbl8

    lsh rx4, rx4, (w8) 1
    sub ex6, ex6, (w32) 1
    jp %lbl7
%lbl8:
    mv l0, l8
    mv ex1, ex6
    mv rx2, rx4
    mv l3, (w8) 0
    mv l4, (w8) 0
    call #build_float(5)
    ret
%lbl:
    mv ex0, (w32) 4294967295
    ret

%lbl3:
    mv ex0, ex2
    ret

%lbl4:
    mv ex0, ex3
    ret