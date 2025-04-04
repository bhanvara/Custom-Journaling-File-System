#include "journal.h"
#include <fstream>
#include <iostream>

Journal::Journal(const std::string &journalFile)
    : journalFilePath(journalFile) {
    // ...existing code...
}

void Journal::init() {
    // For simplicity, clear the journal file on startup
    std::ofstream ofs(journalFilePath, std::ofstream::trunc);
    ofs.close();
}

void Journal::logEntry(const JournalEntry &entry) {
    std::ofstream ofs(journalFilePath, std::ofstream::app);
    // Serialize entry as type, transactionId, payload
    ofs << entry.type << " " << entry.transactionId << " " << entry.payload << "\n";
    ofs.flush(); // ensure the entry is written immediately
    ofs.close();
}

void Journal::commit(uint64_t transactionId) {
    JournalEntry commitEntry {COMMIT, transactionId, "commit"};
    logEntry(commitEntry);
}

std::vector<JournalEntry> Journal::recover() {
    std::vector<JournalEntry> entries;
    std::ifstream ifs(journalFilePath);
    if (!ifs.is_open()) return entries;
    uint32_t type;
    uint64_t transactionId;
    std::string payload;
    while (ifs >> type >> transactionId) {
        std::getline(ifs, payload);
        JournalEntry entry { static_cast<JournalEntryType>(type), transactionId, payload.substr(1) }; // remove leading space
        entries.push_back(entry);
    }
    ifs.close();
    return entries;
}
