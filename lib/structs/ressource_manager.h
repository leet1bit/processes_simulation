#pragma once



#include "../../lib/structs/ressource.h"
#include "../../lib/structs/execution_queue.h"



typedef enum {
    DONE, INIT_ERROR
} init_rm;


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
    
    init_rm (*init)(struct RESSOURCE_MANAGER* self);

    bool (*free_ressource_list) (struct RESSOURCE_MANAGER* self);

    WORK_RETURN (*kill)(struct RESSOURCE_MANAGER* self);

} RESSOURCE_MANAGER;

