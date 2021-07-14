#pragma once
#include "../math/All.h"
#include "Core.h"
#include "GLObject.h"
#include "Buffer.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "RenderObject.h"
#include "Shader.h"
#include "Texture.h"
#include "Renderer.h"

// Order matters. Since RenderObject is written at the end of all the other includes, RenderObject can access all the stuff from the above includes
