#include <stdio.h>
#include <string>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl2.h"
#include <GLFW/glfw3.h>
#include "changeMachine.h"

static void glfw_error_callback(int error, const char* description){
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}


//globals to help with handling of UI
bool dotInserted = false;
int numOfDecimal = 0;
std::string prevBuff = "";
int cursorLocation = 0;
int length = 0;
const char *stringArr[] = {"%d $50s", "%d $20s", "%d $10s", "%d $5s", 
                            "%d $2s", "%d $1s", "%d Quaters", "%d Dimes", "%d Nickels", "%d Pennies"};

//Name:checkUInputCallback  
//Description: Handles input from InputTextWithHint, mainly concerned with maintaining proper input from user
//input: data is a callback data type, which contains things like Eventchar, cursorpositions, etc. 
//Output: returns 0 or 1, which tels the text box wether or not to add the character to the buffer 
int checkUInputCallback(ImGuiInputTextCallbackData* data){
    
    if(data->EventFlag == ImGuiInputTextFlags_CallbackAlways){
        cursorLocation = data->CursorPos;
        length = data->BufTextLen;
    }
    //handle deletions
    if(data->EventFlag == ImGuiInputTextFlags_CallbackEdit){
        if((int)prevBuff.size() > data->BufTextLen){
            //check for entire deletion or deletion of decimal
            if(prevBuff[cursorLocation-1] == '.' || data->BufTextLen == 0){
                //reset number of decimals and remove dot inserted 
                numOfDecimal = 0;
                dotInserted = false;
            }
            //this handles deletion after the dot
            if(dotInserted && cursorLocation >= data->BufTextLen - 2){
                printf("\nDeleteing decimal");
                numOfDecimal--;
            }
        }
        //set prevBuff to the current buffer to handle next event
        prevBuff = data->Buf;
    }

    //handle input
    if(data->EventFlag == ImGuiInputTextFlags_CallbackCharFilter){

        //check if length is bigger then our buffer
        //this tells the input text to not accept anything more than our buffer
        if(length > 64)
            return 1;

        //get the character entered
        char c = data->EventChar;

        //allow for inserting as many imes <= 64. to the left of the decimal
        if(cursorLocation <= length - 3 && (c >= '0' && c <= '9')){
            printf("\nInserting to the left of decimal\n");
            return 0;
        }
        
        //Allow numbers to be inserted twice after the decimal, and allow decimal to be inserted
        if(((c >= '0' && c <= '9') && numOfDecimal < 2) || ((c == '.' && !dotInserted) && cursorLocation >= length - 2)){
                if(c == '.'){
                    dotInserted = true;
                    numOfDecimal = length - cursorLocation;
                }
                if(c != '.' && dotInserted)
                    numOfDecimal++;

                return 0;
            }
            //return 1 if any of these cases dont hole (i.e. input is invalid)
            return 1;
    }
//return 1 by default 
return 1;
}



//Name:startGUIApplication
//Description: sets up glfw and ImGUI, then begins the main UI loop. That handles user input
//             which is then converted by the changeMachine. Then displayed to the user 
//input: None 
//Output: Return code to propigate back to main (0 ok, N something happened) 
int startGUIApplication(){
    char buffer[64] = "";
    
    glfwSetErrorCallback(glfw_error_callback);
    
    if(!glfwInit()){
        return 1;
    }

    //create window
    GLFWwindow* window = glfwCreateWindow(300, 400, "Denomination Calculator", nullptr, nullptr);
    if(window == nullptr){
        return 1;
    }
    glfwMakeContextCurrent(window);
    //Enable Vsync
    glfwSwapInterval(1); 

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL2_Init();
    
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    //locals to use in loop
    denominationResult thisResult;
    bool drawCircle = true;
    //main loop
    
    while(!glfwWindowShouldClose(window)){

        //poll keyboard, mouse, etc
        glfwPollEvents();

        if (glfwGetWindowAttrib(window, GLFW_ICONIFIED) != 0)
        {
            ImGui_ImplGlfw_Sleep(10);
            continue;
        }

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL2_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        //make window full screen remove title bar
        ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->Pos);
        ImGui::SetNextWindowSize(viewport->Size);
        ImGui::SetNextWindowViewport(viewport->ID);


        //do work
        ImGui::Begin("My Window", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar);
       
        ImGui::InputTextWithHint("USD Input##input", "7206335501.00", buffer, sizeof(buffer), 
        ImGuiInputTextFlags_CallbackCharFilter | ImGuiInputTextFlags_CallbackEdit | ImGuiInputTextFlags_CallbackAlways , checkUInputCallback);
        //create seperator
        ImGui::Separator();
        //get result from the buffer(User input)
        thisResult = run3(buffer);

        //reset button to reset locals
        if(ImGui::Button("Reset")){
            dotInserted = false;
            numOfDecimal = 0;
            memset(buffer, '\0', sizeof(buffer) / sizeof(char));
        }

        //check if there is input but everything is set to 0
        //indicating an overflow
        if(thisResult.oneHundred == 0 && buffer[5] != '\0'){

            ImGui::Text("Overflow Detected! Number is to large!");

            //create button for visual notifcation of overflow
            float x = ImGui::GetWindowWidth();
            float y = ImGui::GetCursorPosY();
            ImVec2 center = ImVec2(x - 20.0f, y - 10.0f);
            float radius = 5.0f;

            ImU32 color = IM_COL32(255, 0, 0, 255);

            ImDrawList* drawList= ImGui::GetWindowDrawList();
            if(drawCircle){
                drawList->AddCircleFilled(center, radius, color);
            }
            //alternate draw button to simulate blinking
            drawCircle = !drawCircle;
        }
        
        //print out results
        //uses string arr for better readability
        ImGui::Text("%lld $100s", thisResult.oneHundred);
            for(int i = 0; i < int(sizeof(stringArr) / sizeof(const char*)); i++){
                ImGui::Separator();
                ImGui::Text(stringArr[i], thisResult.denominations[i]);
            }
        

        ImGui::TextWrapped("\nINSTRUCTIONS\n\nInput must be in the form '*.XX'. Meaning you many have as many digits to the left of a '.' and two to the right.");
        ImGui::End();
        
        //render everthing in the stack
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());


        glfwMakeContextCurrent(window);
        glfwSwapBuffers(window);
    }

    // Cleanup
    ImGui_ImplOpenGL2_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    //free malloced memory
    free(thisResult.denominations);

    return 0;
}

int main(int argc, char* argv[]){

        int result = 0;

        //switch statement is used to check wether user gave input on the cmd line or not
        switch (argc){
            //no argument
            case 1:
                result = run1();
                break;
            //have argument
            case 2:
                //check if gui is selected
                if((std::string)argv[1] != "-g"){
                result = run2(argv[1]);
                }else{
                result = startGUIApplication();
                }

                break;
            //if the user gives more the one argument nothing is ran and program exits
            default:
                perror("ERROR provide either one(Dollar ammount in the form *.XX) \nor no arguments\n");
                break;
            }
    //return code
    return result;
}