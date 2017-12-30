#include "VertexDeclaration.hpp"

namespace nu
{

bool VertexDeclaration::sInitialized = false;
VertexDeclaration* VertexDeclaration::sDeclarations[];

VertexDeclaration::VertexDeclaration()
	: mElements()
	, mStruct(VertexStruct_Count)
	, mStride(0)
	, mIndex(0)
{
}

VertexDeclaration::~VertexDeclaration()
{
}

VertexDeclaration& VertexDeclaration::setStruct(VertexStruct vertex)
{
	mStruct = vertex;
	return *this;
}

VertexDeclaration& VertexDeclaration::addElement(VertexElement::Type type, U32 size, U32 nb)
{
	mElements.push_back(VertexElement(type, size, nb));
	mStride += size * nb;
	return *this;
}

const VertexElement& VertexDeclaration::getElement(U32 index) const
{
	assert(index < mElements.size());
	return mElements[index];
}

U32 VertexDeclaration::getElements() const
{
	return mElements.size();
}

VertexStruct VertexDeclaration::getStruct() const
{
	return mStruct;
}

U32 VertexDeclaration::getStride() const
{
	return mStride;
}

bool VertexDeclaration::isInitialized()
{
	return sInitialized;
}

bool VertexDeclaration::initialize()
{
	if (!sInitialized)
	{
		for (U32 i = 0; i < (U32)VertexStruct_Count; i++)
		{
			sDeclarations[i] = new VertexDeclaration();
		}

		#define DECL(s) sDeclarations[s]->setStruct(s)

		#define v2f VertexElement::Float, sizeof(F32), 2
		#define v3f VertexElement::Float, sizeof(F32), 3
		#define col VertexElement::UnsignedByte, sizeof(U8), 4

		DECL(VertexStruct_XY).addElement(v2f);
		DECL(VertexStruct_XY_Color).addElement(v2f).addElement(col);
		DECL(VertexStruct_XY_UV).addElement(v2f).addElement(v2f);
		DECL(VertexStruct_XY_Color_UV).addElement(v2f).addElement(col).addElement(v2f);
		DECL(VertexStruct_XYZ).addElement(v3f);
		DECL(VertexStruct_XYZ_Color).addElement(v3f).addElement(col);
		DECL(VertexStruct_XYZ_Color_UV).addElement(v3f).addElement(col).addElement(v2f);
		DECL(VertexStruct_XYZ_Normal).addElement(v3f).addElement(v3f);
		DECL(VertexStruct_XYZ_Normal_UV).addElement(v3f).addElement(v3f).addElement(v2f);
		DECL(VertexStruct_XYZ_Normal_UV_Tangent).addElement(v3f).addElement(v3f).addElement(v2f).addElement(v3f);
		DECL(VertexStruct_XYZ_UV).addElement(v3f).addElement(v2f);

		#undef v2f
		#undef v3f
		#undef col

		#undef DECL

		sInitialized = true;
	}
	return sInitialized;
}

VertexDeclaration* VertexDeclaration::get(VertexStruct vertex)
{
	if (!sInitialized)
	{
		LogWarning(nu::LogChannel::Graphics, 1, "VertexDeclaration : Initialization within get() is not recommanded");
		initialize();
	}
	return sDeclarations[vertex];
}

} // namespace nu