#include <iostream>
#include <SDL.h>
#include <time.h>


using namespace std;

const int SCREEN_WIDTH = 300;
const int SCREEN_HEIGHT = 300;

SDL_Window* window = NULL;
SDL_Surface* screenSurface = NULL;
SDL_Renderer* renderer = NULL;

SDL_Surface* x_surface = NULL;
SDL_Surface* o_surface = NULL;
SDL_Surface* Bt_PA_surface = NULL;
SDL_Surface* Bt_EX_surface = NULL;
SDL_Surface* P1_WIN_surface = NULL;
SDL_Surface* P2_WIN_surface = NULL;
SDL_Surface* P1_SELECT_surface = NULL;
SDL_Surface* P2_SELECT_surface = NULL;

SDL_Texture* x_Texture = NULL;
SDL_Texture* o_Texture = NULL;
SDL_Texture* Bt_PA_Texture = NULL;
SDL_Texture* Bt_EX_Texture = NULL;
SDL_Texture* P1_WIN_Texture = NULL;
SDL_Texture* P2_WIN_Texture = NULL;
SDL_Texture* P1_SELECT_Texture = NULL;
SDL_Texture* P2_SELECT_Texture = NULL;

unsigned int Quit = 0;
unsigned int Answer = 0;
unsigned int End = 0;
unsigned int Player = 0;
unsigned int Player_cpy = 0;
unsigned int PC = 0;
unsigned int Good_move = 0;

int mouse_pos_x = 0;
int mouse_pos_y = 0;
char moves[3][3] = {0};

