
#include <unistd.h>

#include "../../lib/structs/schedular.h"
#include "../../lib/structs/process.h"


WORK_RETURN execute_rr(float quantum) {
    sleep(quantum);
    return WORK_DONE;
}


WORK_RETURN ex_kill(EXECUTION_QUEUE* self) {
    
    free(self);

    return WORK_DONE;
}



bool ex_init(EXECUTION_QUEUE* self) {

    self->execute_rr = execute_rr;
    self->kill = ex_kill;

    return true;
}


