#include "windows.h"

// Forward declaration of the Window Procedure
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

void CreateMainWindow(HINSTANCE hInstance) {
    WNDCLASSW wc = { 0 };
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"MainWindowClass";

    if (!RegisterClassW(&wc))
    {
        MessageBoxW(NULL, L"Window Registration Failed!", L"Error!", MB_ICONEXCLAMATION | MB_OK);
        ExitProcess(1);
    }

    HWND hwnd = CreateWindowExW(
        0,
        L"MainWindowClass",
        L"Simple Window",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 500, 400,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    if (!hwnd) {
        MessageBoxW(NULL, L"Window creation failed!", L"Error", MB_ICONERROR);
        ExitProcess(1);
    }

    // Calculer les dimensions de la fenêtre
    RECT rect;
    GetClientRect(hwnd, &rect);
    int windowWidth = rect.right - rect.left;
    int windowHeight = rect.bottom - rect.top;

    int buttonWidth = 100;
    int buttonHeight = 30;
    int buttonX = (windowWidth - buttonWidth) / 2;
    int buttonY = (windowHeight - buttonHeight) / 2;

    HWND button = CreateWindowW(
        L"BUTTON",
        L"Click me",
        WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
        buttonX, buttonY, buttonWidth, buttonHeight,
        hwnd,
        (HMENU)1,
        hInstance,
        NULL
    );

    if (!button) {
        MessageBoxW(NULL, L"Button creation failed!", L"Error", MB_ICONERROR);
        ExitProcess(1);
    }

    ShowWindow(hwnd, SW_SHOWDEFAULT);
    UpdateWindow(hwnd);
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}