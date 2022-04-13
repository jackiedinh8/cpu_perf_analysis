CC=clang
CPP=clang++
FLAGS="-O0"

cat /proc/cpuinfo | grep "model name" | head -n 1
$CC --version 2>&1 | egrep "version"

echo "-----Data Cache Analysis-----"
$CC -o matrix.normal matrix.c
$CC -DCACHE_FRIENDLY -o matrix.cache matrix.c
sudo perf stat -e cycles,instructions,L1-dcache-load-misses,L1-dcache-loads -- taskset -c 0 ./matrix.normal
sudo perf stat -e cycles,instructions,L1-dcache-load-misses,L1-dcache-loads -- taskset -c 0 ./matrix.cache

echo "-----Branch Prediction Analysis-----"
$CC -O0 -o prediction.unsorted prediction.c
$CC -O0 -DENABLE_SORT -o prediction.sorted prediction.c
sudo perf stat -e cycles,instructions,branches,branch-misses -- taskset -c 0 ./prediction.unsorted
sudo perf stat -e cycles,instructions,branches,branch-misses -- taskset -c 0 ./prediction.sorted

