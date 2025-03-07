#include <hls_stream.h>

typedef int coef_t;
typedef int data_t;
#define MAX_LENGTH 1024

const int N = 128;


void FIR(hls::stream<data_t> &in_x, hls::stream<data_t> &out_y,int length);
void FIR_flow(data_t in_x[MAX_LENGTH], data_t out_y[MAX_LENGTH], int length);