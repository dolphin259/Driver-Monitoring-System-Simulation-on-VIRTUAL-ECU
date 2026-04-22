#ifndef common_h
#define common_h

#include <iostream>
#include <vector>
#include <map>
#include <stdint.h>

typedef uint32_t Register;

extern Register*** ECU_Memory;
struct Task {
    int priority;
    std::string message;
    Task* next;
    Task(int p, std::string m) : priority(p), message(m), next(nullptr) {}
};

#endif
