#include "journal.h"
#include <iostream>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <sstream>

struct TransactionStatus {
    bool committed = false;
    std::vector<JournalEntry> entries;
};

// Helper function to check if disk already has the expected line.
bool diskHasEntry(const std::string &diskImg, const std::string &expectedLine) {
    std::ifstream ifs(diskImg);
    std::string line;
    while (getline(ifs, line)) {
        if (line.find(expectedLine) != std::string::npos)
            return true;
    }
    return false;
}

void recoverFileSystem(const std::string &journalFile) {
    Journal journal(journalFile);
    auto entries = journal.recover();

    const std::string diskImg = "disk.img"; // disk image filepath

    std::unordered_map<uint64_t, TransactionStatus> transactions;

    // Group entries by transaction ID and determine their commit status.
    for (const auto &entry : entries) {
        transactions[entry.transactionId].entries.push_back(entry);
        if (entry.type == COMMIT) {
            transactions[entry.transactionId].committed = true;
        }
    }

    // Process each transaction.
    for (const auto &tx : transactions) {
        uint64_t txId = tx.first;
        const auto &status = tx.second;
        if (!status.committed) {
            std::cout << "Recovering incomplete transaction: " << txId << "\n";
            bool diskUpdated = true; // assume disk is updated unless missing an expected entry.
            // Check and replay entries: if an expected entry is missing, reapply it.
            for (const auto &entry : status.entries) {
                if (entry.type == COMMIT) continue; // skip commit entries.
                std::stringstream expected;
                if (entry.type == METADATA)
                    expected << "TX " << txId << " Metadata: " << entry.payload;
                else if (entry.type == DATA)
                    expected << "TX " << txId << " Data: " << entry.payload;
                std::string expectedLine = expected.str();

                if (diskHasEntry(diskImg, expectedLine)) {
                    std::cout << "Disk already has entry: " << expectedLine << "\n";
                } else {
                    diskUpdated = false;
                    std::cout << "Replaying missing entry: " << expectedLine << "\n";
                    std::ofstream ofs(diskImg, std::ofstream::app);
                    if (!ofs.is_open()) {
                        std::cerr << "Error accessing disk image: " << diskImg << "\n";
                        diskUpdated = false;
                        break;
                    }
                    ofs << expectedLine << "\n";
                    ofs.flush();
                    ofs.close();
                }
            }
            if (diskUpdated) {
                std::cout << "All entries for transaction " << txId << " already present on disk.\n";
            }
            // Mark the transaction as complete regardless.
            journal.commit(txId);
            std::cout << "Transaction " << txId << " recovered and marked as committed.\n";
        } else {
            std::cout << "Transaction " << txId << " is complete.\n";
        }
    }

    std::cout << "Recovery complete.\n";
}
