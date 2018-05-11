VPATH = src

CUDA_PATH = /usr/local/cuda
CUDA_INC += -I$(CUDA_PATH)/include
NVCC_FLAGS = -Xcompiler -O2 -Xptxas -O2 --compiler-options -Wall -arch=sm_30  --resource-usage
CFLAGS = -O2 -std=c99 -Wall -Wextra

all: pbida c4 c5 c5_pdb

pbida: pbida.cu
	nvcc -o $@ $(NVCC_FLAGS) $<

c4: ida.c
	gcc -o $@ $(CFLAGS) -DSTATE_WIDTH=4 $<
c5: ida.c
	gcc -o $@ $(CFLAGS) -DSTATE_WIDTH=5 $<
c5_pdb: ida_pdb.c
	gcc -o $@ $(CFLAGS) $<

bench_c4: c4
	for fname in ./sliding-puzzle/benchmarks/korf100/*; do time ./c4 $${fname} ; done
bench_c5: c5
	for fname in ./sliding-puzzle/benchmarks/yama24_50_hard_new/*; do time ./c5 $${fname} ; done
bench_c5_pdb: c5
	for fname in ./sliding-puzzle/benchmarks/yama24_50_hard_new/*; do time ./c5_pdb $${fname} ; done
