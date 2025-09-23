make: 
	gcc -g -Wall main.c changeMachine.c -o changeMachine

memtest:
	gcc -g -Wall main.c changeMachine.c -o changeMachine
	valgrind ./changeMachine

clean:
	rm -f *.o changeMachine
	rm -f *.txt