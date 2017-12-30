#include "DebugDraw.hpp"

#include "Renderer.hpp"

#include "../Math/Noise.hpp"

namespace nu
{

DebugDraw* DebugDraw::sSingleton = nullptr;

DebugDraw::DebugDraw()
	: mShader()
{
	if (sSingleton == nullptr)
	{
		sSingleton = this;
	}

	std::string vertexShader = "#version 330 core\n"
		"layout(location = 0) in vec3 vPos;\n"
		"layout(location = 1) in vec4 vCol;\n"
		"uniform mat4 VP;\n"
		"out vec4 Color;\n"
		"void main()\n"
		"{\n"
			"Color = vCol;\n"
			"gl_Position = VP * vec4(vPos, 1.0);\n"
		"}";

	std::string fragmentShader = "#version 330 core\n"
		"in vec4 Color;\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
			"FragColor = vec4(Color);\n"
		"}";

	mShader.load(ShaderLoader::fromSource(vertexShader, fragmentShader));
}

DebugDraw::~DebugDraw()
{
}

void DebugDraw::line(const Vector3f& p1, const Vector3f& p2, const LinearColor& color)
{
	addVertex(p1, color);
	addVertex(p2, color);
}

void DebugDraw::box(const Vector3f& boxCenter, const Vector3f& boxHalfSize, const LinearColor& color)
{
	mVertices.emplace_back(Vector3f(boxCenter.x - boxHalfSize.x, boxCenter.y - boxHalfSize.y, boxCenter.z - boxHalfSize.z), color); // 0
	mVertices.emplace_back(Vector3f(boxCenter.x + boxHalfSize.x, boxCenter.y - boxHalfSize.y, boxCenter.z - boxHalfSize.z), color); // 1
	mVertices.emplace_back(Vector3f(boxCenter.x - boxHalfSize.x, boxCenter.y - boxHalfSize.y, boxCenter.z - boxHalfSize.z), color); // 0
	mVertices.emplace_back(Vector3f(boxCenter.x - boxHalfSize.x, boxCenter.y + boxHalfSize.y, boxCenter.z - boxHalfSize.z), color); // 2
	mVertices.emplace_back(Vector3f(boxCenter.x - boxHalfSize.x, boxCenter.y - boxHalfSize.y, boxCenter.z - boxHalfSize.z), color); // 0
	mVertices.emplace_back(Vector3f(boxCenter.x - boxHalfSize.x, boxCenter.y - boxHalfSize.y, boxCenter.z + boxHalfSize.z), color); // 3
	mVertices.emplace_back(Vector3f(boxCenter.x + boxHalfSize.x, boxCenter.y - boxHalfSize.y, boxCenter.z + boxHalfSize.z), color); // 4
	mVertices.emplace_back(Vector3f(boxCenter.x + boxHalfSize.x, boxCenter.y - boxHalfSize.y, boxCenter.z - boxHalfSize.z), color); // 1
	mVertices.emplace_back(Vector3f(boxCenter.x + boxHalfSize.x, boxCenter.y - boxHalfSize.y, boxCenter.z + boxHalfSize.z), color); // 4
	mVertices.emplace_back(Vector3f(boxCenter.x - boxHalfSize.x, boxCenter.y - boxHalfSize.y, boxCenter.z + boxHalfSize.z), color); // 3
	mVertices.emplace_back(Vector3f(boxCenter.x + boxHalfSize.x, boxCenter.y + boxHalfSize.y, boxCenter.z + boxHalfSize.z), color); // 5
	mVertices.emplace_back(Vector3f(boxCenter.x + boxHalfSize.x, boxCenter.y - boxHalfSize.y, boxCenter.z + boxHalfSize.z), color); // 4
	mVertices.emplace_back(Vector3f(boxCenter.x + boxHalfSize.x, boxCenter.y + boxHalfSize.y, boxCenter.z + boxHalfSize.z), color); // 5
	mVertices.emplace_back(Vector3f(boxCenter.x + boxHalfSize.x, boxCenter.y + boxHalfSize.y, boxCenter.z - boxHalfSize.z), color); // 6
	mVertices.emplace_back(Vector3f(boxCenter.x + boxHalfSize.x, boxCenter.y + boxHalfSize.y, boxCenter.z + boxHalfSize.z), color); // 5
	mVertices.emplace_back(Vector3f(boxCenter.x - boxHalfSize.x, boxCenter.y + boxHalfSize.y, boxCenter.z + boxHalfSize.z), color); // 7
	mVertices.emplace_back(Vector3f(boxCenter.x + boxHalfSize.x, boxCenter.y + boxHalfSize.y, boxCenter.z - boxHalfSize.z), color); // 6
	mVertices.emplace_back(Vector3f(boxCenter.x - boxHalfSize.x, boxCenter.y + boxHalfSize.y, boxCenter.z - boxHalfSize.z), color); // 2
	mVertices.emplace_back(Vector3f(boxCenter.x + boxHalfSize.x, boxCenter.y + boxHalfSize.y, boxCenter.z - boxHalfSize.z), color); // 6
	mVertices.emplace_back(Vector3f(boxCenter.x + boxHalfSize.x, boxCenter.y - boxHalfSize.y, boxCenter.z - boxHalfSize.z), color); // 1
	mVertices.emplace_back(Vector3f(boxCenter.x - boxHalfSize.x, boxCenter.y + boxHalfSize.y, boxCenter.z + boxHalfSize.z), color); // 7
	mVertices.emplace_back(Vector3f(boxCenter.x - boxHalfSize.x, boxCenter.y + boxHalfSize.y, boxCenter.z - boxHalfSize.z), color); // 2
	mVertices.emplace_back(Vector3f(boxCenter.x - boxHalfSize.x, boxCenter.y + boxHalfSize.y, boxCenter.z + boxHalfSize.z), color); // 7
	mVertices.emplace_back(Vector3f(boxCenter.x - boxHalfSize.x, boxCenter.y - boxHalfSize.y, boxCenter.z + boxHalfSize.z), color); // 3
}

void DebugDraw::aabb(const Vector3f& p1, const Vector3f& p2, const LinearColor& color)
{
	box(p1, (p2 - p1) * 0.5f, color);
}

void DebugDraw::cross(const Vector3f& center)
{
	mVertices.emplace_back(Vector3f(center.x, center.y, center.z), LinearColor::Red);
	mVertices.emplace_back(Vector3f(center.x + 1.0f, center.y, center.z), LinearColor::Red);
	mVertices.emplace_back(Vector3f(center.x, center.y, center.z), LinearColor::Green);
	mVertices.emplace_back(Vector3f(center.x, center.y + 1.0f, center.z), LinearColor::Green);
	mVertices.emplace_back(Vector3f(center.x, center.y, center.z), LinearColor::Blue);
	mVertices.emplace_back(Vector3f(center.x, center.y, center.z + 1.0f), LinearColor::Blue);
}

void DebugDraw::transform(const Matrix4f& transform)
{
	/*
	Vector3f center = transform * Vector3f();
	Vector3f uX = center + transform * Vector3f(1.0f, 0.0f, 0.0f);
	Vector3f uY = center + transform * Vector3f(0.0f, 1.0f, 0.0f);
	Vector3f uZ = center + transform * Vector3f(0.0f, 0.0f, 1.0f);
	mVertices.emplace_back(center, LinearColor::Red);
	mVertices.emplace_back(uX, LinearColor::Red);
	mVertices.emplace_back(center, LinearColor::Green);
	mVertices.emplace_back(uY, LinearColor::Green);
	mVertices.emplace_back(center, LinearColor::Blue);
	mVertices.emplace_back(uZ, LinearColor::Blue);
	*/
}

void DebugDraw::transform(const Quaternionf & transform)
{
	this->transform(transform.toMatrix4());
}

void DebugDraw::point(const Vector3f& p, const LinearColor& color)
{
	box(p, Vector3f(0.01f), color);
}

void DebugDraw::xzGrid(F32 begin, F32 end, F32 y, F32 interval, const LinearColor& color)
{
	for (F32 d = begin; d < end; d += interval)
	{
		mVertices.emplace_back(Vector3f(d, y, begin), color);
		mVertices.emplace_back(Vector3f(d, y, end), color);
		mVertices.emplace_back(Vector3f(begin, y, d), color);
		mVertices.emplace_back(Vector3f(end, y, d), color);
	}
	mVertices.emplace_back(Vector3f(end, y, begin), color);
	mVertices.emplace_back(Vector3f(end, y, end), color);
	mVertices.emplace_back(Vector3f(begin, y, end), color);
	mVertices.emplace_back(Vector3f(end, y, end), color);
}

void DebugDraw::sphere(const Vector3f& center, F32 radius, const LinearColor& color)
{
	// TODO : Sphere
}

void DebugDraw::circle(const Vector3f& center, const Vector3f& normal, F32 radius, const LinearColor& color)
{
	Vector3f n = normal.normalized();
	Vector3f r(1, 0, 0); // random vector
	if (n == r)
	{
		r.set(0, 1, 0);
	}
	Vector3f o = r.crossProduct(n);

	U32 points = 30;
	F32 dt = 360.0f / points;

	Quaternionf q(dt, n);
	for (U32 i = 0; i < points; i++)
	{
		addVertex(o * radius + center, color);
		o = q * o;
		addVertex(o * radius + center, color);
	}
}

void DebugDraw::plane(const Vector3f& center, const Vector3f& normal, const Vector2f& halfSize, const LinearColor& color)
{
	// TODO : Plane
}

void DebugDraw::cone(const Vector3f& origin, const Vector3f& dir, F32 length, F32 radius, const LinearColor& color)
{
	Vector3f n = dir.normalized();
	Vector3f r(1, 0, 0); // random vector
	if (n == r)
	{
		r.set(0, 1, 0);
	}
	Vector3f o = r.crossProduct(n);

	Vector3f center = origin + dir * length;

	U32 points = 30;
	F32 dt = 360.0f / points;

	Quaternionf q(dt, n);
	for (U32 i = 0; i < points; i++)
	{
		addVertex(o * radius + center, color);
		line(origin, o * radius + center, color);
		o = q * o;
		addVertex(o * radius + center, color);
	}
}

void DebugDraw::noise(F32 begin, F32 end, F32 gain, U32 oct, F32 lac)
{
	nu::Noise noiseHeight(13678);
	noiseHeight.setGain(gain);
	noiseHeight.setOctaves(oct);
	noiseHeight.setLacunarity(lac);

	nu::LinearColor c = nu::LinearColor::White;
	Vector3f p;

	F32 d = 1.0f;

	F32 min = 600.f;
	F32 max = -600.f;

	for (F32 d1 = begin; d1 < end; d1 += d)
	{
		for (F32 d2 = begin; d2 < end; d2 += d)
		{
			p.set(d1, 0.0f, d2);
			p.y = noiseHeight.getNoise(p.x, p.z) * 1.0f;
			addVertex(p, c * p.y);

			p.set(d1 + d, 0.0f, d2);
			p.y = noiseHeight.getNoise(p.x, p.z) * 1.0f;
			addVertex(p, c * p.y);

			mVertices.push_back(mVertices[mVertices.size() - 2]);

			p.set(d1, 0.0f, d2 + d);
			p.y = noiseHeight.getNoise(p.x, p.z) * 1.0f;
			addVertex(p, c * p.y);
		}
	}

	mVertices.emplace_back(Vector3f(end, 0.0f, begin), c);
	mVertices.emplace_back(Vector3f(end, 0.0f, end), c);
	mVertices.emplace_back(Vector3f(begin, 0.0f, end), c);
	mVertices.emplace_back(Vector3f(end, 0.0f, end), c);

}

void DebugDraw::render(const Matrix4f& viewMatrix, const Matrix4f& projectionMatrix)
{
	mShader.bind();
	mShader.setUniform("VP", projectionMatrix * viewMatrix);

	mBuffer.set(mVertices);
	mBuffer.bind();

	Renderer::instance().drawArrays(Primitive::Lines, mVertices.size());

	mVertices.clear();
}

bool DebugDraw::instantiated()
{
	return sSingleton != nullptr;
}

DebugDraw& DebugDraw::instance()
{
	assert(sSingleton != nullptr);
	return *sSingleton;
}

void DebugDraw::addVertex(F32 x, F32 y, F32 z, const LinearColor& c)
{
	mVertices.emplace_back(Vector3f(x, y, z), c);
}

void DebugDraw::addVertex(const Vector3f & p, const LinearColor& c)
{
	mVertices.emplace_back(p, c);
}

} // namespace nu