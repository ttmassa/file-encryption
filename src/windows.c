#include "windows.h"
#include "encryption.h"
#include <commdlg.h> // for OPENFILENAME and GetOpenFileName

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
    int encryptButtonX = (windowWidth - buttonWidth) / 4;
    int decryptButtonX = (windowWidth - buttonWidth) / 4 * 3;
    int buttonY = (windowHeight - buttonHeight) / 2;

    HWND encryptButton = CreateWindowW(
        L"BUTTON",
        L"Encrypt file",
        WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
        encryptButtonX, buttonY, buttonWidth, buttonHeight,
        hwnd,
        (HMENU)1,
        hInstance,
        NULL
    );

    if (!encryptButton) {
        MessageBoxW(NULL, L"Encrypt button creation failed!", L"Error", MB_ICONERROR);
        ExitProcess(1);
    }

    HWND decryptButton = CreateWindowW(
        L"BUTTON",
        L"Decrypt file",
        WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
        decryptButtonX, buttonY, buttonWidth, buttonHeight,
        hwnd,
        (HMENU)2,
        hInstance,
        NULL
    );

    if (!decryptButton) {
        MessageBoxW(NULL, L"Decrypt button creation failed!", L"Error", MB_ICONERROR);
        ExitProcess(1);
    }

    ShowWindow(hwnd, SW_SHOWDEFAULT);
    UpdateWindow(hwnd);
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_COMMAND:
        if (LOWORD(wParam) == 1) { // if the command ID is 1 (the ID of the button)
            OPENFILENAMEW ofn = { 0 };
            WCHAR file[260] = { 0 }; // buffer to store the file path

            // Initialize OPENFILENAME
            ofn.lStructSize = sizeof(ofn);
            ofn.hwndOwner = hwnd;
            ofn.lpstrFile = file;
            ofn.nMaxFile = sizeof(file) / sizeof(WCHAR);
            ofn.lpstrFilter = L"All\0*.*\0Text\0*.TXT\0";
            ofn.nFilterIndex = 1;
            ofn.lpstrFileTitle = NULL;
            ofn.nMaxFileTitle = 0;
            ofn.lpstrInitialDir = NULL;
            ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

            // Display the Open dialog box.
            if (GetOpenFileNameW(&ofn)) {
                // file contains the path of the selected file
                char filePath[MAX_PATH];
                WideCharToMultiByte(CP_UTF8, 0, file, -1, filePath, MAX_PATH, NULL, NULL);
                encryptFileWithoutKey(filePath);
            }
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}