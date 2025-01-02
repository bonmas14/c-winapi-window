// Copyright 2024 bonmas14

#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>

LRESULT CALLBACK wWindowProc(HWND window, UINT uMsg, WPARAM wParam, LPARAM lParam);

HFONT font;

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
    const wchar_t CLASS_NAME[] = L"Minimal Window";

    WNDCLASSW wc = { 0 };

    wc.style = CS_CLASSDC | CS_VREDRAW | CS_HREDRAW;
    wc.lpfnWndProc = wWindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClassW(&wc);

    HWND window = CreateWindowExW(
            0,
            CLASS_NAME,
            L"Деревня",
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            400,
            300,
            NULL,
            NULL,
            hInstance,
            NULL
            );

    if (window == NULL)
        return 0;

    int n = AddFontResourceW(L"arial.ttf");

    if (n == 0)
        return 0;

    font = CreateFontW(
            24,
            0,

            0,
            0,

            FW_REGULAR, 

            FALSE,
            FALSE,
            FALSE,

            RUSSIAN_CHARSET,
            OUT_DEFAULT_PRECIS,
            CLIP_DEFAULT_PRECIS,
            ANTIALIASED_QUALITY,
            DEFAULT_PITCH,
            L"Arial\0"
            );

    ShowWindow(window, nCmdShow);

    MSG msg = { 0 };

    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK wWindowProc(HWND window, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;

        case WM_PAINT:
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(window, &ps);

            FillRect(hdc, &ps.rcPaint, (HBRUSH) (COLOR_WINDOW + 1));

            (void)SelectObject(hdc, font);

            DrawTextW(hdc, L"Кремируйте её быстрее!", -1, &ps.rcPaint, DT_LEFT | DT_SINGLELINE);

            EndPaint(window, &ps);
            return 0;
    }

    return DefWindowProc(window, uMsg, wParam, lParam);
}
