#include <drawAlgos.h>

void DDA_LineAlgorithm(SDL_Renderer* renderer, int x0, int y0, int x1, int y1);
void Bresenham_LineAlgorithm_naive(SDL_Renderer* renderer, int x0, int y0, int x1, int y1);
void Bresenham_LineAlgorithm_less_naive(SDL_Renderer* renderer, int x0, int y0, int x1, int y1);
void Bresenham_LineAlgorithm(SDL_Renderer* renderer, int x0, int y0, int x1, int y1);

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
            run = SDL_FALSE;
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
    // DDA_LineAlgorithm(renderer, 500, 100, 600, 150);
    // Bresenham_LineAlgorithm_naive(renderer, 0, 0, 3, 2);
    // Bresenham_LineAlgorithm_less_naive(renderer, 0, 0, 3, 2);
    // Bresenham_LineAlgorithm(renderer, 0, 0, 3, 2);

    // performance of the algos
    clock_t start = clock(), diff;
    for (int i = 0; i < 1000000; i++) {
        // DDA_LineAlgorithm(renderer, 0, 0, 666, 555);
    }
    diff = clock() - start;
    int msec = diff * 1000 / CLOCKS_PER_SEC;
    printf("Time taken %d.%d seconds\n", msec/1000, msec%1000);
    
    start = clock();
    for (int i = 0; i < 1000000; i++) {
        // Bresenham_LineAlgorithm_naive(renderer, 0, 0, 666, 555);
    }
    diff = clock() - start;
    msec = diff * 1000 / CLOCKS_PER_SEC;
    printf("Time taken %d.%d seconds\n", msec/1000, msec%1000);

    start = clock();
    for (int i = 0; i < 1000000; i++) {
        // Bresenham_LineAlgorithm_less_naive(renderer, 0, 0, 666, 555);
    }
    diff = clock() - start;
    msec = diff * 1000 / CLOCKS_PER_SEC;
    printf("Time taken %d.%d seconds\n", msec/1000, msec%1000);
    start = clock();

    for (int i = 0; i < 1000000; i++) {
        Bresenham_LineAlgorithm(renderer, 0, 0, 666, 555);
    }
    diff = clock() - start;
    msec = diff * 1000 / CLOCKS_PER_SEC;
    printf("Time taken %d.%d seconds\n", msec/1000, msec%1000);


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
        // SDL_RenderDrawPoint(renderer, (int) x, (int) y);
        x += xInc;
        y += yInc;
    }
}

void Bresenham_LineAlgorithm_naive(SDL_Renderer* renderer, int x0, int y0, int x1, int y1) {
    // assume that x1 > x0
    // assume that y1 > y0
    double slope = (y1 - y0) / (double) (x1 - x0);
    // printf("slope: %lf\n", slope);
    int x = x0;
    double y = y0;
    for (int i = x0; i <= x1; i++) {
        x++;
        y += slope;
    }
}

void Bresenham_LineAlgorithm_less_naive(SDL_Renderer* renderer, int x0, int y0, int x1, int y1) {
    // assume that x1 > x0
    // assume that y1 > y0
    // the added value is for rounding up instead of rounding down.
    double slope = (y1 - y0) / (double) (x1 - x0) + 0.0000000000000001;
    double slope_error = 0;
    // printf("slope: %.17g\n", slope);
    int x = x0;
    int y = y0;
    for (int i = x0; i <= x1; i++) {
        x++;
        slope_error += slope;
        if (slope_error >= 1) {
            y++;
            slope_error--;
        }
    }
}

void Bresenham_LineAlgorithm(SDL_Renderer* renderer, int x0, int y0, int x1, int y1) {
    // assume that x1 > x0
    // assume that y1 > y0
    // the added value is for rounding up instead of rounding down.
    int slope = 2 * (y1 - y0);
    int slope_error = slope - 2 * (x1 - x0);
    // printf("slope: %d\n", slope);
    // printf("slope_error: %d\n", slope_error);
    int x = x0;
    int y = y0;
    for (x = x0; x <= x1; x++) {
        // printf("------\n");
        // printf("x: %d\n", x);
        // printf("y: %d\n", y);
        // x++;
        slope_error += slope;
        if (slope_error > 0) {
            y++;
            slope_error -= 2 * (x1 - x0);
        }
    }
}