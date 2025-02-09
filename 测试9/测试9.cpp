#include <windows.h>
#include <gdiplus.h>
#include <TlHelp32.h>
#include <graphics.h>
#pragma comment (lib,"gdiplus.lib")

// 全局变量
HBRUSH hBrush; // 刷子句柄，用于设置背景颜色
ULONG_PTR gdiplusToken; // GDI+令牌
Gdiplus::GdiplusStartupInput gdiplusStartupInput; // GDI+启动输入

IMAGE jiankang;

// 窗口过程函数
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_CREATE:
        // 启动GDI+
        Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

        // 创建按钮
        CreateWindow("BUTTON", "开始游戏", WS_VISIBLE | WS_CHILD, 500, 300, 100, 50, hwnd, (HMENU)1, ((LPCREATESTRUCT)lParam)->hInstance, NULL);
        CreateWindow("BUTTON", "绿色游玩须知", WS_VISIBLE | WS_CHILD, 500, 400, 100, 50, hwnd, (HMENU)2, ((LPCREATESTRUCT)lParam)->hInstance, NULL);
        break;
    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case 1:
            ShellExecute(NULL, "open", "打砖块游戏.exe", NULL, NULL, SW_SHOWDEFAULT);
            PostQuitMessage(0); // 启动后关闭当前程序
            break;
        case 2:
            initgraph(800, 500);
            HWND hwnd1 = GetHWnd();
            SetWindowPos(hwnd1, NULL, 300, 150, 0, 0, SWP_NOSIZE);
            loadimage(&jiankang, "D:\\c语言\\测试9\\健康.jpg", 800, 500);
            putimage(0, 0, &jiankang);
            break;
        }
        break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        Gdiplus::Graphics graphics(hdc);
        // 加载图片
        Gdiplus::Image image(L"D:\\c语言\\打砖块游戏\\tutu\\菜单界面三选一\\菜单选择1.jpg");
        // 绘制图片
        graphics.DrawImage(&image, 0, 0, ps.rcPaint.right, ps.rcPaint.bottom);
        EndPaint(hwnd, &ps);
    }
    break;
    case WM_DESTROY:
        // 关闭GDI+
        Gdiplus::GdiplusShutdown(gdiplusToken);
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, message, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    const char g_szClassName[] = "myWindowClass";

    WNDCLASSEX wc;
    HWND hwnd;
    MSG Msg;

    // 注册窗口类
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = 0;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = NULL; // 设置为NULL，以便在WM_PAINT中自定义背景
    wc.lpszMenuName = NULL;
    wc.lpszClassName = g_szClassName;
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    if (!RegisterClassEx(&wc)) {
        MessageBox(NULL, "Window Registration Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    // 创建窗口
    hwnd = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        g_szClassName,
        "A Simple Window",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 1080, 600,
        NULL, NULL, hInstance, NULL);

    if (hwnd == NULL) {
        MessageBox(NULL, "Window Creation Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    // 主消息循环
    while (GetMessage(&Msg, NULL, 0, 0) > 0) {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
    return Msg.wParam;
}