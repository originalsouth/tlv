CC=g++

tlv: tlv.cc tlv.h
	$(CC) -Wall -Wextra -std=c++11 -O3 -flto -march=native -o tlv tlv.cc

clean:
	rm -f tlv
