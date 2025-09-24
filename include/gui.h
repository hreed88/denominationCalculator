#ifndef GUI_H
#define GUI_H

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl2.h"
#include <GLFW/glfw3.h>
#include "changeMachine.h"
#include <stdio.h>
#include <string>

static void glfw_error_callback(int error, const char* description){
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
};
int checkUInputCallback(ImGuiInputTextCallbackData* data);
int startGUIApplication();


#endif