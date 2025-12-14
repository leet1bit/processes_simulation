#pragma once




// ordonnanceur to execution queue
EXECUTION_QUEUE_RESPONSE* (*execute_instruction)(INSTRUCTION* instruction); // instruction to execute

// update statistics
bool (*update_schedular_statistics) (ORDONNANCEUR_STATISTICS* schedular, float cpu_total_temps_usage, float cpu_temps_unoccupied, int context_switch, float total_temps_attente, float process_termine_count, float throughtput); // must check nullty


// on start
EXECUTION_QUEUE* op_create_execution_queue() {

}

ORDONNANCEUR_STATISTICS* op_create_statistics() {

}

// ordonnanceur to simulator
bool (*need_ressources)(RESSOURCE_ELEMENT* ressource_needed); // return 1 if ressource is available marked unavailable
bool (*ressource_is_free)(RESSOURCE_ELEMENT* ressource); // return 1 if ressource succesfully free (for error handling)
bool (*update_cpu_time_used)(PCB* process, float inc); // shoudld declancher calcul remaining time inc the value to add to time, because can only increasing not decreasing
bool (*update_process)(PCB* process, float temps_fin, float tournround, float temps_attente); // when updating temps fin mark process terminated
bool (*ask_sort_rt)(); // ask simulator to tell process manager to sort by remaining time ; pour srtf
bool (*ask_sort_priority)(); // ask simulator to tell process manager to sort by priority ; pour ppp
PCB* (*ask_for_next_ready_element)();
// ordonnanceur TO simulator
bool op_need_ressources(RESSOURCE_ELEMENT* ressource_needed) {

}

bool op_ressource_is_free(RESSOURCE_ELEMENT* ressource) {

}

bool op_update_cpu_time_used(PCB* process, float inc) {

}

bool op_update_process(PCB* process, float temps_fin, float tournround, float temps_attente) {

}

bool op_ask_sort_rt() {

}

bool op_ask_sort_priority() {

}

PCB* ask_for_next_ready_element() {

}