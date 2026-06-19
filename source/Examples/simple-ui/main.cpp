#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <PixieUI/PixieUI.h>

PixieUI::Layout* layout = nullptr;

void WindowResizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void WindowClickCallback(GLFWwindow* window, int button, int action, int mods) {
    if (!layout) return;
    if (action != GLFW_PRESS) return;
    double x, y;
    glfwGetCursorPos(window, &x, &y);
    int width, height;
    glfwGetWindowSize(window, &width, &height);
    int layoutX = (x / width) * layout->GetWidth();
    int layoutY = (y / height) * layout->GetHeight();
    layout->Click(layoutX, layoutY);
}

void WindowCursorCallback(GLFWwindow* window, double x, double y) {
    if (!layout) return;
    int width, height;
    glfwGetWindowSize(window, &width, &height);
    int layoutX = (x / width) * layout->GetWidth();
    int layoutY = (y / height) * layout->GetHeight();
    layout->SetCursorPosition(layoutX, layoutY);
}

int main(int argc, char** argv) {
    
    if (!glfwInit()) {
        std::cout << "GLFW failed to initialize.\n";
        return 1;
    }

    GLFWwindow* window = glfwCreateWindow(800, 600, "PixieUI - SimpleUI Example.", NULL, NULL);
    glfwMakeContextCurrent(window);

    glfwSetWindowSizeCallback(window, WindowResizeCallback);
    glfwSetMouseButtonCallback(window, WindowClickCallback);
    glfwSetCursorPosCallback(window, WindowCursorCallback);

    if (!gladLoadGL()) {
        std::cout << "GLAD failed to initialize.\n";
        return 2;
    }

    if (!PixieUI::Init()) {
        std::cout << "PixieUI failed to initialize.\n";
        return 3;
    }

    // Set values, relative to which all transformations are calculated
    PixieUI::SetCanvasSize(400, 300);

    // Create layout that stores elements. Size is currently unused.
    layout = new PixieUI::Layout(400, 300);

    // Create and attach text element
    PixieUI::Text* helloWorld = new PixieUI::Text("Hello, World!", 20, 20);
    layout->AttachElement(helloWorld);

    // Optionally create style for button. Create button with set click callback. Attach Button to layout.
    PixieUI::Style buttonStyle = PixieUI::defaultButtonStyle;
    buttonStyle.bgActiveColor = PixieUI::Color(180, 180, 180);
    PixieUI::Button* button = new PixieUI::Button( 
        PixieUI::ButtonConfig(
            "Clickable",
            [&](int32_t, int32_t) {
                std::cout << "Click!\n";
                return true;
            }
        ), 20, 40, 0, buttonStyle);
    layout->AttachElement(button);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Call Draw() on all attached elements.
        layout->Draw();

        // Draw on screen without creating an element.
        PixieUI::Renderer::DrawRect(20, 60, 88, 15, buttonStyle.bgColor, 1, buttonStyle.borderColor);
        PixieUI::Renderer::DrawText("From Renderer", 23, 61, buttonStyle.fontColor);

        glfwSwapBuffers(window);
    }

    // When layout is deleted, it deletes all attached elements.
    delete layout;

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}