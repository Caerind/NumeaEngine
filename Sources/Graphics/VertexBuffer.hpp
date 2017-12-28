#ifndef NU_VERTEXBUFFER_HPP
#define NU_VERTEXBUFFER_HPP

#include "../Application/GLEWWrapper.hpp"
#include "VertexDeclaration.hpp"

// TODO : Ensure valid vertex type

namespace nu
{

template <typename T>
class VertexBuffer
{
	public:
		VertexBuffer();
		~VertexBuffer();

		void set(const T* vertices, U32 size);
		void set(const std::vector<T>& vertices);

		void bind();

		U32 getVertices() const;
		U32 getStride() const;

		bool isValid() const;
		U32 getId() const;

	private:
		VertexDeclaration& mDeclaration;
		U32 mIndex;
		U32 mVertices;
};

template<typename T>
inline VertexBuffer<T>::VertexBuffer()
	: mDeclaration(*VertexDeclaration::get(T::type))
	, mIndex(0)
	, mVertices(0)
{
	assert(VertexDeclaration::isInitialized());
	glGenBuffers(1, &mIndex);
}

template<typename T>
inline VertexBuffer<T>::~VertexBuffer()
{
	glDeleteBuffers(1, &mIndex);
}

template<typename T>
inline void VertexBuffer<T>::set(const T* vertices, U32 size)
{
	glBindBuffer(GL_ARRAY_BUFFER, mIndex);
	glBufferData(GL_ARRAY_BUFFER, sizeof(T) * size, vertices, GL_STATIC_DRAW);
	mVertices = size;
}

template<typename T>
inline void VertexBuffer<T>::set(const std::vector<T>& vertices)
{
	glBindBuffer(GL_ARRAY_BUFFER, mIndex);
	glBufferData(GL_ARRAY_BUFFER, sizeof(T) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
	mVertices = vertices.size();
}

template<typename T>
inline void VertexBuffer<T>::bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, mIndex);
	
	for (U32 i = 0; i < mDeclaration.getElements(); i++)
	{
		glEnableVertexAttribArray(i);
	}
	
	for (U32 i = 0; i < mDeclaration.getElements(); i++)
	{
		const VertexElement& e(mDeclaration.getElement(i));
		switch (e.typeOfElement)
		{
			case VertexElement::Byte: glVertexAttribPointer(i, e.nbOfElement, GL_BYTE, GL_FALSE, mDeclaration.getStride(), (void*)e.sizeOfElement); break;
			case VertexElement::UnsignedByte: glVertexAttribPointer(i, e.nbOfElement, GL_UNSIGNED_BYTE, GL_FALSE, mDeclaration.getStride(), (void*)e.sizeOfElement); break;
			case VertexElement::Short: glVertexAttribPointer(i, e.nbOfElement, GL_SHORT, GL_FALSE, mDeclaration.getStride(), (void*)e.sizeOfElement); break;
			case VertexElement::UnsignedShort: glVertexAttribPointer(i, e.nbOfElement, GL_UNSIGNED_SHORT, GL_FALSE, mDeclaration.getStride(), (void*)e.sizeOfElement); break;
			case VertexElement::Int: glVertexAttribPointer(i, e.nbOfElement, GL_INT, GL_FALSE, mDeclaration.getStride(), (void*)e.sizeOfElement); break;
			case VertexElement::UnsignedInt: glVertexAttribPointer(i, e.nbOfElement, GL_UNSIGNED_INT, GL_FALSE, mDeclaration.getStride(), (void*)e.sizeOfElement); break;
			case VertexElement::HalfFloat: glVertexAttribPointer(i, e.nbOfElement, GL_HALF_FLOAT, GL_FALSE, mDeclaration.getStride(), (void*)e.sizeOfElement); break;
			case VertexElement::Float: glVertexAttribPointer(i, e.nbOfElement, GL_FLOAT, GL_FALSE, mDeclaration.getStride(), (void*)e.sizeOfElement); break;
			case VertexElement::Double: glVertexAttribPointer(i, e.nbOfElement, GL_DOUBLE, GL_FALSE, mDeclaration.getStride(), (void*)e.sizeOfElement); break;
			default: break;
		}
	}

	glDrawElements(GL_TRIANGLES, mVertices, GL_UNSIGNED_INT, 0);

	for (U32 i = 0; i < mDeclaration.getElements(); i++)
	{
		glDisableVertexAttribArray(i);
	}
}

template<typename T>
inline U32 VertexBuffer<T>::getVertices() const
{
	return mVertices;
}

template<typename T>
inline U32 VertexBuffer<T>::getStride() const
{
	return sizeof(T);
}

template<typename T>
inline bool VertexBuffer<T>::isValid() const
{
	return glIsBuffer(mIndex) == GL_TRUE;
}

template<typename T>
inline U32 VertexBuffer<T>::getId() const
{
	return mIndex;
}

} // namespace nu

#endif // NU_VERTEXBUFFER_HPP