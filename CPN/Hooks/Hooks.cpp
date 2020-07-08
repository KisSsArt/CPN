#include "Hooks.h"

#include <thread>
#include <iostream>

#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_dx9.h"
#include "../imgui/imgui_impl_win32.h"

#include "../Config/Config.h"
#include "../EventListener/EventListener.h"
#include "../GameData/GameData.h"
#include "../GUI.h"
#include "../Hacks/ESP.h"
#include "../Hacks/Antiaim.h"
#include "../Hacks/Misc.h"
#include "../Hacks/Glow.h"
#include "../Hacks/TriggerBot.h"
#include "../Interfaces.h"
#include "Memory.h"

#include "../SDK/UserCmd.h"
#include "../SDK/Engine.h"
#include "../SDK/InputSystem.h"
#include "../SDK/GlobalVars.h"

#ifdef _WIN32
#include <intrin.h>
#endif
//#include "../Memory.hpp"
#include "../Memory.h"

#ifdef _WIN32
static LRESULT WINAPI wndProc(HWND window, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
    if (hooks->getState() == Hooks::State::NotInstalled)
        hooks->install();

    if (hooks->getState() == Hooks::State::Installed) {
        GameData::update();

        LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
        ImGui_ImplWin32_WndProcHandler(window, msg, wParam, lParam);
        interfaces->inputSystem->enableInput(!gui->open);
    }

    return CallWindowProcW(hooks->wndProc, window, msg, wParam, lParam);
}

static HRESULT D3DAPI reset(IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* params) noexcept
{
    ImGui_ImplDX9_InvalidateDeviceObjects();
    return hooks->reset(device, params);
}

static HRESULT D3DAPI present(IDirect3DDevice9* device, const RECT* src, const RECT* dest, HWND windowOverride, const RGNDATA* dirtyRegion, UserCmd* cmd) noexcept
{
    static const auto _ = ImGui_ImplDX9_Init(device);

    if (config->loadScheduledFonts())
        ImGui_ImplDX9_InvalidateDeviceObjects();

    ImGui_ImplDX9_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    
    
    ESP::render();
    Misc::drawReloadProgress(ImGui::GetBackgroundDrawList());
    Misc::drawRecoilCrosshair(ImGui::GetBackgroundDrawList());
    Misc::drawNoscopeCrosshair(ImGui::GetBackgroundDrawList());

    //new
    /*uintptr_t* framePointer;
    __asm mov framePointer, ebp;
    bool& sendPacket = *reinterpret_cast<bool*>(*framePointer - 0x1C);
    static auto previousViewAngles{ cmd->viewangles };
    const auto currentViewAngles{ cmd->viewangles };

    AimA::AntiAim(cmd, previousViewAngles, currentViewAngles, sendPacket);*/


    Misc::bunny_hop();
    Misc::antiflash();
    Glow::render();
    Misc::radarHack();
    Misc::fovChanger();
    Aim::triggerBot();
    Misc::HitmarkerRender();
    Misc::KillmarkerRender();

    Misc::purchaseList();
    Misc::drawObserverList();

    gui->render();
    
    if (ImGui::IsKeyPressed(VK_INSERT, false)) {
        gui->open = !gui->open;
        if (!gui->open)
            interfaces->inputSystem->resetInputState();
    }
    ImGui::GetIO().MouseDrawCursor = gui->open;

    ImGui::EndFrame();
    ImGui::Render();

    if (device->BeginScene() == D3D_OK) {
        ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
        device->EndScene();
    }

    return hooks->present(device, src, dest, windowOverride, dirtyRegion);
}

static BOOL WINAPI setCursorPos(int X, int Y) noexcept
{
    if (gui->open) {
        POINT p;
        GetCursorPos(&p);
        X = p.x;
        Y = p.y;
    }

    return hooks->setCursorPos(X, Y);
}

Hooks::Hooks(HMODULE module) noexcept
{
    this->module = module;

    _MM_SET_FLUSH_ZERO_MODE(_MM_FLUSH_ZERO_ON);
    _MM_SET_DENORMALS_ZERO_MODE(_MM_DENORMALS_ZERO_ON);

    window = FindWindowW(L"Valve001", nullptr);
    wndProc = WNDPROC(SetWindowLongPtrW(window, GWLP_WNDPROC, LONG_PTR(::wndProc)));
}

#endif

void Hooks::install() noexcept
{
    std::cout << "[state] Initialization..." << std::endl;
    state = State::Installing;

    std::cout << "[state] Initialization Interfaces..." << std::endl;
    interfaces = std::make_unique<const Interfaces>();
    std::cout << "[state] Initialization memory..." << std::endl;
    memory = std::make_unique<const Memory>();
    std::cout << "[state] Initialization Event Listener..." << std::endl;
    eventListener = std::make_unique<EventListener>();
    std::cout << "[state] Initialization Config..." << std::endl;
    config = std::make_unique<Config>("CPN");

    ImGui::CreateContext();
#ifdef _WIN32
    ImGui_ImplWin32_Init(window);
#endif
    gui = std::make_unique<GUI>();

#ifdef _WIN32
    reset = *reinterpret_cast<decltype(reset)*>(memory->reset);
    *reinterpret_cast<decltype(::reset)**>(memory->reset) = ::reset;

    present = *reinterpret_cast<decltype(present)*>(memory->present);
    *reinterpret_cast<decltype(::present)**>(memory->present) = ::present;

    setCursorPos = *reinterpret_cast<decltype(setCursorPos)*>(memory->setCursorPos);
    *reinterpret_cast<decltype(::setCursorPos)**>(memory->setCursorPos) = ::setCursorPos;
#endif

    state = State::Installed;
    std::cout << "[state] Initializated!" << std::endl;
}

#ifdef _WIN32

extern "C" BOOL WINAPI _CRT_INIT(HMODULE module, DWORD reason, LPVOID reserved);

static DWORD WINAPI waitOnUnload(HMODULE hModule) noexcept
{
    Sleep(50);

    interfaces->inputSystem->enableInput(true);
    eventListener->remove();

    ImGui_ImplDX9_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    _CRT_INIT(hModule, DLL_PROCESS_DETACH, nullptr);
    FreeLibraryAndExitThread(hModule, 0);
}

#endif

void Hooks::uninstall() noexcept
{
    std::cout << "[state] Closing..." << std::endl;
#ifdef _WIN32

    *reinterpret_cast<void**>(memory->reset) = reset;
    *reinterpret_cast<void**>(memory->present) = present;
    *reinterpret_cast<void**>(memory->setCursorPos) = setCursorPos;

    SetWindowLongPtrW(window, GWLP_WNDPROC, LONG_PTR(wndProc));

    if (HANDLE thread = CreateThread(nullptr, 0, LPTHREAD_START_ROUTINE(waitOnUnload), module, 0, nullptr))
        CloseHandle(thread);

#endif

#ifdef _DEBUG
    FreeConsole();
#endif
}