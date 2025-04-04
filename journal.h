#ifndef JOURNAL_H
#define JOURNAL_H

#include <string>
#include <vector>

enum JournalEntryType {
    METADATA,
    DATA,
    COMMIT
};

struct JournalEntry {
    JournalEntryType type;
    uint64_t transactionId;
    std::string payload; // could represent serialized changes
};

class Journal {
public:
    Journal(const std::string &journalFile);
    void init();
    void logEntry(const JournalEntry &entry);
    void commit(uint64_t transactionId);
    std::vector<JournalEntry> recover();
private:
    std::string journalFilePath;
    // ...existing code...
};

#endif // JOURNAL_H
