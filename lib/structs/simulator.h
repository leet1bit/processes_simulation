#pragma once

#include "structs/process_manager.h"
#include "structs/schedular.h"
#include "structs/ressource_manager.h"
#include "structs/ressource.h"

typedef enum {
    RR, SRTF, PPP, FCFS, SJF
} Algorithms;

typedef enum {
    WORK_DONE, ERROR
} WORK_RETURN;

typedef struct OPTIONS {

    int algorithm;
    float quantum;

} OPTIONS;


typedef struct SIMULATOR {
    ORDONNANCEUR* schedular; // pointeur vers lordonnanceur
    PROCESS_MANAGER* process_manager; // pointeur to process manaer
    RESSOURCE_MANAGER* ressource_manager; // pointeur vers ressource
    struct SIMULATOR* simulator;
    
    int simulation_time;
    bool runing;

    char csv_path[20];


    // functions
    // requiring functions
    struct SIMULATOR* (*start)(struct SIMULATOR* self, char* path); // so void is the return type, (*start) is the function pointer [we need to create or define the function outside then assign the fucntion created to that pointer], then after the arguments
    void (*stop)(struct SIMULATOR* self, char* path); // same thing here
    SIMULATOR* (*run_simulator)(struct SIMULATOR* self, char* path); // same
    FILE* (*load_processus)(char* file_name); // will read a file so it's return type is FILE*

    // functions
    // initialize the managers
    PROCESS_MANAGER* (*start_process_manager)(SIMULATOR* self, FILE* buffer); // process manager need the csv buffer to create the process table
    RESSOURCE_MANAGER* (*start_ressource_manager)(SIMULATOR* self); // passing void to non argument function is a common use :) // i think it needs nothing because all the ressource are defined in the enum and should only toggle the disponibility or availability 
    ORDONNANCEUR* (*start_schedular)(Algorithms algorithm, int quantum, SIMULATOR* self); // we should pass the simulator itself's pointer to the function 

    // process_manager & schedular related function
    bool (*check_ressource_disponibility)(SIMULATOR* simulator, RESSOURCE ressource); // pointer or can be changed to ressource name to the ressource needed if disponible return 1 else 0
    bool (*signal_ressource_is_free)(RESSOURCE_ELEMENT* ressource); // can be void but just to be sure

    // process_manager & schedular related functions
    bool (*update_cpu_time_used)(PCB* process, float inc);

    // check instruction disponibility
    bool (*check_ressource_disponibility) (RESSOURCE_MANAGER* ressource_manager, RESSOURCE ressource);

    bool (*signal_ressource_free) (RESSOURCE_MANAGER* ressource_manager, RESSOURCE ressource);

    PCB* (*simul_ask_for_next_ready_element) (SIMULATOR* self, PCB* current_pcb);

    bool (*ask_sort_rt)(SIMULATOR* self); // ask simulator to tell process manager to sort by remaining time ; pour srtf
    bool (*ask_sort_priority)(SIMULATOR* self); // ask simulator to tell process manager to sort by priority ; pour ppp


    PROCESS_MANAGER* (*create_process_manager)(void);
    RESSOURCE_MANAGER* (*create_ressource_manager)(void);
    ORDONNANCEUR* (*create_schedular)(Algorithms algorithm, int quantum);

    WORK_RETURN (*init) (PROCESS_MANAGER* process_manager, ORDONNANCEUR* schedular, SIMULATOR* simulator, EXECUTION_QUEUE execution_queue);

    OPTIONS (*ask_for_options)(void);

    WORK_RETURN (*run)(SIMULATOR* self,OPTIONS options); // will be pointing on one of 5 functions depens on the algorithm


} SIMULATOR;