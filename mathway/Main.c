#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#define _CRT_SECURE_NO_DEPRECATE 
#define _CRT_NONSTDC_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS


ALLEGRO_BITMAP* fTile[100];
int linhas, colunas;
int c[30][45];
FILE* mapa;

int maps[];



void readTile() {

	for (int i = 0; i < linhas; i++)
	{
		for (int j = 0; j < colunas; j++)
		{
			for (int k = 0; k < 30; k++)
			{
				if (c[i][j] == k)
				{
					al_draw_bitmap(fTile[k], j * 32, i * 32, 0);


				}

			}
		}
	}
}


void gameOver() {

	ALLEGRO_DISPLAY* gmOv = NULL;

	ALLEGRO_BITMAP* fundo = NULL;


	al_init();


	al_init_image_addon();


	gmOv = al_create_display(1440, 960);
	fundo = al_load_bitmap("Tiles/game.png");

	al_draw_bitmap(fundo, 0, 0, 0);

	al_flip_display();







}



int main() {
	ALLEGRO_DISPLAY* janela = NULL;
	ALLEGRO_EVENT_QUEUE* fila_eventos = NULL;
	ALLEGRO_BITMAP* bitmap;
	ALLEGRO_TIMER* timer;
	ALLEGRO_KEYBOARD_STATE keyState;

	al_init();
	al_init_image_addon();
	al_install_keyboard();
	al_init_image_addon();

	janela = al_create_display(1440, 960);
	fila_eventos = al_create_event_queue();
	al_register_event_source(fila_eventos, al_get_keyboard_event_source());
	al_register_event_source(fila_eventos, al_get_display_event_source(janela));
	bitmap = al_load_bitmap("sprites/hosmi.png");

	int width = al_get_display_width(janela);

	timer = al_create_timer(1.0 / 30);
	al_register_event_source(fila_eventos, al_get_timer_event_source(timer));
	al_start_timer(timer);


	ALLEGRO_FONT* font = al_create_builtin_font();

	fTile[0] = al_load_bitmap("Tiles/grass.bmp");
	fTile[1] = al_load_bitmap("Tiles/dirty.bmp");
	fTile[2] = al_load_bitmap("Tiles/tree1.bmp");
	fTile[3] = al_load_bitmap("Tiles/tree2.bmp");
	fTile[4] = al_load_bitmap("Tiles/tree3.bmp");
	fTile[5] = al_load_bitmap("Tiles/tree4.bmp");
	fTile[6] = al_load_bitmap("Tiles/water1.bmp");
	fTile[7] = al_load_bitmap("Tiles/water2.bmp");
	fTile[8] = al_load_bitmap("Tiles/water3.bmp");
	fTile[9] = al_load_bitmap("Tiles/water4.bmp");
	fTile[10] = al_load_bitmap("Tiles/P1.bmp");
	fTile[11] = al_load_bitmap("Tiles/P2.bmp");
	fTile[12] = al_load_bitmap("Tiles/P3.bmp");
	fTile[13] = al_load_bitmap("Tiles/P4.bmp");
	fTile[14] = al_load_bitmap("Tiles/P6.bmp");
	fTile[15] = al_load_bitmap("Tiles/P7.bmp");
	fTile[16] = al_load_bitmap("Tiles/P10.bmp");
	fTile[17] = al_load_bitmap("Tiles/P11.bmp");
	fTile[18] = al_load_bitmap("Tiles/WaterL.bmp");
	fTile[19] = al_load_bitmap("Tiles/WaterR.bmp");
	fTile[20] = al_load_bitmap("Tiles/dirtyup.bmp");
	fTile[21] = al_load_bitmap("Tiles/dirtyDo.bmp");
	fTile[22] = al_load_bitmap("Tiles/ArvoreE.bmp");
	fTile[23] = al_load_bitmap("Tiles/ArvoreD.bmp");


	bool jogando = true;
	bool running = true, draw = true, ativo = false;
	enum direcao { CIMA, DIREITA, BAIXO, ESQUERDA };
	float x = 320, y = 240;
	float movSpeed = 5;
	float dir = BAIXO;
	float sourceX = 0;
	float sourceY = 0;

	mapa = fopen("Mapa/mapa.txt", "r");
	fscanf(mapa, "%i", &linhas);
	fscanf(mapa, "%i", &colunas);

	for (int i = 0; i < linhas; i++)
	{
		for (int j = 0; j < colunas; j++)
		{
			fscanf(mapa, "%i, %i", &c[i][j]);
		}
	}




	while (jogando)
	{
		while (!al_is_event_queue_empty(fila_eventos)) {
			ALLEGRO_EVENT evento;
			al_wait_for_event(fila_eventos, &evento);
			al_get_keyboard_state(&keyState);
			if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
				jogando = 0;
			}










			if (evento.type == ALLEGRO_EVENT_TIMER) {
				ativo = true;




				if (al_key_down(&keyState, ALLEGRO_KEY_DOWN)/* && y < 850*/) {
					//bool and = true;


					//for (int i = 0; i < linhas; i++)
					//{
					//	for (int j = 0; j < colunas; j++)
					//	{
					//		int lug = j * 32;
					//		if (lug == y && c[i][j] != 0) {
					//			and = false;
					//		}
					//	}
					//}
					//while (and == true) {

					int yy = (int)y;
					int resto = yy % 32;
					float pos = y / 32;
					int i = 0;
					int coisa;

					int xx = (int)x;
					int resto1 = xx % 32;
					float pos1 = x / 32;
					int j = 0;
					int coisa1;

					if (resto == 0) {

						i = (int)pos;
					}
					else if (resto > 0) {
						coisa = (int)pos;
						i = coisa + 1;
					}


					if (resto1 == 0) {

						j = pos1;
					}
					else if (resto1 > 0) {
						coisa1 = pos1;
						j = 1 + coisa1;
					}

					if (c[i + 2][j + 1] == 0 || x < 32)
					{

						y += movSpeed;
						dir = BAIXO;
					}





				}
				else if (al_key_down(&keyState, ALLEGRO_KEY_UP) && y > 0) {

					int yy = (int)y;
					int resto = yy % 32;
					float pos = y / 32;
					int i = 0;
					int coisa;

					int xx = (int)x;
					int resto1 = xx % 32;
					float pos1 = x / 32;
					int j = 0;
					int coisa1;

					if (resto == 0) {

						i = (int)pos;
					}
					else if (resto > 0) {
						coisa = (int)pos;
						i = coisa + 1;
					}


					if (resto1 == 0) {

						j = pos1;
					}
					else if (resto1 > 0) {
						coisa1 = pos1;
						j = 1 + coisa1;
					}

					if (c[i][j] == 0 || x < 32)
					{
						y -= movSpeed;
						dir = CIMA;

					}

				}
				else if (al_key_down(&keyState, ALLEGRO_KEY_RIGHT)) {
					int j = 0;

					int yy = (int)y;
					int resto = yy % 32;
					float pos = y / 32;
					int i = 0;
					int coisa;

					int xx = (int)x;
					int resto1 = xx % 32;
					float pos1 = x / 32;



					int coisa1;

					if (resto == 0) {

						i = (int)pos;
					}
					else if (resto > 0) {
						coisa = (int)pos;
						i = coisa + 1;
					}


					if (resto1 == 0) {

						j = pos1;
					}
					else if (resto1 > 0) {
						coisa1 = pos1;
						j = 1 + coisa1;
					}

					if ((c[i + 1][j + 1] == 0 && x < 1370) || x < 32)
					{

						x += movSpeed;
						dir = DIREITA;
					}



				}
				else if (al_key_down(&keyState, ALLEGRO_KEY_LEFT)) {


					int yy = (int)y;
					int resto = yy % 32;
					float pos = y / 32;
					int j = 0;
					int coisa;

					int xx = (int)x;
					int resto1 = xx % 32;
					float pos1 = x / 32;
					int i = 0;
					int coisa1;

					if (resto == 0) {

						i = (int)pos;
					}
					else if (resto > 0) {
						coisa = (int)pos;
						i = coisa + 1;
					}


					if (resto1 == 0) {

						j = pos1;
					}
					else if (resto1 > 0) {
						coisa1 = pos1;
						j = 1 + coisa1;
					}

					if (c[i + 1][j] == 0 && x > 0)
					{
						x -= movSpeed;
						dir = ESQUERDA;
					}

				}



				else if (al_key_down(&keyState, ALLEGRO_KEY_ESCAPE)) {
					gameOver();
					al_destroy_display(janela);
					al_destroy_bitmap(bitmap);


				}
				else { ativo = false; }






				if (ativo)
					sourceX += al_get_bitmap_width(bitmap) / 3;
				else
					sourceX = 0;
				if (sourceX >= al_get_bitmap_width(bitmap))
					sourceX = 90;
				sourceY = dir;
				draw = true;
			}
		}
		readTile();
		al_draw_bitmap_region(bitmap, sourceX, sourceY * al_get_bitmap_height(bitmap) / 4, 90, 126, x, y, NULL);
		al_flip_display();
	}
	al_destroy_display(janela);
	al_uninstall_keyboard();
	al_uninstall_mouse();
	al_destroy_bitmap(bitmap);

	al_destroy_event_queue(fila_eventos);

	return 0;
}