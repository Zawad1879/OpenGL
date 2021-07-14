#pragma once

namespace gfx
{
    class GLObject
    {
    public:
        GLObject(): m_Id(0) {}
        GLObject(const GLObject& other) = delete; //we dont want the class to generate a copy and emov constructor automatically so we want to explicitly tell the compiler not to generate copy and moce constructors
        GLObject(GLObject&& other) = delete;
        virtual ~GLObject() {}; //kind of like abstract in java. If you don't define this you won't be able to use it. You also want to mark any constructor or function as virtual if you want to override it in a child class
        
        virtual void Bind() const = 0; //if you want to make sure child classes must use this, this is the syntax. I know, very arbitrary
        virtual void Unbind() const = 0;
        uint GetId() const
        {
            return m_Id;
        }
    protected:
        uint m_Id; // holds the pointer to a buffer
    };
}
