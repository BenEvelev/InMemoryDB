#include <iostream>
#include <unordered_map>
#include <vector>
#include <stdexcept>

using namespace std;
class InMemoryDB {
private:
    unordered_map<std::string, int> state;
    unordered_map<std::string, int> currentState;
    bool inTransaction;

public:
    InMemoryDB() : inTransaction(false) {}

    int get(const std::string& key) {
        if (inTransaction && currentState.find(key) != currentState.end()) {
            return currentState[key];
        }
        else if (state.find(key) != state.end()) {
            return state[key];
        }
        else {
            // -1 represents null, due to C++'s lack of null
            return -1;
        }
    }

    void put(const std::string& key, int val) {
        // if transaction is not in progress, throws error
        if (!inTransaction) {
            throw std::runtime_error("Transaction not in progress");
        }
        // either creates new key and value, or replaces the keys value
        currentState[key] = val;
    }

    void begin_transaction() {
        // if the transaction is already happening, throws error
        if (inTransaction) {
            throw std::runtime_error("Transaction already in progress");
        }
        //otherwise sets transaction to true
        inTransaction = true;
    }

    void commit() {
        // if transaction is not going on, throws error
        if (!inTransaction) {
            throw std::runtime_error("No open transaction");
        }

        // else apply changes made within the transaction to the main state
        state.insert(currentState.begin(), currentState.end());

        // clears the transaction state to set up for a new one
        currentState.clear();
        // finalizes that transaction is over
        inTransaction = false;
    }

    void rollback() {
        // throws error if transaction is not going on
        if (!inTransaction) {
            throw std::runtime_error("No current transaction");
        }

        // rollback any changes made within the transaction
        currentState.clear();

        inTransaction = false;
    }
};

int main() {
    InMemoryDB inmemoryDB;



    return 0;
}

