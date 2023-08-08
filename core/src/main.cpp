#include <Windows.h>
#include <iostream>
#include "utils/math.h"
#include "StellarRender.h"

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_CLOSE:
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

extern "C" __declspec(dllexport) void StartEngine(HINSTANCE hInstance)
{
    const char* CLASS_NAME = "Polaris2D";

    WNDCLASSEX wcex = { };
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WindowProc;
    wcex.hInstance = hInstance;
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszClassName = CLASS_NAME;

    if (!RegisterClassEx(&wcex))
    {
        MessageBox(NULL, "Window registration failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return;
    }

    HWND hwnd = CreateWindowEx(0, CLASS_NAME, "Polaris2D", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1280, 720, NULL, NULL, hInstance, NULL);

    if (hwnd == NULL)
    {
        DWORD errorCode = GetLastError();
        char errorBuffer[255];
        sprintf_s(errorBuffer, "Window creation failed! Error code: %ld", errorCode);
        MessageBox(NULL, errorBuffer, "Error!", MB_ICONEXCLAMATION | MB_OK);
        return;
    }

    if (!IsWindow(hwnd))
    {
        MessageBox(NULL, "HWND is not valid.", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return;
    }

    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);

    StellarRender stellar(hwnd);

    while (true)
    {
        MSG msg = { 0 };
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        if (msg.message == WM_QUIT)
        {
            break;
        }

        stellar.Render();
    }
}
