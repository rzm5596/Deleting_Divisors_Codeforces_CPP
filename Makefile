CFLAGS = -std=c++11
LIBS = -lstdc++
SOURCES = deleting_divisors.cpp
OUT = deleting_divisors

default:
	gcc $(CFLAGS) $(SOURCES) $(LIBS) -o $(OUT)
debug:
	gcc -g $(CFLAGS) $(SOURCES) $(LIBS) -o $(OUT)
all:
	gcc $(CFLAGS) $(SOURCES) $(LIBS) -o $(OUT)
test:
	./test.sh
clean:
	rm $(OUT)