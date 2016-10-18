// simd.cpp : Defines the entry point for the console application.
// Single Instruction multiple data allows vectorized operations using large registers
// This program uses assembly language in C++

#include "stdafx.h"

string get_cpu_name() {
	uint32_t data[4] = { 0 }; 

	_asm // assembly language instruction
	{
		cpuid;
		mov data[0], ebx;
		mov data[4], edx;
		mov data[8], ecx;

	}
	return string((const char*)data);

}

void assembler() {
	cout << "CPU is:" << get_cpu_name() << endl;
	float f1[] = { 1.f,2.f,3.f,4.f };
	float f2[] = { 5.f,4.f,3.f,2.f };
	float result[4] = { 0.f };
	_asm
	{
		movups xmm1, f1;     //move value of f1 in resgister
		movups xmm2, f2;     //move value of f2 in resgister
		mulps xmm1, xmm2;    // multiply f1 and f2
		movups result, xmm1;  // mover multiplication result in result array
	}
	for (size_t i = 0; i < 4; i++) {
		cout << result[i] << "\t";
	}
	cout << endl;

	int d, c;
	_asm {
		mov eax, 1;
		cpuid;
		mov d, edx;
		mov c, ecx;
	}
	if ((d & (1 < 26)) != 0)
		cout << "SSE2 is supported" << endl;
	if ((c & 1) != 0)
		cout << "SSE3 is supported" << endl;
	if ((c & (1 << 19)) != 0)
		cout << "SSE4.1 is supported" << endl;
	if ((c & (1 << 20)) != 0)
		cout << "SSE4.2 is supported" << endl;

}
void intrinsic() {// wrapper function around assembly language instead of using register
	auto a = _mm_set_ps(1, 2, 3, 4);
	auto b = _mm_set_ps(4, 3, 2, 14);
	auto c = _mm_add_ps(a,b);

	float f = c.m128_f32[1];
	cout << "Intrinsic value is:" << f << endl;

	__try {
		__m256d z = _mm256_set_pd(1, 2, 3, 4);
	}
	__except (1) {
		cout << "Sorry you can not execute this:";
	}


}


int main(int argc,char* argv[] )
{
	assembler();
	intrinsic();


	system("Pause");
    return 0;
}
