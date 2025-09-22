project "Logger"
	kind "StaticLib"
	language "C++"
	staticruntime "off"
	warnings "off"

    targetdir ("../Binaries/" .. OutputDir .. "/%{prj.name}")
    objdir ("../Binaries-Intermediates/" .. OutputDir .. "/%{prj.name}")

	files
	{
		"**.cpp",
		"**.h"
	}

	filter "system:linux"
		pic "On"

		systemversion "latest"
		
		files
		{
			"**.cpp",
			"**.h"
		}

	filter "system:macosx"
		pic "On"

		files
		{
			"**.cpp",
			"**.h"
		}

	filter "system:windows"
		systemversion "latest"

		files
		{
			"**.cpp",
			"**.h"
		}

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter { "system:windows", "configurations:Debug-AS" }	
		runtime "Debug"
		symbols "on"
		sanitize { "Address" }
		flags { "NoRuntimeChecks", "NoIncrementalLink" }

	filter "configurations:Release"
		runtime "Release"
		optimize "speed"

    filter "configurations:Dist"
		runtime "Release"
		optimize "speed"
        symbols "off"