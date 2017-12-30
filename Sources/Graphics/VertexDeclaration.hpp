#ifndef NU_VERTEXDECLARATION_HPP
#define NU_VERTEXDECLARATION_HPP

#include "Vertex.hpp"
#include <vector>

namespace nu
{

struct VertexElement
{
	enum Type
	{
		Byte,
		UnsignedByte,
		Short,
		UnsignedShort,
		Int,
		UnsignedInt,
		HalfFloat,
		Float,
		Double
	};

	VertexElement(Type type, U32 typeSize, U32 nb = 1)
		: typeOfElement(type)
		, sizeOfElement(typeSize * nb)
		, nbOfElement(nb)
	{
	}

	Type typeOfElement;
	U32 sizeOfElement;
	U32 nbOfElement;
};

class VertexDeclaration
{
	public:
		VertexDeclaration();
		~VertexDeclaration();

		VertexDeclaration& setStruct(VertexStruct vertex);
		VertexDeclaration& addElement(VertexElement::Type type, U32 size, U32 nb = 1);

		const VertexElement& getElement(U32 index) const;
		U32 getElements() const;
		VertexStruct getStruct() const;
		U32 getStride() const;

		static bool isInitialized();
		static bool initialize();
		static VertexDeclaration* get(VertexStruct vertex);

	private:
		std::vector<VertexElement> mElements;
		VertexStruct mStruct;
		U32 mStride;
		U32 mIndex;

		static bool sInitialized;
		static VertexDeclaration* sDeclarations[VertexStruct_Count];
};

} // namespace nu

#endif // NU_VERTEXDECLARATION_HPP