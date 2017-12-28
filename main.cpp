#include <cstring>
#include <cstdint>

#ifdef _MSC_VER  
#include <intrin.h>
#endif 


enum class Vendor { NotSet, Intel, AMD };
enum class Instr { NotSet, SSE, SSE2, SSE3, SSE4_1, SSE4_2, AVX, AVX2 };


#include <iostream>

namespace CPUDetect
{	
	void cpuid(uint32_t eax, uint32_t ecx, uint32_t* abcd)
	{
#if _MSC_VER
		__cpuidex((int*)abcd, eax, ecx);
#else
		uint32_t ebx, edx;
		__asm__("cpuid" : "+b" (ebx), "+a" (eax), "+c" (ecx), "=d" (edx));
		abcd[0] = eax; abcd[1] = ebx; abcd[2] = ecx; abcd[3] = edx;
#endif
	}

	Vendor GetVendor()
	{
		Vendor v{ Vendor::NotSet };
		uint32_t abcd[4]{};
		cpuid(0, 0, abcd);
		char name[13];
		memcpy(name + 0, &abcd[1], 4);
		memcpy(name + 4, &abcd[3], 4);
		memcpy(name + 8, &abcd[2], 4);
		name[12] = 0;

		if (strstr(name, "Intel"))
			v = Vendor::Intel;
		else if (strstr(name, "AMD"))
			v = Vendor::AMD;

		return v;
	}

	Instr GetIstr()
	{
		Instr instr{ Instr::NotSet };
		uint32_t abcd[4]{};
		cpuid(1, 0, abcd);

		uint32_t edx = abcd[3];

		uint32_t ecx = abcd[2];

		if ((edx >> 25) & 1)
			instr = Instr::SSE;

		if ((edx >> 26) & 1)
			instr = Instr::SSE2;

		if ((ecx >> 0) & 1);
			instr = Instr::SSE3;

		if ((ecx >> 19) & 1);
			instr = Instr::SSE4_1;

		if ((ecx >> 20) & 1);
			instr = Instr::SSE4_2;

		if ((ecx >> 28) & 1);
			instr = Instr::AVX;

		cpuid(7, 0, abcd);

		uint32_t ebx = abcd[1];
		if ((ebx >> 5) & 1)
			instr = Instr::AVX2;

		return instr;
	}
};

void PrintVendor(Vendor v)
{
	switch (v)
	{
	case Vendor::NotSet:
		std::cout << "NotSet";
		break;
	case Vendor::Intel:
		std::cout << "Intel";
		break;
	case Vendor::AMD:
		std::cout << "AMD";
		break;
	default:
		break;
	}
}

void PrintInstr(Instr instr)
{
	switch (instr)
	{
	case Instr::NotSet:
		std::cout << "NotSet";
		break;
	case Instr::SSE:
		std::cout << "SSE";
		break;
	case Instr::SSE2:
		std::cout << "SSE2";
		break;
	case Instr::SSE3:
		std::cout << "SSE3";
		break;
	case Instr::SSE4_1:
		std::cout << "SSE4.1";
		break;
	case Instr::SSE4_2:
		std::cout << "SSE4.2";
		break;
	case Instr::AVX:
		std::cout << "AVX";
		break;
	case Instr::AVX2:
		std::cout << "AVX2";
		break;
	default:
		break;
	}
}

int main()
{
	auto instr = CPUDetect::GetIstr();
	PrintInstr(instr);
	PrintVendor(CPUDetect::GetVendor());
}
