valgrind ./push_swap 2>&1 | grep lost
    valgrind ./push_swap "1 2" 2>&1 | grep lost
    valgrind ./push_swap "2 2" 2>&1 | grep lost
    valgrind ./push_swap "a 2" 2>&1 | grep lost
    valgrind ./push_swap "2147483649" 2>&1 | grep lost
    echo "sa" | valgrind ./checker 2>&1 | grep lost
    echo "sa" | valgrind ./checker 1 2 2>&1 | grep lost
    echo "sa" | valgrind ./checker "2 2" 2>&1 | grep lost
    echo "sa" | valgrind ./checker "a 2" 2>&1 | grep lost
    echo "sa" | valgrind ./checker "2147483649" 2>&1 | grep lost
    echo "sa " | valgrind ./checker "1 2" 2>&1 | grep lost
    echo "  sa" | valgrind ./checker "1 2" 2>&1 | grep lost
    echo "sa" | valgrind ./checker -v "1 2" 2>&1 | grep lost
    echo "sa" | valgrind ./checker -vact "1 2" 2>&1 | grep lost
    echo "sa" | valgrind ./checker -g "1 2" 2>&1 | grep lost
    ARG=`ruby -e "puts (1..30).to_a.shuffle.join(' ')"`; ./push_swap $ARG | valgrind ./checker $ARG 2>&1 | grep lost
    ARG=`ruby -e "puts (1..30).to_a.shuffle.join(' ')"`; valgrind ./push_swap $ARG 2>&1 | grep lost
    echo "\0" | valgrind ./checker -g "1 2" 2>&1 | grep lost
    ./checker a 2>&1 | cat -e
    ./checker 1 1 2>&1 | cat -e
    ./checker 2147483649 2>&1 | cat -e
    ./checker 2>&1 | cat -e
    echo "swap" | ./checker "1 2" 2>&1 | cat -e
    echo "sa  " | ./checker "1 2" 2>&1 | cat -e
    echo "  sa" | ./checker "1 2" 2>&1 | cat -e
    ./push_swap a 2>&1 | cat -e
    ./push_swap 1 1 2>&1 | cat -e
    ./push_swap -2147483649 2>&1 | cat -e
    ./push_swap 2>&1 | cat -e
    echo "sa\npb\nrrr" | ./checker 0 9 1 8 2 7 3 6 4 5
    echo "sa\npb\nrrr" | ./checker "3 2 5 1"
    echo "\0" | ./checker 0 1 2
    echo "pb\nra\npb\nra\nsa\nra\npa\npa" | ./checker 0 9 1 8 2
    echo "sa" | ./checker 1 0 2
    ./push_swap 42
    ./push_swap 0 1 2 3
    ./push_swap 0 1 2 3 4 5 6 7 8 9
    ARG="2 1 0"; ./push_swap $ARG | ./checker $ARG
    ARG="1 5 2 4 3"; ./push_swap $ARG | ./checker $ARG
    ARG=`ruby -e "puts (1..5).to_a.shuffle.join(' ')"`; ./push_swap $ARG | ./checker $ARG
    ARG=`ruby -e "puts (1..5).to_a.shuffle.join(' ')"`; ./push_swap $ARG | ./checker $ARG
    ARG=`ruby -e "puts (1..5).to_a.shuffle.join(' ')"`; ./push_swap $ARG | ./checker $ARG
    ARG=`ruby -e "puts (1..5).to_a.shuffle.join(' ')"`; ./push_swap $ARG | ./checker $ARG
    ARG=`ruby -e "puts (1..5).to_a.shuffle.join(' ')"`; ./push_swap $ARG | ./checker $ARG
    ARG=`ruby -e "puts (1..100).to_a.shuffle.join(' ')"`; ./push_swap $ARG | ./checker $ARG
    ARG=`ruby -e "puts (1..100).to_a.shuffle.join(' ')"`; ./push_swap $ARG | ./checker $ARG
    ARG=`ruby -e "puts (1..100).to_a.shuffle.join(' ')"`; ./push_swap $ARG | ./checker $ARG
    ARG=`ruby -e "puts (1..100).to_a.shuffle.join(' ')"`; ./push_swap $ARG | ./checker $ARG
    ARG=`ruby -e "puts (1..100).to_a.shuffle.join(' ')"`; ./push_swap $ARG | ./checker $ARG
    ARG=`ruby -e "puts (1..500).to_a.shuffle.join(' ')"`; ./push_swap $ARG | ./checker $ARG
    ARG=`ruby -e "puts (1..500).to_a.shuffle.join(' ')"`; ./push_swap $ARG | ./checker $ARG
    ARG=`ruby -e "puts (1..500).to_a.shuffle.join(' ')"`; ./push_swap $ARG | ./checker $ARG
    ARG=`ruby -e "puts (1..500).to_a.shuffle.join(' ')"`; ./push_swap $ARG | ./checker $ARG
    ARG=`ruby -e "puts (1..500).to_a.shuffle.join(' ')"`; ./push_swap $ARG | ./checker $ARG


