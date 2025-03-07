#include "fir.h"
#include <iostream>


int main()
{
    using namespace std;
	std::cout << "Hello World!\n";
	data_t input[10] = {0, 0, 0, 1, 1, 1, 1, 0, 0, 0};
	data_t output[10] = {0};
	std::cout << "\nOutput:" << std::endl;

	FIR_flow(input, output, 10);

	for(int i=0;i< 10;i++){
		cout<< output[i]<<" " <<endl;

	}

	return 0;
}
