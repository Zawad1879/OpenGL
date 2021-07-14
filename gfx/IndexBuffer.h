#pragma once

namespace gfx
{
    class IndexBuffer : public Buffer<GL_ELEMENT_ARRAY_BUFFER>
    {
    public:
        IndexBuffer(const VertexArray& va, uint indicesPerPrimitive, uint verticesPerPrimitive, const uint* const offsets) :
            Buffer<GL_ELEMENT_ARRAY_BUFFER>(va.GetVertexCount() * 6 / 4)
        {
            printf("Create IB %u\n", m_Id);
            
            uint* temp = new uint[m_Count]; //create array on the heap with new keyword. You need to delete this afterwards since c++ does not do garbage collection
            for (uint i = 0; i < m_Count; i++ )
            {
                temp[i] = s_Offsets[i % indicesPerPrimitive] + i / indicesPerPrimitive * verticesPerPrimitive; //six indices for each group of 4 indices. (4 indices, each index having vertex and rgb). Six indices referring to the indices when creating the triangles
            }
            Write(m_Count * sizeof(uint), temp);
            delete[] temp; // deleting the array we created
        }
        IndexBuffer(const IndexBuffer& other) = delete;
        IndexBuffer(IndexBuffer&& other) = delete;
        ~IndexBuffer()
        {
            printf("Delete IB %u\n", m_Id);
        }
    private:
        constexpr static uint s_Offsets[] = { 0, 1, 2, 0, 2, 3 };
    };
}
