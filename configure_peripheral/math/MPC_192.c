/*
Nguyen Trung Tinh
tinhhayho@gmail.com
mo hinh dieu khien du doan
*/
#include "F2806x_Device.h"     // F2806x Headerfile Include File
float32 Vreal[27] =          \
{0.0        ,  0.0        ,          0.0,\
 0.333333333,  0.333333333,  0.166666667,\
 0.166666667, -0.166666667, -0.166666667,\
-0.333333333, -0.333333333, -0.166666667,\
-0.166666667,  0.166666667,  0.166666667,\
 0.666666667,  0.5        ,  0.333333333,\
 0.0        , -0.333333333, -0.5        ,\
-0.666666667, -0.5        , -0.333333333,\
 0.0        ,  0.333333333,  0.5         \
};

float32 Vimag[27]=
{0.0        ,  0.0        ,         0.0 ,\
 0.0        ,  0.0        ,  0.288675135,\
 0.288675135,  0.288675135,  0.288675135,\
 0.0        ,  0.0        , -0.288675135,\
-0.288675135, -0.288675135, -0.288675135,\
 0.0        ,  0.288675135,  0.577350269,\
 0.577350269,  0.577350269,  0.288675135,\
 0.0        , -0.288675135, -0.577350269,\
-0.577350269, -0.577350269, -0.288675135,\
};

// define swicth control signal
Uint16  output_signal[27][6] =
    {
        {0, 1, 0, 1, 0, 1}, {0, 0, 0, 0, 0, 0}, {1, 1, 1, 1, 1, 1}, \
        {1, 1, 0, 1, 0, 1}, {0, 1, 0, 0, 0, 0}, {1, 1, 1, 1, 0, 1}, \
        {0, 1, 0, 1, 0, 0}, {0, 1, 1, 1, 0, 1}, {0, 0, 0, 1, 0, 0}, \
        {0, 1, 1, 1, 1, 1}, {0, 0, 0, 1, 0, 1}, {0, 1, 0, 1, 1, 1}, \
        {0, 0, 0, 0, 0, 1}, {1, 1, 0, 1, 1, 1}, {0, 1, 0, 0, 0, 1}, \
        {1, 1, 0, 0, 0, 0}, {1, 1, 0, 1, 0, 0}, {1, 1, 1, 1, 0, 0}, \
        {0, 1, 1, 1, 0, 0}, {0, 0, 1, 1, 0, 0}, {0, 0, 1, 1, 0, 1}, \
        {0, 0, 1, 1, 1, 1}, {0, 0, 0, 1, 1, 1}, {0, 0, 0, 0, 1, 1}, \
        {0, 1, 0, 0, 1, 1}, {1, 1, 0, 0, 1, 1}, {1, 1, 0, 0, 0, 1}  \
    };


Uint16 state_p_n[27][6]=
    {
        {0,0,0,0,0,0},{0,1,0,1,0,1},{1,0,1,0,1,0},\
        {1,0,0,0,0,0},{0,0,0,1,0,1},{1,0,1,0,0,0},\
        {0,0,0,0,0,1},{0,0,1,0,0,0},{0,1,0,0,0,1},\
        {0,0,1,0,1,0},{0,1,0,0,0,0},{0,0,0,0,1,0},\
        {0,1,0,1,0,0},{1,0,0,0,1,0},{0,0,0,1,0,0},\
        {1,0,0,1,0,1},{1,0,0,0,0,1},{1,0,1,0,0,1},\
        {0,0,1,0,0,1},{0,1,1,0,0,1},{0,1,1,0,0,0},\
        {0,1,1,0,1,0},{0,1,0,0,1,0},{0,1,0,1,1,0},\
        {0,0,0,1,1,0},{1,0,0,1,1,0},{1,0,0,1,0,0}\
    };

/*
    he so (1 - R*Ts/L)
    he so (Ts /L)
*/
