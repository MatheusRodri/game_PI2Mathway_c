#include <allegro5\allegro.h>  
#include <allegro5\allegro_image.h>    


void movi() {
	//variaveis globais 
	bool running = true,draw=true,ativo=false;
	enum direcao{CIMA,DIREITA,BAIXO,ESQUERDA};
	float x = 320, y = 240;
	float movSpeed = 5;
	float dir=BAIXO;
	float sourceX=0;
	float sourceY=0;
	
	
	

	
	//criação dos ponteiros utilizados para criar o display, a fila de evento e o bitmap(img)
	ALLEGRO_DISPLAY* display = NULL;
	ALLEGRO_EVENT_QUEUE* queue = NULL;
	ALLEGRO_BITMAP* bitmap;
	ALLEGRO_TIMER* timer;
	

		
	//inicia o allegro, var display e var queue(fila)
	al_init();

	display = al_create_display(900, 600);
	queue = al_create_event_queue();



	//instala o teclado 
	al_install_keyboard();
	ALLEGRO_KEYBOARD_STATE keyState;
	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_display_event_source(display));
	
	
	al_init_image_addon();
	bitmap = al_load_bitmap("hosmi.png");
	
	
	
	
	int width = al_get_display_width(display);
	
	

	timer = al_create_timer(1.0/30);
	al_register_event_source(queue, al_get_timer_event_source(timer));
	al_start_timer(timer);
	while (running) {
		

		ALLEGRO_EVENT event;
		al_wait_for_event(queue, &event);
		al_get_keyboard_state(&keyState);
	
		if (event.type == ALLEGRO_EVENT_TIMER) {
			ativo = true;
			if (al_key_down(&keyState, ALLEGRO_KEY_DOWN)){
				 y += movSpeed;
				 dir = BAIXO;
			}else if (al_key_down(&keyState, ALLEGRO_KEY_UP)) {
				 y -= movSpeed;
				 dir = CIMA;
			}else if (al_key_down(&keyState, ALLEGRO_KEY_RIGHT)) {
				 x += movSpeed;
				 dir = DIREITA;
			}else if (al_key_down(&keyState, ALLEGRO_KEY_LEFT)) {
				 x -= movSpeed;
				 dir = ESQUERDA;
			}
			 else if (al_key_down(&keyState, ALLEGRO_KEY_ESCAPE)) {
				 running = false;
			}
			 else { ativo = false; }

			if (ativo)
				sourceX += al_get_bitmap_width(bitmap) / 3;
			else
				sourceX = 0;
			 if (sourceX >= al_get_bitmap_width(bitmap))
				 sourceX = 90;
			 sourceY = dir;
			 draw =true;
		 }

		if (draw) {
			al_clear_to_color(al_map_rgba_f(0, 0, 0, 1));
			al_draw_bitmap_region(bitmap,sourceX, sourceY* al_get_bitmap_height(bitmap) / 4, 90,126, x, y, NULL);
			al_flip_display();
		}

	}


	//desisntala as coisas para não ar problema de buffer de memória 
	al_destroy_display(display);
	al_uninstall_keyboard();
	al_uninstall_mouse();
	al_destroy_bitmap(bitmap);
	
	al_destroy_event_queue(queue);
	

}