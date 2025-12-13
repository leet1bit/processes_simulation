


enum {
    READY, BLOCKED, EXECUTION, TERMINATED
} E_etat;

typedef struct {
    char ressource_name[10];
    bool disponibilite;
} RESSOURCE;

typedef struct {
    int pcb_id;
    char process_name[20];
    char user_id[20];
    int ppid;
    E_etat etat; // one of the values in the enum e_etat
    int prioritie; // priorities from 1 to 5 ; 1-critical
    
    
    
} PCB;