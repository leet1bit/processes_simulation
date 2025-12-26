
#include <stdio.h>
#include <stdlib.h>

#include "structs/process_manager.h"
#include "structs/simulator.h"
#include "structs/process.h"


OPTIONS ask_for_options() {
    int algorithm;
    float quantum;

    do {
        printf("Hello\n\twhich algorithm you wish to run :\n");
        printf("0: RR\n");
        printf("1: SRTF\n");
        printf("2: PPP\n");
        printf("3: FCFS\n");
        printf("4: SJF\n");
        scanf("%d", &algorithm);

        if (algorithm == 0) {
            printf("quantum (in ms)\n");
            scanf("%f", &quantum);
        }

    } while (algorithm != 0 && algorithm != 1 && algorithm != 2 && algorithm != 3 && algorithm != 4);

    OPTIONS return_value;
    return_value.algorithm = algorithm;
    return_value.quantum = quantum;
    
    return return_value;
}



PROCESS_MANAGER* create_process_manager() {
    
    PROCESS_MANAGER* process_manager = (PROCESS_MANAGER*)malloc(sizeof(PROCESS_MANAGER)); // allocate process manager
    
    if (process_manager == NULL) {
        fprintf(stderr, "ERROR ON: create_process_manager , process_manager allocation failed\n");
        exit(1);
    }

    return process_manager;
}

ORDONNANCEUR* op_create_schedular(Algorithms algorithm, int quantum) {

    ORDONNANCEUR* schedular = (ORDONNANCEUR*)malloc(sizeof(ORDONNANCEUR)); // init the schedular    

    if (schedular == NULL) {
        fprintf(stderr, "ERROR ON: op_create_schedular: Failed to allocate memory for schedular\n");
        exit(1);
    }

    schedular->algorithm = algorithm;
    schedular->quantum = quantum;

    return schedular;
}