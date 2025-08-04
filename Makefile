default: build/loldodge.o build/sprite.o build/player.o build/enemy.o build/bullet.o build/fireball.o
	gcc $^ -o build/game -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

build/%.o: src/%.c src/%.h
	gcc -Isrc -c $< -o $@

build/loldodge.o: src/loldodge.c
	gcc -Isrc -c $< -o $@

clean:
	rm -rf build/*
