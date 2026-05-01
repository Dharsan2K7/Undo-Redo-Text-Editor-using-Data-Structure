#include <iostream>
#include <stack>
#include <string>
#include <fstream>
#include <limits>

using namespace std;

class TextEditor {
private:
    string document;
    stack<char> undoStk;
    stack<char> redoStk;

public:
    // Append full text
    void append(const string& text) {
        for (char c : text) {
            document += c;
            undoStk.push(c);
        }

        // Clear redo stack after new input
        while (!redoStk.empty()) {
            redoStk.pop();
        }

        cout << "Appended: " << text << endl;
    }

    // Undo last character
    void undo() {
        if (document.empty()) {
            cout << "Nothing to undo!" << endl;
            return;
        }

        char last = document.back();
        document.pop_back();

        undoStk.pop();
        redoStk.push(last);

        cout << "Undo successful." << endl;
    }

    // Redo last undone character
    void redo() {
        if (redoStk.empty()) {
            cout << "Nothing to redo!" << endl;
            return;
        }

        char ch = redoStk.top();
        redoStk.pop();

        document += ch;
        undoStk.push(ch);

        cout << "Redo successful." << endl;
    }

    // Display document
    void display() const {
        cout << "Current Document: " << document << endl;
    }

    // Save file
    void saveToFile(const string& filename) {
        ofstream out(filename);

        if (out) {
            out << document;
            cout << "Saved to " << filename << endl;
        } else {
            cout << "Error saving file!" << endl;
        }
    }

    // Load file
    void loadFromFile(const string& filename) {
        ifstream in(filename);

        if (in) {
            document.clear();
            getline(in, document, '\0');

            while (!undoStk.empty()) undoStk.pop();
            while (!redoStk.empty()) redoStk.pop();

            for (char c : document)
                undoStk.push(c);

            cout << "Loaded from " << filename << endl;
        } else {
            cout << "File not found!" << endl;
        }
    }
};

int main() {
    TextEditor editor;
    int choice;
    string input;

    do {
        cout << "\n--- Undo-Redo Text Editor ---\n";
        cout << "1. Append Text\n";
        cout << "2. Undo\n";
        cout << "3. Redo\n";
        cout << "4. Display\n";
        cout << "5. Save\n";
        cout << "6. Load\n";
        cout << "7. Exit\n";
        cout << "Choice: ";

        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                cout << "Enter text to append: ";
                getline(cin, input);
                editor.append(input);
                break;

            case 2:
                editor.undo();
                break;

            case 3:
                editor.redo();
                break;

            case 4:
                editor.display();
                break;

            case 5:
                editor.saveToFile("document.txt");
                break;

            case 6:
                editor.loadFromFile("document.txt");
                break;

            case 7:
                cout << "Exiting...\n";
                break;

            default:
                cout << "Invalid choice!\n";
        }

    } while (choice != 7);

    return 0;
}