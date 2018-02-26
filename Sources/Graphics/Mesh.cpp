#include "Mesh.hpp"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <assimp/mesh.h>

#include "Renderer.hpp"

namespace nu
{

Mesh::Mesh()
	: mVBO()
	, mIndices()
{
}

bool Mesh::load(const nu::Loader<Mesh>& loader)
{
	mLoaded = loader.load(*this);
	return mLoaded;
}

void Mesh::bind()
{
	mVBO.bind();
	mIndices.bind();
}

void Mesh::draw()
{
	mIndices.draw();
}

VertexBuffer& Mesh::getVertexBuffer()
{
	return mVBO;
}

IndexBuffer& Mesh::getIndexBuffer()
{
	return mIndices;
}

U32 Mesh::getVertices() const
{
	return mVBO.getVertices();
}

U32 Mesh::getIndices() const
{
	return mIndices.getIndices();
}

Loader<Mesh> MeshLoader::fromFile(const std::string& filename)
{
	return Loader<Mesh>([=](Mesh& mesh)
	{
		std::vector<Vertex_XYZ_Normal_UV> vertices;
		std::vector<U32> indices; 
		
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(filename, aiProcessPreset_TargetRealtime_Fast);
		if (!scene)
		{
			LogError(LogChannel::Graphics, 2, "%s\n", importer.GetErrorString());
			return false;
		}

		assert(scene->mNumMeshes > 0);

		aiMesh* m = scene->mMeshes[0];

		vertices.reserve(m->mNumVertices);
		for (unsigned int i = 0; i < m->mNumVertices; i++)
		{
			nu::vec3 pos;
			nu::vec3 normal;
			nu::vec2 uv;
			memcpy(&pos, &m->mVertices[i], 3 * sizeof(float));
			memcpy(&normal, &m->mNormals[i], 3 * sizeof(float));
			memcpy(&uv, &m->mTextureCoords[0][i], 2 * sizeof(float));
			uv.y = 1.0f - uv.y;
			vertices.push_back(Vertex_XYZ_Normal_UV(pos, normal, uv));
		}

		indices.reserve(3 * m->mNumFaces);
		for (unsigned int i = 0; i < m->mNumFaces; i++)
		{
			indices.push_back(m->mFaces[i].mIndices[0]);
			indices.push_back(m->mFaces[i].mIndices[1]);
			indices.push_back(m->mFaces[i].mIndices[2]);
		}

		mesh.set(vertices, indices);

		return true;
	});
}

} // namespace nu