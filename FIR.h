/* Implemented in 2023 by João Gabriel, electronics coordinator of Mangue Baja 2023/24 */
#ifndef FIR_H
#define FIR_H

#include <stdio.h>

/* If you needed apply the filter two times */
//#define double_filter // uncomment if you wanna apply the filter two times

/*You can change the size of the vetor if you needed*/
#define SIZE 2

/* Here you can change the filter coefficient manually */
const float a = 0.6,
            b = 0.6;

/* Can use only in one variable. Using the second variable the value of the static float has change */
class FIR  {
    public:
    /*========================================================================================================
        * "a" and "b" are the filter coefficients
        * The higher the value of the coefficient, the slower its update rate, but the stronger its filter.
        * Filter based on convolution between previous inputs.
        * Can suport only for order equal 2
    ==========================================================================================================*/
        float filt(float x);
    private:
    /*=========================
        * Update the vetor
        * Second filter
    ==========================*/
        void move_vec(float *vetorAddr, int size, float value); 
        float filtfilt(float x2); // Second filter if you defined
        float double_y;
        bool flag=false;
};


float FIR::filt(float x)
{
    #ifdef double_filter
        flag = true;
    #endif

    static float y_pass[SIZE] = {0,0}, x_pass[SIZE] = {0,0};

    float y = (a+b)*y_pass[0] - a*b*y_pass[1] + (1-a-b + a*b)*x_pass[1];
    
    move_vec(y_pass, SIZE, y);
    move_vec(x_pass, SIZE, x);

    (flag) ? double_y = filtfilt(y) : double_y = y; 

    return double_y;
};

void FIR::move_vec(float *vetorAddr, int size, float value)
{
    for (int k=size-1; k>0; k--)
    {
        *(vetorAddr+k) = *(vetorAddr+k-1);
    }

    *vetorAddr = value;
};

float FIR::filtfilt(float x2)
{
    static float y2_pass[SIZE] = {0,0}, x2_pass[SIZE] = {0,0};

    float y2 = (a+b)*y2_pass[0] - a*b*y2_pass[1] + (1-a-b + a*b)*x2_pass[1];
    
    move_vec(y2_pass, SIZE, y2);
    move_vec(x2_pass, SIZE, x2);

    return y2;
};


#endif
