# Custom Journaling File System

## Overview
This project implements a custom journaling file system with features such as:
- Write-Ahead Logging
- Metadata and Data Journals
- Crash Recovery

## Features
- Transactional design to ensure file system consistency.
- Simple disk layout simulation.
- Recovery mechanism to replay incomplete transactions.

## Files
- `journal.h` / `journal.cpp`: Defines and implements the journaling mechanism.
- `filesystem.h` / `filesystem.cpp`: Provides file system operations using write-ahead logging.
- `recovery.h` / `recovery.cpp`: Implements crash recovery routines.
- `task.h` / `task.cpp`: Defines tasks for file system operations.
- `main.cpp`: Entry point that ties all components together.

## Building
Compile the project with a C++ compiler. For example:
```
g++ -std=c++11 -o fs main.cpp journal.cpp filesystem.cpp recovery.cpp task.cpp
```

## Running
Run the compiled executable:
```
./fs
```

## Testing Recovery
To test crash recovery:
1. Run the executable normally to see complete operations.
2. To simulate a crash, you can either set the environment variable manually:
   ```
   export SIMULATE_CRASH=1
   ./fs
   ```
   or use the provided script:
   ```
   chmod +x run.sh
   ./run.sh
   ```
   After the simulated crash, restart the program (without SIMULATE_CRASH, e.g., by running `./fs`) to trigger the recovery routine.
