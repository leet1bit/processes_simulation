#pragma once

#include "../../lib/structs/process.h"
#include "../../lib/structs/simulator.h"
#include "../../lib/structs/process_manager.h"
#include "../../lib/structs/ressource_manager.h"
#include "../../lib/structs/ressource.h"
#include "../../lib/structs/schedular.h"

#include "../../src/operations/schedular.c"
#include "../../src/operations/ressource_manager.c"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>




// requiring functions
SIMULATOR* op_start(SIMULATOR* self, char* path) {
    
    PROCESS_MANAGER* process_manager = (PROCESS_MANAGER*)malloc(sizeof(PROCESS_MANAGER));
    
    RESSOURCE_MANAGER* ressource_manager = (RESSOURCE_MANAGER*)malloc(sizeof(RESSOURCE_MANAGER));

    ORDONNANCEUR* schedular = (ORDONNANCEUR*)malloc(sizeof(ORDONNANCEUR));

    if (process_manager == NULL || ressource_manager == NULL || schedular == NULL) {
        fprintf(stderr, "ERROR ON: op_start , allocation returned NULL\n");
        exit(1);
    }

    self->process_manager = process_manager;
    self->ressource_manager = ressource_manager;
    self->schedular = schedular;


    return self;
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




bool op_signal_ressource_is_free(RESSOURCE_MANAGER* ressource_manager, RESSOURCE ressource) {
    bool response = ressource_manager->mark_ressource_available(ressource);

    return response;
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

PCB* op_simul_ask_for_next_ready_element(SIMULATOR* simulator, PCB* process) {
    PCB* response = simulator->process_manager->get_next_ready_element(process);

    return response;
}

bool op_simul_ask_sort_rt(SIMULATOR* simulator) {
    bool response = simulator->process_manager->sort_by_rt(simulator->process_manager);

    return response;
}

bool op_simul_ask_sort_priority(SIMULATOR* simulator) {
    bool response = simulator->process_manager->sort_by_priority(simulator->process_manager);

    return response;
}

WORK_RETURN op_run(SIMULATOR* self, OPTIONS options) {

    self->schedular->select(self->schedular, self->schedular->quantum);

    return WORK_DONE;
}

process_update op_sched_update_process(SIMULATOR* self, PCB* pcb, time_t* temps_fin, float* cpu_temps_used) { // with nullty check; updating temps_fin = market_terminated = update_turnround ; updating cpu_temps_used = updating_remaining_time

    return self->process_manager->update_process(self->process_manager, pcb, temps_fin, cpu_temps_used);
}

WORK_RETURN op_simul_stop(SIMULATOR* self) {

    WORK_RETURN stop_process_manager = self->process_manager->kill(self->process_manager);

    WORK_RETURN stop_ressource_manager = self->ressource_manager->kill(self->ressource_manager);

    WORK_RETURN stop_schedular = self->schedular->kill(self->schedular);

    if (stop_process_manager != WORK_DONE || stop_ressource_manager != WORK_DONE || stop_schedular != WORK_DONE) {
        return ERROR;
    }


    return WORK_DONE;

}



WORK_RETURN op_simul_init(SIMULATOR* self, FILE* buffer) {
    
    // ---------- process manager


    OPTIONS options = self->ask_for_options();

    self->process_manager = self->create_process_manager(); // create process manager

    self->process_manager->init(self->process_manager, buffer, options.algorithm);

    // ---------- ressource list

    self->ressource_manager = self->create_ressource_manager(); // create ressource manager

    self->ressource_manager->init = op_rm_init; // assign the initializer function

    self->ressource_manager->init(self->ressource_manager);

    // ---------- schedular
 
    self->schedular = self->create_schedular(options.algorithm, options.quantum); // create schedular
    
    self->schedular->init = op_sched_init; // assign the initialization function to schedular

    self->schedular->init(self->schedular, self, options); // then init it

    // ------- simulator

    self->run = op_run;
    self->update_process = op_sched_update_process;
    self->check_ressource_disponibility = op_check_ressource_disponibility;
    self->signal_ressource_is_free = op_signal_ressource_is_free;
    self->stop = op_simul_stop;


    return WORK_DONE;
}


