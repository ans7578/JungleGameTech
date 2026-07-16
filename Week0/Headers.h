#pragma once
#define _CRTDBG_MAP_ALLOC
#include <Windows.h>

#include "Structs.h"
#include <vector>
#include <cstdlib> // rand, srand 함수 사용
#include <ctime>   // time 함수 사용
#include <map>
#include <unordered_map>
#include <set>
#include <list>
#include <wrl/client.h>


using namespace Microsoft::WRL;

//dx
#pragma comment(lib, "user32")
#pragma comment(lib, "d3d11")
#pragma comment(lib, "d3dcompiler")
#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>

using namespace DirectX;

//ImGui
#include "ImGui/imgui.h"
#include "ImGui/imgui_internal.h"
#include "ImGui/imgui_impl_dx11.h"
#include "ImGui/imgui_impl_win32.h"