#include "AF_classifier.hpp"
#include<string.h>
#include<math.h>
#include<stdio.h>
#include<iostream>
#include<ap_fixed.h>

#define SIZE 20000
//typedef ap_fixed<20,10,AP_RND,AP_SAT> ap_f;
//typedef float ap_f;
//typedef ap_fixed<20,10> ap_f;
//typedef ap_fixed<19,9> ap_f;

//typedef ap_fixed<17,7> ap_f;
//typedef ap_fixed<15,5> ap_f;
//typedef ap_fixed<14,4> ap_f;
//typedef ap_fixed<13,3> ap_f;
//typedef ap_fixed<12,2> ap_f;
//typedef ap_fixed<11,1> ap_f;
//typedef ap_fixed<10,0> ap_f;
//typedef ap_fixed<13,4> ap_f;
//typedef ap_fixed<12,4> ap_f;
//typedef ap_fixed<11,4> ap_f;
//typedef ap_fixed<10,4> ap_f;
//typedef ap_fixed<9,4> ap_f;
typedef ap_fixed<8,4> ap_f;
//typedef ap_fixed<7,4> ap_f;
//typedef ap_fixed<6,4> ap_f;
//typedef ap_fixed<5,4> ap_f;
//typedef ap_fixed<4,4> ap_f;
void AF_classifier(int a0,int a1,int a2,int a3,int a4,int a5,int a6,int len,int& result)
{
#pragma HLS INTERFACE ap_ctrl_none port=return
//#pragma HLS INTERFACE s_axilite port=return bundle=sqrt
#pragma HLS INTERFACE s_axilite port = a0
#pragma HLS INTERFACE s_axilite port = a1
#pragma HLS INTERFACE s_axilite port = a2
#pragma HLS INTERFACE s_axilite port = a3
#pragma HLS INTERFACE s_axilite port = a4
#pragma HLS INTERFACE s_axilite port = a5
#pragma HLS INTERFACE s_axilite port = a6
#pragma HLS INTERFACE s_axilite port = result
#pragma HLS INTERFACE s_axilite port=len

//#pragma HLS INTERFACE s_axilite port = in
//#pragma HLS INTERFACE s_axilite port = out
	//*result = 2;
	result = 2;


	ap_f A[7];
	A[0]=(float)a0/4096;A[1]=(float)a1/4096;A[2]=(float)a2/4096;A[3]=(float)a3/4096;A[4]=(float)a4/4096;A[5]=(float)a5/4096;A[6]=(float)a6/4096;



	int int_para = 1;
	ap_f Hw[16][7]    = {{-2.1635e-01, -4.5685e-01,  9.1990e-02,  6.7167e-02,  3.0201e-01,
            5.3739e-02,  1.8942e-01},
          { 6.5313e-01, -4.2940e-01, -9.1730e-02, -1.0016e-01, -2.3417e-01,
            5.6261e-01, -4.2344e-02},
          { 5.5730e-05, -2.7478e-01, -3.4445e-01, -3.3480e-01,  2.7764e-01,
           -1.5502e-01, -2.2994e-01},
          {-4.3785e-01, -6.6753e-02,  3.4735e-01,  3.7588e-01,  2.8523e-01,
           -1.3024e-01, -3.8435e-01},
          {-3.1664e-01, -2.9045e-01,  3.9429e-01, -9.0817e-02, -8.9274e-02,
           -4.5173e-01, -3.6740e-02},
          { 4.5830e-01,  3.3526e-02,  1.1910e-01,  2.2095e-01, -6.6260e-02,
            4.3027e-01,  1.3397e-01},
          { 2.7276e-01,  2.8809e-01,  5.5234e-02, -2.7251e-01,  1.4922e-01,
            2.2675e-01,  1.2493e-01},
          {-3.7481e-01,  2.3715e-01, -5.8013e-02,  1.1898e-01,  1.2002e-01,
            6.1026e-02, -1.6719e-01},
          { 1.7686e-01,  2.4340e-01,  1.4538e-01, -2.3190e-01, -1.5121e-01,
            1.8622e-01,  4.3862e-01},
          { 3.4162e-01,  2.2434e-01, -3.0738e-01,  3.4456e-01, -2.3012e-01,
            1.0017e-01,  3.2625e-01},
          {-2.6297e-01,  2.0140e-02,  1.9135e-01,  2.7086e-01,  3.9259e-01,
           -4.7247e-01, -2.3859e-01},
          {-5.1901e-01,  1.5271e-01,  1.7464e-01, -1.8270e-01,  2.5449e-01,
            1.8096e-01,  1.9831e-02},
          { 3.4121e-01,  2.4041e-01,  2.3026e-01,  2.5596e-01, -3.6984e-01,
           -3.2944e-02,  2.1602e-01},
          {-2.5915e-01, -3.4253e-01,  1.6798e-01,  1.6753e-01,  2.8481e-01,
            2.8084e-02, -2.8441e-01},
          {-2.4316e-01, -3.0582e-02,  2.7075e-01,  2.7648e-01, -2.8107e-02,
           -3.4062e-01,  2.5736e-02},
          {-9.9231e-02,  4.3162e-02, -1.4912e-01, -3.6930e-01,  2.5256e-01,
           -1.5508e-01, -1.2788e-01}};


	ap_f Hb[16] ={-0.1438,  0.1587,  0.1631,  0.2266, -0.2645,  0.0422,  0.2796, -0.0801,
           0.2275, -0.2703, -0.1767,  0.1844, -0.0750,  0.1539,  0.2741, -0.0958};

	ap_f Ow[2][16] =  {{ 0.2222,  0.4590,  0.1597,  0.0971, -0.1012, -0.1474, -0.3208,  0.0435,
	         -0.2167,  0.1069,  0.0293,  0.0036, -0.0294,  0.2325, -0.0378,  0.2318},
	        {-0.1287, -0.4736, -0.1762, -0.2877, -0.3393,  0.4785,  0.4126, -0.1029,
	          0.3692, -0.1431, -0.3481, -0.3091,  0.4519, -0.1673,  0.1480, -0.1181}};
	ap_f Ob[2] = {0.2173, 0.2293};

	ap_f B[16],C[16],D[12],E[8],F[2];

	for (int i = 0; i < 16; i++) {
		B[i] = 0;
		for (int j = 0; j < 7; j++) {
			B[i] = B[i] + A[j] * Hw[i][j];
		}
		B[i] = B[i]/int_para + Hb[i] ;
		if(B[i] < 0){B[i] = 0;}
	}

		for (int i = 0; i < 2; i++) {
			F[i] = 0;
			for (int j = 0; j < 16; j++) {
				F[i] = F[i] + B[j] * Ow[i][j];
			}
			F[i] = F[i]/int_para + Ob[i] ;
		}
		//
    //std::cout<<F[0]<<':'<<F[1]<<':'<<std::endl;
	//*result = 1;

	if (F[0] > F[1])
		{result = 0 ;}

	else
		{result = 1;}
	if (A[0] == A[2] == A[6]){
		result = 2;
	}
}
