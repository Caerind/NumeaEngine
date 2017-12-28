#ifndef NU_TESTAPPLICATION_HPP
#define NU_TESTAPPLICATION_HPP

#include "../Sources/Application/GLEWWrapper.hpp"
#include "../Sources/Application/GLFWWrapper.hpp"
#include "../Sources/Application/ImGuiWrapper.hpp"
#include "../Sources/Application/Window.hpp"
#include "../Sources/Application/ResourceManager.hpp"
#include "../Sources/Application/ResourceHolder.hpp"
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
	window.create(800, 600, "Window");
	CHECK(window.isOpen());
	CHECK(window.getSize().x == 800);
	CHECK(window.getSize().y == 600);
	window.close();
}

TEST("ImGuiWrapper")
{
	nu::Window window;
	window.create(800, 600, "ImGuiWrapper");
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
		nu::ImGuiWrapper::endFrame();
		nu::ImGuiWrapper::render();
		window.display();

		window.close();
	}
}

TEST("ResourceManager")
{
	class TestResource : public nu::Resource<TestResource>
	{
		public:
			TestResource() {}
	};

	nu::Loader<TestResource> loader([](TestResource&) -> bool { return true; });
	
	nu::ResourceManager manager;

	nu::ResourceHolder holder(manager);

	TestResource::Ptr r = holder.get(10, loader);
	CHECK(r != nullptr);
	CHECK(r);
	CHECK(r->isLoaded());
	CHECK(r->isManaged());
	CHECK(r->getId() != InvalidU32);
}

TEST("StateManager")
{

}

TEST("Application")
{
	nu::Application app;
}

}
END_TEST;

#endif // NU_TESTAPPLICATION_HPP
