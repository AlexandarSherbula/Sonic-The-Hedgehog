#pragma once

#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

namespace Alexio
{
	using Vector2 = glm::vec2;
	using Vector3 = glm::vec3;
	using Vector4 = glm::vec4;

	using Vector2i = glm::ivec2;
	using Vector3i = glm::ivec3;
	using Vector4i = glm::ivec4;

	using Mat2 = glm::mat2;
	using Mat2x2 = glm::mat2x2;

	using Mat2x3 = glm::mat2x3;
	using Mat2x4 = glm::mat2x4;
	using Mat3x2 = glm::mat3x2;

	using Mat3 = glm::mat3;
	using Mat3x3 = glm::mat3x3;

	using Mat3x4 = glm::mat3x4;
	using Mat4x2 = glm::mat4x2;
	using Mat4x3 = glm::mat4x3;

	using Mat4x4 = glm::mat4;
	using Mat4x4 = glm::mat4x4;

	inline float Length(const Vector2& v) { return glm::length(v); }
	inline float Length(const Vector3& v) { return glm::length(v); }
	inline float Length(const Vector4& v) { return glm::length(v); }

	template<typename T>
	inline T Length(T x) { return glm::length(x); }

	template<typename T>
	inline T Radians(T degrees) { return glm::radians(degrees); }

	template<typename T>
	inline T Degree(T radians) { return glm::degrees(radians); }

	inline std::ostream& operator<< (std::ostream& os, const Vector2& vec2) { os << vec2.x << " : " << vec2.y; return os; }
	inline std::ostream& operator<< (std::ostream& os, const Vector3& vec3) { os << vec3.x << " : " << vec3.y << " : " << vec3.z; return os; }
	inline std::ostream& operator<< (std::ostream& os, const Vector4& vec4) { os << vec4.x << " : " << vec4.y << " : " << vec4.z << " : " << vec4.w; return os; }
}