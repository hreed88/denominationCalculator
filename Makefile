
make:
	gcc -shared -I./include/ -fPIC -o ./lib/libChangeMachine.so ./src/changeMachine.c
	g++ main.cpp  -g -Wall -I./include/ -L./lib/ -lChangeMachine -Wl,-rpath='$$ORIGIN/lib' -o changeMachine

memtest:
	make
	valgrind ./changeMachine

clean:
	rm -f *.o changeMachine
	rm -f *.txt
	rm -f ./lib/*
	rm -f *.out