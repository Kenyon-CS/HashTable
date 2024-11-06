#include <iostream>
#include <string>
#include <utility>
using namespace std;

class HashTable {
    static const int PRIME_CONST = 31;
    static const int ARR_SIZE = 3001;
    pair<string, string> table[ARR_SIZE];

public:
    HashTable() {
        for (auto& entry : table) {
            entry = {"", ""};
        }
    }

    void put(const string& key, const string& value) {
        int index = hashFunc(key);
        if (table[index].first.empty() || table[index].first == key) {
            table[index] = {key, value};
        } else {
            // Linear probing for collision resolution
            int originalIndex = index;
            do {
                index = (index + 1) % ARR_SIZE;
            } while (!table[index].first.empty() && table[index].first != key && index != originalIndex);

            if (index == originalIndex) {
                cout << "Hash table is full!" << endl;
                return;
            }
            table[index] = {key, value};
        }
    }

    string get(const string& key) {
        int index = hashFunc(key);
        int originalIndex = index;
        while (!table[index].first.empty()) {
            if (table[index].first == key) {
                return table[index].second;
            }
            index = (index + 1) % ARR_SIZE;
            if (index == originalIndex) break;
        }
        cout << "Not found." << endl;
        return "";
    }

    static int hashFunc(const string& key) {
        long long sum = 0;
        long long power = 1;
        for (char ch : key) {
            sum = (sum + (ch * power) % ARR_SIZE) % ARR_SIZE;
            power = (power * PRIME_CONST) % ARR_SIZE;
        }
        return static_cast<int>(sum);
    }

    void printAll() const {
        for (const auto& entry : table) {
            if (!entry.first.empty()) {
                cout << entry.first << " => " << entry.second << endl;
            }
        }
        cout << endl;
    }
};

int main() {
    HashTable hTable;
    string cmd, key, value;
    cout << "1. Add, 2. Lookup, 3. List, 4. Exit: ";
    while (getline(cin, cmd) && cmd != "4") {
        if (cmd == "1") {
            cout << "Enter key: ";
            getline(cin, key);
            cout << "Enter value: ";
            getline(cin, value);
            hTable.put(key, value);
        } else if (cmd == "2") {
            cout << "Enter key to find: ";
            getline(cin, key);
            value = hTable.get(key);
            if (!value.empty()) {
                cout << key << " => " << value << endl;
            }
        } else if (cmd == "3") {
            hTable.printAll();
        } else {
            cout << "Invalid command." << endl;
        }
        cout << "1. Add, 2. Lookup, 3. List, 4. Exit: ";
    }
    return 0;
}
