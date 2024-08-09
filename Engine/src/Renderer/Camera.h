#pragma once

#include "Math/Math.h"
#include "Events/Events.h"

namespace Alexio
{
	class Camera
	{
	public:
		Camera() = default;
		Camera(const Alexio::Vector2& projectionSize);

		inline float& Rotation() { return mRotation; }
		inline float& ZoomLevel() { return mZoomLevel; }

		void OnEvent(Event& e);
		bool OnWindowResize(WindowResizeEvent& e);
		bool OnMouseScroll(MouseScrolledEvent& e);

		void OnUpdate(float dt);
		void UpdateProjection();

		inline Alexio::Vector2 GetPosition() { return mPosition; }
		inline void SetPosition(const Alexio::Vector2& position) { mPosition = position; }
	private:
		Alexio::Vector2 mPosition;
		float mRotation;
		float mZoomLevel;

		float mAspectRatio = 16.0f / 9.0f;

		glm::mat4x4 mProjection;
		glm::mat4x4 mView;
		glm::mat4x4 mViewProjection;
	};
}