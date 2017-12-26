#include "VertexDeclaration.hpp"

namespace nu
{

bool VertexDeclaration::sInitialized = false;
VertexDeclaration VertexDeclaration::sDeclarations[];

VertexDeclaration& VertexDeclaration::setStruct(VertexStruct vertex)
{
	mStruct = vertex;
	return *this;
}

VertexStruct VertexDeclaration::getStruct() const
{
	return mStruct;
}

VertexDeclaration& VertexDeclaration::addElement(U32 type, U32 nb)
{
	mElements.push_back(VertexElement(type, nb));
	mStride += type * nb;
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
		U32 svec2 = sizeof(Vector2f);
		U32 svec3 = sizeof(Vector3f);
		U32 scol = sizeof(Color);

		#define DECL(s) sDeclarations[s].setStruct(s)

		DECL(VertexStruct_XY).addElement(svec2);
		DECL(VertexStruct_XY_Color).addElement(svec2).addElement(scol);
		DECL(VertexStruct_XY_UV).addElement(svec2).addElement(svec2);
		DECL(VertexStruct_XY_Color_UV).addElement(svec2).addElement(scol).addElement(svec2);
		DECL(VertexStruct_XYZ).addElement(svec3);
		DECL(VertexStruct_XYZ_Color).addElement(svec3).addElement(scol);
		DECL(VertexStruct_XYZ_Color_UV).addElement(svec3).addElement(scol).addElement(svec2);
		DECL(VertexStruct_XYZ_Normal).addElement(svec3).addElement(svec3);
		DECL(VertexStruct_XYZ_Normal_UV).addElement(svec3).addElement(svec3).addElement(svec2);
		DECL(VertexStruct_XYZ_Normal_UV_Tangent).addElement(svec3).addElement(svec3).addElement(svec2).addElement(svec3);
		DECL(VertexStruct_XYZ_UV).addElement(svec3).addElement(svec2);

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
	return &sDeclarations[vertex];
}

} // namespace nu