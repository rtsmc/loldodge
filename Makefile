default: main.o player.o enemy.o bullet.o fireball.o
	gcc main.o player.o enemy.o bullet.o fireball.o -o game -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

main.o: main.c
	gcc -I. -c main.c

player.o: player.c player.h sprite.h
	gcc -I. -c player.c

enemy.o: enemy.c enemy.h sprite.h
	gcc -I. -c enemy.c

bullet.o: bullet.c bullet.h sprite.h
	gcc -I. -c bullet.c

fireball.o: fireball.c fireball.h sprite.h
	gcc -I. -c fireball.c

clean:
	rm -rf *.o game
