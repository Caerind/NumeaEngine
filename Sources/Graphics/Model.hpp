#ifndef NU_MODEL_HPP
#define NU_MODEL_HPP

#include "Node.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "Mesh.hpp"
#include "TransformBinder.hpp"

namespace nu
{

class Model : public TransformBinder
{
	public:
		Model();

		void setTexture(Texture::Ptr texture);
		void setMesh(Mesh::Ptr mesh);

		Texture::Ptr getTexture();
		Mesh::Ptr getMesh();

		void draw();

	private:
		Texture::Ptr mTexture;
		Mesh::Ptr mMesh;
};

} // namespace nu

#endif // NU_MODEL_HPP