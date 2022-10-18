#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>


struct Sprite {
	float x;
	float y;
	float velX;
	float velY;
	int dirX;
	int dirY;

	int maxFrame;
	int curFrame;
	int frameCount;
	int frameDelay;
	int frameWidht;
	int frameHeight;
	int animationColumns;
	int animationDirection;

	ALLEGRO_BITMAP* image;

};
void novaMovi() {

	//variaveis 
	float width =1080;
	float height = 1920;
	bool done = false;


	Sprite monstrin;

	monstrin.x = width / 2;
	monstrin.y = height / 2;
	monstrin.velX = 5;
	monstrin.velY = 0;
	monstrin.dirX = -1;
	monstrin.dirY = 0;


	monstrin.maxFrame = 2;
	monstrin.curFrame = 0;
	monstrin.frameCount = 0;
	monstrin.frameDelay = 5;
	monstrin.frameWidht = 427;
	monstrin.frameHeight = 496;
	monstrin.animationColumns = 2;
	monstrin.animationDirection = 1;


	//allegro variaveis
	ALLEGRO_DISPLAY* display = NULL;
	ALLEGRO_EVENT_QUEUE* event_queue ;
	ALLEGRO_TIMER* timer;
	ALLEGRO_BITMAP* image;

	//init
	al_init();
	display = al_create_display(width, height);

	
	//addon init
	al_install_keyboard();
	al_init_image_addon();

	image = al_load_bitmap("spritMontado.png");
	al_convert_mask_to_alpha(image, al_map_rgb(106, 76, 48));
	monstrin.image = image;

	event_queue = al_create_event_queue();
	
	al_register_event_source(event_queue,al_get_keyboard_event_source());
	timer = al_create_timer(1.0 / 60);
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_start_timer(timer);

	while (!done) {
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			case ALLEGRO_KEY_LEFT:
				monstrin.animationDirection = 1;
				monstrin.dirX = -1;
				break;
			case ALLEGRO_KEY_RIGHT:
				monstrin.animationDirection = -1;
				monstrin.dirX = 1;
				break;
			case ALLEGRO_KEY_UP:

				break;
			case ALLEGRO_KEY_DOWN:

				break;
			}
		}
		else if (ev.type == ALLEGRO_EVENT_TIMER) {
			if (++monstrin.frameCount >= monstrin.frameDelay) {
				monstrin.curFrame += monstrin.animationDirection;
				if (monstrin.curFrame >= monstrin.maxFrame)
					monstrin.curFrame = 0;
				else if (monstrin.curFrame <= 0)
					monstrin.curFrame = monstrin.maxFrame - 1;

				monstrin.frameCount = 0;
			}

			monstrin.x += monstrin.velX * monstrin.dirX;

			if (monstrin.x <= -monstrin.frameWidht)
				monstrin.x = width;
			else if (monstrin.x > width)
				monstrin.x = 0 - monstrin.frameWidht;
			
		}
		al_draw_bitmap_region(monstrin.image, monstrin.curFrame * monstrin.frameWidht,0, monstrin.frameWidht, monstrin.frameHeight, monstrin.x, monstrin.y, 0);
		
		al_flip_display();
		al_clear_to_color(al_map_rgb(0, 0, 0));

	}


	al_destroy_bitmap(image);
	al_destroy_event_queue(event_queue);
	al_destroy_display(display);

	
}