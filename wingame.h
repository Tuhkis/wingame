#ifndef __WINGAME_H__
#define __WINGAME_H__

/* C++ compatibility */
#ifdef __cplusplus
extern "C" {
#endif /* __cplus */

/* Includes */
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#include "process.h"

/* Macro definitions */
#undef TD
#ifndef TD
#define TD typedef
#endif /* TD */

#define var const
#define mut

/* Make sure NULL exists */
#ifndef NULL
#ifdef __cplusplus
#define NULL nullptr
#else
#define NULL (0)
#endif /* __cplusplus */
#endif /* NULL */

/* I decided to undef MAX and MIN,        *
 * because this implementation is smarter *
 * than any other implementation.         */

#undef MIN
#ifndef MIN
#define MIN(a, b) (b + ((a - b) & (a - b) >> 31))
#endif /* MIN */

#undef MAX
#ifndef MAX
#define MAX(a, b) (a - ((a - b) & (a - b) >> 31))
#endif /* MAX */

#ifndef ABS
#define ABS(x) ((x) < 0 ? -(x) : (x))
#endif /* ABS */

#define _wg_main I32 WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, I32 nShowCmd)
#define wg_init wg_init_ex(hInstance)
#define wg_create_window(title, width, height) wg_create_window_ex(title, width, height, hInstance, nShowCmd)
#define wg_close_window(win) DestroyWindow(win.win_handle)
#define wg_window_event_process \
	TranslateMessage(&_wg_msg); \
	DispatchMessage(&_wg_msg)
#define wg_create_thread(proc, params) (HANDLE) (_beginthread(proc, 0, params))
#define wg_window_update \
	InvalidateRect(_wg_win.win_handle, NULL, false); \
	UpdateWindow(_wg_win.win_handle)
#define wg_create_brush(col) CreateSolidBrush(col)
#define wg_delete_object(obj) DeleteObject(obj)

/* WARN: Sleep is inprecise. */
#define wg_sleep(t) Sleep(t)

#ifndef true
#define true (1==1)
#endif /* true */

#ifndef false
#define false (2==1)
#endif /* false */

#ifndef RGB
#error Something has gone vey wrong. (RGB-macro not defined.)
#else
#define wg_rgb(r, g, b) RGB(r, g, b)
#endif /* RGB */

#ifndef WINGAME_BG_COL
#define WINGAME_BG_COL wg_rgb(60, 60, 60)
#endif /* WINGAME_BG_COL */

/* Types */
#ifndef U8 /* If U8 is not defined, we can safely assume the rest aren't either. */
TD unsigned char U8;
TD signed char I8;
TD unsigned char B8;

TD unsigned short U16;
TD signed short I16;

TD unsigned int U32;
TD signed int I32;

TD unsigned long U64;
TD signed long I64;

TD float F32;
TD double F64;
#endif /* U8 */

TD enum wg_renderer_type {
	WG_RENDERER_RECT,
	WG_RENDERER_TEXT,
} wg_Renderer_type;

TD HBRUSH wg_Brush;

TD struct wg_window {
	HWND win_handle;
} wg_Window;

TD struct wg_app {
	wg_Window win;
	HANDLE ready;
	I32 width, height;
	char* title;
} wg_App;

TD struct wg_renderer {
	wg_Brush b;
	void* data;
	wg_Renderer_type t;
} wg_Renderer;

/* Keycodes... fun to type out. */
TD enum wg_keycode {
	WG_KEY_BACKSPACE = 8,
	WG_KEY_TAB = 9,
	WG_KEY_ENTER = 13,
	WG_KEY_SHIFT = 16,
	WG_KEY_CTRL = 17,
	WG_KEY_ALT = 18,
	WG_KEY_PAUSE = 19,
	WG_KEY_CAPSLOCK = 20,
	WG_KEY_ESC = 27,
	WG_KEY_SPACE = 32,
	WG_KEY_PAGEUP = 33,
	WG_KEY_PAGEDOWN = 34,
	WG_KEY_END = 35,
	WG_KEY_HOME = 36,
	WG_KEY_LEFT = 37,
	WG_KEY_UP = 38,
	WG_KEY_RIGHT = 39,
	WG_KEY_DOWN = 40,
	WG_KEY_SELECT = 41,
	WG_KEY_PRINT = 42,
	WG_KEY_EXECUTE = 43,
	WG_KEY_PRTSCR = 44,
	WG_KEY_INS = 45,
	WG_KEY_DEL = 46,
	WG_KEY_HELP = 47,
	WG_KEY_0 = 48,
	WG_KEY_1 = 49,
	WG_KEY_2 = 50,
	WG_KEY_3 = 51,
	WG_KEY_4 = 52,
	WG_KEY_5 = 53,
	WG_KEY_6 = 54,
	WG_KEY_7 = 55,
	WG_KEY_8 = 56,
	WG_KEY_9 = 57,
	WG_KEY_A = 65,
	WG_KEY_B = 66,
	WG_KEY_C = 67,
	WG_KEY_D = 68,
	WG_KEY_E = 69,
	WG_KEY_F = 70,
	WG_KEY_G = 71,
	WG_KEY_H = 72,
	WG_KEY_I = 73,
	WG_KEY_J = 74,
	WG_KEY_K = 75,
	WG_KEY_L = 76,
	WG_KEY_M = 77,
	WG_KEY_N = 78,
	WG_KEY_O = 79,
	WG_KEY_P = 80,
	WG_KEY_Q = 81,
	WG_KEY_R = 82,
	WG_KEY_S = 83,
	WG_KEY_T = 84,
	WG_KEY_U = 85,
	WG_KEY_V = 86,
	WG_KEY_W = 87,
	WG_KEY_X = 88,
	WG_KEY_Y = 89,
	WG_KEY_Z = 90,
	WG_KEY_NUMPAD0 = 96,
	WG_KEY_NUMPAD1 = 97,
	WG_KEY_NUMPAD2 = 98,
	WG_KEY_NUMPAD3 = 99,
	WG_KEY_NUMPAD4 = 100,
	WG_KEY_NUMPAD5 = 101,
	WG_KEY_NUMPAD6 = 102,
	WG_KEY_NUMPAD7 = 103,
	WG_KEY_NUMPAD8 = 104,
	WG_KEY_NUMPAD9 = 105,
	WG_KEY_MUL = 106,
	WG_KEY_ADD = 107,
	WG_KEY_SEP = 108,
	WG_KEY_SUB = 109,
	WG_KEY_DECIMAL = 110,
	WG_KEY_DIV = 111,
	WG_KEY_F1 = 112,
	WG_KEY_F2 = 113,
	WG_KEY_F3 = 114,
	WG_KEY_F4 = 115,
	WG_KEY_F5 = 116,
	WG_KEY_F6 = 117,
	WG_KEY_F7 = 118,
	WG_KEY_F8 = 119,
	WG_KEY_F9 = 120,
	WG_KEY_F10 = 121,
	WG_KEY_F11 = 122,
	WG_KEY_F12 = 123,
	WG_KEY_F13 = 124,
	WG_KEY_F14 = 125,
	WG_KEY_F15 = 126,
	WG_KEY_F16 = 127,
	WG_KEY_F17 = 128,
	WG_KEY_F18 = 129,
	WG_KEY_F19 = 130,
	WG_KEY_F20 = 131,
	WG_KEY_F21 = 132,
	WG_KEY_F22 = 133,
	WG_KEY_F23 = 134,
	WG_KEY_F24 = 135,
} wg_Keycode;

/* Vars */
static var char* _WG_WINDOW_CLASS_NAME = (char*)"wingame_window_class";
static mut WNDCLASS _wg_window_class = {0};
static mut B8 _wg_running = true;
static mut wg_Window _wg_win = {0};
static mut wg_Brush _wg_bg_b;
static mut MSG _wg_msg = {0};

/* Function declarations */
LRESULT CALLBACK wg_window_proc(HWND hwnd, U32 msg, WPARAM wParam, LPARAM lParam);
void wg_init_ex(HINSTANCE hInstance);
void wg_create_window_ex(char *title, I32 width, I32 height, HINSTANCE hInstance, I32 scmd);
B8 wg_running();
void wg_key_down(wg_Keycode k);
void wg_key_up(wg_Keycode k);

wg_App wg_main();

/* Function implemantions */
#ifdef WG_IMPL
LRESULT CALLBACK wg_window_proc(HWND hwnd, U32 msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_SIZE: {
		/* var I32 w = LOWORD(lParam); *
		 * var I32 h = HIWORD(lParam); */
		/* TODO: Deal with resizing the window. */
		return DefWindowProc(hwnd, msg, wParam, lParam);
		break;
	}
	case WM_QUIT: /* NOTE: Fallthrough */
	case WM_DESTROY: {
		_wg_running = false;
		PostQuitMessage(0);
		break;
	}
	case WM_PAINT: {
		static mut RECT winr;
		GetWindowRect(_wg_win.win_handle, &winr);
		mut PAINTSTRUCT ps;
		mut HDC hdc = BeginPaint(_wg_win.win_handle, &ps);
		mut HDC mem_hdc = CreateCompatibleDC(hdc);
		mut HBITMAP mem_b_map = CreateCompatibleBitmap(hdc, winr.right - winr.left, winr.bottom - winr.top);
		SelectObject(mem_hdc, mem_b_map);
		/* DRAW THINGS TO MEM_HDC */
		var RECT bgr = {0, 0, winr.right - winr.left, winr.bottom - winr.top};
		FillRect(mem_hdc, &bgr, _wg_bg_b);

		BitBlt(hdc, 0, 0, winr.right - winr.left, winr.bottom - winr.top, mem_hdc, 0, 0, SRCCOPY);
		DeleteObject(mem_b_map);
		DeleteDC(mem_hdc);
		DeleteDC(hdc);
		EndPaint(_wg_win.win_handle, &ps);
		break;
	}
	case WM_KEYDOWN: {
		wg_key_down((wg_Keycode)wParam);
		break;
	}
	case WM_KEYUP: {
		wg_key_up((wg_Keycode)wParam);
		break;
	}
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
		break;
	}
	return 0;
}

