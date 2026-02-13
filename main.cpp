#include "Keeper.h"
#include <fstream>
#include <sstream>
#include <cctype>
#include <cstdlib>

using namespace std;

bool isSentenceDelimiter(char c) {
    return c == '.' || c == '!' || c == '?';
}

int countWords(const string& sentence) {
    int wordCount = 0;
    bool inWord = false;

    for (size_t i = 0; i < sentence.length(); i++) {
        char c = sentence[i];
        if (isspace(c)) {
            inWord = false;
        } else if (!inWord && !isSentenceDelimiter(c) && c != ',' && c != ';' && c != ':') {
            inWord = true;
            wordCount++;
        }
    }

    return wordCount;
}

void processTextFile() {
    string filename;
    cout << "Enter input filename: ";
    cin >> filename;

    ifstream file;
    file.open(filename.c_str());

    if (!file.is_open()) {
        cout << "Error opening file " << filename << endl;
        return;
    }

    int targetWordCount;
    cout << "Enter the number of words for sentences to display: ";
    cin >> targetWordCount;

    cout << "\nSentences with " << targetWordCount << " words:" << endl;
    cout << "==================================================" << endl;

    string content;
    string line;
    bool found = false;

    // Читаем весь файл
    while (getline(file, line)) {
        content += line + " ";
    }
    file.close();

    cout << "File content read: " << content << endl;
    cout << "==================================================" << endl;

    string currentSentence;
    for (size_t i = 0; i < content.length(); i++) {
        char c = content[i];
        currentSentence += c;

        if (isSentenceDelimiter(c)) {
            // Убираем лишние пробелы в начале и конце
            size_t start = currentSentence.find_first_not_of(" \t\n");
            size_t end = currentSentence.find_last_not_of(" \t\n");

            if (start != string::npos && end != string::npos) {
                string sentence = currentSentence.substr(start, end - start + 1);

                int words = countWords(sentence);
                cout << "DEBUG: Sentence \"" << sentence << "\" has " << words << " words" << endl;

                if (words == targetWordCount) {
                    cout << "FOUND: " << sentence << endl;
                    cout << "------------------------------" << endl;
                    found = true;
                }
            }

            currentSentence.clear();
        }
    }

    if (!found) {
        cout << "No sentences with " << targetWordCount << " words found." << endl;
    }
}

void createTestFile() {
    string testFilename = "test_text.txt";
    ofstream out;
    out.open(testFilename.c_str());

    if (out.is_open()) {
        out << "Hello world. This is a test sentence. ";
        out << "C++ programming is fun! How are you today? ";
        out << "File streams are useful. This sentence has five words here. ";
        out << "Short one. Another test with seven words in this sentence. ";
        out << "End of file example!";
        out.close();
        cout << "Test file '" << testFilename << "' created." << endl;

        // Показываем содержимое файла
        cout << "\nFile content:" << endl;
        cout << "==================================================" << endl;
        ifstream in;
        in.open(testFilename.c_str());
        string line;
        while (getline(in, line)) {
            cout << line << endl;
        }
        in.close();
        cout << "==================================================" << endl;
    } else {
        cout << "Error creating test file!" << endl;
    }
}

int main() {
    Keeper keeper;
    string filename = "trains.txt";
    int choice;

    do {
        cout << "\n=========================================" << endl;
        cout << "        TRAIN MANAGEMENT SYSTEM" << endl;
        cout << "=========================================" << endl;
        cout << "1. Add train" << endl;
        cout << "2. Remove train" << endl;
        cout << "3. Edit train" << endl;
        cout << "4. Show all trains" << endl;
        cout << "5. Find train by number" << endl;
        cout << "6. Save to file" << endl;
        cout << "7. Load from file" << endl;
        cout << "8. Process text file (sentences by word count)" << endl;
        cout << "9. Create test text file" << endl;
        cout << "0. Exit" << endl;
        cout << "=========================================" << endl;
        cout << "Your choice: ";
        cin >> choice;

        switch(choice) {
            case 1: {
                keeper.addTrainFromInput();
                break;
            }
            case 2: {
                if (keeper.isEmpty()) {
                    cout << "No trains to remove!" << endl;
                } else {
                    keeper.printAll();
                    string num;
                    cout << "Enter train number to remove: ";
                    cin >> num;
                    if (keeper.removeTrain(num)) {
                        cout << "Train removed successfully!" << endl;
                    } else {
                        cout << "Train not found!" << endl;
                    }
                }
                break;
            }
            case 3: {
                if (keeper.isEmpty()) {
                    cout << "No trains to edit!" << endl;
                } else {
                    string num;
                    cout << "Enter train number to edit: ";
                    cin >> num;
                    if (!keeper.editTrain(num)) {
                        cout << "Train not found!" << endl;
                    }
                }
                break;
            }
            case 4: {
                keeper.printAll();
                break;
            }
            case 5: {
                if (keeper.isEmpty()) {
                    cout << "No trains in the system!" << endl;
                } else {
                    string num;
                    cout << "Enter train number to find: ";
                    cin >> num;
                    keeper.printTrainByNumber(num);
                }
                break;
            }
            case 6: {
                keeper.saveToFile(filename);
                break;
            }
            case 7: {
                keeper.loadFromFile(filename);
                break;
            }
            case 8: {
                processTextFile();
                break;
            }
            case 9: {
                createTestFile();
                break;
            }
            case 0: {
                cout << "Program finished!" << endl;
                break;
            }
            default: {
                cout << "Invalid choice! Try again." << endl;
            }
        }

        if (choice != 0) {
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
        }

    } while (choice != 0);

    return 0;
}
