#pragma once

namespace gfx
{
    class VertexBuffer : public Buffer<GL_ARRAY_BUFFER>
    {
    public:
        VertexBuffer(uint count, const float* const data) :
            Buffer<GL_ARRAY_BUFFER>(count) // meaning of weird syntax: not only can the data not be modified , you can't also change the pointer
        {
            printf("Create VB %u\n", m_Id);
            Write(count * sizeof(float), data);
        }
        VertexBuffer(const VertexBuffer& other) = delete;
        VertexBuffer(VertexBuffer&& other) = delete;
        virtual ~VertexBuffer()
        {
            printf("Delete VB %u\n", m_Id);
        }
    };
}
