make:
	gcc -shared -I./include/ -fPIC -o ./lib/libChangeMachine.so ./src/changeMachine.c
	g++ main.cpp -g -Wall -I./include/ -L./lib/ -lChangeMachine -Wl,-rpath='$$ORIGIN/lib' -o changeMachine

so:
	gcc -shared -I./include/ -fPIC -o ./lib/libChangeMachine.so /src/changeMachine.c

cpp:
	g++ main.cpp -g -Wall -I./include/ -L./lib/ -lChangeMachine -Wl,-rpath='$$ORIGIN/lib' -o changeMachine

# make: 
# 	gcc -g -Wall main.c changeMachine.c -o changeMachine

# memtest:
# 	gcc -g -Wall main.c changeMachine.c -o changeMachine
# 	valgrind ./changeMachine

clean:
	rm -f *.o changeMachine
	rm -f *.txt
	rm -f ./lib/*