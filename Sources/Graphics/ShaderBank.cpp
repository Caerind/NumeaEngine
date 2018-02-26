#include "ShaderBank.hpp"

namespace nu
{

ShaderBank::ShaderBank()
{
}

ShaderBank::~ShaderBank()
{
}

void ShaderBank::addShader(VertexStruct vStruct, Shader::Ptr shader)
{
	if (shader != nullptr && shader->isValid() && shader->isLoaded())
	{
		ShaderElement s;
		s.vStruct = vStruct;
		s.shader = shader;
		mShaders.push_back(s);
	}
}

Shader::Ptr ShaderBank::getShader(VertexStruct vStruct, const std::string& identifier)
{
	return getShader(vStruct, StringId::hash(identifier));
}

Shader::Ptr ShaderBank::getShader(VertexStruct vStruct, U32 identifier)
{
	for (U32 i = 0; i < mShaders.size(); i++)
	{
		if (mShaders[i].vStruct == vStruct && mShaders[i].shader != nullptr && mShaders[i].shader.getId() == identifier)
		{
			return mShaders[i].shader;
		}
	}
	return nullptr;
}

void ShaderBank::clear()
{
	mShaders.clear();
}

} // namespace nu