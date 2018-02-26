#include "VertexArray.hpp"

namespace nu
{

VertexArray::VertexArray()
	: mVertexStruct(VertexStruct_Count)
	, mIndex(0)
{
	glCheck(glGenVertexArrays(1, &mIndex));
}

VertexArray::VertexArray(VertexStruct vertexStruct)
	: mVertexStruct(vertexStruct)
	, mIndex(0)
{
	glCheck(glGenVertexArrays(1, &mIndex));
	setStruct(vertexStruct);
}

VertexArray::~VertexArray()
{
	glCheck(glDeleteVertexArrays(1, &mIndex));
}

void VertexArray::setStruct(VertexStruct vertexStruct)
{
	mVertexStruct = vertexStruct;

	glCheck(glBindVertexArray(mIndex));

	VertexDeclaration* decl = VertexDeclaration::get(mVertexStruct);
	assert(decl != nullptr);

	U32 offset = 0;
	for (U32 i = 0; i < decl->getElements(); i++)
	{
		glCheck(glEnableVertexAttribArray(i));

		const VertexElement& e(decl->getElement(i));
		GLenum type;
		switch (e.typeOfElement)
		{
			case VertexElement::Byte: type = GL_BYTE; break;
			case VertexElement::UnsignedByte: type = GL_UNSIGNED_BYTE; break;
			case VertexElement::Short: type = GL_SHORT; break;
			case VertexElement::UnsignedShort: type = GL_UNSIGNED_SHORT; break;
			case VertexElement::Int: type = GL_INT; break;
			case VertexElement::UnsignedInt: type = GL_UNSIGNED_INT; break;
			case VertexElement::HalfFloat: type = GL_HALF_FLOAT; break;
			case VertexElement::Float: type = GL_FLOAT; break;
			case VertexElement::Double: type = GL_DOUBLE; break;
			default: break;
		}

		glCheck(glVertexAttribPointer(i, e.nbOfElement, type, GL_FALSE, decl->getStride(), (void*)(offset)));

		//printf("%d : %d, %d, %x, %d, %d\n", mVertexStruct, i, e.nbOfElement, type, decl->getStride(), offset);

		offset += e.sizeOfElement;
	}
}

void VertexArray::bind()
{
	glCheck(glBindVertexArray(mIndex));
}

bool VertexArray::isValid() const
{
	return glIsVertexArray(mIndex) == GL_TRUE && mVertexStruct != VertexStruct_Count;
}

U32 VertexArray::getId() const
{
	return mIndex;
}

VertexStruct VertexArray::getStruct() const
{
	return mVertexStruct;
}

} // namespace nu