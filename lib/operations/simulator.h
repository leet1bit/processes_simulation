#pragma once

#include "structs/process.h"
#include "structs/simulator.h"
#include "structs/process_manager.h"
#include "structs/ressource_manager.h"
#include "structs/schedular.h"
#include "structs/ressource.h"




// requiring functions
void op_start(SIMULATOR* self, char* path) {
    

}

void op_stop(SIMULATOR* self, char* path) {

}

void op_load_simulator(SIMULATOR* self, char* path) {

}

FILE* op_load_processus(SIMULATOR* self) {

}

//initialize managers
PROCESS_MANAGER* op_start_process_manager(SIMULATOR* self, FILE* buffer) {

    PROCESS_MANAGER* process_manager = (PROCESS_MANAGER*)malloc(sizeof(PROCESS_MANAGER));
    
    if (process_manager == NULL) {
        fprintf(stderr, "ERROR ON: op_start_ressource_manager , process_manager allocation returned NULL\n");
        exit(1);
    }

    self->process_manager = process_manager;

    return process_manager;
}

RESSOURCE_MANAGER* op_start_ressource_manager(SIMULATOR* self) {
    
    RESSOURCE_MANAGER* ressource_manager = (RESSOURCE_MANAGER*)malloc(sizeof(RESSOURCE_MANAGER));

    if (ressource_manager == NULL) {
        fprintf(stderr, "ERROR ON: op_start_ressource_manager , ressource_manager allocation returned NULL\n");
        exit(1);
    }

    self->ressource_manager = ressource_manager;

    return ressource_manager;
}

ORDONNANCEUR* op_start_schedular(Algorithms algorithm, int quantum, SIMULATOR* self) {
    
    ORDONNANCEUR* schedular = (ORDONNANCEUR*)malloc(sizeof(ORDONNANCEUR));

    if (schedular == NULL) {
        fprintf(stderr, "ERROR ON: op_start_schedular , schedular allocation returned NULL\n");
        exit(1);
    }

    self->schedular = schedular;

    return schedular;
}


// process_manager & schedular related function
bool op_check_ressource_disponibility(SIMULATOR* self, RESSOURCE_ELEMENT* ressource_needed) {
    bool response = self->ressource_manager->check_if_ressource_available(ressource_needed);

    return response;
}

bool op_signal_ressource_is_free(RESSOURCE_MANAGER* ressource_manager, RESSOURCE ressource) {
    bool response = ressource_manager->mark_ressource_available(ressource);

    return response;
}

// process_manager & schedular related functions
bool op_update_cpu_time_used(PCB* process, float inc) {

}


bool op_sched_check_instruction_disponibility(INSTRUCTION* instruction) {

}

bool op_simul_check_instruction_disponibility(RESSOURCE_MANAGER* ressource_manager, RESSOURCE ressource) {
    bool result = ressource_manager->check_if_ressource_available(ressource);

    return result;
}

bool op_signal_ressource_free(RESSOURCE_MANAGER* ressource_manager, RESSOURCE ressource) {
    bool response = ressource_manager->mark_ressource_available(ressource);

    return response;
}

PCB* op_ask_for_next_ready_element(SIMULATOR* simulator, PCB* process) {
    bool response = simulator->process_manager->get_next_ready_element(process);

    return response;
}

bool op_ask_sort_rt(SIMULATOR* simulator) {
    bool response = simulator->process_manager->sort_by_rt(simulator->process_manager);

    return response;
}

bool op_ask_sort_priority(SIMULATOR* simulator) {
    bool response = simulator->process_manager->sort_by_priority(simulator->process_manager);

    return response;
}