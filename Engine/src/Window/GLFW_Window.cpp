#include "aio_pch.h"

#if defined(AIO_API_OPENGL)
#include "GLFW_Window.h"

#include "Renderer/Renderer.h"

namespace Alexio
{
    static bool sGLFW_Initialize = false;

    static void GLFWErrorCallback(int error, const char* description)
    {
        AIO_LOG_ERROR("GLFW Error {0}: {1}", error, description);
    }

    GLFW_Window::GLFW_Window(const std::string& title, uint32_t width, uint32_t height, uint32_t pixelSize, bool fullscreen)
    {
        mTitle = mData.title = title;
        mProjectionWidth = mData.width = width;
        mProjectionHeight = mData.height = height;

        mPixelSize = pixelSize;

        mIsFullScreen = fullscreen;

        Initialize();
    }

    GLFW_Window::~GLFW_Window()
    {
        glfwDestroyWindow(mHandle);
        glfwTerminate();
    }

    void GLFW_Window::Initialize()
    {
        if (!sGLFW_Initialize)
        {
            AIO_ASSERT(glfwInit(), "Failed to initialize GLFW");
            glfwSetErrorCallback(GLFWErrorCallback);
            sGLFW_Initialize = true;
        }
#ifdef AIO_DEBUG
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
#endif // AIO_DEBUG

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);

        mMonitor = glfwGetPrimaryMonitor();
        mFullScreen = { glfwGetVideoMode(mMonitor)->width, glfwGetVideoMode(mMonitor)->height };

        mWindowSize.x = mIsFullScreen ? mFullScreen.x : mProjectionWidth * mPixelSize;
        mWindowSize.y = mIsFullScreen ? mFullScreen.y : mProjectionHeight * mPixelSize;

        mPosition = { mFullScreen.x / 2.0f - (mProjectionWidth * mPixelSize) / 2.0f, mFullScreen.y / 2.0f - (mProjectionHeight * mPixelSize) / 2.0f };

        mHandle = glfwCreateWindow(mWindowSize.x, mWindowSize.y, mTitle.c_str(), mMonitor, NULL);

        AIO_ASSERT(mHandle, "Failed to create a GLFW window");

        glfwSetWindowPos(mHandle, mPosition.x, mPosition.y);

        glfwMakeContextCurrent(mHandle);
        glfwSetWindowUserPointer(mHandle, &mData);

        EventProcess();
    }

    void GLFW_Window::PollEvents()
    {
        glfwPollEvents();
    }

    void GLFW_Window::PixelResize(uint32_t pixelSize)
    {
        if (!mIsFullScreen)
        {
            mPixelSize = pixelSize;

            mWindowSize.x = mProjectionWidth * mPixelSize;
            mWindowSize.y = mProjectionHeight * mPixelSize;

            mPosition = { mFullScreen.x / 2.0f - mWindowSize.x / 2.0f, mFullScreen.y / 2.0f - mWindowSize.y / 2.0f };

            glfwSetWindowPos(mHandle, mPosition.x, mPosition.y);
            glfwSetWindowSize(mHandle, mWindowSize.x, mWindowSize.y);
        }
    }

    void GLFW_Window::SetFullScreen()
    {
        mIsFullScreen = !mIsFullScreen;

        Alexio::Vector2 windowPos = mPosition;

        if (mIsFullScreen)
        {
            mWindowSize = mFullScreen;
            int32_t width = mFullScreen.x;
            int32_t height = mFullScreen.y;

            glfwGetWindowPos(mHandle, (int32_t*)&windowPos.x, (int32_t*)&windowPos.y);
            glfwGetWindowSize(mHandle, &width, &height);

            glfwSetWindowMonitor(mHandle, mMonitor, 0, 0, mFullScreen.x, mFullScreen.y, 0);
        }
        else
        {
            mWindowSize.x = mProjectionWidth * mPixelSize;
            mWindowSize.y = mProjectionHeight * mPixelSize;

            glfwSetWindowMonitor(mHandle, nullptr, mPosition.x, mPosition.y, mWindowSize.x, mWindowSize.y, (int32_t)Renderer::GetBackend()->IsVSync());
        }
    }

    void GLFW_Window::EventProcess()
    {
        glfwSetWindowSizeCallback(mHandle, [](GLFWwindow* window, int width, int height)
            {
                WindowDataFromCallback& data = *(WindowDataFromCallback*)glfwGetWindowUserPointer(window);
                data.width = width;
                data.height = height;

                WindowResizeEvent event(width, height);
                data.eventCallback(event);
            }
        );

        glfwSetWindowCloseCallback(mHandle, [](GLFWwindow* window)
            {
                WindowDataFromCallback& data = *(WindowDataFromCallback*)glfwGetWindowUserPointer(window);
                WindowCloseEvent event;
                data.eventCallback(event);
            }
        );

        glfwSetKeyCallback(mHandle, [](GLFWwindow* window, int key, int scancode, int action, int mods)
            {
                WindowDataFromCallback& data = *(WindowDataFromCallback*)glfwGetWindowUserPointer(window);

                switch (action)
                {
                case GLFW_PRESS:
                {
                    KeyPressedEvent event(key, 0);
                    data.eventCallback(event);
                    Input::UpdateKeyState(Input::mapKeys[key], true);
                    break;
                }
                case GLFW_RELEASE:
                {
                    KeyReleasedEvent event(key);
                    data.eventCallback(event);
                    Input::UpdateKeyState(Input::mapKeys[key], false);
                    break;
                }
                case GLFW_REPEAT:
                {
                    KeyPressedEvent event(key, 1);
                    data.eventCallback(event);
                    break;
                }
                }
            }
        );

        glfwSetMouseButtonCallback(mHandle, [](GLFWwindow* window, int button, int action, int mods)
            {
                WindowDataFromCallback& data = *(WindowDataFromCallback*)glfwGetWindowUserPointer(window);

                switch (action)
                {
                case GLFW_PRESS:
                {
                    MouseButtonPressedEvent event(button);
                    data.eventCallback(event);
                    Input::UpdateMouseState(button, true);
                    break;
                }
                case GLFW_RELEASE:
                {
                    MouseButtonReleasedEvent event(button);
                    data.eventCallback(event);
                    Input::UpdateMouseState(button, false);
                    break;
                }
                }
            }
        );

        glfwSetScrollCallback(mHandle, [](GLFWwindow* window, double xOffset, double yOffset)
            {
                WindowDataFromCallback& data = *(WindowDataFromCallback*)glfwGetWindowUserPointer(window);

                MouseScrolledEvent event((float)xOffset, (float)yOffset);
                data.eventCallback(event);
            }
        );

        glfwSetCursorPosCallback(mHandle, [](GLFWwindow* window, double xPos, double yPos)
            {
                WindowDataFromCallback& data = *(WindowDataFromCallback*)glfwGetWindowUserPointer(window);

                MouseMovedEvent event((float)xPos, (float)yPos);
                data.eventCallback(event);
            });
    }
}
#endif