#include "Shader.hpp"

#include <fstream>
#include <sstream>

namespace nu
{

Shader::Shader()
	: mProgram(0)
	, mCurrentTexture(-1)
{
	mProgram = glCreateProgram();
}

Shader::~Shader()
{
	glDeleteProgram(mProgram);
}

bool Shader::load(const Loader<Shader>& loader)
{
	mLoaded = loader.load(*this);
	return mLoaded;
}

void Shader::bind() const
{
	glUseProgram(mProgram);
	auto itr = mTextures.begin();
	for (U32 i = 1; i <= mTextures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glUniform1i(itr->first, i);
		itr->second->bind();
		++itr;
	}
	glActiveTexture(GL_TEXTURE0);
	if (mCurrentTexture != -1)
	{
		glUniform1i(mCurrentTexture, 0);
	}
}

bool Shader::isValid() const
{
	return glIsProgram(mProgram) == GL_TRUE;
}

void Shader::setUniform(const std::string& name, F32 x)
{
	I32 location = getUniformLocation(name);
	if (location != -1)
	{
		glUniform1f(location, x);
	}
}

void Shader::setUniform(const std::string& name, F32 x, F32 y)
{
	I32 location = getUniformLocation(name);
	if (location != -1)
	{
		glUniform2f(location, x, y);
	}
}

void Shader::setUniform(const std::string& name, F32 x, F32 y, F32 z)
{
	I32 location = getUniformLocation(name);
	if (location != -1)
	{
		glUniform3f(location, x, y, z);
	}
}

void Shader::setUniform(const std::string& name, F32 x, F32 y, F32 z, F32 w)
{
	I32 location = getUniformLocation(name);
	if (location != -1)
	{
		glUniform4f(location, x, y, z, w);
	}
}

void Shader::setUniform(const std::string& name, const Vector2f& v)
{
	I32 location = getUniformLocation(name);
	if (location != -1)
	{
		glUniform2fv(location, 1, &v[0]);
	}
}

void Shader::setUniform(const std::string& name, const Vector3f& v)
{
	I32 location = getUniformLocation(name);
	if (location != -1)
	{
		glUniform3fv(location, 1, &v[0]);
	}
}

void Shader::setUniform(const std::string& name, const Vector4f& v)
{
	I32 location = getUniformLocation(name);
	if (location != -1)
	{
		glUniform4fv(location, 1, &v[0]);
	}
}

void Shader::setUniform(const std::string& name, const Matrix3f& m)
{
	I32 location = getUniformLocation(name);
	if (location != -1)
	{
		glUniformMatrix3fv(location, 1, GL_FALSE, &m.data[0]);
	}
}

void Shader::setUniform(const std::string& name, const Matrix4f& m)
{
	I32 location = getUniformLocation(name);
	if (location != -1)
	{
		glUniformMatrix4fv(location, 1, GL_FALSE, &m.data[0]);
	}
}

void Shader::setUniform(const std::string& name, const Color& color)
{
	setUniform(name, LinearColor(color));
}

void Shader::setUniform(const std::string& name, const LinearColor& color)
{
	I32 location = getUniformLocation(name);
	if (location != -1)
	{
		// TODO : Color as vector4 is faster ?
		glUniform4f(location, color.r, color.g, color.b, color.a);
	}
}

void Shader::setUniform(const std::string& name, const Texture& texture)
{
	I32 location = getUniformLocation(name);
	if (location != -1)
	{
		auto itr = mTextures.find(location);
		if (itr == mTextures.end())
		{
			mTextures[location] = &texture;
		}
		else
		{
			itr->second = &texture;
		}
	}
}

void Shader::setUniform(const std::string& name, SpecialUniforms type)
{
	switch (type)
	{
		case CurrentTexture: mCurrentTexture = getUniformLocation(name); break;
	}
}

I32 Shader::getAttribLocation(const std::string& name) const
{
	return glGetAttribLocation(mProgram, name.c_str());
}

U32 Shader::getIndex() const
{
	return mProgram;
}

void Shader::reset()
{
	mCurrentTexture = -1;
	mUniforms.clear();
	mTextures.clear();
}

U32 Shader::compileShader(const std::string& shader, ShaderType type)
{
	U32 shaderIndex;
	switch (type)
	{
		case VertexShader: shaderIndex = glCreateShader(GL_VERTEX_SHADER); break;
		case FragmentShader: shaderIndex = glCreateShader(GL_FRAGMENT_SHADER); break;
		case GeometryShader: shaderIndex = glCreateShader(GL_GEOMETRY_SHADER); break;
		default: shaderIndex = 0; break;
	}
	if (glIsShader(shaderIndex))
	{
		const char* source = shader.c_str();
		glShaderSource(shaderIndex, 1, &source, nullptr);
		glCompileShader(shaderIndex);
		I32 compiled;
		glGetShaderiv(shaderIndex, GL_COMPILE_STATUS, &compiled);
		if (!compiled)
		{
			I32 len;
			glGetShaderiv(shaderIndex, GL_INFO_LOG_LENGTH, &len);
			GLchar* log = new GLchar[len + 1];
			glGetShaderInfoLog(shaderIndex, len, &len, log);
			switch (type)
			{
				case VertexShader: LogError(LogChannel::Graphics, 4, "Vertex shader compilation failed : %s\n", log); break;
				case FragmentShader: LogError(LogChannel::Graphics, 4, "Fragment shader compilation failed : %s\n", log); break;
				case GeometryShader: LogError(LogChannel::Graphics, 4, "Geometry shader compilation failed : %s\n", log); break;
				default: LogError(LogChannel::Graphics, 4, "Unknown shader compilation failed : %s\n", log); break;
			}
			
			delete[] log;
			return 0;
		}
		return shaderIndex;
	}
	else
	{
		return 0;
	}
}

I32 Shader::getUniformLocation(const std::string& name)
{
	auto it = mUniforms.find(name);
	if (it != mUniforms.end())
	{
		return it->second;
	}
	else
	{
		I32 location = glGetUniformLocation(mProgram, name.c_str());
		mUniforms.insert(std::make_pair(name, location));
		if (location == -1)
		{
			LogError(LogChannel::Graphics, 3, "Uniform \"%s\" not found in shader\n", name.c_str());
		}
		return location;
	}
}

Loader<Shader> ShaderLoader::fromFile(const std::string& vs, const std::string& fs)
{
	return Loader<Shader>([=](Shader& shader)
	{
		bool error = false;

		std::ifstream vsFile(vs, std::ios::in | std::ios::binary);
		if (!vsFile)
		{
			fprintf(stderr, "Failed to open vertex shader : %s\n", vs.c_str());
			error = true;
		}
		std::stringstream vsBuffer;
		vsBuffer << vsFile.rdbuf();

		std::ifstream fsFile(fs, std::ios::in | std::ios::binary);
		if (!fsFile)
		{
			fprintf(stderr, "Failed to open fragment shader : %s\n", fs.c_str());
			error = true;
		}
		std::stringstream fsBuffer;
		fsBuffer << fsFile.rdbuf();

		if (error)
		{
			return false;
		}

		U32 program = shader.getIndex();
		shader.reset();

		U32 vertex = Shader::compileShader(vsBuffer.str(), Shader::VertexShader);
		U32 fragment = Shader::compileShader(fsBuffer.str(), Shader::FragmentShader);
		if (vertex == 0 || fragment == 0)
		{
			return false;
		}

		glAttachShader(program, vertex);
		glAttachShader(program, fragment);
		glLinkProgram(program);

		I32 linked;
		glGetProgramiv(program, GL_LINK_STATUS, &linked);
		if (!linked)
		{
			I32 len;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &len);
			GLchar* log = new GLchar[len + 1];
			glGetProgramInfoLog(program, len, &len, log);
			LogError(LogChannel::Graphics, 4, "Program linking failed: %s\n", log);
			delete[] log;
			return false;
		}

		glDeleteShader(vertex);
		glDeleteShader(fragment);

		return shader.isValid();
	});
}

Loader<Shader> ShaderLoader::fromSource(const std::string& vs, const std::string& fs)
{
	return Loader<Shader>([=](Shader& shader)
	{
		U32 program = shader.getIndex();
		if (glIsProgram(program))
		{
			return false;
		}
		shader.reset();

		U32 vertex = Shader::compileShader(vs, Shader::VertexShader);
		U32 fragment = Shader::compileShader(fs, Shader::FragmentShader);
		if (vertex == 0 || fragment == 0)
		{
			return false;
		}

		glAttachShader(program, vertex);
		glAttachShader(program, fragment);
		glLinkProgram(program);

		I32 linked;
		glGetProgramiv(program, GL_LINK_STATUS, &linked);
		if (!linked)
		{
			I32 len;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &len);
			GLchar* log = new GLchar[len + 1];
			glGetProgramInfoLog(program, len, &len, log);
			LogError(LogChannel::Graphics, 4, "Program linking failed: %s\n", log);
			delete[] log;
			return false;
		}

		glDeleteShader(vertex);
		glDeleteShader(fragment);

		return true;
	});
}

} // namespace nu