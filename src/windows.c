#include "windows.h"
#include "encryption.h"
#include "db_manager.h"
#include <commdlg.h> // for OPENFILENAME and GetOpenFileName

// Forward declaration of the Window Procedure
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

HWND hEdit;

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

    int textFieldWidth = 200;
    int textFieldHeight = 25;
    int textFieldX = (windowWidth - textFieldWidth) / 2;
    int textFieldY = (windowWidth - textFieldWidth) / 3;

    hEdit = CreateWindowExW(
        WS_EX_CLIENTEDGE,
        L"EDIT",
        L"",
        WS_VISIBLE | WS_CHILD | ES_AUTOHSCROLL,
        textFieldX, textFieldY, textFieldWidth, textFieldHeight,
        hwnd,
        (HMENU)3,
        hInstance,
        NULL
    );

    if (!hEdit) {
        MessageBoxW(NULL, L"Edit control creation failed!", L"Error", MB_ICONERROR);
        ExitProcess(1);
    }

    ShowWindow(hwnd, SW_SHOWDEFAULT);
    UpdateWindow(hwnd);
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_COMMAND:
        if (LOWORD(wParam) == 1 || LOWORD(wParam) == 2) { // if the command ID is 1 (encrypt button) or 2 (decrypt button)
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
                // Get the text from the Edit control
                WCHAR name[260];
                GetWindowTextW(hEdit, name, 260);

                // Convert the name to a multibyte string if necessary
                char fileName[260];
                WideCharToMultiByte(CP_UTF8, 0, name, -1, fileName, 260, NULL, NULL);

                // file contains the path of the selected file
                char filePath[MAX_PATH];
                WideCharToMultiByte(CP_UTF8, 0, file, -1, filePath, MAX_PATH, NULL, NULL);
                if (LOWORD(wParam) == 1) {
                    encryptFileWithoutKey(filePath, fileName);
                } else if (LOWORD(wParam) == 2) {
                    char* key = getKey(fileName);
                    decryptFile(filePath, key);
                }
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