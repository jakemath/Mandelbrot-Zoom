//
//  main.cpp
//  mandelbrot
//
//  Created by Jacob Mathai on 8/2/20.
//  Copyright © 2020 Jacob Mathai. All rights reserved.
//

#include <iostream>
#include <cmath>
#include <math.h>
#include <string>
#include <SDL2/SDL.h>

int WIDTH = 1000, HEIGHT = 1000, MAX_ITERATIONS = 200;
long double RANGE_MIN = -2.0, RANGE_MAX = 2.0, FACTOR = 1.0;

long double map_to_range(long double value,
                      	 long double input_min,
                      	 long double input_max,
                      	 long double output_min,
                      	 long double output_max)
{
    return (value - input_min) * (output_max - output_min) / (input_max - input_min) + output_min;
}

int main(int argc, char *argv[])
{
    std::cout << "Starting..." << std::endl;
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event event;
    SDL_CreateWindowAndRenderer(1440, 900, 0, &window, &renderer);
    SDL_RenderSetLogicalSize(renderer, WIDTH, HEIGHT);
    int x, y, iteration = 0, count = 0, red, green, blue, bright;
    long double a, b, a0, b0, ai, bi;
    while (true)
    {
	RANGE_MAX -= 0.1*FACTOR;
	RANGE_MIN += 0.15*FACTOR;
	FACTOR *= 0.9349;
	MAX_ITERATIONS += 5;
	if (count > 30)
	    MAX_ITERATIONS *= 1.02;
        SDL_RenderPresent(renderer);
        for (x = 0; x < WIDTH; ++x)
        {
            if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
	        return 0;
	    for (y = 0; y < HEIGHT; ++y)
            {
                a = map_to_range(x, 0, WIDTH, RANGE_MIN, RANGE_MAX);
                b = map_to_range(y, 0, HEIGHT, RANGE_MIN, RANGE_MAX);
                a0 = a;
                b0 = b;
                for (iteration = 0; iteration < MAX_ITERATIONS && a + b < RANGE_MAX; ++iteration)
              	{
		    ai = a*a - b*b;
		    bi = 2*a*b;
                    a = a0 + ai;
                    b = b0 + bi;
		}
		bright = map_to_range(iteration, 0, MAX_ITERATIONS, 0, 255);
            	if (iteration == MAX_ITERATIONS || bright < 20) 
                    bright = 0;
            	red = map_to_range(bright*bright, 0, 650, 0, 255);
            	green = bright;
            	blue = map_to_range(sqrt(bright), 0, sqrt(255), 0, 255);
            	SDL_SetRenderDrawColor(renderer, red, green, blue, 255);
            	SDL_RenderDrawPoint(renderer, x, y);
            }
	}
	++count;
    }
    return 0;
}
