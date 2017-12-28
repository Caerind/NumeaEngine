#include "IndexBuffer.hpp"

namespace nu
{

IndexBuffer::IndexBuffer()
	: mIndex(0)
	, mIndices(0)
{
	glGenBuffers(1, &mIndex);
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &mIndex);
}

void IndexBuffer::set(U32* indices, U32 size)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndex);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(U32) * size, indices, GL_STATIC_DRAW);
	mIndices = size;
}

void IndexBuffer::set(const std::vector<U32>& indices)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndex);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(U32) * indices.size(), &indices[0], GL_STATIC_DRAW);
	mIndices = indices.size();
}

void IndexBuffer::bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndex);
}

U32 IndexBuffer::getIndices() const
{
	return mIndices;
}

bool IndexBuffer::isValid() const
{
	return glIsBuffer(mIndex) == GL_TRUE;
}

U32 IndexBuffer::getId() const
{
	return mIndex;
}

} // namespace nu