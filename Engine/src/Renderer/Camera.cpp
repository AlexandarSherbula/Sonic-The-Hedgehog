#include "aio_pch.h"
#include "Camera.h"
#include "Alexio/Timer.h"
#include "Input/Input.h"
#include "Renderer/Renderer.h"
#include "Alexio/Engine.h"

namespace Alexio
{
	Camera::Camera(const Alexio::Vector2& projectionSize)
	{
		mZoomLevel = 1.0f;

		mProjection = glm::ortho(0.0f, projectionSize.x, projectionSize.y, 0.0f);
		mView = glm::mat4x4(1.0f);
		mViewProjection = mProjection * mView;

		mPosition = { 0.0f, 0.0f };
		mRotation = 0.0f;
	}

	void Camera::OnEvent(Event& e)
	{
		//EventDispatcher dispatcher(e);
		//dispatcher.Dispatch<WindowResizeEvent>(AIO_BIND_EVENT_FN(Camera::OnWindowResize));
		//dispatcher.Dispatch<MouseScrolledEvent>(AIO_BIND_EVENT_FN(Camera::OnMouseScroll));
	}

	bool Camera::OnWindowResize(WindowResizeEvent& e)
	{
		return false;
	}

	bool Camera::OnMouseScroll(MouseScrolledEvent& e)
	{
		return false;
	}

	void Camera::OnUpdate(float dt)
	{
		mView = glm::translate(glm::mat4x4(1.0f), glm::vec3(mPosition, 0.0f)) *
			glm::rotate(glm::mat4x4(1.0f), glm::radians(mRotation), glm::vec3(0, 0, 1));
		
		mViewProjection = mProjection * mView;

		Renderer::GetCameraBuffer()->SetData(&mViewProjection, sizeof(glm::mat4x4));
		Renderer::GetCameraBuffer()->Bind(0);
	}

	void Camera::UpdateProjection()
	{
		
	}
}