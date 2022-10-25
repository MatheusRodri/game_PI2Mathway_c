#include <allegro5\allegro.h>  
#include <allegro5\allegro_image.h>    

void gerarSprites() {

	//variaveis
	int width = 640;
	int height = 480;

	int imgWidht = 0;
	int imgHeight = 0;

	const int spriteSize = 2;

	//Variaeveis allegro
	ALLEGRO_DISPLAY* display = NULL;
	ALLEGRO_BITMAP* img[2];
	ALLEGRO_BITMAP* sprite;

	//init
	!al_init();
		
	
	display = al_create_display(width, height);

	
		

	al_init_image_addon();
	img[0] = al_load_bitmap("frame-1.png");
	img[1] = al_load_bitmap("frame-2.png");

	imgWidht=al_get_bitmap_width(img[0]);
	imgHeight=al_get_bitmap_height(img[1]);
	
	sprite = al_create_bitmap(imgWidht * spriteSize, imgHeight);

	al_set_target_bitmap(sprite);
	al_clear_to_color(al_map_rgb(0, 0, 0));
	for (int i = 0; i < spriteSize; i++) {
		al_draw_bitmap(img[i], i * imgWidht, 0, 0);
	}

	al_save_bitmap("spritMontado.png", sprite);

	al_set_target_bitmap(al_get_backbuffer(display));

	for (int i = 0; i < spriteSize; i++) {
		al_destroy_bitmap(img[i]);
	}
	al_destroy_bitmap(sprite);
	al_destroy_display(display);
}