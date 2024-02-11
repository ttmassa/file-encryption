#include "encryption.h"
#include "windows.h"

int main() {
    HINSTANCE hInstance = GetModuleHandle(NULL);
    CreateMainWindow(hInstance);

    MSG msg = { 0 };
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}