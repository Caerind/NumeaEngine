#include <cstdio>
#include <iostream>

#include "TestSystem.hpp"
#include "TestMath.hpp"
#include "TestApplication.hpp"
#include "TestGraphics.hpp"

void test()
{
	RUN_TEST(System);
	RUN_TEST(Math);
	RUN_TEST(Application);
	RUN_TEST(Graphics);
}

int main()
{
	test();

	nu::LogManager::initialize();

	nu::ResourceManager manager;

	nu::Window window;
	window.create(800, 600, "test");

	nu::Renderer renderer;
	renderer.getCamera().perspective(60.0f, window.getSizeRatio(), 0.1f, 100.0f);
	renderer.getCamera().lookAt(nu::Vector3f(-2.0f, 1.0f, -2.0f), nu::Vector3f(0, 0, 0), nu::Vector3f(0, 1, 0));

	nu::ImGuiWrapper::init(window);

	nu::Texture::Ptr texture = manager.get("texture", nu::TextureLoader::fromFile("suzanne.png"));
	nu::Shader::Ptr shader = manager.get("shader", nu::ShaderLoader::fromFile("shader.vert", "shader.frag"));
	nu::Mesh::Ptr mesh = manager.get("mesh", nu::MeshLoader::fromFile("suzanne.obj"));

	assert(texture);
	assert(shader);
	assert(mesh);

	assert(texture->isLoaded());
	assert(shader->isLoaded());
	assert(mesh->isLoaded());

	assert(texture->isValid());
	assert(shader->isValid());

	nu::Matrix4f m = nu::Matrix4f::identity();
	nu::Matrix4f v = renderer.getCamera().getViewMatrix();
	nu::Matrix4f p = renderer.getCamera().getProjectionMatrix();
	nu::Matrix4f mv = v * m;
	nu::Matrix4f mvp = p * mv;

	nu::Matrix3f n = mv.toMatrix3();

	shader->setUniform("MV", mv);
	shader->setUniform("N", n);
	shader->setUniform("MVP", mvp); 
	
	printf("V   I\n");
	for (int i = 0; i < 9; i++)
	{
		int r = i % 3;
		int c = i / 3;
		printf("%d %f %f\n", i, n.m[c][r], v.m[c][r]);
	}

	while (window.isOpen())
	{
		window.pollEvents();
		if (window.isKeyPressed(GLFW_KEY_ESCAPE))
		{
			window.close();
		}

		nu::ImGuiWrapper::newFrame();
		ImGuiWrapper_Begin();
		ImGui::SetNextWindowSize(ImVec2(100, 100), ImGuiSetCond_FirstUseEver);
		ImGui::Begin("Window");
		ImGui::Text("Hello World !");
		ImGui::End();
		ImGuiWrapper_End();
		nu::ImGuiWrapper::endFrame();

		window.clear();
		renderer.begin(nu::Color::LightBlue);

		shader->bind();
		texture->bind();

		shader->setUniform("Texture", nu::Shader::CurrentTexture);

		shader->setUniform("Ambient", nu::LinearColor(0.2f, 0.3f, 0.3f));
		shader->setUniform("LightColor", nu::LinearColor::Red);
		shader->setUniform("Shininess", 5.0f);
		shader->setUniform("Strength", 1.0f);
		shader->setUniform("ConstantAttenuation", 0.5f);
		shader->setUniform("LinearAttenuation", 0.5f);
		shader->setUniform("QuadraticAttenuation", 0.5f);

		shader->setUniform("LightPosition", nu::Vector3f::zero());
		shader->setUniform("EyeDirection", nu::Vector3f(0, -1, 0));

		mesh->bind();

		renderer.end();
		nu::ImGuiWrapper::render();
		window.display();
	}

	return 0;
}