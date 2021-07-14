#pragma once

namespace gfx
{
    struct TextureOptions
    {
        GLenum min = GL_LINEAR, mag = GL_LINEAR, s = GL_CLAMP, t = GL_CLAMP;
        GLenum format = GL_RGBA, internalFormat = GL_RGBA8, type = GL_UNSIGNED_BYTE; // Glenum format controls how the data is formatted(look at data parameter in the Texture constructor below)
    };
    class Texture : public GLObject
    {
    public:
        Texture(uchar* data, uint width, uint height, uint frames, const TextureOptions& options = {}) //data going to be (R, G, B, R, G, B...)
        {
            glGenTextures(1, &m_Id);
            Bind();
            
//            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // function to resize texture if area smaller than texture
//            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // function to resize texture if area bigger than texture
            glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, options.min); // function to resize texture if area smaller than texture // GL_NEAREST for each pixel instead of interpolation it gets the x, y color of the nearest color
            glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, options.mag); // function to resize texture if area bigger than texture
            glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, options.s); // Specifies tiling . GL_CLAMP resizes image to whatever the texture size is
            glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, options.t); // These params are apparently not too important. Just used now to circumvent errors
            
            glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, options.internalFormat, width, height, frames, 0, options.format, options.type, data);
        }
        
        void Bind() const override
        {
            Bind(0);
        }
        
        void Bind(uint slot) const
        {
            glActiveTexture(GL_TEXTURE0 + slot);  // Unlike buffers, textures can have bunch of different targets, from 0 to 31
            glBindTexture(GL_TEXTURE_2D_ARRAY, m_Id);
        }
        
        void Unbind() const override
        {
            glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
        }
    };
}
