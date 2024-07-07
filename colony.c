#include "colony.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

void initialize_colony(Colony *colony) {
    if (colony == NULL) {
        fprintf(stderr, "Error: Null pointer passed to initialize_colony.\n");
        return;
    }

    colony->colony_position.x = GRID_SIZE / 2;
    colony->colony_position.y = GRID_SIZE / 2;
    colony->num_ants = INITIAL_NUM_ANTS;

    // Initialize ants
    for (int i = 0; i < colony->num_ants; i++) {
        colony->ants[i].position.x = colony->colony_position.x;
        colony->ants[i].position.y = colony->colony_position.y;
        colony->ants[i].carrying_food = 0;
        colony->ants[i].carrying_water = 0;
        colony->ants[i].alive = 1;
    }

    // Initialize food
    srand(time(NULL));
    for (int i = 0; i < NUM_FOOD; i++) {
        colony->food[i].position.x = (rand() % BOX_SIZE) + (GRID_SIZE / 2 - BOX_SIZE / 2);
        colony->food[i].position.y = (rand() % BOX_SIZE) + (GRID_SIZE / 2 - BOX_SIZE / 2);
        colony->food[i].available = 1;
    }

    // Initialize water
    for (int i = 0; i < NUM_WATER; i++) {
        colony->water[i].position.x = (rand() % BOX_SIZE) + (GRID_SIZE / 2 - BOX_SIZE / 2);
        colony->water[i].position.y = (rand() % BOX_SIZE) + (GRID_SIZE / 2 - BOX_SIZE / 2);
        colony->water[i].available = 1;
    }
}

void move_ant(Ant *ant) {
    int direction = rand() % 4;
    switch (direction) {
        case 0: ant->position.x = (ant->position.x + 1) % GRID_SIZE; break;
        case 1: ant->position.x = (ant->position.x - 1 + GRID_SIZE) % GRID_SIZE; break;
        case 2: ant->position.y = (ant->position.y + 1) % GRID_SIZE; break;
        case 3: ant->position.y = (ant->position.y - 1 + GRID_SIZE) % GRID_SIZE; break;
    }

    // Ensure the ant stays within the box
    if (ant->position.x < GRID_SIZE / 2 - BOX_SIZE / 2) ant->position.x = GRID_SIZE / 2 - BOX_SIZE / 2;
    if (ant->position.x >= GRID_SIZE / 2 + BOX_SIZE / 2) ant->position.x = GRID_SIZE / 2 + BOX_SIZE / 2 - 1;
    if (ant->position.y < GRID_SIZE / 2 - BOX_SIZE / 2) ant->position.y = GRID_SIZE / 2 - BOX_SIZE / 2;
    if (ant->position.y >= GRID_SIZE / 2 + BOX_SIZE / 2) ant->position.y = GRID_SIZE / 2 + BOX_SIZE / 2 - 1;
}

void search_for_resources(Colony *colony) {
    for (int i = 0; i < colony->num_ants; i++) {
        Ant *ant = &colony->ants[i];

        // Move towards colony if ant is alive
        if (ant->alive) {
            // Check if ant is carrying both food and water
            if (ant->carrying_food && ant->carrying_water) {
                // Move directly towards colony
                if (ant->position.x != colony->colony_position.x || ant->position.y != colony->colony_position.y) {
                    // Move horizontally
                    if (ant->position.x < colony->colony_position.x) {
                        ant->position.x++;
                    } else if (ant->position.x > colony->colony_position.x) {
                        ant->position.x--;
                    }
                    // Move vertically
                    if (ant->position.y < colony->colony_position.y) {
                        ant->position.y++;
                    } else if (ant->position.y > colony->colony_position.y) {
                        ant->position.y--;
                    }
                }
            } else {
                // Check if ant is on food or water position and collect resources
                for (int f = 0; f < NUM_FOOD; f++) {
                    if (colony->food[f].available && colony->food[f].position.x == ant->position.x && colony->food[f].position.y == ant->position.y) {
                        ant->carrying_food = 1;
                        colony->food[f].available = 0;
                        break;
                    }
                }

                for (int w = 0; w < NUM_WATER; w++) {
                    if (colony->water[w].available && colony->water[w].position.x == ant->position.x && colony->water[w].position.y == ant->position.y) {
                        ant->carrying_water = 1;
                        colony->water[w].available = 0;
                        break;
                    }
                }

                // Move randomly if not carrying both resources
                move_ant(ant);
            }

            // Check if ant has reached colony position
            if (ant->position.x == colony->colony_position.x && ant->position.y == colony->colony_position.y) {
                // Drop resources
                if (ant->carrying_food && ant->carrying_water) {
                    ant->carrying_food = 0;
                    ant->carrying_water = 0;

                    // Produce one ant at a time
                    if (colony->num_ants < MAX_NUM_ANTS) {
                        colony->ants[colony->num_ants].position = colony->colony_position;
                        colony->ants[colony->num_ants].carrying_food = 0;
                        colony->ants[colony->num_ants].carrying_water = 0;
                        colony->ants[colony->num_ants].alive = 1;
                        colony->num_ants++;
                    }
                }
            }

            // Simulate ant death with a very reduced rate
            if (rand() % 200 == 0) {
                ant->alive = 0;
            }
        }
    }
}

