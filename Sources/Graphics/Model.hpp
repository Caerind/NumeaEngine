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

		void setTexture(const Texture* texture);
		void setMesh(const Mesh* mesh);

		const Texture* getTexture() const;
		const Mesh* getMesh() const;

		void draw();

	private:
		const Texture* mTexture;
		const Mesh* mMesh;
};

} // namespace nu

#endif // NU_MODEL_HPP