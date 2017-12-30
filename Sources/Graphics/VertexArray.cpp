#include "VertexArray.hpp"

namespace nu
{

bool VertexArray::sInitialized = false;
VertexArray* VertexArray::sArrays[];

VertexArray::VertexArray(VertexStruct vertexStruct)
	: mStruct(vertexStruct)
	, mIndex(0)
{

	glCheck(glGenVertexArrays(1, &mIndex));
	glCheck(glBindVertexArray(mIndex));

	VertexDeclaration* decl = VertexDeclaration::get(mStruct);

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

		//printf("%d, %d, %x, %d, %x\n", i, e.nbOfElement, type, decl->getStride(), (void*)(offset));

		offset += e.sizeOfElement;
	}
}

VertexArray::~VertexArray()
{
	glCheck(glDeleteVertexArrays(1, &mIndex));
}

void VertexArray::bind()
{
	glCheck(glBindVertexArray(mIndex));
}

U32 VertexArray::getIndex() const
{
	return mIndex;
}

VertexStruct VertexArray::getStruct() const
{
	return mStruct;
}

bool VertexArray::isInitialized()
{
	return sInitialized;
}

bool VertexArray::initialize()
{
	if (!sInitialized)
	{
		for (U32 i = 0; i < VertexStruct_Count; i++)
		{
			sArrays[i] = nullptr;
		}
		sInitialized = true;
	}
	return sInitialized;
}

VertexArray* VertexArray::get(VertexStruct vertex)
{
	if (!sInitialized)
	{
		LogWarning(nu::LogChannel::Graphics, 1, "VertexArray : Initialization within get() is not recommanded");
		initialize();
	}
	if (sInitialized && sArrays[vertex] == nullptr)
	{
		sArrays[vertex] = new VertexArray(vertex);
	}
	return sArrays[vertex];
}

} // namespace nu