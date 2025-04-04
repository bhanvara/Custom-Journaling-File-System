#include "filesystem.h"
#include <fstream>
#include <iostream>

FileSystem::FileSystem(const std::string &diskFile, const std::string &journalFile)
    : diskFilePath(diskFile), journal(journalFile), currentTransaction(0) {
    // ...existing code...
}

void FileSystem::init() {
    // Initialize the disk file and journal
    journal.init();
    // ...initialize disk file if needed...
}

void FileSystem::writeMetadata(const std::string &metadata) {
    currentTransaction++;
    // Write-ahead log for metadata update
    JournalEntry entry { METADATA, currentTransaction, metadata };
    journal.logEntry(entry);
    
    // Now write metadata to disk (simulate by appending to file)
    std::ofstream ofs(diskFilePath, std::ofstream::app);
    ofs << "Metadata: " << metadata << "\n";
    ofs.close();

    // Commit the transaction in journal
    journal.commit(currentTransaction);
}

void FileSystem::writeMetadataIncomplete(const std::string &metadata) {
    currentTransaction++;
    JournalEntry entry { METADATA, currentTransaction, metadata };
    journal.logEntry(entry);
    std::ofstream ofs(diskFilePath, std::ofstream::app);
    ofs << "Metadata: " << metadata << "\n";
    ofs.close();
    // No commit is performed
}

void FileSystem::writeData(const std::string &data) {
    currentTransaction++;
    // Write-ahead log for data update
    JournalEntry entry { DATA, currentTransaction, data };
    journal.logEntry(entry);
    
    // Now write data to disk (simulate by appending to file)
    std::ofstream ofs(diskFilePath, std::ofstream::app);
    ofs << "Data: " << data << "\n";
    ofs.close();

    // Commit the transaction in journal
    journal.commit(currentTransaction);
}

void FileSystem::writeDataIncomplete(const std::string &data) {
    currentTransaction++;
    JournalEntry entry { DATA, currentTransaction, data };
    journal.logEntry(entry);
    std::ofstream ofs(diskFilePath, std::ofstream::app);
    ofs << "Data: " << data << "\n";
    ofs.close();
    // No commit is performed
}

void FileSystem::recover() {
    std::cout << "Starting recovery...\n";
    auto entries = journal.recover();
    // Simple recovery: iterate over entries and roll back if commit is missing
    // Here, using a simplified approach
    // ...existing recovery logic...
    std::cout << "Recovery complete.\n";
}
