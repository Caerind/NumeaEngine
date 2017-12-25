#ifndef NU_TESTAPPLICATION_HPP
#define NU_TESTAPPLICATION_HPP

#include "../Sources/Application/GLEWWrapper.hpp"
#include "../Sources/Application/GLFWWrapper.hpp"
#include "../Sources/Application/ImGuiWrapper.hpp"
#include "../Sources/Application/Window.hpp"
#include "../Sources/Application/StateManager.hpp"
#include "../Sources/Application/Application.hpp"

#include "../Sources/System/UnitTest.hpp"

BEGIN_TEST(Application)
{

TEST("GLEWWrapper")
{
	
}

TEST("GLFWWrapper")
{

}

TEST("Window")
{
	nu::Window window;
	window.create(800, 600, "Test");
	while (window.isOpen())
	{
		window.pollEvents();
		if (window.isKeyPressed(GLFW_KEY_ESCAPE))
		{
			window.close();
		}

		window.clear();

		window.display();
	}
}

TEST("ImGuiWrapper")
{
	nu::Window window;
	window.create(800, 600, "Test");
	nu::ImGuiWrapper::init(window);
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

		window.clear();
		nu::ImGuiWrapper::preRender();
		nu::ImGuiWrapper::render();
		window.display();
	}
}

TEST("StateManager")
{

}

TEST("Application")
{
	
}

}
END_TEST;

#endif // NU_TESTAPPLICATION_HPP
