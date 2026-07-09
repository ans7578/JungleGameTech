#pragma once
#define _CRTDBG_MAP_ALLOC
#include <Windows.h>

//dx
#pragma comment(lib, "user32")
#pragma comment(lib, "d3d11")
#pragma comment(lib, "d3dcompiler")
#include <d3d11.h>
#include <d3dcompiler.h>

#include "Structs.h"
#include <vector>
#include <cstdlib> // rand, srand 함수 사용
#include <ctime>   // time 함수 사용
#include <map>


//ImGui
#include "ImGui/imgui.h"
#include "ImGui/imgui_internal.h"
#include "ImGui/imgui_impl_dx11.h"
#include "ImGui/imgui_impl_win32.h"

//Managers
#include "ResourceManager.h"