#ifndef NU_VERTEXDECLARATION_HPP
#define NU_VERTEXDECLARATION_HPP

#include "Vertex.hpp"
#include <vector>

namespace nu
{

struct VertexElement
{
	VertexElement(U32 type, U32 nb = 1)
		: typeOfElement(type)
		, nbOfElement(nb)
	{
	}

	U32 typeOfElement;
	U32 nbOfElement;
};

class VertexDeclaration
{
	public:
		VertexDeclaration() = default;

		VertexDeclaration& setStruct(VertexStruct vertex);
		VertexStruct getStruct() const;

		VertexDeclaration& addElement(U32 type, U32 nb = 1);

		const VertexElement& getElement(U32 index) const;
		U32 getElements() const;
		U32 getStride() const;

		static bool isInitialized();
		static bool initialize();
		static VertexDeclaration* get(VertexStruct vertex);

	private:
		std::vector<VertexElement> mElements;
		VertexStruct mStruct;
		U32 mStride;

		static bool sInitialized;
		static VertexDeclaration sDeclarations[VertexStruct_Count];
};

} // namespace nu

#endif // NU_VERTEXDECLARATION_HPP