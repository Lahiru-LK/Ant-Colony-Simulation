#ifndef COLONY_H
#define COLONY_H

#define GRID_SIZE 30
#define BOX_SIZE 15
#define INITIAL_NUM_ANTS 1
#define MAX_NUM_ANTS 100
#define NUM_FOOD 10
#define NUM_WATER 10

typedef struct {
    int x;
    int y;
} Position;

typedef struct {
    Position position;
    int carrying_food;
    int carrying_water;
    int alive;
} Ant;

typedef struct {
    Position position;
    int available;
} Food;

typedef struct {
    Position position;
    int available;
} Water;

typedef struct {
    Position colony_position;
    Ant ants[MAX_NUM_ANTS];
    int num_ants;
    Food food[NUM_FOOD];
    Water water[NUM_WATER];
} Colony;

void initialize_colony(Colony *colony);
void move_ant(Ant *ant);
void search_for_resources(Colony *colony);
void simulate(Colony *colony, int steps);
void display_colony(const Colony *colony);

#endif /* COLONY_H */
