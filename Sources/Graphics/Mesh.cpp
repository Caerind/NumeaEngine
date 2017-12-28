#include "Mesh.hpp"

#define TINYOBJLOADER_IMPLEMENTATION
#include "../ExtLibs/tiny_obj_loader/tiny_obj_loader.h"

namespace nu
{

Mesh::Mesh()
{
}

bool Mesh::load(const nu::Loader<Mesh>& loader)
{
	mLoaded = loader.load(*this);
	return mLoaded;
}

void Mesh::bind()
{
	mIndices.bind();
	mVertices.bind();
}

void Mesh::set(const std::vector<Vertex_XYZ_Normal_UV>& vertices, const std::vector<U32>& indices)
{
	mVertices.set(vertices);
	mIndices.set(indices);
}

U32 Mesh::getVertices() const
{
	return mVertices.getVertices();
}

U32 Mesh::getIndices() const
{
	return mIndices.getIndices();
}

Loader<Mesh> MeshLoader::fromFile(const std::string& filename)
{
	return Loader<Mesh>([=](Mesh& mesh)
	{
		tinyobj::attrib_t attrib;
		std::vector<tinyobj::shape_t> shapes;
		std::vector<tinyobj::material_t> materials;
		std::string error;
		if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &error, filename.c_str()))
		{
			LogError(LogChannel::Graphics, 2, "%s", error.c_str());
			return false;
		}
		if (shapes.size() > 0)
		{
			tinyobj::shape_t& shape = shapes[0];

			std::vector<Vertex_XYZ_Normal_UV> vertices;
			std::vector<U32> indices;

			indices.reserve(shape.mesh.indices.size());

			U32 indexOffset = 0;
			for (U32 f = 0; f < shape.mesh.num_face_vertices.size(); f++)
			{
				U32 fnum = shape.mesh.num_face_vertices[f];
				for (U32 v = 0; v < fnum; v++)
				{
					tinyobj::index_t idx = shape.mesh.indices[indexOffset + v];

					vertices.push_back(Vertex_XYZ_Normal_UV());
					Vertex_XYZ_Normal_UV& back = vertices.back();

					std::memcpy(&back.position, &attrib.vertices[3 * idx.vertex_index], 3 * sizeof(F32));
					std::memcpy(&back.normal, &attrib.normals[3 * idx.normal_index], 3 * sizeof(F32));
					std::memcpy(&back.uv, &attrib.texcoords[2 * idx.texcoord_index], 2 * sizeof(F32)); 

					indices.push_back(idx.vertex_index);
				}
				indexOffset += fnum;
			}
			mesh.set(vertices, indices);
		}

		return true;
	});
}

} // namespace nu