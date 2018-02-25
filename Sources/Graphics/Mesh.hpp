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
		void draw();

		template <typename T>
		void set(const std::vector<T>& vertices, const std::vector<U32>& indices);

		VertexBuffer& getVertexBuffer();
		IndexBuffer& getIndexBuffer();

		U32 getVertices() const;
		U32 getIndices() const;

	private:
		VertexBuffer mVBO;
		IndexBuffer mIndices;
};

class MeshLoader
{
	public:
		static Loader<Mesh> fromFile(const std::string& filename);
};

template<typename T>
inline void Mesh::set(const std::vector<T>& vertices, const std::vector<U32>& indices)
{
	mVBO.set<T>(vertices);
	mIndices.set(indices);
}

} // namespace nu

#endif // NU_MESH_HPP