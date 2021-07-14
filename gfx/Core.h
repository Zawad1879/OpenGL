#pragma once
#include "glew.h"
#include "glfw3.h"
#include "glfw3native.h"
#include <stdio.h>

typedef uint32_t uint;

namespace gfx
{
    struct Color
    {
        float r = 0.f, g = 0.f, b = 0.f;
    };

    struct OpenGLInstance
    {
        GLFWwindow* window;
        
        bool IsRunning() const { return !glfwWindowShouldClose(window); }
        
    };

    struct WindowOptions
    {
        bool resizable = false;
        Color clear = {};
    };

    // to be called if any initialization fails
    static OpenGLInstance err(const char* msg, GLFWwindow* window = nullptr)
    {
        printf("%s error, aborting...\n", msg);
        glfwTerminate();
        if (window)
            glfwDestroyWindow(window);
        return { nullptr };
    }

static OpenGLInstance init(uint width, uint height, const char* title, const WindowOptions& options = {})
    {
        if(!glfwInit())
            return err("GLFW init");
        
        glfwWindowHint(GLFW_RESIZABLE, options.resizable);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        
        GLFWwindow* window = glfwCreateWindow(width, height, title, nullptr, nullptr);
        glfwMakeContextCurrent(window);
        
        if(!window)
            return err("Window creation");
        
        glewExperimental = GL_TRUE;
        if(glewInit()) //glewInit returns true if it fails, opposite of glfwInit
        {
            printf("Failed to initialize GLFW, aborting...\n");
            glfwDestroyWindow(window);
            glfwTerminate();
            return { nullptr };
        }
        
        glClearColor(options.clear.r, options.clear.g, options.clear.b, 1.f); //set the background color of the pixels not filled by the rasterization process //last value is the alpha value(opacity)
        glEnable(GL_BLEND); // using the alpha value to blend colors
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glfwSetWindowSizeCallback(window, [](GLFWwindow* w, int width, int height)
                                  { glViewport(0, 0, width, height); });
        
        return { window };
    }
    static void end(OpenGLInstance& instance)
    {
        glfwDestroyWindow(instance.window);
        glfwTerminate();
    }

    static int getMaxTextureUnits() 
    {
        int result;
        glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &result);
        return result;
    }
}
