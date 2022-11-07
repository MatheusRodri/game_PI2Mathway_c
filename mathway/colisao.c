
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>

const int WIDTH = 800;
const int HEIGHT = 600;

bool keys[] = { false,false,false,false,false };
enum KEYS { UP, DOWN, LEFT, RIGHT, SPACE };

enum direcao { BAIXO, ESQUERDA, DIREITA, CIMA };

typedef struct sprite sprite;
struct sprite
{
    float x;
    float y;
    float velX;
    float velY;
    int dirX;
    int dirY;

    int bx;
    int by;
    int w;
    int h;

    ALLEGRO_BITMAP* image;
};

int main(int argc, char** argv)
{


    //project variables
    bool done = false;
    bool render = false;

    bool bound = false;
    bool collision = false;

    sprite p1;
    sprite p2;

    p1.x = 0;
    p1.y = 0;

    p2.x = WIDTH / 2;
    p2.y = HEIGHT / 2;

    //--------------------
    bool acao = true;
    int dir = BAIXO;
    int sourceX = 0;
    int sourceY = 0;
    //--------------------

    //allegro variables

    ALLEGRO_DISPLAY* display = NULL;
    ALLEGRO_EVENT_QUEUE* event_queue = NULL;
    ALLEGRO_TIMER* timer;

    //ALLEGRO_FONT* font18 = NULL;

    //allegro init functions

    if (!al_init()) {
        return -1;
    }

    display = al_create_display(WIDTH, HEIGHT);

    if (!display) {
        return -1;
    }

    //addon inti

    al_install_keyboard();
    al_init_image_addon();
    //al_init_font_addon();
    al_init_ttf_addon();
    al_init_primitives_addon();

    //project init
    //font18=al_load_font("",18,0)

    //p1.image = al_load_bitmap("macacocafe.jpg");
    p2.image = al_load_bitmap("macacocafe.jpg");
    //-----------------------------------
    p1.image = al_load_bitmap("Movimento.png");
    //-----------------------------------
    p1.w = al_get_bitmap_width(p1.image);
    p1.h = al_get_bitmap_height(p1.image);


    p2.w = al_get_bitmap_width(p2.image);
    p2.h = al_get_bitmap_height(p2.image);

    p1.bx = p1.w / 10;
    p1.by = p1.h / 10;

    p2.bx = p2.w / 2;
    p2.by = p2.h / 2;


    //timer init setup
    event_queue = al_create_event_queue();
    timer = al_create_timer(1.0 / 60);

    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source());

    al_start_timer(timer);
    while (!done) {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        //inputs
        if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
            switch (ev.keyboard.keycode) {
            case ALLEGRO_KEY_ESCAPE:
                done = true;
                break;
            case ALLEGRO_KEY_LEFT:
                keys[LEFT] = true;
                break;
            case ALLEGRO_KEY_RIGHT:
                keys[RIGHT] = true;
                break;
            case ALLEGRO_KEY_UP:
                keys[UP] = true;
                break;
            case ALLEGRO_KEY_DOWN:
                keys[DOWN] = true;
                break;
            case ALLEGRO_KEY_SPACE:
                keys[SPACE] = true;
                break;
            }
        }
        else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
            switch (ev.keyboard.keycode) {
            case ALLEGRO_KEY_ESCAPE:
                done = true;
                break;
            case ALLEGRO_KEY_LEFT:
                keys[LEFT] = false;
                break;
            case ALLEGRO_KEY_RIGHT:
                keys[RIGHT] = false;
                break;
            case ALLEGRO_KEY_UP:
                keys[UP] = false;
                break;
            case ALLEGRO_KEY_DOWN:
                keys[DOWN] = false;
                break;
            case ALLEGRO_KEY_SPACE:
                keys[SPACE] = false;
                break;
            }
        }

        //game update
        else if (ev.type == ALLEGRO_EVENT_TIMER) {
            render = true;
            //---------------
            acao = true;
            //---------------

            if (keys[UP]) {
                p1.y -= 5;
                dir = CIMA;
            }
            else if (keys[DOWN]) {
                p1.y += 5;
                dir = BAIXO;
            }
            else if (keys[RIGHT]) {
                p1.x += 5;
                dir = DIREITA;
            }
            else if (keys[LEFT]) {
                p1.x -= 5;
                dir = ESQUERDA;
            }
            else {
                acao = false;
            }


            if (keys[SPACE])
                bound = true;
            else
                bound = false;

            if (p1.x + 64 > p2.x - p2.bx &&
                p1.x<p2.x + p2.bx &&
                p1.y + 64>p2.y - p2.by &&
                p1.y < p2.y + p2.by) {
                collision = true;
                acao = false;
            }
            else
                collision = false;

            if (acao) {
                sourceX += al_get_bitmap_width(p1.image) / 4.0;
            }
            else { sourceX = 0; }


            if (sourceX >= al_get_bitmap_width(p1.image)) { sourceX = 0; }

            sourceY = dir;

        }

        //render
        if (render && al_is_event_queue_empty(event_queue)) {
            render = false;

            al_draw_bitmap(p2.image, p2.x - p2.w / 2, p2.y - p2.h / 2, 0);
            //al_draw_bitmap(p1.image, p1.x - p1.w / 2, p1.y - p1.h / 2, 0);
            //
            al_draw_bitmap_region(p1.image, sourceX, sourceY * p1.h / 4, 64, 64, p1.x, p1.y, 0);
            //
            if (bound) {
                al_draw_filled_rectangle(p1.x, p1.y, p1.x + 64, p1.y + 64, al_map_rgba_f(.6, 0, .6, .6));
                al_draw_filled_rectangle(p2.x - p2.bx, p2.y - p2.by, p2.x + p2.bx, p2.y + p2.by, al_map_rgba_f(.6, 0, .6, .6));
            }
            if (collision) {
                al_draw_circle(10, 10, 5, al_map_rgb(255, 255, 255), 1);
            }
            al_flip_display();
            al_clear_to_color(al_map_rgb(0, 0, 0));
        }
    }

    //destroy
    al_destroy_bitmap(p1.image);
    al_destroy_bitmap(p2.image);
    al_destroy_display(display);
    al_destroy_timer(timer);
    al_destroy_event_queue(event_queue);

    return 0;

}
