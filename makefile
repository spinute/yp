VPATH = src

CUDA_PATH = /usr/local/cuda
CUDA_INC += -I$(CUDA_PATH)/include
NVCC_FLAGS = -Xcompiler -O2 -Xptxas -O2 --compiler-options -Wall -arch=sm_30  --resource-usage
CFLAGS = -O2 -std=c99 -Wall -Wextra

BENCH4=korf100
BENCH5=yama24_50_hard_new
# BENCH5KORF=korf50_24puzzle
BENCH5KORF10=korf-24-easy10


all: bpida4 bpida4_global bpida5 bpida5_global bpida5_pdb bpida5_pdb_global c4 c5 c5_pdb bpida4_fa bpida4_global_fa bpida5_fa bpida5_global_fa bpida5_pdb_fa bpida5_pdb_global_fa c4_fa c5_fa c5_pdb_fa bpida5_global_sh_fa_4312 bpida5_global_sh_fa_8720 bpida5_global_sh_fa_13128 bpida5_global_sh_fa_17536 bpida5_global_sh_fa_35168
all_bench: bench_bpida4 bench_bpida4_global bench_bpida5 bench_bpida5_global bench_bpida5_pdb bench_bpida5_pdb_global bench_c4 bench_c5 bench_c5_pdb bench_bpida4_fa bench_bpida4_global_fa bench_bpida5_fa bench_bpida5_global_fa bench_bpida5_pdb_fa bench_bpida5_pdb_global_fa bench_c4_fa bench_c5_fa bench_c5_pdb_fa bench_bpida5_pdb_korf10 bench_bpida5_pdb_global_korf10 bench_c5_pdb_korf10 bench_bpida5_pdb_fa_korf10 bench_bpida5_pdb_global_fa_korf10 bench_c5_pdb_fa_korf10 bench_bpida5_global_sh_fa_4312 bench_bpida5_global_sh_fa_8720 bench_bpida5_global_sh_fa_13128 bench_bpida5_global_sh_fa_17536 bench_bpida5_global_sh_fa_35168

# without korf100
all_bench_wo_hard: bench_bpida4 bench_bpida4_global bench_bpida5 bench_bpida5_global bench_bpida5_pdb bench_bpida5_pdb_global bench_c4 bench_c5 bench_c5_pdb bench_bpida4_fa bench_bpida4_global_fa bench_bpida5_fa bench_bpida5_global_fa bench_bpida5_pdb_fa bench_bpida5_pdb_global_fa bench_c4_fa bench_c5_fa bench_c5_pdb_fa

# with korf10
all_bench_korf10: bench_bpida5_pdb_korf10 bench_bpida5_pdb_global_korf10 bench_c5_pdb_korf10 bench_bpida5_pdb_fa_korf10 bench_bpida5_pdb_global_fa_korf10 bench_c5_pdb_fa_korf10

all_bench_shard: bench_bpida5_global_sh_fa_4312 bench_bpida5_global_sh_fa_8720 bench_bpida5_global_sh_fa_13128 bench_bpida5_global_sh_fa_17536 bench_bpida5_global_sh_fa_35168

clean:
	rm bpida4 bpida4_global bpida5 bpida5_global bpida5_pdb bpida5_pdb_global c4 c5 c5_pdb bpida4_fa bpida4_global_fa bpida5_fa bpida5_global_fa bpida5_pdb_fa bpida5_pdb_global_fa c4_fa c5_fa c5_pdb_fa bpida5_global_sh_fa_4312 bpida5_global_sh_fa_8720 bpida5_global_sh_fa_13128 bpida5_global_sh_fa_17536 bpida5_global_sh_fa_35168

%: %.cu
	nvcc -o $@ $(NVCC_FLAGS) -DFIND_ALL=false $<
	nvcc -o $@_fa $(NVCC_FLAGS) -DFIND_ALL=true $<

%: %.cu
	nvcc -o $@ $(NVCC_FLAGS) -DFIND_ALL=false $<
	nvcc -o $@_fa $(NVCC_FLAGS) -DFIND_ALL=true $<

bpida5_global_sh_fa_4312: bpida5_global.cu
	nvcc -o $@ $(NVCC_FLAGS) -DFIND_ALL=true -DFAKE_SHARED=4312 $<

bpida5_global_sh_fa_8720: bpida5_global.cu
	nvcc -o $@ $(NVCC_FLAGS) -DFIND_ALL=true -DFAKE_SHARED=8720 $<

bpida5_global_sh_fa_13128: bpida5_global.cu
	nvcc -o $@ $(NVCC_FLAGS) -DFIND_ALL=true -DFAKE_SHARED=13128 $<

bpida5_global_sh_fa_17536: bpida5_global.cu
	nvcc -o $@ $(NVCC_FLAGS) -DFIND_ALL=true -DFAKE_SHARED=17536 $<

bpida5_global_sh_fa_35168: bpida5_global.cu
	nvcc -o $@ $(NVCC_FLAGS) -DFIND_ALL=true -DFAKE_SHARED=35168 $<




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
bench_bpida5_pdb_global: bpida5_pdb_global
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
bench_bpida5_pdb_global_fa: bpida5_pdb_global_fa
	bash script/run_bench.sh $< $(BENCH5)

bench_c4_fa: c4_fa
	bash script/run_bench.sh $< $(BENCH4)
bench_c5_fa: c5_fa
	bash script/run_bench.sh $< $(BENCH5)
bench_c5_pdb_fa: c5_pdb_fa
	bash script/run_bench.sh $< $(BENCH5)


# bench5korf
bench_bpida5_pdb_korf10: bpida5_pdb
	bash script/run_bench.sh $< $(BENCH5KORF10)
bench_bpida5_pdb_global_korf10: bpida5_pdb_global
	bash script/run_bench.sh $< $(BENCH5KORF10)
bench_c5_pdb_korf10: c5_pdb
	bash script/run_bench.sh $< $(BENCH5KORF10)

bench_bpida5_pdb_fa_korf10: bpida5_pdb_fa
	bash script/run_bench.sh $< $(BENCH5KORF10)
bench_bpida5_pdb_global_fa_korf10: bpida5_pdb_global_fa
	bash script/run_bench.sh $< $(BENCH5KORF10)
bench_c5_pdb_fa_korf10: c5_pdb_fa
	bash script/run_bench.sh $< $(BENCH5KORF10)

# bench_shared
bench_bpida5_global_sh_fa_4312: bpida5_global_sh_fa_4312
	bash script/run_bench.sh $< $(BENCH5)
bench_bpida5_global_sh_fa_8720: bpida5_global_sh_fa_8720
	bash script/run_bench.sh $< $(BENCH5)
bench_bpida5_global_sh_fa_13128: bpida5_global_sh_fa_13128
	bash script/run_bench.sh $< $(BENCH5)
bench_bpida5_global_sh_fa_17536: bpida5_global_sh_fa_17536
	bash script/run_bench.sh $< $(BENCH5)
bench_bpida5_global_sh_fa_35168: bpida5_global_sh_fa_35168
	bash script/run_bench.sh $< $(BENCH5)



