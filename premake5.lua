workspace "GameTechLabWeek2"
	configurations { "Debug", "Release" }

project "GameTechlabWeek2"
	kind "WindowedApp"
	language "C++"
	cppdialect "C++20"
	characterset "Unicode"
	
	targetdir "bin/%{cfg.buildcfg}"
	
	-- include를 상대 경로 대신 절대 경로로 쓸 수 있도록 수정
	-- ex. #include "../../GEngine.h" -> #include "Engine/GEngine.h"
	includedirs { "./GameTechlabWeek2/" } 
	
	files {
		"**.h",
		"**.cpp",
		"**.hpp",
		"**.c" 
	}


	-- Precompiled Header
	-- 아래 헤더들은 한번만 컴파일 후 변경 없음
	enablepch "Off"

	-- pchheader "windows.h"
	-- pchheader "d3d11.h"
	-- pchheader "d3dcompiler.h"
	-- 
	-- pchheader "imgui.h"
	-- pchheader "imgui_impl_dx11.h"
	-- pchheader "imgui_impl_win32.h"
	-- 
	-- pchheader "iostream"
	-- pchheader "fstream"
	-- pchheader "sstream"
	-- pchheader "cstddef"
	-- pchheader "cstdint"
	-- pchheader "vector"
	-- pchheader "format"
	-- pchheader "string"
	-- pchheader "chrono"
	-- pchheader "unordered_map"
	-- pchheader "map"
	-- pchheader "utility"
	-- 
	-- pchheader "SimpleJSON.hpp"


	-- 멀티 프로세싱 컴파일
	-- 한번에 여러 cpp 파일 컴파일로 컴파일 속도 향상
	multiprocessorcompile "On"
	
	filter "toolset:msc*"
		-- 호출 규약이 팀원마다 다른(?) 기이한 버그 때문에 추가
		callingconvention "Cdecl"

		-- 한글 인코딩 문제를 UTF-8로 강제하여 해결
        buildoptions { "/utf-8" }
	
	filter "configurations:Debug"
		defines { "DEBUG" }
		symbols "On"
		
	filter "configurations:Release"
		defines { "NDEBUG" }
		optimize "On"
	
	-- 동적 링킹
	links {
		"d3d11",			-- DirectX11 
		"d3dcompiler",		-- DirectX11
		"dxgi",				-- DirectX11
		"user32"			-- Win32
	}

	-- Standalone test entry points are not part of the editor application.
	removefiles { "tests/**" }
