#include "cpu_info.h"
#include <iostream>
#include <iomanip>
#include <string>

void Print(std::ostream& outstream, const std::string& ext_name, bool is_enabled)
{
	outstream << ext_name <<": " << std::setw(10) << (is_enabled ? "ENABLED" : "DISABLED") << "\n";
}

int main()
{
	std::cout << CCpuInfo::GetVendor() << "\n";
	std::cout << CCpuInfo::GetBrand() << "\n";
	
	std::cout << "Extensions: ";
	auto& out = std::cout;
	Print(out, "SSE", CCpuInfo::SSE_Enabled());
	Print(out, "SSE2", CCpuInfo::SSE2_Enabled());
	Print(out, "SSE3", CCpuInfo::SSE3_Enabled());
	Print(out, "SSE4.1", CCpuInfo::SSE41_Enabled());
	Print(out, "SSE4.2", CCpuInfo::SSE42_Enabled());
	Print(out, "AVX", CCpuInfo::AVX_Enabled());
	Print(out, "AVX2", CCpuInfo::AVX2_Enabled());
}