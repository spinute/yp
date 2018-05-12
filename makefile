VPATH = src

CUDA_PATH = /usr/local/cuda
CUDA_INC += -I$(CUDA_PATH)/include
NVCC_FLAGS = -Xcompiler -O2 -Xptxas -O2 --compiler-options -Wall -arch=sm_30  --resource-usage
CFLAGS = -O2 -std=c99 -Wall -Wextra

all: bpida4 bpida5 c4 c5 c5_pdb

bpida4: bpida4.cu
	nvcc -o $@ $(NVCC_FLAGS) $<
bpida4_global: bpida4_global.cu
	nvcc -o $@ $(NVCC_FLAGS) $<
bpida5: bpida5.cu
	nvcc -o $@ $(NVCC_FLAGS) $<
bpida5_pdb: bpida5_pdb.cu
	nvcc -o $@ $(NVCC_FLAGS) $<



c4: ida.c
	gcc -o $@ $(CFLAGS) -DSTATE_WIDTH=4 $<
c5: ida.c
	gcc -o $@ $(CFLAGS) -DSTATE_WIDTH=5 $<
c5_pdb: ida_pdb.c
	gcc -o $@ $(CFLAGS) $<

bench_bpida4: bpida4
	for fname in ./benchmarks/korf100/*; do time ./bpida4 $${fname} ; done
bench_bpida4_global: bpida4_global
	for fname in ./benchmarks/korf100/*; do time ./bpida4_global $${fname} ; done
bench_bpida5: bpida5
	for fname in ./benchmarks/yama24_50_hard_new/*; do time ./bpida5 $${fname} ; done
bench_bpida5_pdb: bpida5_pdb
	for fname in ./benchmarks/yama24_50_hard_new/*; do time ./bpida5_pdb $${fname} ; done

bench_c4: c4
	for fname in ./benchmarks/korf100/*; do time ./c4 $${fname} ; done
bench_c5: c5
	for fname in ./benchmarks/yama24_50_hard_new/*; do time ./c5 $${fname} ; done
bench_c5_pdb: c5
	for fname in ./benchmarks/yama24_50_hard_new/*; do time ./c5_pdb $${fname} ; done
