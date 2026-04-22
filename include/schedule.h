#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <iostream>
#include <string>
#include "common.h"
class TaskScheduler {
private:
    Task* head; 
public:
    TaskScheduler();
    void addTask(int priority, std::string msg);
    void run();
};

#endif
