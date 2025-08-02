default: build/main.o build/sprite.o build/player.o build/enemy.o build/bullet.o build/fireball.o
	gcc $^ -o build/game -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

build/%.o: src/%.c include/%.h
	gcc -Iinclude -c $< -o $@

build/main.o: src/main.c
	gcc -Iinclude -c $< -o $@

clean:
	rm -rf build/*
