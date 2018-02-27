#include "IndexBuffer.hpp"

#include "Renderer.hpp"

namespace nu
{

IndexBuffer::IndexBuffer()
	: mIndex(0)
	, mIndices(0)
{
	glCheck(glGenBuffers(1, &mIndex));
}

IndexBuffer::~IndexBuffer()
{
	glCheck(glDeleteBuffers(1, &mIndex));
}

void IndexBuffer::set(U32* indices, U32 size)
{
	glCheck(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndex));
	glCheck(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(U32) * size, indices, GL_STATIC_DRAW));
	mIndices = size;
}

void IndexBuffer::set(const std::vector<U32>& indices)
{
	glCheck(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndex));
	glCheck(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(U32) * indices.size(), &indices[0], GL_STATIC_DRAW));
	mIndices = indices.size();
}

U32 IndexBuffer::getIndices() const
{
	return mIndices;
}

void IndexBuffer::bind() const
{
	glCheck(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndex));
}

void IndexBuffer::draw() const
{
	Renderer::instance().drawElements(Primitive::Triangles, mIndices);
}

bool IndexBuffer::isValid() const
{
	return glIsBuffer(mIndex) == GL_TRUE;
}

U32 IndexBuffer::getOpenGLId() const
{
	return mIndex;
}

} // namespace nu