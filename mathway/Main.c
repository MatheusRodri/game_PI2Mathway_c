#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <locale.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_ttf.h>
#include "Logica.h"

#define _CRT_SECURE_NO_DEPRECATE 
#define _CRT_NONSTDC_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS


const int larg = 1440;
const int altu = 960;


//variaveis de texto
const char quest[] = "7+7";
char answr[10];


ALLEGRO_BITMAP* fTile[100];
int linhas, colunas;
int c[30][45];
FILE* mapa;

int maps[];
//nova movimenta��o
enum direcao { BAIXO, ESQUERDA, DIREITA, CIMA };


//enumeracao de fase
enum fases { faseUm, faseDois, faseTres, faseQuatro, faseCinco };

void gameOver() {

	ALLEGRO_DISPLAY* gmOv = NULL;
	ALLEGRO_BITMAP* fundo = NULL;

	al_init();

	al_init_image_addon();

	gmOv = al_create_display(1440, 960);
	fundo = al_load_bitmap("Tiles/game.png");

	al_draw_bitmap(fundo, 0, 0, 0);

	al_flip_display();
	// fecha a tela de game over (d� interrup��o)
	/*
	ALLEGRO_EVENT close;
	ALLEGRO_EVENT_QUEUE *event = al_create_event_queue();
	al_register_event_source(event, al_get_display_event_source(gmOv));
	al_wait_for_event(event, &close);
	while (gmOv != NULL) {
		if (close.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			al_destroy_bitmap(fundo);
			atexit(0);
			al_destroy_display(gmOv);  
		}
	}*/
}

//void caixaTexto(ALLEGRO_FONT* font) {
//	al_draw_rectangle(50, 400, 750, 550, al_map_rgb(0, 0, 0), 3);
//	al_draw_filled_rectangle(50, 400, 750, 550, al_map_rgb(255, 255, 255));
//	al_draw_textf(font, al_map_rgb(0, 0, 0), 400, 420, ALLEGRO_ALIGN_CENTER, "%s", quest);
//	al_flip_display();
//}


//struct para inserir personagens na tela
typedef struct personagens persona;
struct personagens {
	float x;
	float y;
	float velX;
	float velY;
	float dirX;
	float dirY;

	//propor��es
	int boundX;
	int boundY;
	int w;
	int h;

	ALLEGRO_BITMAP* perImage;
};

int calcularPosicaoC(float x)
{
	int posC = (int)x;	
	float calcC = x / 32;
	int restC = posC % 32;
	int pos;

	if (restC == 0)
	{
		return (int)calcC;
	}
	else
	{
		pos = ((int)calcC) + 1;
	}
}

int calcularPosicaoL(float y)
{
	int posL = (int)y;
	float calcL = y / 32;
	int restL = posL % 32;
	int pos;

	if (restL == 0)
	{
		return (int)calcL;
	}
	else
	{
		pos = ((int)calcL) + 1;
	}
}

void telaInicial() {
	//iniciando tela inicial
	ALLEGRO_BITMAP* inScreen = al_load_bitmap("telainicial/inicio.png");
	al_draw_bitmap(inScreen, 0, 0, 0);
	

}
void fimTelaInicial() {
	ALLEGRO_BITMAP* inScreen = al_load_bitmap("telainicial/inicio.png");
	al_destroy_bitmap(inScreen);
}


