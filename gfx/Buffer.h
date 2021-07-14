#pragma once


namespace gfx
{
    template<GLenum TARGET>
    class Buffer : public GLObject // extends GLObject
    {
    public:
        void Bind() const override
        {
            glBindBuffer(TARGET, m_Id); // Using uppercase TARGET to make it clear that it is a template parameter
        }
        void Unbind() const override
        {
            glBindBuffer(TARGET, 0); // Using uppercase TARGET to make it clear that it is a template parameter
        }
        uint GetCount() const
        {
            return m_Count; // returns number of elements in buffer
        }
    protected:
        uint m_Count;
        
        Buffer(uint count) :
            m_Count(count)
        {
            glGenBuffers(1, &m_Id);
        }
        Buffer(const Buffer& other) = delete;
        Buffer(Buffer&& other) = delete;
        virtual ~Buffer()
        {
            glDeleteBuffers(1, &m_Id);
        }
        
        template<typename T>
        void Write(uint size, const T* const data) //Upload bytes to gpu
        {
            Bind();
            glBufferData(TARGET, size, data, GL_STATIC_DRAW);
        }
    };
}
