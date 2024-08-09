#pragma once

#include <iostream>
#include <memory>
#include <utility>
#include <random>
#include <algorithm>
#include <functional>

#include <string>
#include <sstream>
#include <array>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "Alexio/Log.h"
#include "Alexio/Utilities.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#ifdef AIO_PLATFORM_WINDOWS
	#include <Windows.h>
	#include <comdef.h>
	#include <d3d11.h>
	#include <d3dcompiler.h>
	#include <wrl/client.h>
#endif // AIO_PLATFORM_WINDOWS