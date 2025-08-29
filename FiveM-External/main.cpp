#include "Overlay\Overlay.h"
#include "Cheat\Cheat.h"
#include "Utils\Memory\Memory.h"
#include <thread>

Cheat* five = new Cheat;
Overlay* ov = new Overlay;

// Debug時のみコンソールあり
#if _DEBUG
int main()
#else 
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
#endif
{
	// Fix DPI Scale
	SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_SYSTEM_AWARE);

	// Memory
	if (!m.Init())
		return 1;

	// Overlay
	if (!ov->CreateOverlay())
		return 2;

	// Create some threads
	g.Run = true;
	std::thread([&]() { ov->OverlayManager(); }).detach();
	std::thread([&]() { five->AimBot(); }).detach();
	std::thread([&]() { five->Misc(); }).detach();
	std::thread([&]() { five->UpdateList(); }).detach();
	std::thread([&]() { five->TriggerBot(); }).detach();
	ov->OverlayLoop();
	ov->DestroyOverlay();
	CloseHandle(m.pHandle);
	delete[] five, ov;

	return 0;
}

void Overlay::OverlayLoop()
{
	while (g.Run)
	{
		MSG msg;
		while (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		five->RenderInfo();

		if (g.ShowMenu)
			five->RenderMenu();

		if (g.ESP)
			five->RenderESP();

		ImGui::Render();
		const float clear_color_with_alpha[4] = { 0.f, 0.f, 0.f, 0.f };
		g_pd3dDeviceContext->OMSetRenderTargets(1, &g_mainRenderTargetView, NULL);
		g_pd3dDeviceContext->ClearRenderTargetView(g_mainRenderTargetView, clear_color_with_alpha);
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

		g_pSwapChain->Present(1, 0);
	}
}