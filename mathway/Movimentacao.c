#include <allegro5\allegro.h>  
#include <allegro5\allegro_image.h>    


void movi() {
	//criação dos ponteiros utilizados para criar o display, a fila de evento e o bitmap(img)
	ALLEGRO_DISPLAY* display;
	ALLEGRO_EVENT_QUEUE* queue;
	ALLEGRO_BITMAP* bitmap = NULL;
	//inicia o allegro, var display e var queue(fila)
	al_init();
	display = al_create_display(640, 480);
	queue = al_create_event_queue();

	//instala o teclado 
	al_install_keyboard();
	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_display_event_source(display));

	al_init_image_addon();
	bitmap = al_load_bitmap("carinha.jpg");

	assert(bitmap != NULL);

	bool running = true;

	float x = 320, y = 240;
	int width = al_get_display_width(display);

	while (running) {
		al_clear_to_color(al_map_rgba_f(0, 0, 0, 1));
		al_draw_bitmap(bitmap, x, y, 0);
		al_flip_display();

		ALLEGRO_EVENT event;

		if (!al_is_event_queue_empty(queue)) {
			al_wait_for_event(queue, &event);
		}

		// Actively poll the keyboard  		
		ALLEGRO_KEYBOARD_STATE keyState;
		al_get_keyboard_state(&keyState);

		if (al_key_down(&keyState, ALLEGRO_KEY_RIGHT))
			if (al_key_down(&keyState, ALLEGRO_KEY_LCTRL))
				x += 0.5;
			else
				x += 0.1;
		if (al_key_down(&keyState, ALLEGRO_KEY_LEFT))
			if (al_key_down(&keyState, ALLEGRO_KEY_LCTRL))
				x -= 0.5;
			else
				x -= 0.1;
		if (al_key_down(&keyState, ALLEGRO_KEY_UP))
			if (al_key_down(&keyState, ALLEGRO_KEY_LCTRL))
				y -= 0.5;
			else
				y -= 0.1;
		if (al_key_down(&keyState, ALLEGRO_KEY_DOWN))
			if (al_key_down(&keyState, ALLEGRO_KEY_LCTRL))
				y += 0.5;
			else
				y += 0.1;
	}

	//desisntala as coisas para não ar problema de buffer de memória 
	al_destroy_display(display);
	al_uninstall_keyboard();
	al_uninstall_mouse();
	al_destroy_bitmap(bitmap);


}