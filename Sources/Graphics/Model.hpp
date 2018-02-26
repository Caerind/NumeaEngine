#ifndef NU_MODEL_HPP
#define NU_MODEL_HPP

#include "Node.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "Mesh.hpp"

namespace nu
{

class Model : public Node
{
	public:
		Model();

		enum TransformBindingUniform
		{
			ModelMatrix = 0,
			ModelViewMatrix,
			ModelViewProjectionMatrix,
			NormalMatrix,
			Count
		};

		void setShader(Shader::Ptr shader);
		void setTexture(Texture::Ptr texture);
		void setMesh(Mesh::Ptr mesh);

		Shader::Ptr getShader();
		Texture::Ptr getTexture();
		Mesh::Ptr getMesh();

		void setUniformBinding(TransformBindingUniform binding, const std::string& uniform);
		void clearUniformBindings();

		void draw();

	private:
		void bindTransforms();

	private:
		std::string mBindings[TransformBindingUniform::Count];
		Shader::Ptr mShader;
		Texture::Ptr mTexture;
		Mesh::Ptr mMesh;
};

} // namespace nu

#endif // NU_MODEL_HPP