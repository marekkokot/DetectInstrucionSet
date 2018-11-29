CC = g++
CFLAGS = -O3 -std=c++14

CPP_FILES = DetectInstrucionSet/cpu_info.cpp DetectInstrucionSet/detect_cpu.cpp

detect_cpu: 
	$(CC) $(CFLAGS) -o $@ $(CPP_FILES)
clean:
	rm detect_cpu