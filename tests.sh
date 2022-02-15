#/bin/sh

dprint()
{
    echo "$(tput setaf 6)$1$(tput setaf 7)"
}

test()
{
    dprint "$1"
    valgrind $1
    echo "\n"
}

dprint "Building new executable..."

make clean
make

dprint "\nRunning tests...\n"

test "./node.bin"
test "./node.bin 0"
test "./node.bin 10"
test "./node.bin 5"
test "./node.bin 5 a"
test "./node.bin 5a"
test "./node.bin 5a a"
test "./node.bin 11"
