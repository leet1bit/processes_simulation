#pragma once

#include "structs/process.h"

#include <stdbool.h>

// need_to_be_changed
char instructions_list[6] = ["aaa", "bbb", "ccc", "ddd", "eee", "fff"];

typedef struct {
    PCB* head;
    int size;
} buffer_return;

buffer_return* extract_from_buffer(FILE* csv_buffer) {
    
    int count = 0;

    char line_pcb[70000];
    while(fgets(line_pcb, sizeof(buffer), csv_buffer)) { // dont forget temps creation
        

        PCB pcb = {
            count,

        }
    }
}

// process_name,user_id,ppid,priority,[instruction],n_instruction,memoire,burst,
typedef struct parser_return{
    char process_name[20];
    char user_id[20];
    int priority;
    char** instructions;
    int instructions_count;
    int memoire;
    float burst;
    bool unvalid_process_csv_check;
} parser_return;

typedef struct {
    char** instructions;
    int count;
} insruction_parser_return;


parser_return* parser(char* line) {
    parser_return* parsed_line = (parser_return*)malloc(sizeof(parser_return));

    int char_count = 0;
    int value_number = 0;
    char value[100];
    int line_length = strlen(line); // for time consuming
    if (line[line_length] != '\n' && line[line_length] != '\0') { // trust no one
        fprintf(stderr, "ERROR ON: parser function parser line gived is unvalid (probably will lead to loop infinite)\n", line);
        exit(1);
    }
    for(int i = 0; i < line_length;i++) { // line_size
        if (line[i] != ',') { // so it's a char of ressource
            value[char_count] = line[i];
            char_count++;
        } else if (line[i] == ',') {
            switch (value_number) {
                case 0:
                    if (strlen(value) > 20) {
                        fprintf(stderr, "ERROR ON: parser function process line in csv '%s' \nhas exceded 20 caracter in process_name\n", line);
                        free(parsed_line);
                        exit(1);
                    }
                    strncpy(parsed_line->process_name, value, sizeof(parsed_line->process_name) - 1); // copy just the size of process_name and leave on char fo \0
                    parsed_line->process_name[sizeof(parsed_line->process_name) - 1] = '\0'; // add null terminator
                    break;
                case 1:
                    if (strlen(value) > 20) {
                        fprintf(stderr, "ERROR ON: parser function process line in csv '%s' \nhas exceded 20 caracter in user_id\n", line);
                        free(parsed_line->process_name);
                        free(parsed_line);
                        exit(1);
                    }
                    strncpy(parsed_line->user_id, value, sizeof(parsed_line->process_name) - 1); // copy just the size of process_name 
                    parsed_line->user_id[sizeof(parsed_line->user_id) - 1] = '\0'; // add null terminator
                    break;    
                case 2:
                    long value_to_long = strtol(value, NULL, 10);
                    // casting direct to int can make overflow o we check the limits
                    if (value_to_long > INT_MAX || value_to_long < INT_MIN) {
                        // if overflow
                        fprintf(stderr, "ERROR ON: parser function process line in csv '%s' \npriority is ouuuut of range\n", line);
                        exit(1);
                    } else {
                        value = (int)value_to_long;
                    }

                    if (value > 5 || value < 1) {
                        fprintf(stderr, "ERROR ON: parser function process line in csv '%s' \npriority out of range(1-5)\n", line);
                        free(parsed_line);
                        exit(1);
                    }
                    parsed_line->priority = value; // atoi stand for ascii to integer and located in stdlib; maybe make ours if we still have time
                    break;    
                case 3:
                    if (strlen(value) < 1 || strlen(value) > 60000) {
                        fprintf(stderr, "ERROR ON: parser function process line in csv '%s' \ninstructions error\n", line);
                        free(parsed_line->priority);
                        free(parsed_line);
                        exit(1);
                    }
                    insruction_parser_return* parsed_instructions = instruction_parser(value);
                    if (parsed_instructions == NULL || parsed_instructions->instructions == NULL) { // NULLTY CHECKS
                        fprintf(stderr, "ERROR ON: parser line function, instruction_parser has returned a NULL value\n"); 
                        free(parsed_instructions->instructions);
                        free(parsed_instructions);  // setting free a null value is safe :-)
                        exit(1);
                    }
                    parsed_line->instructions = parsed_instructions->instructions; // we assign the adress to the variable we'll return
                    parsed_line->instructions_count = parsed_instructions->count; // here we define the count to check later from csv 
                    break;
                case 4:
                    long ins_cnt_lng = strtol(value, NULL, 10);
                    if (ins_cnt_lng > INT_MAX || ins_cnt_lng < INT_MIN) {
                        // if overflow case
                        fprintf(stderr, "ERROR ON: parser function process line in csv '%s' \ninstructions are out of range\n", line);
                        exit(1);
                    } else {
                        value = (int)ins_cnt_lng;
                    }

                    if (value == 0) {
                        fprintf(stderr, "ERROR ON: the parser function the instructions_count specified is invalid\n");
                        exit(1);
                    }
                    if (parsed_line->instructions_count != instructions_count) { // we check if the parsed ressource count are correct actualy this add a layer of validating
                        fprintf(stderr, "ERROR ON: the parser function the instructions_count specified in csv :%d doesn't equal to the counted by parser: %d\n", instructions_count, parsed_line->count);
                        for (int i = 0; i < parsed_line->instructions_count; i++) {
                            free(parsed_line->instructions[i]);
                        } 
                        free(parsed_line->instructions);
                        free(parsed_line);
                        exit(1);
                    }
                    break;
                case 5:
                    long memoire_lng = strtol(value, NULL, 10); // 10 for base deciaml
                    if (memoire_lng > INT_MAX || memoire_lng < INT_MIN) {
                        // if overflow case
                        fprintf(stderr, "ERROR ON: parser function process line in csv '%s' \ninstructions are out of range\n", line);
                        exit(1);
                    } else {
                        value = (int)memoire_lng;
                    }
                    if (value == 0) {
                        fprintf(stderr, "ERROR ON: the parser function the memoire specified is invalid\n");
                        for (int i = 0; i < parsed_line->instructions_count; i++) {
                            free(parsed_line->instructions[i]);
                        }
                        free(parsed_line->instructions);
                        free(parsed_line);
                        exit(1);
                    }
                    parsed_line->memoire = value;
                    break;
                case 6:
                    float burst = strtof(value, NULL);
                    if (burst == NULL) {
                        fprintf(stderr, "ERROR ON: the parser function the BURST specified is invalid\n");
                        for (int i = 0; i < parsed_line->instructions_count; i++) {
                            free(parsed_line->instructions[i]);
                        }
                        free(parsed_line->instructions);
                        free(parsed_line);
                        exit(1);
                    }
                    parsed_line->unvalid_process_csv_check = false;
                    parsed_line->burst = burst;
                    break;
                default:
                    for (int i = 0; i < parsed_line->instructions_count; i++) {
                        free(parsed_line->instructions[i]);
                    }
                    free(parsed_line->instructions);
                    free(parsed_line);
                    fprintf(stderr, "ERROR ON: the parser function the value_number has exceded the number of columns in csv file (protocol: 7) current:%d\n", value_number);
                    exit(1);
            }
            char_count = 0;
            value_number++;
            if (value_number < 7) {
                fprintf(stderr, "ERROR ON: parser function fields excedded in line %s", line);
                exit(1);
            }
            memset(value, 0, sizeof(value)); // setting all the bytes in memory will make it equivalent to empty string

            if (value_number > 6) {
                fprintf(stderr, "ERROR ON: parser function (csv file data unvalid)", line);
                exit(1);
            }
        } else if (line[i] == '\n') {
            if (value_number < 7) {
                fprintf(stderr, "ERROR ON: parser function not all the seven fields are present in line %s", line);
                exit(1);
            }
            break;
        } else {
            fprintf(stderr, "ERROR ON: parser function on line %s\nunknwon error", line);
            exit(1);
        }
    }
    return parsed_line;
}

