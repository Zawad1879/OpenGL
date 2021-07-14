//#pragma once
//
//namespace gfx
//{
//    class Renderer
//    {
//    public:
//        Renderer() {}
//        Renderer(const char* fp) :
//            m_Shader(fp)
//        {}
//        Renderer(const Renderer& other) = delete;
//        Renderer(Renderer&& other) = delete;
//        void Clear() const
//        {
//            glClear(GL_COLOR_BUFFER_BIT);
//        }
//        void Draw(const RenderObject& obj) const
//        {
//            m_Shader.Bind();
//            obj.Bind();
//            glDrawElements(GL_TRIANGLES, obj.GetIndexCount(), GL_UNSIGNED_INT, nullptr);
//        }
//        void Draw(const RenderObject& obj, const Texture& texture, const Shader& shader) const
//        {
//            obj.Bind();
//            texture.Bind();
//            shader.Bind();
//            glDrawElements(GL_TRIANGLES, obj.GetIndexCount(), GL_UNSIGNED_INT, nullptr);
//        }
//        void Render(const OpenGLInstance& gl ) const
//        {
//            glfwSwapBuffers(gl.window);
//            glfwPollEvents();
//        }
//        Shader& GetShader() const // we are definining this as const because this method does not change the state of the renderer. We are just defining this method here for convenience. In reality the shader would probably be defined in another class.
//        {
//            return m_Shader;
//        }
//    private:
//        mutable Shader m_Shader;
//    };
//}





#pragma once

namespace gfx
{
    class Renderer
    {
    public:
        Renderer() {}
        Renderer(const Renderer& other) = delete;
        Renderer(Renderer&& other) = delete;


        void Clear() const
        {
            glClear(GL_COLOR_BUFFER_BIT);
        }
        void Draw(const RenderObject& obj, const Shader& shader) const
        {
            shader.Bind();
            obj.Bind();
            glDrawElements(GL_TRIANGLES, obj.GetIndexCount(), GL_UNSIGNED_INT, nullptr);
        }
        void Draw(const RenderObject& obj, const Texture& texture, const Shader& shader) const
        {
            obj.Bind();
            texture.Bind();
            shader.Bind();
            glDrawElements(GL_TRIANGLES, obj.GetIndexCount(), GL_UNSIGNED_INT, nullptr);
        }
        void Draw(const RenderObject& obj, const Texture*const*const textures, uint count, const Shader& shader) const
        {
            obj.Bind();
            for (uint i = 0; i < count; i++)
                textures[i]->Bind(i);
            shader.Bind();
            glDrawElements(GL_TRIANGLES, obj.GetIndexCount(), GL_UNSIGNED_INT, nullptr);
        }
        void Render(const OpenGLInstance& gl) const
        {
            glfwSwapBuffers(gl.window);
            glfwPollEvents();
        }
    };
}
