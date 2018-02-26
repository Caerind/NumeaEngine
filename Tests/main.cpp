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
	//test();

	nu::LogManager::initialize();

	nu::FileLogger file;
	file.setFilename("log.txt");

	nu::ResourceManager manager;

	nu::Window window; 
	window.create(800, 600, "test");

	nu::ImGuiWrapper::init(window);

	nu::Renderer renderer;
	renderer.getCamera().perspective(60.0f, window.getSizeRatio(), 0.1f, 30.0f);
	renderer.getCamera().lookAt(nu::Vector3f(-2.0f, 1.5f, -2.0f), nu::Vector3f(0, 0, 1), nu::Vector3f(0, 1, 0));

	nu::Texture::Ptr textureCube = manager.get("textureCube", nu::TextureLoader::fromFile("testCube.png"));
	nu::Texture::Ptr textureSheep = manager.get("textureSheep", nu::TextureLoader::fromFile("testSheep.png"));
	nu::Shader::Ptr shader = manager.get("shader", nu::ShaderLoader::fromFile("shader.vert", "shader.frag"));
	nu::Mesh::Ptr meshCube = manager.get("meshCube", nu::MeshLoader::fromFile("testCube.obj"));
	nu::Mesh::Ptr meshSheep = manager.get("meshSheep", nu::MeshLoader::fromFile("testSheep.obj"));

	nu::DebugDraw debug;

	nu::Vector3f position = renderer.getCamera().getPosition();
	nu::Vector3f direction = nu::Vector3f::forward;
	nu::Vector3f right = direction.crossProduct(nu::Vector3f::up);
	renderer.getCamera().setTarget(position + direction);

	nu::Model mCube;
	mCube.setShader(shader);
	mCube.setTexture(textureCube);
	mCube.setMesh(meshCube);
	mCube.setPosition(0, 1, 4);
	mCube.setScale(0.7f);
	mCube.setUniformBinding(nu::Model::ModelViewMatrix, "MV");
	mCube.setUniformBinding(nu::Model::ModelViewProjectionMatrix, "MVP");
	mCube.setUniformBinding(nu::Model::NormalMatrix, "N");

	nu::Model mSheep;
	mSheep.setShader(shader);
	mSheep.setTexture(textureSheep);
	mSheep.setMesh(meshSheep);
	mSheep.setPosition(0, 1.5, 0.5);
	mSheep.setUniformBinding(nu::Model::ModelViewMatrix, "MV");
	mSheep.setUniformBinding(nu::Model::ModelViewProjectionMatrix, "MVP");
	mSheep.setUniformBinding(nu::Model::NormalMatrix, "N");

	mCube.attach(&mSheep);

	nu::LinearColor clearColor(nu::LinearColor::LightBlue);
	nu::LinearColor ambientColor(0.2f, 0.3f, 0.3f, 1.0f);
	nu::LinearColor lightColor(1.0f, 0.0f, 0.0f, 1.0f);
	F32 shininess = 5.0f;
	F32 strength = 1.0f;
	F32 constantAttenuation = 0.5f;
	F32 linearAttenuation = 0.5f;
	F32 quadraticAttenuation = 0.5f;

	bool show = false;
	nu::Frustum f = renderer.getCamera().buildFrustum();

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
		if (window.isKeyPressed(GLFW_KEY_F3) && !show)
		{
			show = true;
		}
		if (window.isKeyPressed(GLFW_KEY_DOWN) || window.isKeyPressed(GLFW_KEY_S))
		{
			position -= direction * 3.0f * dt.asSeconds();
		}
		if (window.isKeyPressed(GLFW_KEY_UP) || window.isKeyPressed(GLFW_KEY_W))
		{
			position += direction * 3.0f * dt.asSeconds();
		}
		if (window.isKeyPressed(GLFW_KEY_D))
		{
			position += right * 3.0f * dt.asSeconds();
		}
		if (window.isKeyPressed(GLFW_KEY_A))
		{
			position -= right * 3.0f * dt.asSeconds();
		}
		if (window.isKeyPressed(GLFW_KEY_RIGHT))
		{
			direction = nu::Matrix4f(nu::Matrix3f::rotationY(-110.0f * dt.asSeconds())) * direction;
		}
		if (window.isKeyPressed(GLFW_KEY_LEFT))
		{
			direction = nu::Matrix4f(nu::Matrix3f::rotationY(110.0f * dt.asSeconds())) * direction;
		}

		// Update vectors
		right = direction.crossProduct(nu::Vector3f::up);
		renderer.getCamera().setPosition(position);
		renderer.getCamera().setTarget(position + direction);

		debug.frustum(f);
		debug.point(nu::Vector3f(0, 0, 0));
		debug.point(nu::Vector3f(2, 2, 2));
		debug.point(nu::Vector3f(-2, 2, -2));
		debug.point(nu::Vector3f(2, 2, -2));
		debug.point(nu::Vector3f(-2, 2, 2));
		debug.xzGrid(-10.0f, 10.0f, 0.0f, 1.0f, nu::Color::Green);
		debug.box(nu::Vector3f(5, 2, -5), nu::Vector3f(1, 1, 1), nu::Color::Red);
		debug.cross(nu::Vector3f(0.01f, 0.01f, 0.01f));
		debug.transform(mCube.getGlobalTransform());
		debug.sphere(nu::Vector3f(1, 1, 2), 1, nu::Color::Yellow);
		debug.circle(nu::Vector3f(3, 3, 3), nu::Vector3f(1, 0, 0), 2, nu::Color::Red);
		debug.circle(nu::Vector3f(3, 3, 3), nu::Vector3f(0, 1, 0), 2, nu::Color::Green);
		debug.circle(nu::Vector3f(3, 3, 3), nu::Vector3f(0, 0, 1), 2, nu::Color::Blue);
		debug.cone(nu::Vector3f(4, 4, 0), nu::Vector3f(0, -1, 0), 4, 2, nu::Color::Yellow);

		// ImGui config
		if (show)
		{
			nu::ImGuiWrapper::newFrame();
			ImGuiWrapper_Begin();
			ImGui::Begin("Debug");
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
		}

		// Model self rotation
		mCube.rotate(nu::Quaternionf(nu::Matrix3f::rotationY(30.0f * dt.asSeconds())));

		// View
		nu::Vector3f viewPosition = renderer.getCamera().getViewMatrix() * position;
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

		mCube.draw();
		mSheep.draw();

		debug.render(renderer.getCamera().getViewMatrix(), renderer.getCamera().getProjectionMatrix());

		renderer.end();

		if (show)
			nu::ImGuiWrapper::render();

		window.display();
	}

	return 0;
}