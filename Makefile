default: build/loldodge.o build/sprite.o build/player.o build/enemy.o build/bullet.o build/fireball.o
	gcc -g $^ -o build/game -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

build/%.o: src/%.c src/%.h
	gcc -g -Isrc -c $< -o $@

build/loldodge.o: src/loldodge.c
	gcc -g -Isrc -c $< -o $@

clean:
	rm -rf build/*
