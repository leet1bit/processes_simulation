#pragma once

#include "../../lib/structs/process.h"
#include "../../lib/structs/simulator.h"
#include "../../lib/structs/process_manager.h"
#include "../../lib/structs/ressource_manager.h"
#include "../../lib/structs/ressource.h"
#include "../../lib/structs/schedular.h"

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


// process_manager & schedular related function
bool op_check_ressource_disponibility(SIMULATOR* self, RESSOURCE ressource_needed) {

    bool response = self->ressource_manager->check_if_ressource_available(ressource_needed);

    return response;
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

bool op_ask_sort_rt(SIMULATOR* simulator) {
    bool response = simulator->process_manager->sort_by_rt(simulator->process_manager);

    return response;
}

bool op_ask_sort_priority(SIMULATOR* simulator) {
    bool response = simulator->process_manager->sort_by_priority(simulator->process_manager);

    return response;
}

WORK_RETURN op_init(SIMULATOR* self, ORDONNANCEUR* schedular, RESSOURCE_MANAGER* ressource_manager, FILE* buffer) {
    
    // ---------- process manager


    OPTIONS options = self->ask_for_options();

    self->process_manager = self->create_process_manager(); // create process manager

    self->process_manager->run(self->process_manager);

    // ---------- ressource list

    self->ressource_manager = self->create_ressource_manager(); // create ressource manager

    self->ressource_manager->init(self->ressource_manager);

    // ---------- schedular
 
    self->schedular = self->create_schedular(options.algorithm, options.quantum); // create schedular

    self->schedular->init(self->schedular, self, options);

    return WORK_DONE;
}

WORK_RETURN op_run(SIMULATOR* self, OPTIONS options) {

    switch (options.algorithm) {
        // assign schedular->select depoend on the algorithm
    }




}

