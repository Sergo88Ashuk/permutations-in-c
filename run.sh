echo "compile"
clang main.c symbol_counter.c 

echo "generate big n input"
python3 test_gen.py 1000

echo "run with test0 input"
./a.out $(cat test0) > test0_res

echo "run with big_n_input"
./a.out $(cat big_n_input) > big_n_input_res

echo "check test0 and big_n_input"
python3 check_res.py

echo "generate bigger n input"
python3 test_gen.py 10000

echo "time it: "
time ./a.out $(cat big_n_input) > big_n_input_res

rm a.out big_n_input big_n_input_res test0_res
