#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include "journal.h"
#include <string>

class FileSystem {
public:
    FileSystem(const std::string &diskFile, const std::string &journalFile);
    void init();
    void writeMetadata(const std::string &metadata);
    void writeData(const std::string &data);
    // New methods for incomplete writes (no commit)
    void writeMetadataIncomplete(const std::string &metadata);
    void writeDataIncomplete(const std::string &data);
    void recover();
private:
    std::string diskFilePath;
    Journal journal;
    uint64_t currentTransaction;
};

#endif // FILESYSTEM_H
