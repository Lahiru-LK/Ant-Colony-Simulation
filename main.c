#include "colony.h"

int main() {
    Colony colony;
    initialize_colony(&colony);
    simulate(&colony, 1000);
    return 0;
}