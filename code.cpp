#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// Trie Node Definition
class TrieNode {
public:
    bool isEnd;
    TrieNode* children[26];
    TrieNode() {
        isEnd = false;
        fill(begin(children), end(children), nullptr);
    }
};

// Trie Class
class Trie {
private:
    TrieNode* root;

    void dfs(TrieNode* node, string prefix, vector<string>& results) {
        if (node->isEnd) {
            results.push_back(prefix);
        }
        for (int i = 0; i < 26; ++i) {
            if (node->children[i]) {
                dfs(node->children[i], prefix + char('a' + i), results);
            }
        }
    }

public:
    Trie() {
        root = new TrieNode();
    }

    void insert(string word) {
        TrieNode* node = root;
        for (char ch : word) {
            if (!node->children[ch - 'a']) {
                node->children[ch - 'a'] = new TrieNode();
            }
            node = node->children[ch - 'a'];
        }
        node->isEnd = true;
    }

    vector<string> searchPrefix(string prefix) {
        TrieNode* node = root;
        for (char ch : prefix) {
            if (!node->children[ch - 'a']) {
                return {};
            }
            node = node->children[ch - 'a'];
        }

        vector<string> results;
        dfs(node, prefix, results);
        return results;
    }
};

// Event Class
class Event {
    string title;
    string desc;
    string date; // yyy-mm-dd
    bool isCompleted;

public:
    Event(string title, string desc, string date) {
        this->title = title;
        this->desc = desc;
        this->date = date;
        this->isCompleted = false;
    }

    string getTitle() { return title; }
    string getDesc() { return desc; }
    string getDate() { return date; }
    bool status() { return isCompleted; }

    void changeStatus() {
        isCompleted = !isCompleted;
    }
};

// Manager Class
class reminderManager {
    vector<Event> list;
    Trie trie;

public:
    void addEvent(Event e) {
        list.push_back(e);
        string t = e.getTitle();
        transform(t.begin(), t.end(), t.begin(), ::tolower);
        trie.insert(t);
    }

    void viewEvent() {
        if (list.empty()) {
            cout << "No events available.\n";
            return;
        }
        for (int i = 0; i < list.size(); i++) {
            cout << i + 1 << ". " << list[i].getTitle() << "\n";
            cout << "   Description: " << list[i].getDesc() << "\n";
            cout << "   Date: " << list[i].getDate() << "\n";
            cout << "   Status: " << (list[i].status() ? "Completed" : "Pending") << "\n";
        }
    }

    void removeEvent(int ind) {
        if (ind <= 0 || ind > list.size()) {
            cout << "Invalid index.\n";
            return;
        }
        list.erase(list.begin() + ind - 1);
    }

    void markEventAsDone(int ind) {
        if (ind <= 0 || ind > list.size()) {
            cout << "Invalid index.\n";
            return;
        }
        list[ind - 1].changeStatus();
    }

    void viewCompletedEvents() {
        int c = 1;
        for (int i = 0; i < list.size(); i++) {
            if (list[i].status()) {
                cout << c++ << ". " << list[i].getTitle() << "\n";
                cout << "   " << list[i].getDesc() << "\n";
            }
        }
        if (c == 1) {
            cout << "No completed events.\n";
        }
    }

    void searchByPrefix(string prefix) {
        transform(prefix.begin(), prefix.end(), prefix.begin(), ::tolower);
        vector<string> results = trie.searchPrefix(prefix);
        if (results.empty()) {
            cout << "No events found with prefix '" << prefix << "'.\n";
        } else {
            cout << "Events starting with '" << prefix << "':\n";
            for (string& r : results) {
                cout << "- " << r << "\n";
            }
        }
    }
};

// Main function
int main() {
    reminderManager rm;

    while (true) {
        cout << "\n*** Event Reminder System ***\n";
        cout << "1. Add Event\n";
        cout << "2. View Events\n";
        cout << "3. Remove Event\n";
        cout << "4. Mark Event as Done\n";
        cout << "5. View Completed Events\n";
        cout << "6. Search Event by Prefix\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";

        int ch;
        cin >> ch;

        switch (ch) {
            case 1: {
                string title, desc, date;
                cout << "Enter title: ";
                cin.ignore();
                getline(cin, title);
                cout << "Enter description: ";
                getline(cin, desc);
                cout << "Enter date (yyyy-mm-dd): ";
                cin >> date;
                rm.addEvent(Event(title, desc, date));
                break;
            }

            case 2:
                rm.viewEvent();
                break;

            case 3: {
                rm.viewEvent();
                int ind;
                cout << "Enter index to remove: ";
                cin >> ind;
                rm.removeEvent(ind);
                break;
            }

            case 4: {
                rm.viewEvent();
                int ind;
                cout << "Enter index to mark as done: ";
                cin >> ind;
                rm.markEventAsDone(ind);
                break;
            }

            case 5:
                rm.viewCompletedEvents();
                break;

            case 6: {
                string prefix;
                cout << "Enter prefix to search: ";
                cin >> prefix;
                rm.searchByPrefix(prefix);
                break;
            }

            case 7:
                cout << "Exiting program.\n";
                return 0;

            default:
                cout << "Invalid option. Try again.\n";
        }
    }

    return 0;
}
