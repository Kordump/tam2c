CC=g++
LDFLAG=
CCFLAG=-Wall -Wextra -pedantic
CCEXTRA=-O2 -march=native

CPP14_leguacy=c++1y
CPP14=c++14
CPP17=c++1z

# Use at least C++14
STD=$(CPP17)
ALL=tam2c tam2c_debug

all: tam2c

everything: $(ALL)

tam2c:
	$(CC) -std=$(STD) $(CCFLAG) $(CCEXTRA) $(LDFLAG) tam2c.cpp -o tam2c

tam2c_debug:
	$(CC) -std=$(STD) $(CCFLAG) -g $(LDFLAG) tam2c.cpp -o tam2c_debug

clean:
	find -iname "*.o" -exec rm -v {} \;

mr_proper: clean
	rm -vf $(ALL)
