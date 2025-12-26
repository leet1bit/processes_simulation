#pragma once

#include "../../lib/structs/process.h"
#include "../../lib/structs/schedular.h"
#include "../../lib/structs/ressource.h"

typedef enum {

    EXEC_SUCCESS,      // Instruction executed successfully
    NEED_RESSOURCE,    // ressource needed
    EXEC_ERROR         // General error

} EXECUT_RESPONSE;

typedef enum {
    WORK_DONE, WORK_ERROR
} WORK_RETURN; // moved here because the compiler doesnt reconize it when it's file is loded last


typedef struct EXECUTION_QUEUE {

    int id; // l id du composant en train d'executer
    char name[10]; // name du composant qui execute

    INSTRUCTION* current_instruction; // l instruction en train de s'executer
    PCB* current_process; // process en train de s'executer
    int process_id; // l'pid du current process
    float quantum;

    struct ORDONNANCEUR* schedular;

    bool (*init)(struct EXECUTION_QUEUE* self);

    //function
    INSTRUCTION* (*next_instruction) (PCB* pcb); // retrieve the next instruction to pass it to execute instruction
    EXECUT_RESPONSE* (*execute_instruction) (INSTRUCTION* instruction); // execute it and return the result
    bool (*check_ressource_disponibility) (RESSOURCE ressource); // check if instruction is disponible
    bool (*mark_ressource_unavailable) (RESSOURCE ressource); // mark ressource indisponible

    WORK_RETURN (*execute_rr)(float quantum); // execute for round robin

    WORK_RETURN (*kill)(struct EXECUTION_QUEUE* self);

} EXECUTION_QUEUE;