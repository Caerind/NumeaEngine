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
	nu::LogManager::initialize();

	nu::FileLogger file;
	file.setFilename("log.txt");

	nu::ResourceManager manager;

	nu::Window window; 
	window.create(800, 600, "test");

	nu::ImGuiWrapper::init(window);

	nu::Renderer renderer;
	renderer.getCamera().perspective(60.0f, window.getSizeRatio(), 0.1f, 100.0f);
	renderer.getCamera().lookAt(nu::Vector3f(-2.0f, 1.5f, -2.0f), nu::Vector3f(0, 0, 1), nu::Vector3f(0, 1, 0));

	nu::Texture::Ptr texture1 = manager.get("texture1", nu::TextureLoader::fromFile("suzanne.png"));
	nu::Texture::Ptr texture2 = manager.get("texture2", nu::TextureLoader::fromFile("meganne.png"));
	nu::Shader::Ptr shader = manager.get("shader", nu::ShaderLoader::fromFile("shader.vert", "shader.frag"));
	nu::Mesh::Ptr mesh = manager.get("mesh", nu::MeshLoader::fromFile("suzanne.obj"));
	nu::Mesh::Ptr mesh2 = manager.get("mesh2", nu::MeshLoader::fromFile("sheep.obj"));

	nu::DebugDraw debug;

	nu::Vector3f position = renderer.getCamera().getPosition();
	nu::Vector3f direction = nu::Vector3f(0, 0, 1);
	nu::Vector3f right = direction.crossProduct(nu::Vector3f(0, 1, 0));

	nu::LinearColor clearColor(nu::LinearColor::LightBlue);
	nu::LinearColor ambientColor(0.2f, 0.3f, 0.3f, 1.0f);
	nu::LinearColor lightColor(1.0f, 0.0f, 0.0f, 1.0f);
	F32 shininess = 5.0f;
	F32 strength = 1.0f;
	F32 constantAttenuation = 0.5f;
	F32 linearAttenuation = 0.5f;
	F32 quadraticAttenuation = 0.5f;

	nu::Matrix4f model1 = nu::Matrix4f::translation(nu::Vector3f(0, 1, 0)) * nu::Matrix4f::scale(nu::Vector3f(0.7f, 0.7f, 0.7f));
	nu::Matrix4f model2 = nu::Matrix4f::translation(nu::Vector3f(5, 1, 5));

	F32 lac = 2.0f;
	F32 gain = 0.5f;
	I32 oct = 3;

	nu::Clock clock;
	while (window.isOpen())
	{
		// Time
		nu::Time dt = clock.restart();

		// Events
		window.pollEvents();

		// Inputs
		if (window.isKeyPressed(GLFW_KEY_ESCAPE))
		{
			window.close();
		}
		if (window.isKeyPressed(GLFW_KEY_DOWN))
		{
			position -= direction * 3.0f * dt.asSeconds();
		}
		if (window.isKeyPressed(GLFW_KEY_UP))
		{
			position += direction * 3.0f * dt.asSeconds();
		}
		if (window.isKeyPressed(GLFW_KEY_RIGHT))
		{
			direction = nu::Matrix4f(nu::Matrix3f::rotationY(-90.0f * dt.asSeconds())) * direction;
		}
		if (window.isKeyPressed(GLFW_KEY_LEFT))
		{
			direction = nu::Matrix4f(nu::Matrix3f::rotationY(90.0f * dt.asSeconds())) * direction;
		}

		// Update vectors
		right = direction.crossProduct(nu::Vector3f(0, 1, 0));
		renderer.getCamera().setPosition(position);
		renderer.getCamera().setTarget(position + direction);


		debug.point(nu::Vector3f());
		debug.point(nu::Vector3f(2, 2, 2));
		debug.point(nu::Vector3f(-2, 2, -2));
		debug.point(nu::Vector3f(2, 2, -2));
		debug.point(nu::Vector3f(-2, 2, 2));
		//debug.xzGrid(-10.0f, 10.0f, 0.0f, 1.0f, nu::Color::Green);
		debug.noise(-10.0f, 10.0f, gain, (U32)oct, lac);
		debug.box(nu::Vector3f(5, 2, -5), nu::Vector3f(1, 1, 1), nu::Color::Red);
		debug.cross(nu::Vector3f());
		debug.transform(model1);
		debug.sphere(nu::Vector3f(), 4, nu::Color::Yellow);
		debug.circle(nu::Vector3f(3, 3, 3), nu::Vector3f(1, 0, 0), 2, nu::Color::Red);
		debug.circle(nu::Vector3f(3, 3, 3), nu::Vector3f(0, 1, 0), 2, nu::Color::Green);
		debug.circle(nu::Vector3f(3, 3, 3), nu::Vector3f(0, 0, 1), 2, nu::Color::Blue);
		debug.cone(nu::Vector3f(4, 4, 0), nu::Vector3f(0, -1, 0), 4, 2, nu::Color::Yellow);

		// ImGui config
		nu::ImGuiWrapper::newFrame();
		ImGuiWrapper_Begin();
		ImGui::Begin("Debug");
		ImGui::SliderInt("Octaves", &oct, 1, 7);
		ImGui::SliderFloat("Gain", &gain, 0.0f, 1.0f);
		ImGui::SliderFloat("Lacunarity", &lac, 0.0f, 5.0f);
		ImGui::ColorEdit3("Clear color", (float*)&clearColor);
		ImGui::ColorEdit3("Ambient color", (float*)&ambientColor);
		ImGui::ColorEdit3("Light color", (float*)&lightColor);
		ImGui::SliderFloat("Shininess", &shininess, 0.0f, 10.0f);
		ImGui::SliderFloat("Strength", &strength, 0.0f, 10.0f);
		ImGui::SliderFloat("Catt", &constantAttenuation, -5.0f, 10.0f);
		ImGui::SliderFloat("Latt", &linearAttenuation, -5.0f, 10.0f);
		ImGui::SliderFloat("Qatt", &quadraticAttenuation, -5.0f, 10.0f);
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();
		ImGuiWrapper_End();
		nu::ImGuiWrapper::endFrame();

		// Model self rotation
		model1 *= nu::Matrix3f::rotationY(30.0f * dt.asSeconds());

		// Matrices
		nu::Matrix4f v = renderer.getCamera().getViewMatrix();
		nu::Matrix4f p = renderer.getCamera().getProjectionMatrix();
		nu::Matrix4f mv1 = v * model1;
		nu::Matrix4f mvp1 = p * mv1;
		nu::Matrix3f n1 = mv1.toMatrix3();
		nu::Matrix4f mv2 = v * model2;
		nu::Matrix4f mvp2 = p * mv2;
		nu::Matrix3f n2 = mv2.toMatrix3();

		nu::Vector3f viewPosition = v * position;
		nu::Vector3f viewDirection = nu::Vector3f() - viewPosition;


		// Render
		renderer.begin(clearColor);

		shader->bind();
		shader->setUniform("Texture", nu::Shader::CurrentTexture);
		shader->setUniform("Ambient", ambientColor);
		shader->setUniform("LightColor", lightColor);
		shader->setUniform("Shininess", shininess);
		shader->setUniform("Strength", strength);
		shader->setUniform("ConstantAttenuation", constantAttenuation);
		shader->setUniform("LinearAttenuation", linearAttenuation);
		shader->setUniform("QuadraticAttenuation", quadraticAttenuation);
		shader->setUniform("LightPosition", viewPosition);
		shader->setUniform("EyeDirection", viewDirection);

		// RENDER MODEL 1
		shader->bind();
		shader->setUniform("MV", mv1);
		shader->setUniform("MVP", mvp1);
		shader->setUniform("N", n1);
		texture1->bind();
		mesh->bind();
		mesh->draw();

		debug.render(renderer.getCamera().getViewMatrix(), renderer.getCamera().getProjectionMatrix());

		// RENDER MODEL 2
		shader->bind();
		shader->setUniform("MV", mv2);
		shader->setUniform("MVP", mvp2);
		shader->setUniform("N", n2);
		texture2->bind();
		mesh2->bind();
		mesh2->draw();


		renderer.end();
		nu::ImGuiWrapper::render();
		window.display();
	}

	return 0;
}