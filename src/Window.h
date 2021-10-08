#pragma once
#include "bgfx/bgfx.h"
#include "GLFW/glfw3.h"
#if BX_PLATFORM_LINUX
#define GLFW_EXPOSE_NATIVE_X11
#elif BX_PLATFORM_WINDOWS
#define GLFW_EXPOSE_NATIVE_WIN32
#elif BX_PLATFORM_OSX
#define GLFW_EXPOSE_NATIVE_COCOA
#endif
#include "GLFW/glfw3native.h"

#define WNDW_WIDTH 1024
#define WNDW_HEIGHT 768

class Window
{
public:
	Window();
	~Window();

	int init();
	void update();
	void shutdown();

	int	getWidth()	{ return width; }
	int	getHeight()	{ return height; }

	bool windowShouldClose() { return glfwWindowShouldClose(window); }

private:
	GLFWwindow* window;
	const bgfx::ViewId kClearView = 0;
	int width;
	int height;
};