// Function to check if all ants are dead
int all_ants_dead(const Colony *colony) {
    for (int i = 0; i < colony->num_ants; i++) {
        if (colony->ants[i].alive) {
            return 0; // Not all ants are dead
        }
    }
    return 1; // All ants are dead
}

// Modified simulate function to stop when all ants are dead
void simulate(Colony *colony, int steps) {
    for (int step = 0; step < steps; step++) {
        search_for_resources(colony);
        printf("\033[H\033[J");  // ANSI escape code to clear the screen and move the cursor to the top-left corner
        display_colony(colony);
        usleep(300000);  // Sleep for 0.3 seconds to observe the simulation

        // Check if all ants are dead
        if (all_ants_dead(colony)) {
            printf("All ants are dead. Simulation stopped.\n");
            break;
        }
    }
}

void display_colony(const Colony *colony) {
    char grid[GRID_SIZE][GRID_SIZE];

    // Initialize grid with empty spaces
    for (int y = 0; y < GRID_SIZE; y++) {
        for (int x = 0; x < GRID_SIZE; x++) {
            grid[x][y] = '.';
        }
    }

    // Place food and annotate details
    int food_count = 0;
    for (int i = 0; i < NUM_FOOD; i++) {
        if (colony->food[i].available) {
            grid[colony->food[i].position.x][colony->food[i].position.y] = 'F';
            food_count++;
        }
    }

    // Place water and annotate details
    int water_count = 0;
    for (int i = 0; i < NUM_WATER; i++) {
        if (colony->water[i].available) {
            grid[colony->water[i].position.x][colony->water[i].position.y] = 'W';
            water_count++;
        }
    }

    // Place ants and annotate details (A for alive, D for dead)
    int live_count = 0;
    int dead_count = 0;
    int birth_count = 0;
    for (int i = 0; i < colony->num_ants; i++) {
        if (colony->ants[i].alive) {
            grid[colony->ants[i].position.x][colony->ants[i].position.y] = 'A';
            live_count++;
        } else {
            grid[colony->ants[i].position.x][colony->ants[i].position.y] = 'D';
            dead_count++;
        }
        if (colony->ants[i].position.x == colony->colony_position.x && colony->ants[i].position.y == colony->colony_position.y && colony->ants[i].alive) {
            birth_count++;
        }
    }

    // Annotate colony position
    grid[colony->colony_position.x][colony->colony_position.y] = 'C';

    // Print the grid with details
    printf("Ant Colony Dashboard:\n");
    printf("-----------------------\n");
    printf("| Live Ant Count: %d   |\n", live_count);
    printf("| Dead Ant Count: %d   |\n", dead_count);
    printf("| Birth Site Count: %d |\n", birth_count);
    printf("| Food Count: %d       |\n", food_count);
    printf("| Water Count: %d      |\n", water_count);
    printf("-----------------------\n");
    printf("Legend:\n");
    printf("  A - Alive Ant\n");
    printf("  D - Dead Ant\n");
    printf("  C - Colony\n");
    printf("  F - Food\n");
    printf("  W - Water\n");
    printf("  . - Empty Space\n");

    // Display the grid
    for (int y = 0; y < GRID_SIZE; y++) {
        for (int x = 0; x < GRID_SIZE; x++) {
            putchar(grid[x][y]);
        }
        putchar('\n');
    }
}

