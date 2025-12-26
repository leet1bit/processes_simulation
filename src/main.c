
#include "../lib/structs/simulator.h"
#include "../src/operations/simulator.c"


int main() {

    SIMULATOR* simulator = (SIMULATOR*)malloc(sizeof(SIMULATOR));

    FILE* buffer = fopen("data.csv", "r");

    simulator->init = op_simul_init;

    simulator->init(simulator, buffer);

    fclose(buffer);

    return 0;

}