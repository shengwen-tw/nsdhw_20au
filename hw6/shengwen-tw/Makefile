EXECUTABLE=hw4
SHARED_OBJ=_matrix.so
CC=g++

#on my pc
#MKL_PATH=/opt/intel/mkl
#MKL_LDFLAGS=-L$(MKL_PATH)/lib/intel64 -lmkl_rt

#on ec2
MKL_PATH=$(HOME)/opt/conda
MKL_LDFLAGS=-L$(MKL_PATH)/lib -lmkl_rt

CFLAGS=-O3 -Wall -g

LDFLAGS=-lm

CFLAGS+=-I$(MKL_PATH)/include

PYBIND_CFLAGS=-shared -std=c++17 -fPIC \
	`python3 -m pybind11 --includes`
PYBIND_LDFLAGS=`python3-config --ldflags`

SRC=matrix.cpp

PYBIND_SRC=share.cpp

OBJS=$(SRC:.cpp=.o)
DEPEND=$(SRC:.cpp=.d)

all: $(SHARED_OBJ)

$(EXECUTABLE): $(OBJS)
	@echo "LD" $@
	@$(CC) $(CFLAGS) $(OBJS) $(MKL_LDFLAGS) $(LDFLAGS) -o $@

$(SHARED_OBJ): $(SRC) $(PYBIND_SRC)
	@echo "LD" $@
	@$(CC) $(CFLAGS) $(PYBIND_CFLAGS) $(SRC) $(PYBIND_SRC) $(MKL_LDFLAGS) $(LDFLAGS) $(PYBIND_LDFLAGS) -o $@

-include $(DEPEND)

%.o: %.cpp
	@echo "CC" $@
	@$(CC) $(CFLAGS) -MMD -MP -c $< $(LDFLAGS) -o $@

test: $(EXECUTABLE) $(SHARED_OBJ)
	#@echo 'start generating `performance.txt`'
	#@./hw3 > performance.txt
	#@echo ''
	#@echo 'finish generating `performance.txt`'

clean:
	rm -rf $(EXECUTABLE)
	rm -rf $(SHARED_OBJ)
	rm -rf $(OBJS)

.PHONY: all clean test
