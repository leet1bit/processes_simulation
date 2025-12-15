

#include "structs/process.h"


typedef struct {
    PCB* head;
    int size;
} buffer_return;


typedef struct {
    int pid;
    char process_name[20];
    char user_id[20];
    int ppid;
    E_etat etat; // one of the values in the enum e_etat
    int prioritie; // priorities from 1 to 5 ; 1-critical

    INSTRUCTION* instructions;
    long programme_compteur; // max 9,223,372,036,854,775,807 instruction
    int memoire_necessaire; // en MB
    INSTRUCTION* current_instruction; // l'instruction en train de s executer

    int burst_time; // total temps necessaire en ms pour l'exec . burst = compte_temps + temps_restant
    float cpu_time_used; // temps cpu consomme en ms init 0
    int remaining_time; // temps restant : = burst - cpu_time_used
    int cpu_usage; // initialized as 0

    PROCESS_STATISTICS* statistics; 

    int* pid_childrens;
    PCB* pid_sibling_next; // pointeur vers next sib
    PCB* pid_sibling_previous; // pointeur vers previous sib
} PCB;

typedef struct {
    uint32_t* instruct_id; // the id of instruction because process can stop at it if need ressources, pointer because it can be too long
    PCB* process; // the id of the process owner

    float time_remaining; // in nano seconds
    RESSOURCE_ELEMENT* type; // type of instruction which is ressource needed
    INSTRUCTION_STATE* state; // state of instruction 
} INSTRUCTION;

buffer_return* extract_from_buffer(FILE* csv_buffer) {
    
    int count = 0;

    char line_pcb[10000];
    while(fgets(line_pcb, sizeof(buffer), csv_buffer)) { // dont forget temps creation
        

        PCB pcb = {
            count,

        }
    }
}





// process_name,user_id,ppid,priority,[instruction],n_instruction,memoire,burst,
typedef struct {
    char process_name[20];
    char user_id[20];
    int priority;
    char** instructions;
    int instructions_count;
    int memoire;
    float burst;
    bool unvalid_process;
} parser_return;

typedef struct {
    INSTRUCTION* head;
    int size;
} insruction_parser_return;

parser_return* parser(char* line) {
    parser_return parsed_line = {};

    int loop = 0; 
    int char_count = 0;
    int value_number = 0;
    char value[100];
    for(int i = 0; i < 10000;i++) { // instructions_count
        if (line[i] != ',') {
            value[char_count] = line[i];
            char_count++;
        } else if (line[i] == ',') {
            switch (value_number) {
                case 0:
                    if (sizeof(value) > 20) {
                        printf("ERROR ON: parser function process line in csv '%s' \nhas exceded 20 caracter in process_name\n");
                        exit(1);
                    }
                    (value > 20) ? 
                    parsed_line->process_name = value;
                    break;    
                case 1:
                    if (sizeof(value) > 20) {
                        printf("ERROR ON: parser function process line in csv '%s' \nhas exceded 20 caracter in user_id\n");
                        exit(1);
                    }
                    parsed_line->user_id = value;
                    break;    
                case 2:
                    if (value > 5 || value < 1) {
                        printf("ERROR ON: parser function process line in csv '%s' \npriority out of range(1-5)\n");
                        exit(1);
                    }
                    parsed_line->priority = atoi(value); // atoi stand for ascii to integer and located in stdlib; maybe make ours if we still have time
                    break;    
                case 3:
                    if (sizeof(value) < 1) {
                        parsed_line->unvalid_process = 1;
                    }
                    insruction_parser_return parsed_instructions = instruction_parser(value);

            }

            char_count = 0;
            value_number++;
            memset(value, 0, sizeof(value)); // setting all the bytes in memory will make it equivalent to empty string

            if (value_number > 6) {
                printf("ERROR ON: parser function (csv file data unvalid)");
                exit(1);
            }
        } else if (line[i] == '\n') {
            break;
        } else {
            printf("ERROR ON: parser function");
            exit(1);
        }
    }
    return parsed_line;
}


typedef struct {
    INSTRUCTION* head;
    int size;
} insruction_parser_return;

insruction_parser_return* instruction_parser(char* value) {

}