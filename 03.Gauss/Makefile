CXX_EXTRA_FLAGS=-std=c++17 -I ../external/lazycsv/include -I ../external/eigen -I /usr/include/eigen3 $(shell pkg-config --cflags openblas 2>/dev/null)
LD_EXTRA_OPT=$(shell pkg-config --libs openblas 2>/dev/null)

include ../Makefile.inc

release : gauss

gauss : util.r.o Gauss_main.r.o Gauss_solve.r.o
	$(LD) -fopenmp -o $@ $^ $(LD_EXTRA_OPT)

debug : util.d.o Gauss_main.d.o Gauss_solve.d.o
	$(LD) -fopenmp -o $@ $^ $(LD_EXTRA_OPT)

utest : Gauss_test.d.o util.d.o Gauss_solve.d.o
	$(LD) -fopenmp -o $@ $^ $(GTEST_LIBS) $(LD_EXTRA_OPT)

run_utest : utest
	./$^

run_itest : release
	./integration_test.sh

all: depends run_utest run_itest

include Makefile.hdrdep
