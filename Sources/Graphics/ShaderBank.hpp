#ifndef NU_SHADERBANK_HPP
#define NU_SHADERBANK_HPP

#include "Shader.hpp"
#include "Vertex.hpp"
#include <unordered_map>

namespace nu
{

struct ShaderElement
{
	VertexStruct vStruct;
	Shader::Ptr shader;
};

class ShaderBank
{
	public:
		ShaderBank();
		~ShaderBank();

		void addShader(VertexStruct vStruct, Shader::Ptr shader);

		Shader::Ptr getShader(VertexStruct vStruct, const std::string& identifier);
		Shader::Ptr getShader(VertexStruct vStruct, U32 identifier);

		void clear();

	private:
		std::vector<ShaderElement> mShaders;
};

} // namespace nu

#endif // NU_DEBUGDRAW_HPP