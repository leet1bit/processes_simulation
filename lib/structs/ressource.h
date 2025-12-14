#pragma once


typedef enum {
    MEMORY, SOCKET, FILE, CPU, DEVICE_A, DEVICE_B, DEVICE_C
} RESSOURCE;

typedef struct {
    char* ressource_name[10]; // nom de ressource
    RESSOURCE* ressource; // type 
    bool disponibilite; // dispo ou non 1 / 0
} RESSOURCE_ELEMENT;