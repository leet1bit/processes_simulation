
#include "../lib/structs/simulator.h"
#include "../src/implementation/simulator.c"


int main() {

    SIMULATOR* simulator = (SIMULATOR*)malloc(sizeof(SIMULATOR));

    
    printf("hit main\n\n\n");

    FILE* buffer = fopen("data.csv", "r");

    simulator->init = op_simul_init;

    simulator->init(simulator, buffer);

    simulator->stop(simulator);

    fclose(buffer);

    return 0;

}