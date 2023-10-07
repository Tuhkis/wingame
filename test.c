#define WG_IMPL
/* #define WG_CUSTOM_RENDER */
#include "wingame.h"

#include <stdio.h>

#define FPS (60)

mut wg_Brush b[4];
mut U32 x = 32;

/* HBITMAP bmap = NULL; */

void wg_key_down(wg_Keycode k) {
	if (k == WG_KEY_SPACE) printf_s(STR"Space down\n");
}

void wg_key_up(wg_Keycode k) {
	if (k == WG_KEY_SPACE) printf_s(STR"Space up\n");
}

static void ready() {
	while (wg_running()) {
		++x;
		if (x > 512) x = 32;
		
		wg_window_update;
		wg_sleep(1000 / FPS);
	}
	
	wg_delete_object(b[0]);
	wg_delete_object(b[1]);
	wg_delete_object(b[2]);
	wg_delete_object(b[3]);
	return;
}

void wg_render(wg_Graphics g) {
	mut U8 a = 0;
	for (mut U8 x = 0; x < 17; ++x) {
		for (mut U8 i = 0; i < 5; ++i) {
			var RECT r = {i * 32 + (x * 42), i * 32, i * 32 + 32 + (x * 42), i * 32 + 32};
			FillRect(g, &r, b[a]);
			++a;
			if (a > 3) a = 0;
		}
		++a;
		if (a > 3) a = 0;
	}
	
	wg_PointI64 m_pos = wg_get_mouse_pos();
	RECT r = {m_pos.x, m_pos.y, m_pos.x + 32, m_pos.y + 32};
	FillRect(g, &r, b[0]);

	/* BITMAP bm;
	HDC hdcMem = CreateCompatibleDC(g);
	HBITMAP hbmOld = SelectObject(hdcMem, bmap);
	GetObject(bmap, sizeof(bm), &bm);
	BitBlt(g, 0, 0, bm.bmWidth, bm.bmHeight, hdcMem, 0, 0, SRCCOPY);
	SelectObject(hdcMem, hbmOld);
	DeleteDC(hdcMem); */
}

wg_App wg_main(void) {
	/* bmap = LoadImage( NULL, ".\test.bmp", IMAGE_BITMAP, 64, 64, LR_LOADFROMFILE); */
	
	b[0] = wg_create_brush(wg_rgb(232, 255, 60));
	b[1] = wg_create_brush(wg_rgb(255, 40, 232));
	b[2] = wg_create_brush(wg_rgb(255, 40, 40));
	b[3] = wg_create_brush(wg_rgb(128, 255, 255));
	mut wg_App app = {0};
	app.title = STR"Game Window";
	app.width = 1024 - 128;
	app.height = 512 + 128;
	app.ready = wg_create_thread(ready, NULL);
	
	printf_s(STR"wg_sin(90) = %f.\n", wg_sin(90));
	printf_s(STR"wg_invsqrt(90) = %f.\n", wg_invsqrt(90));
	printf_s(STR"wg_sqrt(9) = %f.\n", wg_sqrt(9));
	
	return app;
}
