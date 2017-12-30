#ifndef NU_VERTEXARRAY_HPP
#define NU_VERTEXARRAY_HPP

#include "../Application/GLEWWrapper.hpp"

#include "VertexDeclaration.hpp"

namespace nu
{

class VertexArray
{
	public:
		VertexArray(VertexStruct vertexStruct);
		~VertexArray();

		void bind();

		U32 getIndex() const;

		VertexStruct getStruct() const;

		static bool isInitialized();
		static bool initialize();
		static VertexArray* get(VertexStruct vertex);

	private:
		VertexStruct mStruct;
		U32 mIndex;

		static bool sInitialized;
		static VertexArray* sArrays[VertexStruct_Count];
};

} // namespace nu

#endif // NU_VERTEXARRAY_HPP