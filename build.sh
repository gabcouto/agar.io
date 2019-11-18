# Este script automatiza a compilação de programas que usem raylib.h.
# Para utilizar, basta mudar os diretórios para os seus correspondentes,
# porque provavelmente não será /home/gabrielcouto/.../
set -e
cc -g -std=c99 -c -I /home/gabrielcouto/raylib/src agario.c -o ./obj/agario.o
cc -o agario  obj/agario.o -s -Wall -std=c99 -I/home/gabrielcouto/raylib/src -L/home/gabrielcouto/raylib/release/libs/linux -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
./agario

