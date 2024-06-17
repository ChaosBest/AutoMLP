// #include "AF_classifier.hpp"
// #include<string.h>
// #include<math.h>
// #include<stdio.h>
// #include<iostream>
// #include<ap_fixed.h>  // 非HLS的C环境下，需要把这句注释掉

#include "AutoMLP_gen.hpp"

typedef float ap_f;

void AF_classifier(float *in, float *out, int len)
{
#pragma HLS INTERFACE s_axilite port=return bundle=sqrt
#pragma HLS INTERFACE s_axilite port=len bundle=sqrt
#pragma HLS INTERFACE m_axi depth=50 port=out offset=slave bundle=output
#pragma HLS INTERFACE m_axi depth=50 port=in offset=slave bundle=input
#pragma HLS INTERFACE s_axilite port=in bundle=sqrt
#pragma HLS INTERFACE s_axilite port=out bundle=sqrt

        ap_f A[50]; // input features: in[] -> A[]
		int int_para = 1;
		int result = 2;
        memcpy(A, (const float*) in, len * sizeof(float));ap_f B[4];
ap_f C[1];
ap_f Hw1[4][6] = {{-0.2910785675048828,-1.2862141132354736,3.169438600540161,-1.6389503479003906,0.5535781979560852,-1.9670149087905884},
{3.219022512435913,3.4730072021484375,-3.2917275428771973,1.0623385906219482,-0.2618819773197174,0.3571542799472809},
{1.6618882417678833,-4.357565879821777,-2.3874921798706055,0.6701198220252991,-0.4003327190876007,1.1839827299118042},
{4.810781955718994,-0.7426977157592773,-0.29800909757614136,3.0840702056884766,0.5274797677993774,1.9114278554916382}};


ap_f Hb1[4] = {-0.20586463809013367,-1.0412694215774536,-0.33689144253730774,1.3424952030181885};


ap_f Hw2[1][4] = {{0.3618382513523102,-3.4302470684051514,-1.1112910509109497,-1.0121639966964722}};


ap_f Hb2[1] = {-2.173591136932373};


    for (int i = 0; i < 4; i++) {
        B[i] = 0;
        for (int j = 0; j < 6; j++) {
            B[i] = B[i] + A[j] * Hw1[i][j];
        }
        B[i] = B[i] + Hb1[i] ;
        B[i] = 2/(1+expf(-2*B[i]))-1;    }
    for (int i = 0; i < 1; i++) {
        C[i] = 0;
        for (int j = 0; j < 4; j++) {
            C[i] = C[i] + B[j] * Hw2[i][j];
        }
        C[i] = C[i] + Hb2[i] ;
    }
    if (C[0] > C[1])    // the logic here is for binary classification, need adjust
        {result = 0 ;}
    else
        {result = 1 ;}
    out[0] = result;
}
