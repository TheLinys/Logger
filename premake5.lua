project "Logger"
	kind "StaticLib"
	language "C++"
	staticruntime "off"
	warnings "off"

    targetdir ("../../../Binaries/" .. OutputDir .. "/%{prj.name}")
    objdir ("../../../Binaries-Intermediates/" .. OutputDir .. "/%{prj.name}")

	files
	{
		"**.h",
        "**.cpp"
	}

	includedirs
	{
		"include"
	}

	filter "system:linux"
		pic "On"

		systemversion "latest"
		
		files
		{
		    "**.h",
            "**.cpp"
		}

	filter "system:macosx"
		pic "On"

		files
		{
		    "**.h",
            "**.cpp"
		}

	filter "system:windows"
		systemversion "latest"

		files
		{
		    "**.h",
            "**.cpp"
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