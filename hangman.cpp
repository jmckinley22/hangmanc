#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;


vector<string> readWords(const string& filename) {
    vector<string> words;
    ifstream file(filename.c_str());
    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        exit(1);
    }

    string word;
    while (file >> word) {
        words.push_back(word);
    }
    file.close();
    return words;
}

string chooseWord(const vector<string>& words) {
    srand(time(0));
    int i = rand() % words.size();
    return words[i];
}

void showWord(const string& word, const vector<char>& guessed) {
    for (int i = 0; i < word.length(); i++) {
        if (find(guessed.begin(), guessed.end(), word[i]) != guessed.end()) {
            cout << word[i] << " ";
        } else {
            cout << "_ ";
        }
    }
    cout << endl;
}

bool won(const string& word, const vector<char>& guessed) {
    for (int i = 0; i < word.length(); i++) {
        if (find(guessed.begin(), guessed.end(), word[i]) == guessed.end()) {
            return false; // A letter is missing
        }
    }
    return true;
}

int main() {
    string filename = "hangman_word_list.txt";

    vector<string> words = readWords(filename);
    if (words.empty()) {
        cerr << "Error: No words found in file " << filename << endl;
        return 1;
    }

    string word = chooseWord(words);
    vector<char> guessed;
    int maxAttempts = 6;
    int attemptsLeft = maxAttempts;
    char guess;

    cout << "!xxx__Hangman__xxx!" << endl;

    while (attemptsLeft > 0) {
        cout << "word: ";
        showWord(word, guessed);
        cout << "tries left: " << attemptsLeft << endl;

        cout << "guess: ";
        cin >> guess;

        if (find(guessed.begin(), guessed.end(), guess) != guessed.end()) {
            cout << "already did that" << endl;
            continue;
        }

        guessed.push_back(guess);

        if (word.find(guess) != string::npos) {
            cout << "Good guess!" << endl;
        } else {
            cout << "Wrong guess!" << endl;
            attemptsLeft--;
        }

        // Check win condition
        if (won(word, guessed)) {
            cout << "you got it: " << word << endl;
            break;
        }
    }

    if (attemptsLeft == 0) {
        cout << "wrong, it was:  " << word << endl;
    }

    return 0;
}
