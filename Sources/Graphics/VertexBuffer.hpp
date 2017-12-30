#ifndef NU_VERTEXBUFFER_HPP
#define NU_VERTEXBUFFER_HPP

#include "../Application/GLEWWrapper.hpp"
#include "VertexDeclaration.hpp"
#include "VertexArray.hpp"

namespace nu
{

class VertexBuffer
{
	public:
		VertexBuffer();
		VertexBuffer(VertexStruct vertexStruct);
		~VertexBuffer();

		void setStruct(VertexStruct vertexStruct);

		template <typename T>
		void set(const T* vertices, U32 size);

		template <typename T>
		void set(const std::vector<T>& vertices);

		void bind();

		U32 getVertices() const;
		U32 getStride() const;
		U32 getSize() const;

		bool isValid() const;
		U32 getId() const;

		VertexStruct getStruct() const;

	private:
		VertexArray* mVertexArray;
		VertexStruct mVertexStruct;
		U32 mIndex;
		U32 mVertices;
		U32 mStride;
};

template<typename T>
inline void VertexBuffer::set(const T* vertices, U32 size)
{
	glCheck(glBindBuffer(GL_ARRAY_BUFFER, mIndex));
	glCheck(glBufferData(GL_ARRAY_BUFFER, sizeof(T) * size, vertices, GL_STATIC_DRAW));
	mVertices = size;
	mStride = sizeof(T);
	setStruct(T::type);
}

template<typename T>
inline void VertexBuffer::set(const std::vector<T>& vertices)
{
	glCheck(glBindBuffer(GL_ARRAY_BUFFER, mIndex));
	glCheck(glBufferData(GL_ARRAY_BUFFER, sizeof(T) * vertices.size(), &vertices[0], GL_STATIC_DRAW));
	mVertices = vertices.size();
	mStride = sizeof(T);
	setStruct(T::type);
}

} // namespace nu

#endif // NU_VERTEXBUFFER_HPP