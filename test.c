#define WG_IMPL
#include "wingame.h"
#include <stdio.h>

void wg_key_down(wg_Keycode k) {
	if (k == WG_KEY_SPACE) printf_s("Space down\n");
}

void wg_key_up(wg_Keycode k) {
	if (k == WG_KEY_SPACE) printf_s("Space up\n");
}

static void ready(void*) {
	while (wg_running()) {
		wg_window_update;
		wg_sleep(16);
	}
	return;
}

wg_App wg_main() {
	mut wg_App app = {0};
	app.title = (char*)"Game Window";
	app.width = 1024;
	app.height = 512 + 128;
	app.ready = wg_create_thread(ready, NULL);
	return app;
}
