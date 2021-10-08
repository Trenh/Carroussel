#include <stdio.h>
#include "bgfx/platform.h"
#include "Window.h"

static bool s_showStats = false;

static void glfw_errorCallback(int error, const char* description)
{
    fprintf(stderr, "GLFW error %d: %s\n", error, description);
}

static void glfw_keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_F1 && action == GLFW_RELEASE)
        s_showStats = !s_showStats;
}

Window::Window() :
    width(WNDW_WIDTH),
    height(WNDW_HEIGHT)
{

}

Window::~Window() {
    shutdown();
}

int Window::init() {
    // Init GLFW
    if (!glfwInit())
        return 1;
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    // Window creation (width, height, windowName, null, null)
    window = glfwCreateWindow(width, height, "TDs Engine", NULL, NULL);
    if (!window)
        return 1;

    glfwSetKeyCallback(window, glfw_keyCallback);

    // Give to bgfx the window
    bgfx::PlatformData platformData;
#if BX_PLATFORM_LINUX || BX_PLATFORM_BSD
    platformData.ndt = glfwGetX11Display();
    platformData.nwh = (void*)(uintptr_t)glfwGetX11Window(window);
#elif BX_PLATFORM_OSX
    platformData.nwh = glfwGetCocoaWindow(window);
#elif BX_PLATFORM_WINDOWS
    platformData.nwh = glfwGetWin32Window(window);
#endif
    bgfx::setPlatformData(platformData);

    // Init bgfx
    bgfx::Init init;
    int l_width, l_height;
    glfwGetWindowSize(window, &l_width, &l_height);
    init.resolution.width = (uint32_t)l_width;
    init.resolution.height = (uint32_t)l_height;
    init.resolution.reset = BGFX_RESET_VSYNC;
    if (!bgfx::init(init))
        return 1;

    // Set the background color and clear window
    bgfx::setViewClear(kClearView, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x443355FF, 1.0f, 0);
    bgfx::setViewRect(kClearView, 0, 0, width, height);
    return 0;
}

void Window::update() {
    glfwPollEvents();
    // Handle window resize.
    int oldWidth = width, oldHeight = height;
    glfwGetWindowSize(window, &width, &height);
    if (width != oldWidth || height != oldHeight) {
        bgfx::reset((uint32_t)width, (uint32_t)height, BGFX_RESET_VSYNC);
        bgfx::setViewRect(kClearView, 0, 0, bgfx::BackbufferRatio::Equal);
    }
    // This dummy draw call is here to make sure that view 0 is cleared if no other draw calls are submitted to view 0.
    bgfx::touch(kClearView);
}

void Window::shutdown() {
    glfwDestroyWindow(window);
    glfwTerminate();
}