insruction_parser_return* instruction_parser(char* value) { // retrieve instruction name .. value is the instructions line
    if (value[0] == '\0' || value[0] != '[') { // we already checked NULLTY, check string hadi jsp ida kan khawi to make sure and check instruction line satts with '['
        fprintf(stderr, "ERROR ON: instruction parser check the validity of instruction line\n");
        exit(1);
    }
    insruction_parser_return* returned = (insruction_parser_return*)malloc(sizeof(insruction_parser_return));
    if (returned == NULL) {
        fprintf(stderr, "ERROR ON: instruction_parser function, dynamic allocation returned failed\n");
        exit(1);
    }

    returned->instructions = (char**)malloc(20000 * sizeof(char*)); // 20000 instruction each instruction is a pointer to a string and has exactly 3caracters
    if (returned->instructions == NULL) {
        free(returned); // leakmemory eskive
        fprintf(stderr, "ERROR ON: instruction_parser function, dynamic allocation returned->instructions failed\n");
        exit(1);
    }

    returned->count = 0;
    char instruction[4] = {0}; // initializing it to prevent random value

    int instruction_char_count = 0;
    for (int i = 1; i < 60001; i++) {// instructions_count // initializing i to 1 bach na9zo hadak '['
        if (value[i] != ',' && instruction_char_count < 3) { // if value is a ressource character and we didnt arrive to the end which is 3characters
            instruction[instruction_char_count] = value[i]; // character at instruction retriving variable = fgets or instructions line char
            instruction_char_count++;
        } else if (value[i] == ',' && instruction_char_count == 3) { // if tge char in instructions line is comma and instruction_char_count is 3 mean that valid instruction variable so we have a ressource
            if (instruction_char_count != 3) { // ressource is more than 3 characters
                // "concurrence bagha la vendetta"
                fprintf(stderr, "ERROR ON: instruction_parser failed at line %s\nan instruction %s with length %d is more than allowed", value, instruction, instruction_char_count);
                free(returned->instructions); // liberer memoire
                free(returned); // liberer memoire
                exit(1);
            }
            returned->instructions[returned->count] = malloc(4 * sizeof(char));// chwiiiiiiiya 3la lbufferoverflow, 3 + \0 null terminator
            if (returned->instructions[returned->count] == NULL) {
                fprintf(stderr, "ERROR ON: instruction_parser failed allocating the instruction\n");
                free(returned->instructions);
                free(returned);
                exit(1);
            }
            instruction[3] = '\0';
            strcpy(returned->instructions[returned->count], instruction); // copy the string to the allocated instruction but if the instruction is not ended with \0 strcpy will copy more exceeding the buffer
            returned->instructions[returned->count][3] = '\0';
            returned->count++;
            instruction_char_count = 0;
            instruction[0] = "\0"; // clearing the array
        } else if (value[i] == ']') { // didnt merge it with previous if for time, like ida zedt wahed l if (value[i] == '[')  ghayexecuteha bzf which is bad
            if (instruction_char_count != 3) { // ressource is more than 3 characters
                // "concurrence bagha la vendetta"
                fprintf(stderr, "ERROR ON: instruction_parser failed at line %s\nan instruction %s with length %d is more than allowed", value, instruction, instruction_char_count);
                free(returned->instructions); // liberer memoire
                free(returned); // liberer memoire
                exit(1);
            }
            returned->instructions[returned->count] = malloc(4 * sizeof(char));// chwiiiiiiiya 3la lbufferoverflow, 3 + \0 null terminator
            if (returned->instructions[returned->count] == NULL) {
                fprintf(stderr, "ERROR ON: instruction_parser failed allocating the instruction\n");
                free(returned->instructions);
                free(returned);
                exit(1);
            }
            instruction[3] = '\0';
            strcpy(returned->instructions[returned->count], instruction); // copy the string to the allocated instruction
            returned->count++;
            break; // instead of setting char count to 0 break the loop and return the parsed instructions
        } else if (i == 60000) { // that why we make 20001 in the condition
            fprintf(stderr, "ERROR ON: instruction_parser the ] ending instruction never found\n");
            free(returned->instructions);
            free(returned);
            exit(1);
        } else {
            fprintf(stderr, "ERROR ON: instruction_parser function process line in csv \n '%s' unvalid instruction with unknwon error\n", value);
            // free the instructions then the list then returned
            for (int i = 0; i < returned->count; i++) {
                free(returned->instructions[i]);
            }
            free(returned->instructions);
            free(returned);
            exit(1);
        }
    }
    return returned;
}