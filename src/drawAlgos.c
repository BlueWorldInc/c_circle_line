#include <drawAlgos.h>

void DDA_LineAlgorithm(SDL_Renderer* renderer, int x0, int y0, int x1, int y1);

int main(int argc, char *argv[])
{

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    int statut = EXIT_FAILURE;
    SDL_Color orange = {255, 127, 40, 255};
    SDL_Color black = {0, 0, 0, 255};
    SDL_Color white = {255, 255, 255, 255};
    SDL_bool init_error = SDL_FALSE;
    SDL_bool run = SDL_TRUE;
    srand(time(NULL));

    if (0 != SDL_Init(SDL_INIT_VIDEO))
    {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
        return -1;
    }

    window = SDL_CreateWindow("Cycle", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 500, 700, SDL_WINDOW_FULLSCREEN_DESKTOP);

    if (NULL == window)
    {
        fprintf(stderr, "Erreur de creation de la fenetre : %s\n", SDL_GetError());
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (NULL == renderer)
    {
        fprintf(stderr, "Erreur SDL_CreateRenderer : %s", SDL_GetError());
        init_error = SDL_TRUE;
    }
    if (0 != SDL_SetRenderDrawColor(renderer, black.r, black.g, black.b, black.a))
    {
        fprintf(stderr, "Erreur SDL_SetRenderDrawColor : %s", SDL_GetError());
        init_error = SDL_TRUE;
    }

    if (0 != SDL_RenderClear(renderer))
    {
        fprintf(stderr, "Erreur SDL_SetRenderDrawColor : %s", SDL_GetError());
        init_error = SDL_TRUE;
    }

    if (!init_error)
    {


        while (run) {
            SDL_Event event;
            SDL_PollEvent(&event);

            drawMainWindow(renderer);

            SDL_Delay(10);
            switch (event.type) {
                case SDL_KEYDOWN:
                    run = SDL_FALSE;
                    break;
            }
        }

        SDL_DestroyWindow(window);
    }

    SDL_Quit();
    return 0;
}

void drawMainWindow(SDL_Renderer* renderer) {
    SDL_Color black = {0, 0, 0, 255};
    SDL_Color white = {255, 255, 255, 255};

     // clear window
    SDL_SetRenderDrawColor(renderer, black.r, black.g, black.b, black.a);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, white.r, white.g, white.b, white.a);

    // draw baseline
    SDL_RenderDrawLine(renderer, 0, BASELINE, SCREEN_WIDTH, BASELINE);

    // draw point
    DDA_LineAlgorithm(renderer, 0, 0, SCREEN_WIDTH, BASELINE);
    DDA_LineAlgorithm(renderer, 0, BASELINE, SCREEN_WIDTH, 0);

    SDL_RenderPresent(renderer);
}

void DDA_LineAlgorithm(SDL_Renderer* renderer, int x0, int y0, int x1, int y1) {
    int d0 = x1 - x0;
    int d1 = y1 - y0;
    int steps = abs(d0) > abs(d1) ? abs(d0) : abs(d1);

    double xInc = d0 / (double) steps;
    double yInc = d1 / (double) steps;

    double x = (double) x0;
    double y = (double) y0;

    for (int i = 0; i <= steps; i++) {
        SDL_RenderDrawPoint(renderer, (int) x, (int) y);
        x += xInc;
        y += yInc;
    }
}