void readTile() {

	for (int i = 0; i < linhas; i++)
	{
		for (int j = 0; j < colunas; j++)
		{
			for (int k = 0; k < 40; k++)
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
	al_init_ttf_addon();
	al_init_primitives_addon();
	al_init_font_addon();

    bool done = false;


    //posi�ao do texto
    int pos_x = 720;
	int pos_y = 800;

	ALLEGRO_FONT* fonte = al_load_font("Fonts/ariblk.ttf", 50, NULL);
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
	fTile[6] = al_load_bitmap("Tiles/path.bmp");
	fTile[7] = al_load_bitmap("Tiles/pathU.bmp");
	fTile[8] = al_load_bitmap("Tiles/LtoD.bmp");
	fTile[9] = al_load_bitmap("Tiles/UtoD.bmp");
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
	fTile[24] = al_load_bitmap("Tiles/DtoR.bmp");
	fTile[25] = al_load_bitmap("Tiles/UtoR.bmp");
	fTile[26] = al_load_bitmap("Tiles/DtoL.bmp");
	fTile[27] = al_load_bitmap("Tiles/T.bmp");
	fTile[28] = al_load_bitmap("Tiles/TtoD.bmp");
	fTile[29] = al_load_bitmap("Tiles/TtoU.bmp");
	fTile[30] = al_load_bitmap("Tiles/flor.bmp");
	fTile[31] = al_load_bitmap("Tiles/Arbust.bmp");


	int vidaPersonagem = 20;
	int faseAtual = 1;
	char buffer[sizeof(int) * 8 + 1];

	
	//iniciando personagens 
	persona player;
	player.x = 320;
	player.y = 240;
	player.perImage = al_load_bitmap("sprites/personagem.png");

	player.w = al_get_bitmap_width(player.perImage);
	player.h = al_get_bitmap_height(player.perImage);

	player.boundX = player.w / 10;
	player.boundY = player.h / 10;

	//inimigo 1
	persona inimigo;
	inimigo.x = larg / 2;
	inimigo.y = altu / 2;
	inimigo.perImage = al_load_bitmap("sprites/inimigo.jpg");

	inimigo.w = al_get_bitmap_width(inimigo.perImage);
	inimigo.h = al_get_bitmap_height(inimigo.perImage);

	inimigo.boundX = inimigo.w / 2;
	inimigo.boundY = inimigo.h / 2;

	//inimigo 2

	persona inimigo1;

	inimigo1.x = 100;
	inimigo1.y = 600;
	inimigo1.perImage = al_load_bitmap("sprites/inimigo.jpg");

	inimigo1.w = al_get_bitmap_width(inimigo1.perImage);
	inimigo1.h = al_get_bitmap_height(inimigo1.perImage);

	inimigo1.boundX = inimigo1.w / 2;
	inimigo1.boundY = inimigo1.h / 2;

	//inimigo 3

	persona inimigo2;

	inimigo2.x = 550;
	inimigo2.y = 400;
	inimigo2.perImage = al_load_bitmap("sprites/inimigo.jpg");

	inimigo2.w = al_get_bitmap_width(inimigo2.perImage);
	inimigo2.h = al_get_bitmap_height(inimigo2.perImage);

	inimigo2.boundX = inimigo2.w / 2;
	inimigo2.boundY = inimigo2.h / 2;

	//inimigo 4

	persona inimigo3;

	inimigo3.x = 1200;
	inimigo3.y = 500;
	inimigo3.perImage = al_load_bitmap("sprites/inimigo.jpg");

	inimigo3.w = al_get_bitmap_width(inimigo3.perImage);
	inimigo3.h = al_get_bitmap_height(inimigo3.perImage);

	inimigo3.boundX = inimigo3.w / 2;
	inimigo3.boundY = inimigo3.h / 2;

	//inimigo 5

	persona inimigo4;

	inimigo4.x = 800;
	inimigo4.y = 750;
	inimigo4.perImage = al_load_bitmap("sprites/inimigo.jpg");

	inimigo4.w = al_get_bitmap_width(inimigo4.perImage);
	inimigo4.h = al_get_bitmap_height(inimigo4.perImage);

	inimigo4.boundX = inimigo4.w / 2;
	inimigo4.boundY = inimigo4.h / 2;

	
	//alguns bool para identificar colisao

	bool colisao = false;
	bool bound = false;

	//bools para cada fase fase = render + numero da fase
	bool inicio = true;
	bool render = false;
	bool render2 = false;
	bool render3 = false;
	bool render4 = false;
	bool render5 = false;

	//fase inicial
	int fase = faseUm;


	bool jogando = true, running = true, draw = true, ativo = false;

	float movSpeed = 5;
	float dir = BAIXO;
	float sourceX = 0;
	float sourceY = 0;

	mapa = fopen("Mapa/mapa.txt", "r");
	fscanf(mapa, "%i", &linhas);
	fscanf(mapa, "%i", &colunas);

	//colis�o de tiles
	//COLUNA X LINHA Y
	bool colisaoB = false;
	bool colisaoC = false;
	bool colisaoD = false;
	bool colisaoE = false;

	bool contact = false;
	int mapH = 32;
	int mapW = 32;
	int mapBX = mapW / 2;
	int mapBy = mapH / 2;

	

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
				bound = false;

				//pos Inicio = C10, L8	
				int posAtC = calcularPosicaoC(player.x);
				int posAtL = calcularPosicaoL(player.y);

				//C=11 L=8

				int posCTileD = posAtC + 1;
				int posLTileD = posAtL;
				int xTileD = (posAtC * 32) + 1; //posi��o atual do boneco *32 +1 sera o x do tile a direita 
				int yTileD = (posAtL * 32);

				//C=9 L=8

				int posCTileE = posAtC - 1;
				int posLTileE = posAtL;
				int xTileE = (posCTileE * 32) - 31;
				int yTileE = (posAtL * 32);

				//C=10 L=9
				int posCTileB = posAtC;
				int posLTileB = posAtL + 1;
				int xTileB = (posAtC * 32);
				int yTileB = (posAtL * 32) + 1;

				//C=10 L=7
				int posCTileC = posAtC;
				int posLTileC = posAtL - 1;
				int xTileC = (posAtC * 32);
				int yTileC = (posLTileC * 32) - 31;


				//fases

				if (fase == faseUm) {
					render = true;
					if (player.x + 64 > inimigo.x - inimigo.boundX &&
						player.x<inimigo.x + inimigo.boundX &&
						player.y + 64>inimigo.y - inimigo.boundY &&
						player.y < inimigo.y + inimigo.boundY) {

						colisao = true;
						bound = true;
						ativo = false;
						fase = faseDois;
					}
				}
				if (fase == faseDois) {
					render2 = true;
					if (player.x + 64 > inimigo1.x - inimigo1.boundX &&
						player.x<inimigo1.x + inimigo1.boundX &&
						player.y + 64>inimigo1.y - inimigo1.boundY &&
						player.y < inimigo1.y + inimigo1.boundY) {

						colisao = true;
						bound = true;
						ativo = false;
						fase = faseTres;
					}
					else
						bound = false;
						colisao = false;
				}
				if (fase == faseTres) {
					render3 = true;
					if (player.x + 64 > inimigo2.x - inimigo2.boundX &&
						player.x<inimigo2.x + inimigo2.boundX &&
						player.y + 64>inimigo2.y - inimigo2.boundY &&
						player.y < inimigo2.y + inimigo2.boundY) {

						colisao = true;
						bound = true;
						ativo = false;
						fase = faseQuatro;
					}
					else
						bound = false;
						colisao = false;
				}
				if (fase == faseQuatro) {
					render4 = true;
					if (player.x + 64 > inimigo3.x - inimigo3.boundX &&
						player.x<inimigo3.x + inimigo3.boundX &&
						player.y + 64>inimigo3.y - inimigo3.boundY &&
						player.y < inimigo3.y + inimigo3.boundY) {

						colisao = true;
						bound = true;
						ativo = false;
						fase = faseCinco;
					}
					else
						bound = false;
						colisao = false;
				}

				//
				if (fase == faseCinco) {
					render5 = true;
					if (player.x + 64 > inimigo4.x - inimigo4.boundX &&
						player.x<inimigo4.x + inimigo4.boundX &&
						player.y + 64>inimigo4.y - inimigo4.boundY &&
						player.y < inimigo4.y + inimigo4.boundY) {

						colisao = true;
						bound = true;
						ativo = false;
						
					}
					else
						bound = false;
					    colisao = false;
				}

				


				if (al_key_down(&keyState, ALLEGRO_KEY_DOWN) && player.y < 850 ) {


				
				
						int oi = c[posLTileB][posCTileB];

						if (oi == 2 ||oi== 3 || oi == 4 || oi == 5|| oi == 31 )
						{
							contact = true;
							if (player.x + 32 > xTileB - mapBX &&
								player.x<xTileB + mapBX &&
								player.y + 32>yTileB - mapBy &&
								player.y < yTileB + mapBy
								
								/*contact == true &&
								player.y >= yTileB*/) {

								colisaoB = true;
							}
						}
						else {
							colisaoB = false;
						}

			

						if (colisaoB == false) {

							player.y += movSpeed;
							dir = BAIXO;
						}
						
				}
				else if (al_key_down(&keyState, ALLEGRO_KEY_UP) && player.y > 0) {
				

					int yy = (int)player.y;
					int resto = yy % 32;
					float pos = player.y / 32;
					int i = 0;
					int coisa;

					int xx = (int)player.x;
					int resto1 = xx % 32;
					float pos1 = player.x / 32;
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

					if (c[i][j] == 0 || c[i][j] == 6 || c[i][j] == 7 || c[i][j] == 8 || c[i][j] == 9 || c[i][j] == 24 || c[i][j] == 25 || c[i][j] == 26 || c[i][j] == 27 || c[i][j] == 28 || c[i][j] == 29 || c[i][j] == 30 || player.x < 32)
					{
						player.y -= movSpeed;
						dir = CIMA;

					}

					
				}

				else if (al_key_down(&keyState, ALLEGRO_KEY_RIGHT) && player.x < 1370) {
					int j = 0;

					int yy = (int)player.y;
					int resto = yy % 32;
					float pos = player.y / 32;
					int i = 0;
					int coisa;

					int xx = (int)player.x;
					int resto1 = xx % 32;
					float pos1 = player.x / 32;



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

					if (((c[i + 1][j + 1] == 0 || c[i + 1][j + 1] == 6 || c[i + 1][j + 1] == 7 || c[i + 1][j + 1] == 8 || c[i + 1][j + 1] == 9 || c[i + 1][j + 1] == 24 || c[i + 1][j + 1] == 25 || c[i + 1][j + 1] == 26 || c[i + 1][j + 1] == 27 || c[i + 1][j + 1] == 28 || c[i + 1][j + 1] == 29 || c[i + 1][j + 1] == 30 )&& player.x < 1370)  || player.x < 32)
					{

						player.x += movSpeed;
						dir = DIREITA;
					}

				}
				else if (al_key_down(&keyState, ALLEGRO_KEY_LEFT) && player.x > 0) {
				int yy = (int)player.y;
				int resto = yy % 32;
				float pos = player.y / 32;
				int j = 0;
				int coisa;

				int xx = (int)player.x;
				int resto1 = xx % 32;
				float pos1 = player.x / 32;
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

				if ((c[i+1][j] == 0 || c[i + 1][j] == 6 || c[i + 1][j] == 7 || c[i + 1][j] == 8 || c[i + 1][j] == 9 || c[i + 1][j] == 24|| c[i + 1][j] == 25 || c[i + 1][j] == 26 || c[i + 1][j] == 27 || c[i + 1][j] == 28 || c[i + 1][j] == 29 || c[i + 1][j] == 30)  && player.x > 0)
				{
					player.x -= movSpeed;
					dir = ESQUERDA;
				}

				}

				

				else if (al_key_down(&keyState, ALLEGRO_KEY_ESCAPE)) {
					jogando = false;

				}
				else { ativo = false; }
				
					
				if (ativo)
					sourceX += al_get_bitmap_width(player.perImage) / 4.0;
				else
					sourceX = 0;
				if (sourceX >= al_get_bitmap_width(player.perImage))
					sourceX = 0;
				sourceY = dir;
				draw = true;
			}
			if (evento.type == ALLEGRO_EVENT_KEY_DOWN) {
				switch (evento.keyboard.keycode)
				{
				case ALLEGRO_KEY_ENTER:
					al_draw_filled_rectangle(50, 400, 750, 550, al_map_rgb(255, 255, 255)); al_draw_filled_rectangle(50, 400, 750, 550, al_map_rgb(255, 255, 255));
					al_draw_textf(font, al_map_rgb(0, 0, 0), pos_x, pos_y, ALLEGRO_ALIGN_CENTER, "%s", answr);
					int i;
					sscanf(answr,"%d",&i);
					
					int resultado = logica(1,1,faseAtual,7,7,i);
					
					if (resultado == 0) {
						faseAtual++;
						break;
					}
					else {
						vidaPersonagem = vidaPersonagem + resultado;
					}
					if (vidaPersonagem <= 0) {
						gameOver();
					}
					

					break;
				case ALLEGRO_KEY_BACKSPACE:
					answr[strlen(answr) - 1] = '\0';
					al_draw_filled_rectangle(50, 400, 750, 550, al_map_rgb(255, 255, 255)); al_draw_filled_rectangle(50, 400, 750, 550, al_map_rgb(255, 255, 255));
					pos_x -= 3;
					al_draw_textf(font, al_map_rgb(0, 0, 0), pos_x, pos_y, ALLEGRO_ALIGN_CENTER, "%s", quest);
					al_draw_textf(font, al_map_rgb(0, 0, 0), pos_x + 20, pos_y, ALLEGRO_ALIGN_CENTER, "%s", answr);
					pos_x += 3;
					break;
				case ALLEGRO_KEY_1:
					strcat_s(answr, 8, "1");
					
					pos_x += 3;
					break;
				case ALLEGRO_KEY_2:
					strcat_s(answr, 8, "2");
					
					pos_x += 3;
					break;
				case ALLEGRO_KEY_3:
					strcat_s(answr, 8, "3");
					pos_x += 3;
					break;
				case ALLEGRO_KEY_4:
					strcat_s(answr, 8, "4");
					pos_x += 3;
					break;
				case ALLEGRO_KEY_5:
					strcat_s(answr, 8, "5");
					pos_x += 3;
					break;
				case ALLEGRO_KEY_6:
					strcat_s(answr, 8, "6");
					pos_x += 3;
					break;
				case ALLEGRO_KEY_7:
					strcat_s(answr, 8, "7");
					pos_x += 3;
					break;
				case ALLEGRO_KEY_8:
					strcat_s(answr, 8, "8");
					pos_x += 3;
					break;
				case ALLEGRO_KEY_9:
					strcat_s(answr, 8, "9");
					pos_x += 3;
					break;
				case ALLEGRO_KEY_0:
					strcat_s(answr, 8, "0");
					pos_x += 3;
					break;
				}
			}

		}
		//desenha a tela inicial
		if (inicio) {
			inicio = false;
			telaInicial();
			al_flip_display(janela);
			al_rest(5);
			fimTelaInicial();
		}
		readTile();
		

		//renderizacao personagem inimigo e caixa de texto
		//render fase um
		if (render) {
			render = false;
			//desenho
			al_draw_bitmap_region(player.perImage, sourceX, sourceY * al_get_bitmap_height(player.perImage) / 4, 64, 64, player.x, player.y, NULL);
			al_draw_bitmap(inimigo.perImage, inimigo.x - inimigo.boundX, inimigo.y - inimigo.boundY, 0);
			if (bound) {
					al_draw_rectangle(50, 760, 1390, 910, al_map_rgb(0, 0, 0), 3);
					al_draw_filled_rectangle(50, 760, 1390, 910, al_map_rgb(255, 255, 255));
					al_draw_textf(font, al_map_rgb(0, 0, 0),pos_x, pos_y, ALLEGRO_ALIGN_CENTER, "%s", "11+10");
					al_draw_textf(font, al_map_rgb(0, 0, 0), pos_x + 20, pos_y, ALLEGRO_ALIGN_CENTER, "%s", answr);

					//al_flip_display(janela);
					
			}
			if (colisao) {
				ativo = false;
			}
			al_draw_text(fonte, al_map_rgb(255, 0, 0), 100, 20, ALLEGRO_ALIGN_CENTER, itoa(vidaPersonagem, buffer, 10));
			al_draw_text(fonte, al_map_rgb(0, 0, 0), 1130, 20, ALLEGRO_ALIGN_CENTER, "Fase Atual");
			al_draw_text(fonte, al_map_rgb(0, 0, 0), 1320, 20, ALLEGRO_ALIGN_CENTER, itoa(faseAtual, buffer, 10));
			al_flip_display();
		}
		//render fase 2
		if (render2) {
			render2 = false;
			//desenho
			al_draw_bitmap_region(player.perImage, sourceX, sourceY * al_get_bitmap_height(player.perImage) / 4, 64, 64, player.x, player.y, NULL);
			al_draw_bitmap(inimigo1.perImage, inimigo1.x - inimigo1.boundX, inimigo1.y - inimigo1.boundY, 0);
			if (bound) {
				al_draw_rectangle(50, 760, 1390, 910, al_map_rgb(0, 0, 0), 3);
				al_draw_filled_rectangle(50, 760, 1390, 910, al_map_rgb(255, 255, 255));
				al_draw_textf(font, al_map_rgb(0, 0, 0), pos_x, pos_y, ALLEGRO_ALIGN_CENTER, "%s", "10-9");
				al_draw_textf(font, al_map_rgb(0, 0, 0), pos_x + 20, pos_y, ALLEGRO_ALIGN_CENTER, "%s", answr);

				//al_flip_display(janela);

			}
			if (colisao) {
				ativo = false;
			}
			al_draw_text(fonte, al_map_rgb(255, 0, 0), 100, 20, ALLEGRO_ALIGN_CENTER, itoa(vidaPersonagem, buffer, 10));
			al_draw_text(fonte, al_map_rgb(0, 0, 0), 1130, 20, ALLEGRO_ALIGN_CENTER, "Fase Atual");
			al_draw_text(fonte, al_map_rgb(0, 0, 0), 1320, 20, ALLEGRO_ALIGN_CENTER, itoa(faseAtual, buffer, 10));
			al_flip_display();
		}

		//render fase 3
		if (render3) {
			render3 = false;
			//desenho
			al_draw_bitmap_region(player.perImage, sourceX, sourceY * al_get_bitmap_height(player.perImage) / 4, 64, 64, player.x, player.y, NULL);
			al_draw_bitmap(inimigo2.perImage, inimigo2.x - inimigo2.boundX, inimigo2.y - inimigo2.boundY, 0);
			if (bound) {
				al_draw_rectangle(50, 760, 1390, 910, al_map_rgb(0, 0, 0), 3);
				al_draw_filled_rectangle(50, 760, 1390, 910, al_map_rgb(255, 255, 255));
				al_draw_textf(font, al_map_rgb(0, 0, 0), pos_x, pos_y, ALLEGRO_ALIGN_CENTER, "%s", "5*15");
				al_draw_textf(font, al_map_rgb(0, 0, 0), pos_x + 20, pos_y, ALLEGRO_ALIGN_CENTER, "%s", answr);

				//al_flip_display(janela);

			}
			if (colisao) {
				ativo = false;
			}
			al_draw_text(fonte, al_map_rgb(255, 0, 0), 100, 20, ALLEGRO_ALIGN_CENTER, itoa(vidaPersonagem, buffer, 10));
			al_draw_text(fonte, al_map_rgb(0, 0, 0), 1130, 20, ALLEGRO_ALIGN_CENTER, "Fase Atual");
			al_draw_text(fonte, al_map_rgb(0, 0, 0), 1320, 20, ALLEGRO_ALIGN_CENTER, itoa(faseAtual, buffer, 10));
			al_flip_display();
		}

		//render fase 4
		if (render4) {
			render4 = false;
			//desenho
			al_draw_bitmap_region(player.perImage, sourceX, sourceY * al_get_bitmap_height(player.perImage) / 4, 64, 64, player.x, player.y, NULL);
			al_draw_bitmap(inimigo3.perImage, inimigo3.x - inimigo3.boundX, inimigo3.y - inimigo3.boundY, 0);
			if (bound) {
				al_draw_rectangle(50, 760, 1390, 910, al_map_rgb(0, 0, 0), 3);
				al_draw_filled_rectangle(50, 760, 1390, 910, al_map_rgb(255, 255, 255));
				al_draw_textf(font, al_map_rgb(0, 0, 0), pos_x, pos_y, ALLEGRO_ALIGN_CENTER, "%s","90/2");
				al_draw_textf(font, al_map_rgb(0, 0, 0), pos_x + 20, pos_y, ALLEGRO_ALIGN_CENTER, "%s", answr);

				//al_flip_display(janela);

			}
			if (colisao) {
				ativo = false;
			}
			al_draw_text(fonte, al_map_rgb(255, 0, 0), 100, 20, ALLEGRO_ALIGN_CENTER, itoa(vidaPersonagem, buffer, 10));
			al_draw_text(fonte, al_map_rgb(0, 0, 0), 1130, 20, ALLEGRO_ALIGN_CENTER, "Fase Atual");
			al_draw_text(fonte, al_map_rgb(0, 0, 0), 1320, 20, ALLEGRO_ALIGN_CENTER, itoa(faseAtual, buffer, 10));
			al_flip_display();
		}
		//render fase 5
		if (render5) {
			render5 = false;
			//desenho
			al_draw_bitmap_region(player.perImage, sourceX, sourceY * al_get_bitmap_height(player.perImage) / 4, 64, 64, player.x, player.y, NULL);
			al_draw_bitmap(inimigo4.perImage, inimigo4.x - inimigo4.boundX, inimigo4.y - inimigo4.boundY, 0);
			if (bound) {
				al_draw_rectangle(50, 760, 1390, 910, al_map_rgb(0, 0, 0), 3);
				al_draw_filled_rectangle(50, 760, 1390, 910, al_map_rgb(255, 255, 255));
				al_draw_textf(font, al_map_rgb(0, 0, 0), pos_x, pos_y, ALLEGRO_ALIGN_CENTER, "%s", "5^3");
				al_draw_textf(font, al_map_rgb(0, 0, 0), pos_x + 20, pos_y, ALLEGRO_ALIGN_CENTER, "%s", answr);

				//al_flip_display(janela);

			}
			if (colisao) {
				ativo = false;
			}
			al_draw_text(fonte, al_map_rgb(255, 0, 0), 100, 20, ALLEGRO_ALIGN_CENTER, itoa(vidaPersonagem, buffer, 10));
			al_draw_text(fonte, al_map_rgb(0, 0, 0), 1130, 20, ALLEGRO_ALIGN_CENTER, "Fase Atual");
			al_draw_text(fonte, al_map_rgb(0, 0, 0), 1320, 20, ALLEGRO_ALIGN_CENTER, itoa(faseAtual, buffer, 10));
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