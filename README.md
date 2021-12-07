How to compile:

mkdir -p build/      
gcc -O3 -Wall -Wextra -c main.c -o build/main.c.o
gcc ./build/main.c.o -o build/program.run

How to run:

./program.run < FILE_NAME