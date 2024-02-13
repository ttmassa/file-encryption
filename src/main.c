#include "encryption.h"
#include "windows.h"
#include "db_manager.h"

int main() {
    initializeDb();
    HINSTANCE hInstance = GetModuleHandle(NULL);
    CreateMainWindow(hInstance);

    MSG msg = { 0 };
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}