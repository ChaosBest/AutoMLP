#ifndef _AUTO_MLP_GEN_HPP_
#define _AUTO_MLP_GEN_HPP_

#include<string.h>
#include<math.h>
#include<stdio.h>
#include<iostream>
// #include<ap_fixed.h>  // 非HLS的C环境下，需要把这句注释掉
typedef float ap_f;

void AF_classifier(float *in, float *out, int len);


#endif