#pragma once

// We are just creating a single shader class for both the shaders as they are not that complicated

namespace gfx
{
    class Shader : public GLObject
    {
    public:
        Shader(const char* fp)
        {
            m_Id = glCreateProgram();
            // Parse()
            ShaderSources source = Parse(fp);
            // vertex = Compile(...)
            // fragment = Compile(...)
            uint vertex = Compile(source.vertex, GL_VERTEX_SHADER);
            uint fragment = Compile(source.fragment, GL_FRAGMENT_SHADER);
            // Attach vertex + fragment to m_Id
            glAttachShader(m_Id, vertex);
            glAttachShader(m_Id, fragment);
            
            // finalize program
            glLinkProgram(m_Id);
            glValidateProgram(m_Id);
            // delete vertex + fragment
            glDeleteShader(vertex);
            glDeleteShader(fragment);
        }
        Shader(const Shader& other) = delete;
        Shader(Shader&& other) = delete;
        ~Shader()
        {
            glDeleteProgram(m_Id);
        }
        
        void Bind() const override
        {
            glUseProgram(m_Id);
        }
        void Unbind() const override
        {
            glUseProgram(0);
        }
        void SetUniform1f(const std::string& name, float f)
        {
            SetUniform(glUniform1f, name, f);
        }
        void SetUniform2f(const std::string& name, float x, float y)
        {
            SetUniform(glUniform2f, name, x, y);
        }
        void SetUniform1iv(const std::string& name, uint length, const int* const data)
        {
            SetUniform(glUniform1iv, name, length, data);
        }
    private:
        struct ShaderSources
        {
            std::string vertex, fragment;
        };
        
        std::unordered_map<std::string, int> m_UniformCache;
        
        template<typename T, typename ... Args>
        void SetUniform(T fn, const std::string& name, Args& ... args)
        {
            Bind();
            fn(GetUniformLocation(name), args...);
            
        }
        
        int GetUniformLocation(const std::string& s)
        {
            auto cached = m_UniformCache.find(s);
            if(cached != m_UniformCache.end()) // if contained in the map
            {
                return cached->second; //second value is the int
            }
            
            int location = glGetUniformLocation(m_Id, s.c_str());
            if(location == -1)
            {
                printf("Uniform '%s' not found\n", s.c_str());
                return -1;
            }
            
            m_UniformCache[s] = location;
            return location;
        }
        
        ShaderSources Parse(const char* fp) //fp is filepath
        {
            std::ifstream in(fp);
            if(!in.is_open())
            {
                printf("Error opening shader file '%s', aborting...\n", fp);
                return { "" , "" };
            }
            
            std::string line;
            std::stringstream streams[2]; //allows to append to strings
            // 0 = vertex shader, 1 = fragment shader
            uint currentType = 0; // Index into the string stream
            while(getline(in, line))
            {
                if (line.find("#type") != std::string::npos)
                {
                    if(line.find("vertex") != std::string::npos)
                        currentType = 0;
                    else if(line.find("fragment") != std::string::npos)
                        currentType = 1;
                    else{
                        printf("Invalid shader type on line '%s', aborting...\n", line.c_str()); // c_str is the char pointer of string
                        return { "" , "" };
                    }
                }
                else
                {
                    streams[currentType] << line << '\n';
                }
            }
            
            in.close();
            return { streams[0].str(), streams[1].str() };
        }
        uint Compile(const std::string& src, GLenum type)
        {
            uint id = glCreateShader(type);
            const char* ptr = src.c_str();
            glShaderSource(id, 1, &ptr, nullptr);
            glCompileShader(id);
            
            int result;
            glGetShaderiv(id, GL_COMPILE_STATUS, &result); // gl_compile_status tells us whether there was a compiler error
            if (result == GL_FALSE)
            {
                printf("%s shader compilation failed, aborting...\n", ( type == GL_VERTEX_SHADER ? "shader" : "fragment"));
                printf("Source:\n%s\n", src.c_str());
                
                int length;
                glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
                char* buffer = new char[length]; // Since its not a compile time array it should be stored in the heap
                glGetShaderInfoLog(id, length, nullptr, buffer);
                printf(buffer);
                delete[] buffer;
                
                glDeleteShader(id);
                return 0;
            }
            return id;
        }
    };
}
