project "GLAD"
    kind "StaticLib"
    language "C"
    staticruntime "On"

    targetdir "build/%{prj.name}/bin/%{cfg.system}/%{cfg.buildcfg}-%{cfg.architecture}"
    objdir    "build/%{prj.name}/intermediate/%{cfg.system}/%{cfg.buildcfg}-%{cfg.architecture}"

    files
    {
        "include/glad/glad.h",
        "include/KHR/khrplatform.h",
        "src/glad.c"
    }

    includedirs
    {
        "include"
    }

    filter "system:windows"
        systemversion "latest"
        
    
    filter "configurations:Debug"        
        runtime "Debug"
        symbols "on"
    
    filter "configurations:Release"
        runtime "Release"
        optimize "on"