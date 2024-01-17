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
        memcpy(A, (const float*) in, len * sizeof(float));