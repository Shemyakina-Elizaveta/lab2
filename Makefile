build/base32_file.o: src/base_file/base32_file/base32_file.cpp src/base_file/base32_file/base32_file.h
	g++ -g -c -o build/base32_file.o src/base_file/base32_file/base32_file.cpp

build/i_file.o: src/base_file/i_file/i_file.cpp src/base_file/i_file/i_file.h
	g++ -g -c -o build/i_file.o src/base_file/i_file/i_file.cpp

build/rle_file.o: src/base_file/rle_file/rle_file.cpp src/base_file/rle_file/rle_file.h
	g++ -g -c -o build/rle_file.o src/base_file/rle_file/rle_file.cpp


build/base_file.o: src/base_file/base_file.cpp src/base_file/base_file.h
	g++ -g -c -o build/base_file.o src/base_file/base_file.cpp


build/my_string.o: src/my_string/my_string.cpp src/my_string/my_string.h
	g++ -g -c -o build/my_string.o src/my_string/my_string.cpp



build/debug.out: build/base32_file.o build/rle_file.o build/base_file.o build/my_string.o build/i_file.o src/lab2.cpp
	g++ -g -o build/debug.out build/base32_file.o build/rle_file.o build/base_file.o build/i_file.o build/my_string.o src/lab2.cpp


build/leaks.out: build/base32_file.o build/rle_file.o build/base_file.o build/my_string.o build/i_file.o src/lab2.cpp
	g++ -g -o build/leaks.out build/base32_file.o build/rle_file.o build/base_file.o build/i_file.o build/my_string.o src/lab2.cpp -fsanitize=address



leaks: build/leaks.out
	./build/leaks.out

debug: build/debug.out
	./build/debug.out 