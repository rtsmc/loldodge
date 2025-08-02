default: build/main.o build/player.o build/enemy.o build/bullet.o build/fireball.o
	gcc $^ -o build/game -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

build/%.o: src/%.c include/%.h
	gcc -Iinclude -c $< -o $@

build/main.o: src/main.c
	gcc -Iinclude -c $< -o $@
#
# main.o: src/main.c
# 	gcc -Iinclude -c src/main.c
#
# player.o: src/player.c include/player.h include/sprite.h
# 	gcc -Iinclude -c src/player.c
#
# enemy.o: src/enemy.c include/enemy.h include/sprite.h
# 	gcc -Iinclude -c src/enemy.c
#
# bullet.o: src/bullet.c include/bullet.h include/sprite.h
# 	gcc -Iinclude -c src/bullet.c
#
# fireball.o: src/fireball.c include/fireball.h include/sprite.h
# 	gcc -Iinclude -c src/fireball.c

clean:
	rm -rf build/*
