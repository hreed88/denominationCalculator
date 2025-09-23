make:
	gcc -shared -fPIC -o ./lib/libChangeMachine.so changeMachine.c
	g++ main.cpp -g -Wall -L./lib/ -lChangeMachine -Wl,-rpath='$$ORIGIN/lib' -o changeMachine

so:
	gcc -shared -fPIC -o ./lib/libChangeMachine.so changeMachine.c

cpp:
	g++ main.cpp -g -Wall -L./lib/ -lChangeMachine -Wl,-rpath='$$ORIGIN/lib' -o changeMachine

# make: 
# 	gcc -g -Wall main.c changeMachine.c -o changeMachine

# memtest:
# 	gcc -g -Wall main.c changeMachine.c -o changeMachine
# 	valgrind ./changeMachine

clean:
	rm -f *.o changeMachine
	rm -f *.txt
	rm -f ./lib/*