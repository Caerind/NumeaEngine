#ifndef NU_TESTGRAPHICS_HPP
#define NU_TESTGRAPHICS_HPP

#include "../Sources/Graphics/Color.hpp"
#include "../Sources/Graphics/LinearColor.hpp"
#include "../Sources/Graphics/Image.hpp"
#include "../Sources/Graphics/Camera.hpp"
#include "../Sources/Graphics/Texture.hpp"
#include "../Sources/Graphics/Shader.hpp"
#include "../Sources/Graphics/Mesh.hpp"
#include "../Sources/Graphics/VertexArray.hpp"
#include "../Sources/Graphics/DebugDraw.hpp"
#include "../Sources/Graphics/Node.hpp"
#include "../Sources/Graphics/Model.hpp"

#include "../Sources/System/UnitTest.hpp"

BEGIN_TEST(Graphics)
{

TEST("Color")
{
	nu::Color color;

}

TEST("LinearColor")
{
	nu::LinearColor color;

}

TEST("Image")
{
	nu::LinearColor red = nu::LinearColor::Red;

	nu::Image image;
	CHECK(image.load(nu::ImageLoader::fromFile("testnoise.png")));
	for (U32 i = 0; i < image.getSize().x; i++)
	{
		for (U32 j = 0; j < image.getSize().y; j++)
		{
			image.setPixel(i, j, nu::Color(red * nu::LinearColor(image.getPixel(i, j))));
		}
	}
	CHECK(image.save(nu::ImageLoader::toFile("testfire.png")));
}

}
END_TEST;

#endif // NU_TESTGRAPHICS_HPP
