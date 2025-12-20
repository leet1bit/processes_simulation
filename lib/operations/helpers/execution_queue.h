

#include <structs/process.h>
#include <structs/schedular.h>


bool op_check_ressource_disponibility(ORDONNANCEUR* schedular, RESSOURCE ressource) {

    return schedular->check_ressource_disponibility(ressource);

}