void wg_init_ex(HINSTANCE hInstance) {
	_wg_window_class.lpfnWndProc = wg_window_proc;
	_wg_window_class.hInstance = hInstance;
	_wg_window_class.lpszClassName = _WG_WINDOW_CLASS_NAME;
	RegisterClass(&_wg_window_class);
}

void wg_create_window_ex(char *title, I32 width, I32 height, HINSTANCE hInstance, I32 scmd) {
	mut wg_Window ret = {0};
	_wg_running = true;
	ret.win_handle = CreateWindowEx(0, _WG_WINDOW_CLASS_NAME, title, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, width, height,
		NULL, NULL, hInstance, NULL);

	if (ret.win_handle == NULL) exit(1);
	ShowWindow(ret.win_handle, scmd);
	_wg_win = ret;
	_wg_bg_b = CreateSolidBrush(WINGAME_BG_COL);
}

B8 wg_running() {
	return _wg_running;
}

_wg_main {
	mut wg_App a = wg_main();
	wg_init;
	if (a.title == NULL) a.title = (char*)"Game Window";
	if (a.width == 0) a.width = 800;
	if (a.height == 0) a.height = 600;
	wg_create_window(a.title, a.width, a.height);

	while (_wg_running && GetMessage(&_wg_msg, NULL, 0, 0)) {
		wg_window_event_process;
	}
	WaitForSingleObject(a.ready, INFINITE);
	/* TerminateThread(a.ready, 0); */
	DeleteObject(_wg_bg_b); /* Delete the background brush object. */
	wg_close_window(a.win);
	return 0;
}

#endif /* WG_IMPL */

/* C++ compatibility */
#ifdef __cplusplus
}
#endif /* __cplus */

#endif /* __WINGAME_H__ */