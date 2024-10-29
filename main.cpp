#include <cmath>
#include <iostream>
#include <algorithm>
using namespace std;

class HashTable {
    static const int PRIME_CONST = 31;
    static const int ARR_SIZE = 3001;
    pair<string,string> table[ARR_SIZE];

    public:
        HashTable() {
          for (auto entry: table) {
            entry.first = "";
            entry.second = "";
          }
        }

        void put(string key, string value) {
            int index = hashFunc(key);
            table[index].first = key;
            table[index].second = value;
        }

        string get(string key) {
          int index = hashFunc(key);
          pair<string,string>  result = table[index];
          if (key == result.first) {
            return result.second;
          } else if (result.first.length() < 1) {
            return "";
          } else {
            cout << "collision: ";
            cout << result.first << "=>" << result.second << endl;
            return "";
          }
          return "";
        }

        static int hashFunc(string key) {
            size_t sum;
            for (int i = 0; i < key.length(); i++) {
                sum += (key[i] * (int)pow(PRIME_CONST, i)) % ARR_SIZE;
            }
            return sum % ARR_SIZE;
        }

        void printAll() {
            for (auto entry: table) {
                if (entry.first.length() > 0) {
                    cout << entry.first << "=>" << entry.second << endl;
                  
                }
            }
            cout << endl;
        }
};

int main() {
    HashTable hTable;
    string cmd,key,value;
    cout << "1. Add, 2. Lookup, 3. List, 4. Exit: ";
    getline(cin,cmd);
    while (cmd != "4") {
      if (cmd == "1") {
        cout << "Enter key:";
        getline(cin,key);
        cout << "Enter Value:";
        getline(cin,value);
        hTable.put(key, value);
        
      } else if (cmd == "2") {
        cout << "Enter key to find: ";
        getline(cin,key);
        value = hTable.get(key);
        if (value.length() > 0) {
          cout << key << " => " << value << endl; 
        } else {
          cout << "Not found" << endl;
        }

      } else if (cmd == "3") {
        hTable.printAll();
      
      } else {
        cout << "What?";
      }
      cout << "1. Add, 2. Lookup, 3. List, 4. Exit: ";
      getline(cin,cmd);     
    }
    return 0;
}
