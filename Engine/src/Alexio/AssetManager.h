#pragma once

#include "Utilities.h"
#include "Renderer/Renderer.h"

namespace Alexio
{
	class AssetManager
	{
	public:
		static Ref<Texture> CreateCustomSprite();
		static Ref<Shader>  CreateCustomShader();
	};
}

