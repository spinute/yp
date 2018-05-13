VPATH = src

CUDA_PATH = /usr/local/cuda
CUDA_INC += -I$(CUDA_PATH)/include
NVCC_FLAGS = -Xcompiler -O2 -Xptxas -O2 --compiler-options -Wall -arch=sm_30  --resource-usage
CFLAGS = -O2 -std=c99 -Wall -Wextra

BENCH4=korf100
#BENCH5=yama24_50_hard_new
BENCH5=try_difficult

all: bpida4 bpida4_global bpida5 bpida5_global bpida5_pdb bpida5_pdb_global c4 c5 c5_pdb bpida4_fa bpida4_global_fa bpida5_fa bpida5_global_fa bpida5_pdb_fa bpida5_pdb_global_fa c4_fa c5_fa c5_pdb_fa
all_bench: bench_bpida4 bench_bpida4_global bench_bpida5 bench_bpida5_global bench_bpida5_pdb bench_c4 bench_c5 bench_c5_pdb bench_bpida4_fa bench_bpida4_global_fa bench_bpida5_fa bench_bpida5_global_fa bench_bpida5_pdb_fa bench_c4_fa bench_c5_fa bench_c5_pdb_fa

%: %.cu
	nvcc -o $@ $(NVCC_FLAGS) -DFIND_ALL=false $<
	nvcc -o $@_fa $(NVCC_FLAGS) -DFIND_ALL=true $<

%: %.cu
	nvcc -o $@ $(NVCC_FLAGS) -DFIND_ALL=false $<
	nvcc -o $@_fa $(NVCC_FLAGS) -DFIND_ALL=true $<

c4: ida.c
	gcc -o $@ $(CFLAGS) -DSTATE_WIDTH=4  -DFIND_ALL=false $<
c5: ida.c
	gcc -o $@ $(CFLAGS) -DSTATE_WIDTH=5  -DFIND_ALL=false $<
c5_pdb: ida_pdb.c
	gcc -o $@ $(CFLAGS)  -DFIND_ALL=false $<

c4_fa: ida.c
	gcc -o $@ $(CFLAGS) -DSTATE_WIDTH=4  -DFIND_ALL=true $<
c5_fa: ida.c
	gcc -o $@ $(CFLAGS) -DSTATE_WIDTH=5  -DFIND_ALL=true $<
c5_pdb_fa: ida_pdb.c
	gcc -o $@ $(CFLAGS)  -DFIND_ALL=true $<

bench_bpida4: bpida4
	bash script/run_bench.sh $< $(BENCH4)
bench_bpida4_global: bpida4_global
	bash script/run_bench.sh $< $(BENCH4)
bench_bpida5: bpida5
	bash script/run_bench.sh $< $(BENCH5)
bench_bpida5_global: bpida5_global
	bash script/run_bench.sh $< $(BENCH5)
bench_bpida5_pdb: bpida5_pdb
	bash script/run_bench.sh $< $(BENCH5)

bench_c4: c4
	bash script/run_bench.sh $< $(BENCH4)
bench_c5: c5
	bash script/run_bench.sh $< $(BENCH5)
bench_c5_pdb: c5_pdb
	bash script/run_bench.sh $< $(BENCH5)

bench_bpida4_fa: bpida4_fa
	bash script/run_bench.sh $< $(BENCH4)
bench_bpida4_global_fa: bpida4_global_fa
	bash script/run_bench.sh $< $(BENCH4)
bench_bpida5_fa: bpida5_fa
	bash script/run_bench.sh $< $(BENCH5)
bench_bpida5_global_fa: bpida5_global_fa
	bash script/run_bench.sh $< $(BENCH5)
bench_bpida5_pdb_fa: bpida5_pdb_fa
	bash script/run_bench.sh $< $(BENCH5)

bench_c4_fa: c4_fa
	bash script/run_bench.sh $< $(BENCH4)
bench_c5_fa: c5_fa
	bash script/run_bench.sh $< $(BENCH5)
bench_c5_pdb_fa: c5_pdb_fa
	bash script/run_bench.sh $< $(BENCH5)



