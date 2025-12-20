#pragma once



#include "structs/ressource.h"



typedef struct {
    RESSOURCE_ELEMENT* ressources; // again using malloc to allocate N ressources
    int ressource_count; // n ressources

    //functions
    // on start
    RESSOURCE_ELEMENT* (*create_ressource_list)(void);

    // ressources operations
    RESSOURCE_ELEMENT* (*look_for_ressource_in_list)(RESSOURCE ressource);
    bool (*mark_ressource_available)(RESSOURCE ressource);
    bool (*mark_ressource_unavailable)(RESSOURCE ressource);
    bool (*check_if_ressource_available)(RESSOURCE ressource); // if available return  if not return 0
    
} RESSOURCE_MANAGER;

