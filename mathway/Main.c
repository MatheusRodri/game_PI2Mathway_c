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
int c[30][40];
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

int main() {
	ALLEGRO_DISPLAY* janela = NULL;
	ALLEGRO_EVENT_QUEUE* fila_eventos = NULL;

	al_init();
	al_init_image_addon();
	al_install_keyboard();
	

	janela = al_create_display(1280, 960);
	fila_eventos = al_crate_event_queue();

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
	readTile();


	bool jogando = true;
	
	while (jogando)
	{
		while (!al_is_event_queue_empty(fila_eventos)) {
			ALLEGRO_EVENT evento;
			al_wait_for_event(fila_eventos, &evento);

			if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
				jogando = 0;
			}
		}


		al_flip_display();	
	}
	return 0;
}