int WinMain(int argc, char* argv[]) {
    srand(time(0));
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        return -1;
    }
    window = SDL_CreateWindow("TicTacToe", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (window == NULL)
    {
        return -2;
    }
    if (renderer == nullptr) {
        return -3;
    }

    screenSurface = SDL_GetWindowSurface(window);
    x_surface = SDL_LoadBMP("Imgs/X-.bmp");
    o_surface = SDL_LoadBMP("Imgs/O-.bmp");
    Bt_PA_surface = SDL_LoadBMP("Imgs/Bt1.bmp");
    Bt_EX_surface = SDL_LoadBMP("Imgs/Bt2.bmp");
    P1_WIN_surface = SDL_LoadBMP("Imgs/P1.bmp");
    P2_WIN_surface = SDL_LoadBMP("Imgs/P2.bmp");
    P1_SELECT_surface = SDL_LoadBMP("Imgs/1P.bmp");
    P2_SELECT_surface = SDL_LoadBMP("Imgs/2P.bmp");

    if ((x_surface == NULL || o_surface == NULL) || (Bt_PA_surface == NULL || Bt_EX_surface == NULL)) {
        return -4;
    }
    if (P1_WIN_surface == NULL || P2_WIN_surface == NULL) {
        return -9;
    }

    x_Texture = SDL_CreateTextureFromSurface(renderer, x_surface);
    o_Texture = SDL_CreateTextureFromSurface(renderer, o_surface);
    Bt_PA_Texture = SDL_CreateTextureFromSurface(renderer, Bt_PA_surface);
    Bt_EX_Texture = SDL_CreateTextureFromSurface(renderer, Bt_EX_surface);
    P1_WIN_Texture = SDL_CreateTextureFromSurface(renderer, P1_WIN_surface);
    P2_WIN_Texture = SDL_CreateTextureFromSurface(renderer, P2_WIN_surface);
    P1_SELECT_Texture = SDL_CreateTextureFromSurface(renderer, P1_SELECT_surface);
    P2_SELECT_Texture = SDL_CreateTextureFromSurface(renderer, P2_SELECT_surface);

    if ((x_Texture == NULL || o_Texture == NULL) || (Bt_PA_Texture == NULL || Bt_EX_Texture == NULL)) {
        return -10;
    }
    if ((P1_WIN_Texture == NULL || P2_WIN_Texture == NULL) || (P1_SELECT_Texture == NULL || P2_SELECT_Texture == NULL)) {
        return -35;
    }
    SDL_FreeSurface(x_surface);
    SDL_FreeSurface(o_surface);
    SDL_FreeSurface(Bt_PA_surface);
    SDL_FreeSurface(Bt_EX_surface);
    SDL_FreeSurface(P1_WIN_surface);
    SDL_FreeSurface(P2_WIN_surface);
    SDL_FreeSurface(P1_SELECT_surface);
    SDL_FreeSurface(P2_SELECT_surface);

    SDL_Rect Line_Row1 = { 0, 30 * (SCREEN_HEIGHT / 100), SCREEN_WIDTH, 2 };
    SDL_Rect Line_Row2 = { 0, 66 * (SCREEN_HEIGHT / 100), SCREEN_WIDTH, 2 };
    SDL_Rect Line_Column1 = { 33 * (SCREEN_WIDTH / 100), 0, 2, SCREEN_HEIGHT };
    SDL_Rect Line_Column2 = { 66 * (SCREEN_WIDTH / 100), 0, 2, SCREEN_HEIGHT };
    SDL_Rect Rect_x;
    SDL_Event events;

    while (!Quit) {
        Answer = 0;
        Player = 1;
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        Rect_x.x = 10 * (SCREEN_WIDTH / 100);
        Rect_x.y = 30 * (SCREEN_HEIGHT / 100);
        Rect_x.w = 40 * (SCREEN_WIDTH / 100);
        Rect_x.h = 23 * (SCREEN_HEIGHT / 100);
        SDL_RenderCopy(renderer, P1_SELECT_Texture, NULL, &Rect_x);
        Rect_x.x = 50 * (SCREEN_WIDTH / 100);
        Rect_x.h = 20 * (SCREEN_HEIGHT / 100);
        SDL_RenderCopy(renderer, P2_SELECT_Texture, NULL, &Rect_x);
        SDL_RenderPresent(renderer);
        while (!Answer) {
            while (SDL_PollEvent(&events))
            {
                switch (events.type) {
                case SDL_QUIT: End = 1; Quit = 1; Answer = 1; break;
                case SDL_MOUSEBUTTONUP: {
                    SDL_GetMouseState(&mouse_pos_x, &mouse_pos_y);
                    if ((mouse_pos_x > 10 * (SCREEN_WIDTH / 100)) && (mouse_pos_x < 50 * (SCREEN_WIDTH / 100))) {
                        if ((mouse_pos_y > 30 * (SCREEN_HEIGHT / 100)) && (mouse_pos_y < 53 * (SCREEN_HEIGHT / 100))) {
                            PC = 1;
                            Answer = 1;
                        }
                    }
                    if ((mouse_pos_x > 50 * (SCREEN_WIDTH / 100)) && (mouse_pos_x < 90 * (SCREEN_WIDTH / 100))) {
                        if ((mouse_pos_y > 23 * (SCREEN_HEIGHT / 100)) && (mouse_pos_y < 43 * (SCREEN_HEIGHT / 100))) {
                            Answer = 1;
                            PC = 0;
                        }
                    }
                }
                }
            }
        }
        if (Quit)
            break;

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderFillRect(renderer, &Line_Row1);
        SDL_RenderFillRect(renderer, &Line_Row2);
        SDL_RenderFillRect(renderer, &Line_Column1);
        SDL_RenderFillRect(renderer, &Line_Column2);
        Answer = 0;

        Rect_x.w = 20 * (SCREEN_WIDTH / 100);
        Rect_x.h = 20 * (SCREEN_HEIGHT / 100);

        while (!End) {
            Good_move = 0;
            if ((PC) && (Player == 2)) {
                while (!Good_move) {
                    int choose = (rand() % 9) + 1;
                    switch (choose) {
                        case 1: {
                            if (moves[0][0] == 0) {
                                Rect_x.x = 6 * (SCREEN_WIDTH / 100);
                                Rect_x.y = 5 * (SCREEN_HEIGHT / 100);
                                SDL_RenderCopy(renderer, o_Texture, NULL, &Rect_x);
                                moves[0][0] = 'O';
                                Good_move = 1;
                            }
                            break;
                        }
                        case 2: {
                            if (moves[0][1] == 0) {
                                Rect_x.x = 40 * (SCREEN_WIDTH / 100);
                                Rect_x.y = 5 * (SCREEN_HEIGHT / 100);
                                SDL_RenderCopy(renderer, o_Texture, NULL, &Rect_x);
                                moves[0][1] = 'O';
                                Good_move = 1;
                            }
                            break;
                        }
                        case 3: {
                            if (moves[0][2] == 0) {
                                Rect_x.x = 73 * (SCREEN_WIDTH / 100);
                                Rect_x.y = 5 * (SCREEN_HEIGHT / 100);
                                SDL_RenderCopy(renderer, o_Texture, NULL, &Rect_x);
                                moves[0][2] = 'O';
                                Good_move = 1;
                            }
                            break;
                        }
                        case 4: {
                            if (moves[1][0] == 0) {
                                Rect_x.x = 6 * (SCREEN_WIDTH / 100);
                                Rect_x.y = 38 * (SCREEN_HEIGHT / 100);
                                SDL_RenderCopy(renderer, o_Texture, NULL, &Rect_x);
                                moves[1][0] = 'O';
                                Good_move = 1;
                            }
                            break;
                        }
                        case 5: {
                            if (moves[1][1] == 0) {
                                Rect_x.x = 40 * (SCREEN_WIDTH / 100);
                                Rect_x.y = 38 * (SCREEN_HEIGHT / 100);
                                SDL_RenderCopy(renderer, o_Texture, NULL, &Rect_x);
                                moves[1][1] = 'O';
                                Good_move = 1;
                            }
                            break;
                        }
                        case 6: {
                            if (moves[1][2] == 0) {
                                Rect_x.x = 73 * (SCREEN_WIDTH / 100);
                                Rect_x.y = 38 * (SCREEN_HEIGHT / 100);
                                SDL_RenderCopy(renderer, o_Texture, NULL, &Rect_x);
                                moves[1][2] = 'O';
                                Good_move = 1;
                            }
                            break;
                        }
                        case 7: {
                            if (moves[2][0] == 0) {
                                Rect_x.x = 6 * (SCREEN_WIDTH / 100);
                                Rect_x.y = 73 * (SCREEN_HEIGHT / 100);
                                SDL_RenderCopy(renderer, o_Texture, NULL, &Rect_x);
                                moves[2][0] = 'O';
                                Good_move = 1;
                            }
                            break;
                        }
                        case 8: {
                            if (moves[2][1] == 0) {
                                Rect_x.x = 40 * (SCREEN_WIDTH / 100);
                                Rect_x.y = 73 * (SCREEN_HEIGHT / 100);
                                SDL_RenderCopy(renderer, o_Texture, NULL, &Rect_x);
                                moves[2][1] = 'O';
                                Good_move = 1;
                            }
                            break;
                        }
                        case 9: {
                            if (moves[2][2] == 0) {
                                Rect_x.x = 73 * (SCREEN_WIDTH / 100);
                                Rect_x.y = 73 * (SCREEN_HEIGHT / 100);
                                SDL_RenderCopy(renderer, o_Texture, NULL, &Rect_x);
                                moves[2][2] = 'O';
                                Good_move = 1;
                            }
                            break;
                        }
                    }
                }
                Player = 1;
            }
            while (SDL_PollEvent(&events)) {
                switch (events.type) {
                case SDL_QUIT: End = 1; Quit = 1; break;
                case SDL_MOUSEBUTTONUP: {
                    SDL_GetMouseState(&mouse_pos_x, &mouse_pos_y);

                    if (mouse_pos_x < 33 * (SCREEN_WIDTH / 100)) {
                        if (mouse_pos_y < 30 * (SCREEN_HEIGHT / 100) && (moves[0][0] == 0)) {
                            Rect_x.x = 6 * (SCREEN_WIDTH / 100);
                            Rect_x.y = 5 * (SCREEN_HEIGHT / 100);
                            if (Player == 1) {
                                moves[0][0] = 'X';
                                SDL_RenderCopy(renderer, x_Texture, NULL, &Rect_x);
                                Player = 2;
                            }
                            else {
                                moves[0][0] = 'O';
                                SDL_RenderCopy(renderer, o_Texture, NULL, &Rect_x);
                                Player = 1;
                            }
                        }
                        else if ((30 * (SCREEN_HEIGHT / 100) < mouse_pos_y) && (mouse_pos_y < 60 * (SCREEN_HEIGHT / 100)) && (moves[1][0] == 0)) {
                            Rect_x.x = 6 * (SCREEN_WIDTH / 100);
                            Rect_x.y = 38 * (SCREEN_HEIGHT / 100);
                            if (Player == 1) {
                                moves[1][0] = 'X';
                                SDL_RenderCopy(renderer, x_Texture, NULL, &Rect_x);
                                Player = 2;
                            }
                            else {
                                moves[1][0] = 'O';
                                SDL_RenderCopy(renderer, o_Texture, NULL, &Rect_x);
                                Player = 1;
                            }
                        }
                        else if (mouse_pos_y > 60 * (SCREEN_HEIGHT / 100) && (moves[2][0] == 0)) {
                            Rect_x.x = 6 * (SCREEN_WIDTH / 100);
                            Rect_x.y = 73 * (SCREEN_HEIGHT / 100);
                            if (Player == 1) {
                                moves[2][0] = 'X';
                                SDL_RenderCopy(renderer, x_Texture, NULL, &Rect_x);
                                Player = 2;
                            }
                            else {
                                moves[2][0] = 'O';
                                SDL_RenderCopy(renderer, o_Texture, NULL, &Rect_x);
                                Player = 1;
                            }
                        }
                    }
                    else if ((33 * (SCREEN_WIDTH / 100) < mouse_pos_x) && (mouse_pos_x < 66 * (SCREEN_WIDTH / 100))) {
                        if (mouse_pos_y < 30 * (SCREEN_HEIGHT / 100) && (moves[0][1] == 0)) {
                            Rect_x.x = 40 * (SCREEN_WIDTH / 100);
                            Rect_x.y = 5 * (SCREEN_HEIGHT / 100);
                            if (Player == 1) {
                                moves[0][1] = 'X';
                                SDL_RenderCopy(renderer, x_Texture, NULL, &Rect_x);
                                Player = 2;
                            }
                            else {
                                moves[0][1] = 'O';
                                SDL_RenderCopy(renderer, o_Texture, NULL, &Rect_x);
                                Player = 1;
                            }
                        }
                        else if ((30 * (SCREEN_HEIGHT / 100) < mouse_pos_y) && (mouse_pos_y < 60 * (SCREEN_HEIGHT / 100)) && (moves[1][1] == 0)) {
                            Rect_x.x = 40 * (SCREEN_WIDTH / 100);
                            Rect_x.y = 38 * (SCREEN_HEIGHT / 100);
                            if (Player == 1) {
                                moves[1][1] = 'X';
                                SDL_RenderCopy(renderer, x_Texture, NULL, &Rect_x);
                                Player = 2;
                            }
                            else {
                                moves[1][1] = 'O';
                                SDL_RenderCopy(renderer, o_Texture, NULL, &Rect_x);
                                Player = 1;
                            }
                        }
                        else if (mouse_pos_y > 60 * (SCREEN_HEIGHT / 100) && (moves[2][1] == 0)) {
                            Rect_x.x = 40 * (SCREEN_WIDTH / 100);
                            Rect_x.y = 73 * (SCREEN_HEIGHT / 100);
                            if (Player == 1) {
                                moves[2][1] = 'X';
                                SDL_RenderCopy(renderer, x_Texture, NULL, &Rect_x);
                                Player = 2;
                            }
                            else {
                                moves[2][1] = 'O';
                                SDL_RenderCopy(renderer, o_Texture, NULL, &Rect_x);
                                Player = 1;
                            }
                        }
                    }
                    else if (mouse_pos_x > 66 * (SCREEN_WIDTH / 100)) {
                        if (mouse_pos_y < 30 * (SCREEN_HEIGHT / 100) && (moves[0][2] == 0)) {
                            Rect_x.x = 73 * (SCREEN_WIDTH / 100);
                            Rect_x.y = 5 * (SCREEN_HEIGHT / 100);
                            if (Player == 1) {
                                moves[0][2] = 'X';
                                SDL_RenderCopy(renderer, x_Texture, NULL, &Rect_x);
                                Player = 2;
                            }
                            else {
                                moves[0][2] = 'O';
                                SDL_RenderCopy(renderer, o_Texture, NULL, &Rect_x);
                                Player = 1;
                            }
                        }
                        else if ((30 * (SCREEN_HEIGHT / 100) < mouse_pos_y) && (mouse_pos_y < 60 * (SCREEN_HEIGHT / 100)) && (moves[1][2] == 0)) {
                            Rect_x.x = 73 * (SCREEN_WIDTH / 100);
                            Rect_x.y = 38 * (SCREEN_HEIGHT / 100);
                            if (Player == 1) {
                                moves[1][2] = 'X';
                                SDL_RenderCopy(renderer, x_Texture, NULL, &Rect_x);
                                Player = 2;
                            }
                            else {
                                moves[1][2] = 'O';
                                SDL_RenderCopy(renderer, o_Texture, NULL, &Rect_x);
                                Player = 1;
                            }
                        }
                        else if (mouse_pos_y > 60 * (SCREEN_HEIGHT / 100) && (moves[2][2] == 0)) {
                            Rect_x.x = 73 * (SCREEN_WIDTH / 100);
                            Rect_x.y = 73 * (SCREEN_HEIGHT / 100);
                            if (Player == 1) {
                                moves[2][2] = 'X';
                                SDL_RenderCopy(renderer, x_Texture, NULL, &Rect_x);
                                Player = 2;
                            }
                            else {
                                moves[2][2] = 'O';
                                SDL_RenderCopy(renderer, o_Texture, NULL, &Rect_x);
                                Player = 1;
                            }
                        }
                    }
                    
                    break;
                    }
                }
            }
            if (((moves[0][0] == moves[1][1]) && (moves[1][1] == moves[2][2])) && (moves[0][0] != 0)) {
                End = 1;
            }
            else if (((moves[0][0] == moves[1][0]) && (moves[1][0] == moves[2][0])) && (moves[0][0] != 0)) {
                End = 1;
            }
            else if (((moves[0][0] == moves[0][1]) && (moves[0][1] == moves[0][2])) && (moves[0][0] != 0)) {
                End = 1;
            }
            else if (((moves[0][2] == moves[1][1]) && (moves[1][1] == moves[2][0])) && (moves[0][2] != 0)) {
                End = 1;
            }
            else if (((moves[0][1] == moves[1][1]) && (moves[1][1] == moves[2][1])) && (moves[0][1] != 0)) {
                End = 1;
            }
            else if (((moves[0][2] == moves[1][2]) && (moves[1][2] == moves[2][2])) && (moves[0][2] != 0)) {
                End = 1;
            }
            else if (((moves[1][0] == moves[1][1]) && (moves[1][0] == moves[1][2])) && (moves[1][0] != 0)) {
                End = 1;
            }
            else if (((moves[2][0] == moves[2][1]) && (moves[2][1] == moves[2][2])) && (moves[2][0] != 0)) {
                End = 1;
            }
            if (End == 1)
                break;
            else
                End = 1;

            Player_cpy = Player;
            Player = 0;

            for (int i = 0; i < 3; i++)
                for (int j = 0; j < 3; j++)
                    if (moves[i][j] == 0) {
                        End = 0;
                        Player = Player_cpy;
                        break;
                    }
            
            SDL_RenderPresent(renderer);
        }
        Rect_x.x = 30 * (SCREEN_WIDTH / 100);
        Rect_x.y = Rect_x.y = SCREEN_HEIGHT / 9;
        Rect_x.w = 38 * (SCREEN_WIDTH / 100);
        Rect_x.h = 18 * (SCREEN_HEIGHT / 100);

        if (Player == 1) {
            SDL_RenderCopy(renderer, P2_WIN_Texture, NULL, &Rect_x);
        }
        else if(Player == 2) {
            SDL_RenderCopy(renderer, P1_WIN_Texture, NULL, &Rect_x);
        }

        Rect_x.w = 40 * (SCREEN_WIDTH / 100);
        Rect_x.h = 25 * (SCREEN_HEIGHT / 100);
        Rect_x.x = 5 * (SCREEN_WIDTH / 100);
        Rect_x.y = SCREEN_HEIGHT / 3;
        SDL_RenderCopy(renderer, Bt_PA_Texture, NULL, &Rect_x);
        Rect_x.x = 55 * (SCREEN_WIDTH / 100);
        SDL_RenderCopy(renderer, Bt_EX_Texture, NULL, &Rect_x);
        SDL_RenderPresent(renderer);
        while (!Answer) {
            while (SDL_PollEvent(&events))
            {
                switch (events.type) {
                case SDL_QUIT: End = 1; Quit = 1; Answer = 1; break;
                case SDL_MOUSEBUTTONUP: {
                    SDL_GetMouseState(&mouse_pos_x, &mouse_pos_y);
                    if ((mouse_pos_x > 5 * (SCREEN_WIDTH / 100)) && (mouse_pos_x < 45 * (SCREEN_WIDTH / 100))) {
                        if ((mouse_pos_y > SCREEN_HEIGHT / 3) && (mouse_pos_y < SCREEN_HEIGHT / 3 + 25 * (SCREEN_HEIGHT / 100))) {
                            End = 0;
                            Answer = 1;
                            for (int i = 0; i < 3; i++)
                                for (int j = 0; j < 3; j++)
                                    moves[i][j] = 0;
                        }
                    }
                    if ((mouse_pos_x > 55 * (SCREEN_WIDTH / 100)) && (mouse_pos_x < 95 * (SCREEN_WIDTH / 100))) {
                        if ((mouse_pos_y > SCREEN_HEIGHT / 3) && (mouse_pos_y < SCREEN_HEIGHT / 3 + 25 * (SCREEN_HEIGHT / 100))) {
                            Quit = 1;
                            Answer = 1;
                        }
                    }
                }
                }
            }
        }

    }
    SDL_DestroyTexture(o_Texture);
    SDL_DestroyTexture(x_Texture);
    SDL_DestroyTexture(Bt_PA_Texture);
    SDL_DestroyTexture(Bt_EX_Texture);
    SDL_DestroyTexture(P1_WIN_Texture);
    SDL_DestroyTexture(P2_WIN_Texture);
    SDL_DestroyTexture(P1_SELECT_Texture);
    SDL_DestroyTexture(P2_SELECT_Texture);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}