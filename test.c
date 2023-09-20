#define WG_IMPL
#include "wingame.h"

#include <stdio.h>

#define FPS (60)

mut wg_Brush b[4];
mut U32 x = 32;

void wg_key_down(wg_Keycode k) {
	if (k == WG_KEY_SPACE) printf_s("Space down\n");
}

void wg_key_up(wg_Keycode k) {
	if (k == WG_KEY_SPACE) printf_s("Space up\n");
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
}

wg_App wg_main() {
	b[0] = wg_create_brush(wg_rgb(232, 255, 60));
	b[1] = wg_create_brush(wg_rgb(255, 40, 232));
	b[2] = wg_create_brush(wg_rgb(255, 40, 40));
	b[3] = wg_create_brush(wg_rgb(128, 255, 255));
	mut wg_App app = {0};
	app.title = (char*)"Game Window";
	app.width = 1024 - 128;
	app.height = 512 + 128;
	app.ready = wg_create_thread(ready, NULL);
	
	printf_s("Sin 90: %f.\n", _wg_sin[90]);
	
	return app;
}
