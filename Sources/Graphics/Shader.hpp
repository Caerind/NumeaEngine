#ifndef NU_SHADER_HPP
#define NU_SHADER_HPP

#include <map>

#include "Color.hpp"
#include "LinearColor.hpp"
#include "Texture.hpp"
#include "../Math/Matrix4.hpp"
#include "../Application/ResourcePtr.hpp"

namespace nu
{

class Shader : public Resource<Shader>
{
	public:
		enum SpecialUniforms
		{
			CurrentTexture
		};

		enum ShaderType
		{
			VertexShader,
			FragmentShader,
			GeometryShader
		};

	public:
		Shader();
		~Shader();

		bool load(const Loader<Shader>& loader);

		void bind() const;
		bool isValid() const;

		void setUniform(const std::string& name, F32 x);
		void setUniform(const std::string& name, F32 x, F32 y);
		void setUniform(const std::string& name, F32 x, F32 y, F32 z);
		void setUniform(const std::string& name, F32 x, F32 y, F32 z, F32 w);
		void setUniform(const std::string& name, const Vector2f& v);
		void setUniform(const std::string& name, const Vector3f& v);
		void setUniform(const std::string& name, const Vector4f& v);
		void setUniform(const std::string& name, const Matrix3f& m);
		void setUniform(const std::string& name, const Matrix4f& m);
		void setUniform(const std::string& name, const Color& color);
		void setUniform(const std::string& name, const LinearColor& color);
		void setUniform(const std::string& name, const Texture& texture);
		void setUniform(const std::string& name, SpecialUniforms type);

		I32 getAttribLocation(const std::string& name) const;

		U32 getIndex() const;

		void reset();

		static U32 compileShader(const std::string& shader, ShaderType type);

	private:
		I32 getUniformLocation(const std::string& name);

	private:
		U32 mProgram;
		I32 mCurrentTexture;
		std::map<std::string, I32> mUniforms;
		std::map<I32, const Texture*> mTextures;
};

class ShaderLoader
{
	public:
		static Loader<Shader> fromFile(const std::string& vs, const std::string& fs);
		static Loader<Shader> fromSource(const std::string& vs, const std::string& fs);
};

} // namespace nu

#endif // NU_SHADER_HPP