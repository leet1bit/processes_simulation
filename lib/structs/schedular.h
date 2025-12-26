#pragma once

#include "structs/process.h" // for pcb
#include "structs/simulator.h" // for SIMULATOR
#include "structs/execution_queue.h" // for the exec queue
#include "structs/ressource.h"

#include <unistd.h> // for time wait in second

typedef enum {

    RR, SRTF, PPP, FCFS, SJF

} Algorithms;

typedef enum {

    FINISHED,      // Instruction executed successfully
    RESSOURCE_NEEDED,
    QUANTUM_EXPIRED,
    ERROR         // General error

}  process_return;

typedef struct ORDONNANCEUR_STATISTICS {

    float cpu_total_temps_usage; // somme temps cpu occup total de tout process
    int context_switch; // nombre total de changement de processus

    // when process is terminated
    float total_turnround; // somme de tout processus (temps termine - temps arrive)
    int processus_termine_count; // processus terminé
    float troughtput; // processus terminé / total temps en ms
    float total_temps_attente; // somme temps waiting de tout processus
    
} ORDONNANCEUR_STATISTICS;

typedef struct ORDONNANCEUR {

    Algorithms algorithm;
    PCB* exec_proc; // processus en train de s'executer
    int current_pid; // pid du processus en cours d'exec

    float quantum; // quantum de time pour RR
    time_t start;
    time_t end;
    int cpu_time_used; // en ms: end - start

    float current_time;

    SIMULATOR* simulator; // pointeur vers simulator
    EXECUTION_QUEUE* execution_queue; // pointeur vers queue d'execution

    ORDONNANCEUR_STATISTICS* statistics; // pointeur vers les statistics du schedular
    INSTRUCTION* current_instruction; // need to be init as head

    // functions
    // on start
    OPTIONS (*init)(ORDONNANCEUR* self, SIMULATOR* simulator, OPTIONS option);

    EXECUTION_QUEUE* (*create_execution_queue)(void);
    ORDONNANCEUR_STATISTICS* (*create_statistics)(void);

    // ordonnanceur to simulator (using bool for simplicity)
    // EXECUT_RESPONSE (*signal_execute_instruction) (ORDONNANCEUR* self, EXECUTION_QUEUE* execution_queue, INSTRUCTION* instruction); // tell the execution queue to execute an instruction
    bool (*need_ressources)(RESSOURCE_ELEMENT* ressource_needed); // return 1 if ressource is available marked unavailable
    bool (*ressource_is_free)(SIMULATOR* simulator, RESSOURCE ressource); // return 1 if ressource succesfully free (for error handling)
    // bool (*update_cpu_time_used)(PCB* process, float inc); // shoudld declancher calcul remaining time inc the value to add to time, because can only increasing not decreasing
    bool (*ask_sort_rt)(SIMULATOR* simulator); // ask simulator to tell process manager to sort by remaining time ; pour srtf
    bool (*ask_sort_priority)(SIMULATOR* simulator); // ask simulator to tell process manager to sort by priority ; pour ppp
    PCB* (*sched_ask_for_next_ready_element)(ORDONNANCEUR* self,PCB* current_pcb);

    // update statistics
    bool (*update_schedular_statistics) (ORDONNANCEUR* self, float* exec_time, float* burst, float* temp_attente, bool finished); // must check nullty

    // check instruction disponibility
    bool (*check_ressource_disponibility) (RESSOURCE ressource);
    
    
    process_update (*update_process)(ORDONNANCEUR* self, PCB* pcb, time_t* temps_fin, float* cpu_temps_used); // with nullty check; updating temps_fin = market_terminated = update_turnround ; updating cpu_temps_used = updating_remaining_time

    // execute process    
    
    WORK_RETURN (*select)(ORDONNANCEUR* self, float quantum); // will be pointing on one of 5 functions depens on the algorithm

} ORDONNANCEUR;

// like n9dr n3ti l ordonnanceur process i3tih l execution_queue