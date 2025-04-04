#include "filesystem.h"
#include "task.h"
#include <iostream>
#include <unistd.h>
#include <string>

// Declaration of the recovery function.
void recoverFileSystem(const std::string &journalFile);

int main(int argc, char* argv[]) {
    // If the user passes "recover" as the first argument, run the recovery routine and exit.
    if (argc > 1 && std::string(argv[1]) == "recover") {
        recoverFileSystem("journal.log");
        return 0;
    }

    FileSystem fs("disk.img", "journal.log");
    fs.init();

    // Execute task wrapped by main.
    performTask(fs);

    std::cout << "Operations completed successfully!\n";

    return 0;
}
