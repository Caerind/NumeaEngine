#ifndef NU_TRANSFORMBINDER_HPP
#define NU_TRANSFORMBINDER_HPP

#include "Node.hpp"
#include "Shader.hpp"

namespace nu
{

class TransformBinder : public Node
{
	public:
		TransformBinder();

		enum TransformBindingUniform
		{
			ModelMatrix = 0,
			ModelViewMatrix,
			ModelViewProjectionMatrix,
			ViewProjectionMatrix,
			NormalMatrix,
			Count
		};

		void setShader(Shader::Ptr shader);
		Shader::Ptr getShader();

		void setUniformBinding(TransformBindingUniform binding, const std::string& uniform);
		void clearUniformBindings();

	protected:
		void bindTransforms();

	private:
		std::string mBindings[TransformBindingUniform::Count];
		
	protected:
		Shader::Ptr mShader;
};

} // namespace nu

#endif // NU_TRANSFORMBINDER_HPP