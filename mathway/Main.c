#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_ttf.h>
#define _CRT_SECURE_NO_DEPRECATE 
#define _CRT_NONSTDC_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS


const int larg = 1440;
const int altu = 960;

ALLEGRO_BITMAP* fTile[100];
int linhas, colunas;
int c[30][45];
FILE* mapa;

int maps[];
//nova movimentação

enum direcao { BAIXO, ESQUERDA, DIREITA, CIMA };

//struct para inserir personagens na tela
typedef struct personagens persona;
struct personagens {
	float x;
	float y;
	float velX;
	float velY;
	float dirX;
	float dirY;
	//proporções
	int boundX;
	int boundY;
	int w;
	int h;

	ALLEGRO_BITMAP* perImage;
};


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
	ALLEGRO_TIMER* timer;
	ALLEGRO_KEYBOARD_STATE keyState;

	al_init();
	
	al_install_keyboard();
	al_init_image_addon();

	janela = al_create_display(larg, altu);
	fila_eventos = al_create_event_queue();
	al_register_event_source(fila_eventos, al_get_keyboard_event_source());
	al_register_event_source(fila_eventos, al_get_display_event_source(janela));
	 

	int width = al_get_display_width(janela);



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


	//iniciando personagens 
	persona player;
	player.x = 320;
	player.y = 240;
	player.perImage= al_load_bitmap("sprites/personagem.png");

	player.w = al_get_bitmap_width(player.perImage);
	player.h = al_get_bitmap_height(player.perImage);

	player.boundX = player.w / 10;
	player.boundY = player.h / 10;

	//inimigo
	persona inimigo;
	inimigo.x = larg / 2;
	inimigo.y = altu / 2;
	inimigo.perImage = al_load_bitmap("sprites/inimigo.jpg");

	inimigo.w = al_get_bitmap_width(inimigo.perImage);
	inimigo.h = al_get_bitmap_height(inimigo.perImage);

	inimigo.boundX = inimigo.w / 2;
	inimigo.boundY = inimigo.h / 2;


	bool colisao = false;
	bool bound = false;
	bool render = false;


	bool jogando = true;
	bool running = true, draw = true, ativo = false;
	
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
	

	timer = al_create_timer(1.0 / 60.0);
	al_register_event_source(fila_eventos, al_get_timer_event_source(timer));
	al_start_timer(timer);
	
	
	
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
				render = true;
				bound = false;
				if (al_key_down(&keyState, ALLEGRO_KEY_DOWN)&& player.y < 850 ) {

						player.y += movSpeed;
						dir = BAIXO;
				}
				else if (al_key_down(&keyState, ALLEGRO_KEY_UP)&& player.y > 0 ) {
					player.y -= movSpeed;
					dir = CIMA;
				}
			
				else if (al_key_down(&keyState, ALLEGRO_KEY_RIGHT) && player.x < 1370) {
					player.x += movSpeed;
					dir = DIREITA;
				}
				else if (al_key_down(&keyState, ALLEGRO_KEY_LEFT) && player.x > 0) {
					player.x -= movSpeed;
					dir = ESQUERDA;
					
				}
			
				else if (al_key_down(&keyState, ALLEGRO_KEY_ESCAPE)) {
					jogando = false;
					
				}
				else { ativo = false; }

				if (player.x + 64 > inimigo.x - inimigo.boundX &&
					player.x<inimigo.x + inimigo.boundX &&
					player.y + 64>inimigo.y - inimigo.boundY &&
					player.y < inimigo.y + inimigo.boundY) {
					colisao = true;
					bound = true;
					ativo = false;
				}
				else
					bound = false;
					colisao = false;



				if (ativo)
					sourceX += al_get_bitmap_width(player.perImage) / 4.0;
				else
					sourceX = 0;
				if (sourceX >= al_get_bitmap_width(player.perImage))
					sourceX = 0;
				sourceY = dir;
				draw = true;
			}
		}
		readTile();
		if (render && al_is_event_queue_empty(fila_eventos)) {
			render = false;
			//desenho
			al_draw_bitmap_region(player.perImage, sourceX, sourceY* al_get_bitmap_height(player.perImage) / 4, 64, 64, player.x, player.y, NULL);
			al_draw_bitmap(inimigo.perImage, inimigo.x, inimigo.y, 0);
			if (bound) {
				al_draw_filled_rectangle(player.x, player.y, player.x + 64, player.y + 64, al_map_rgba_f(.6, 0, .6, .6));
				al_draw_filled_rectangle(inimigo.x - inimigo.boundX, inimigo.y - inimigo.boundY, inimigo.x + inimigo.boundX, inimigo.y + inimigo.boundY, al_map_rgba_f(.6, 0, .6, .6));
			}
			if (colisao) {
				ativo = false;
				
			}
			
			al_flip_display();
		}
			
	}
	al_destroy_display(janela);
	al_uninstall_keyboard();
	al_uninstall_mouse();
	al_destroy_bitmap(player.perImage);

	al_destroy_event_queue(fila_eventos);

	return 0;
}