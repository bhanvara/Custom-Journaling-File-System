#include "task.h"
#include <iostream>
#include <unistd.h>
#include <cstdlib>

#define SIMULATE_CRASH 1

void performTask(FileSystem &fs) {
    std::cout << "Starting task execution...\n";
    
    if(SIMULATE_CRASH) {
        // Log beginning of operation without committing
        fs.writeMetadataIncomplete("Task: Begin file operation");
        sleep(1); // Simulate processing delay
        fs.writeMetadata("Task: Begin file operation");
        sleep(1); // Simulate processing delay
        std::cout << "Simulating crash now...\n";
        exit(1);
    } else {
        fs.writeData("Task: Write file block for task operation");
        sleep(1); // Simulate processing delay
        fs.writeMetadata("Task: End file operation");
        std::cout << "Task completed.\n";
    }
}
