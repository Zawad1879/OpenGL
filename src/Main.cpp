//
//  main.cpp
//  GDW
//
//  Created by Niamat Zawad on 2021/05/21.
//

#include <iostream>
#include "pch.h"


int main(int argc, const char* argv[]) {

    gfx::WindowOptions wo;
    gfx::Color color;
    color.b = 1.f;
    wo.clear = color;
    gfx::OpenGLInstance gl = gfx::init(800, 600, "Title", wo);

    //    //1 create vertex data
    //    uint va;
    //    glGenVertexArrays(1, &va);
    //    glBindVertexArray(va); //So all the operations will only be on va
    //
    //    uint vbo;
    //    glGenBuffers(1, &vbo);
    //    float vertices[] //this is the opengl convention for vertices
    //    {
    //        // bottom left
    //        -.5f, -.5f, 1.f, 0.f, 0.f,
    //        // bottom right
    //        .5f, -.5f, 0.f, 1.f, 0.f,
    //        // top right
    //        .5f, .5f, 0.f, 0.f, 1.f,
    //        // top left
    //        -.5f, .5f, 1.f, 1.f, 1.f
    //    };
    //
    //    // Send our test vertex data to our vertex buffer. Because we're only doing this
    //    // once, GL_STATIC_DRAW works fine.
    //    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    //    glBufferData(GL_ARRAY_BUFFER, math::arrsize(vertices), vertices, GL_STATIC_DRAW); //GL_STATIC_DRAW means we won't be changing this data
    //
    //    /**
    //         * CPU step 2 - describe vertex data
    //         */
    //        // NOTE: this 0 corresponds to the layout(location = 0) in our vertex shader.
    //        // OpenGL knows that this metadata corresponds to our specific vertex buffer
    //        // because we have bound a vertex array.
    //    glEnableVertexAttribArray(0);
    //    // Operate on index 0. We have 2 elements per vertex. Our data type is floats.
    //    // Our floats are not normalized. The size of each vertex is 5 floats. This group
    //    // is not offset from the start of the vertex at all (that is, 0 bytes).
    //    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (const void*)0);
    //
    //     //In the above vertex attrib the 2 means the group of first 2 indices in each row are vertices. We want to create another group of 3 indices which denotes the color
    //    glEnableVertexAttribArray(1);
    //    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (const void*)(2 * sizeof(float)));
    //
    //
    //
    //    //3 create index data
    //    uint ibo;
    //    glGenBuffers(1, &ibo);
    //    uint indices[] = { 0, 1, 2, 0, 2, 3 }; //Two triangles. First one has bottom left, bottom right, top right vertices. Second one has bottom left, top right, top left vertices
    //    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    //    glBufferData(GL_ELEMENT_ARRAY_BUFFER, math::arrsize(indices), indices, GL_STATIC_DRAW);


    //    float vertices[] //this is the opengl convention for vertices
    //        {
    //            // bottom left
    //            -.5f, -.5f,
    //            // bottom right
    //            .5f, -.5f,
    //            // top right
    //            .5f, .5f,
    //            // top left
    //            -.5f, .5f
    //        };

    float vertices[] //this is the opengl convention for vertices
    {
        // bottom left
        -.5f, -.5f, 0.f, 0.f, 0.f, // last 3 indices are texture. Textcoord for bottom left are the 3rd 4th indices, texture index is last index
        // bottom right
        .5f, -.5f, 1.f, 0.f, 0.f,
        // top right
        .5f, .5f, 1.f, 1.f, 0.f,
        // top left
        -.5f, .5f, 0.f, 1.f, 0.f
    };

    //    gfx::VertexArray va(math::arrlen(vertices), vertices, { 2, 3 });
    //    gfx::IndexBuffer ibo(va);
    gfx::RenderObject ro(math::arrlen(vertices), vertices, { 2, 2, 1 }, engine::s_IndicesPerQuad, engine::s_VerticesPerQuad, engine::s_IndexOffsets); //first two are vertices. Next 2 are textcoord. Last is tex index

    const gfx::Renderer renderer;
    gfx::Shader shader("res/shader_texture.glsl");

    int textureUnits = gfx::getMaxTextureUnits();

    printf("%d\n", textureUnits);
    int* samplers = new int[textureUnits]; 
    for (uint i = 0; i < textureUnits; i++)
        samplers[i] = i;
    shader.SetUniform1iv("u_Textures", textureUnits, samplers); // length of our array is texture units and data we are sending is samplers. We are thus setting these dynamically
    /*for (uint i = 0; i < textureUnits; i++)
        samplers[i] = 0;*/
    //shader.SetUniform1iv("u_TextureFrames", textureUnits, samplers);
    delete[] samplers;

    constexpr uint dataWidth = 16, dataHeight = 16, dataFrames = 2; // number of pixels in width and height
    constexpr uint dataFrameSize = dataWidth * dataHeight * 4, dataSize = dataFrameSize * dataFrames;

    uchar data[dataSize] = { 0 }; // initialize all values with 0
    for (uint i = 0; i < dataWidth * dataHeight; i++)
    {
        data[i * 4 + 0] = 255; // set color to red
        data[i * 4 + 3] = 255; // set transparency to opaque
    }
    gfx::TextureOptions txOps;
    txOps.min = GL_NEAREST;
    txOps.mag = GL_NEAREST;
    gfx::Texture tex(data, dataWidth, dataHeight, 1, txOps);
    //4 vertex + fragment shader
//    uint vertex = glCreateShader(GL_VERTEX_SHADER);
//    uint fragment = glCreateShader(GL_FRAGMENT_SHADER);

    // this simply takes the data from our vertex buffer
    // and outputs it (unmodified) as a vec4
//    const char* vertexSource =
//        "#version 330 core\n"
//        "layout(location = 0) in vec2 i_Position;\n"
//        "layout(location = 1) in vec3 i_Color;\n"
//        "out vec3 v_Color;\n" //Pass down the color from here to fragment shader. Vertex shader has no use for color
//        "void main() {\n"
//        "    gl_Position = vec4(i_Position, 0, 1);\n"
//        "    v_Color = i_Color;\n"
//        "}";
//    // this sets every pixel to be solid red
//    const char* fragmentSource =
//        "#version 330 core\n"
//        "layout(location = 0) out vec4 o_Color;\n"
//        "in vec3 v_Color;\n" //Accepting color group from vertex shader
//        "void main() {\n"
//        //"    o_Color = vec4(1, 0, 0, 1);\n" //We dont need this anymore as we are passing down colors
//        "    o_Color = vec4(v_Color, 1);\n"
//        "}";
//
//    // vertex shader runs on each vertex of triangle while fragment shader runs on each pixel. This results in an interpolation effect where for each pixel it looks at the distance between that pixel and each vertex to get the weighted average color value of that. This results in a combination effect. Vertex shader runs 3 times for each vertex while fragment shader will run once for each pixel in the triangle
//    // give our shaders the source code and compile them
//    glShaderSource(vertex, 1, &vertexSource, nullptr);
//    glShaderSource(fragment, 1, &fragmentSource, nullptr);
//    glCompileShader(vertex);
//    glCompileShader(fragment);
//
//    // Check for compilation errors. Eventually, we will print
//    // the actual error output, but for now this is enough.
//    int result;
//    glGetShaderiv(vertex, GL_COMPILE_STATUS, &result);
//    if (result == GL_FALSE)
//        printf("Vertex shader compilation failed\n");
//    glGetShaderiv(fragment, GL_COMPILE_STATUS, &result);
//    if (result == GL_FALSE)
//        printf("Fragment shader compilation failed\n");
//
//    // create a program to store both of our shaders
//    uint program = glCreateProgram();
//    // attach both shaders
//    glAttachShader(program, vertex);
//    glAttachShader(program, fragment);
//    // finalize the program
//    glLinkProgram(program);
//    glValidateProgram(program);
//
//    // our shaders are now within our program,
//    // so we can delete the originals
//    glDeleteShader(vertex);
//    glDeleteShader(fragment);

//    const gfx::Renderer renderer;
//    const gfx::Renderer renderer("/Users/niamatzawad/Projects/GameDev/GDW/res/shader.glsl");
//    gfx::Shader shader("/Users/niamatzawad/Projects/GameDev/GDW/res/shader.glsl");

//    renderer.GetShader().SetUniform2f("u_Offset", 1.f, 0.f); // we only bind the shader when calling the draw method in Renderer. We're doing this ugly temporary workaround for now
//    int index = glGetUniformLocation(renderer.m_Shader.GetId(), "u_offset");
//    glUniform1f(index, 1.f);
    float offset = 0.f, increment = .005f;
    double updateTime = 0;
    int frame = 0;

    while (gl.IsRunning()) //each loop run is a different frame
    {
        renderer.Clear();

        if (math::abs(offset) >= 1.f)
            increment *= -1;
        offset += increment;
        shader.SetUniform2f("u_Camera", offset, offset);
        //        renderer.GetShader().SetUniform2f("u_Camera", offset, offset);
        //        glClear(GL_COLOR_BUFFER_BIT); //Clear the screen at the start of each frame. We set the color to blue in the other Core file in gfx // The frame buffer has several components and this is one of them. Later we will be using depth buffer

        //        double time = glfwGetTime();
        //        if (time - updateTime > 1)
        //        {
        //            samplers[0] = frame;
        //            frame = (frame + 1) % dataFrames;
        //            shader.SetUniform1iv("u_TextureFrames", textureUnits, samplers);
        //            updateTime = time;
        //        }
        //        glUseProgram(program);
        //        shader.Bind();

        //        renderer.Draw(ro);
        renderer.Draw(ro, tex, shader);
        //        glBindVertexArray(va);
        //        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
        //        glDrawElements(GL_TRIANGLES, math::arrlen(indices), GL_UNSIGNED_INT, nullptr); //we have already bound the buffer ibo and this method is going to use that so we set it to nullptr
        //        va.Bind();
        //        ibo.Bind();

        //        ro.Bind();
        //        glDrawElements(GL_TRIANGLES, ro.GetIndexCount(), GL_UNSIGNED_INT, nullptr);
        //
        //        glfwSwapBuffers(gl.window); //Draw everything and move the current buffer to the screen
        //        glfwPollEvents(); //Handle events like moving window, clicking window buttons ...
        
        renderer.Render(gl);
    }

    gfx::end(gl);
    return 0;

}
