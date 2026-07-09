#pragma once
#define _CRTDBG_MAP_ALLOC
#include <Windows.h>

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