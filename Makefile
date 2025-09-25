IMGUI_DIR = ./thirdParty
BACKEND = ./thirdParty/backends
IMGUI_SRC = $(IMGUI_DIR)/imgui.cpp \
            $(IMGUI_DIR)/imgui_draw.cpp \
            $(IMGUI_DIR)/imgui_tables.cpp \
            $(IMGUI_DIR)/imgui_widgets.cpp \
            $(BACKEND)/imgui_impl_glfw.cpp \
            $(BACKEND)/imgui_impl_opengl2.cpp

make:
	gcc -shared -I./include/ -fPIC -o ./lib/libChangeMachine.so ./src/changeMachine.c
	g++ main.cpp ./src/gui.cpp $(IMGUI_SRC) -g -Wall -I./include/ -I$(IMGUI_DIR) -I$(BACKEND) -lGL -lglfw -L./lib/ -lChangeMachine -Wl,-rpath='$$ORIGIN/lib' -o changeMachine

so:
	gcc -shared -I./include/ -fPIC -o ./lib/libChangeMachine.so /src/changeMachine.c

cpp:
	g++ main.cpp -g -Wall -I./include/ -L./lib/ -lChangeMachine -Wl,-rpath='$$ORIGIN/lib' -o changeMachine

memtestNoGUI:
	make
	valgrind ./changeMachine

clean:
	rm -f *.o changeMachine
	rm -f *.txt
	rm -f ./lib/*
	rm -f *.out