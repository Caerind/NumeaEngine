#ifndef NU_MESH_HPP
#define NU_MESH_HPP

#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "../Application/Resource.hpp"

namespace nu
{

class Mesh : public Resource<Mesh>
{
	public:
		Mesh();

		bool load(const nu::Loader<Mesh>& loader);

		void bind();

		void set(const std::vector<Vertex_XYZ_Normal_UV>& vertices, const std::vector<U32>& indices);

		U32 getVertices() const;
		U32 getIndices() const;

	private:
		VertexBuffer<Vertex_XYZ_Normal_UV> mVertices;
		IndexBuffer mIndices;
};

class MeshLoader
{
	public:
		static Loader<Mesh> fromFile(const std::string& filename);
};

} // namespace nu

#endif // NU_MESH_HPP