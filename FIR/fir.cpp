#include "fir.h"


void FIR(hls::stream<data_t> &in_x, hls::stream<data_t> &out_y, int length) {
    static coef_t c[N] = { 10, 11, 11, 8, 3, -3, -8, -11, -11, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -11, -11, -8, -3, 3, 8, 11, 11, 10, 10, 10, 10, 10, 10, 10, 10, 11, 11, 8, 3, -3, -8, -11, -11, -10, -10, -10, -10, -10, -10, -10, -10, -11, -11, -8, -3, 3, 8, 11, 11, 10, 10, 10, 10, 10, 10, 10, 10, 11, 11, 8, 3, -3, -8, -11, -11, -10, -10, -10, -10, -10, -10, -10, -10, -11, -11, -8, -3, 3, 8, 11, 11, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10 };
    static data_t reg[128];
	static int buffer_id;
	//data_t out_y = 0;
	data_t sum = 0;

	reg[buffer_id] = in_x.read();
FIR: for (int i = 0; i <N; i++) {
		int idx = (buffer_id + N - i) % N;
		sum += c[i] * reg[idx];
		//out_y = sum;
	}
	buffer_id=(buffer_id + 1) % N;
	out_y.write(sum);
}



void read_from_mem(data_t in_x[MAX_LENGTH],hls::stream<data_t> &in_st, int length){
	int i;
	read_mem:for(i=0;i<length;i++){
		in_st.write(in_x[i]);
	}
}

void write_to_mem(data_t out_y[MAX_LENGTH],hls::stream<data_t> &out_st, int length){
	int i;
	write_mem:for(i=0;i<length;i++){
		out_y[i]=out_st.read();
	}
}




void FIR_flow(data_t in_x[MAX_LENGTH], data_t out_y[MAX_LENGTH], int length){
//#pragma HLS INTERFACE mode=m_axi bundle=img_i depth=1024 port=in_x
//#pragma HLS INTERFACE mode=m_axi bundle=img_i depth=1024 port=out_y
	data_t output,input;
	int i;
	hls::stream<data_t> in_st, out_st;
#pragma HLS DATAFLOW
	read_from_mem:
	read_from_mem(in_x, in_st, length);

	fir_loop:
	for (i = 0; i < length; i++) {
		//input = in_x.read();
		FIR(in_st, out_st,length);
		//out_st.write(output);
		//std::cout << "Input: " << in_x[i] << " -> Output: " << output << std::endl;
	}
	write_to_mem:
	write_to_mem(out_y, out_st, length);
}
