#include <iostream>
#include <vector>
#include <limits>
#include <string>
#include <fstream>
#include <sstream>
#include <codecvt>
#include <unordered_map>

using namespace std;
void censorShip(){
    locale::global(locale(""));
    wifstream inFile("arabic text.txt");
    wifstream censorFile("censorFile.txt");
    inFile.imbue(locale(inFile.getloc(), new codecvt_utf8<wchar_t>));

    if (inFile.fail()) {
        cout << "Opening failed, please try again!" << endl;
    } else {
        cout << "File opened successfully!\n";
    }

    wstring arabic_text, sentence;
    censorFile.imbue(locale(censorFile.getloc(), new codecvt_utf8<wchar_t>));
    while (getline(inFile, sentence)) {
        arabic_text += sentence + L"\n";
    }
    unordered_map<wstring, wstring> censorMap;
    wstring wordKey, alter;
    while (censorFile >> wordKey >> alter) {
        censorMap[wordKey] = alter;
    }

//    for (const auto& pair : censorMap) {
//        wcout << L"Censor word: " << pair.first << L", Replace with: " << pair.second << endl;
//    }

    for (const auto& pair : censorMap) {
        size_t pos = arabic_text.find(pair.first);
        // Replace all occurrences of the censor word
        while (pos != wstring::npos) {
            arabic_text.replace(pos, pair.first.length(), pair.second);
            pos = arabic_text.find(pair.first, pos + pair.second.length());
        }
    }

    wcout.imbue(locale(""));
    wcout << L"Modified Arabic Text:\n" << arabic_text << endl;

    // Output file for the censored Arabic text
    wofstream outFile("goodArabicText.txt");
    outFile.imbue(locale(outFile.getloc(), new codecvt_utf8<wchar_t>));
//    while (!outFile.eof() && !outFile.fail()){
//        getline(outFile, text);
//        wcout << text;
//    }

    // Write the modified text to the output file
    outFile << arabic_text;
    inFile.close();
    censorFile.close();
    outFile.close();
}
void correction(){
    char c;
    string output;
    bool space = false;
    bool first_space = true;
    cout << "Enter your sentence that ends with a '.' :-\n";
    for (int i = 0; i < 100; ++i) {
        cin.get(c);
        if(c == '.'){
            // To remove the last character before space in output if it's space
            if(isspace(output.back())){
                output.pop_back();
            }
            output += c;
            break;
        }
        if(isspace(c) && first_space){
            continue;
        }
        if(isspace(c)){
            if(!space){
                output += ' ';
                space = true;
            }
        }else if(isalpha(c)){
            output += (char)tolower(c);
            space = false;
            first_space = false;
        }else{
            output += c;
            space = false;
        }
    }
    output[0] = (char)toupper(output[0]);
    cout << output << endl;
    // To discard any characters after the point and don't disturb the menu
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
void SieveOfEratosthenes(){
    int n;
    while(true){
        cout << "Enter limit of numbers:";
        cin >> n;

        if (cin.fail() || n < 0)
        {
            // Clear n input
            cin.clear();
            // Ignore n input
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Please, enter a valid number!" << endl;
            continue;
        }
        break;
    }
    // A vector initialized to false; to store primes
    vector<bool> vec(n+1, false);
    for (int i = 2; i * i <= n; ++i) {
        // Decrease looping if it's true we don't need to check on it
        if(!vec[i-2]){
            // Loops on the multiples of i
            for(int a = i * i; a <= n; a+=i){
                // If changed to true means it's a multiple of i "not prime"
                vec[a-2] = true;
            }
        }
    }
    // Print prime numbers
    cout << '(';
    bool comma = false;
    for (int i = 0; i <= n-2; ++i) {
        if(!vec[i]){
            // Print the comma before the number expect for the first time
            if(comma){
                cout << ", ";
            }
            cout << i + 2;
            comma = true;
        }
    }
    cout << ')';
    cout << endl;
}

// A structure to store the items of domino
struct dominoT {
    int leftDots;
    int rightDots;
};

// To flip a domino and try each side
dominoT flipDomino(dominoT domino) {
    return {domino.rightDots, domino.leftDots};
}

// Recursive function that compare each side of the domino with others
bool trackDomino(const vector<dominoT>& domino, vector<bool>& used, vector<dominoT>& chain, int len) {
    // when the len var reaches the size of domino vector; so the chain is successfully formed
    if (len == domino.size()) {
        return true;
    }

    // Loop on all the unused dominoes
    for (int i = 0; i < domino.size(); i++) {
        if (!used[i]) {
            // Try both sides of each domino
            for (int j = 0; j < 2; j++) {
                // when j = 0 it's in the original position, j = 1 when flipped
                dominoT sidePos = (j == 0) ? domino[i] : flipDomino(domino[i]);

                // Check if it can be placed in the chain
                if (len == 0 || chain.back().rightDots == sidePos.leftDots) {
                    // When the domino can be placed; add it to the chain and mark as used
                    used[i] = true;
                    chain.push_back(sidePos);

                    // recursion to call itself back for the next domino
                    if (trackDomino(domino, used, chain, len + 1)) {
                        // A valid chain is found
                        return true;
                    }

                    // "Backtrack" to remove the last domino from the chain and mark as unused
                    chain.pop_back();
                    used[i] = false;
                }
            }
        }
    }
    // No valid chain
    return false;
}

// The entry point function to check if a domino chain can be formed
bool FormsDominoChain(const vector<dominoT>& domino, vector<dominoT>& chain) {
    // Initialize a vector and Set its default to false
    vector<bool> used(domino.size(), false);

    for (int i = 0; i < domino.size(); ++i) {
        used[i] = true;
        chain.push_back(domino[i]);

        // Start tracking with the first domino
        if (trackDomino(domino, used, chain, 1)) {
            // A valid chain is found
            return true;
        }
        // "Backtrack" to remove the last domino from the chain and mark as unused
        chain.pop_back();
        used[i] = false;
    }
    // No valid chain is formed
    return false;
}

// Function to start the program
void start() {
    while (true) {
        int n;
        cout << "Enter the number of dominoes (more than 2):\n";
        cin >> n;

        if (cin.fail() || n <= 2) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Please, enter a valid number!" << endl;
            continue;
        }

        // A vector to add the inputs in it
        vector<dominoT> domino(n);
        cout << "Enter the left and right number of each domino (0 -> 6):\n";
        for (int i = 0; i < n; ++i) {
            cin >> domino[i].leftDots >> domino[i].rightDots;
            // Validation for the inputs of the dominoes
            if (cin.fail() || domino[i].leftDots < 0 || domino[i].leftDots > 6 || domino[i].rightDots < 0 || domino[i].rightDots > 6) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Please, enter a valid number!" << endl;
                // Return back to the correct index
                --i;
                continue;
            }
        }

        // A vector to add in it the correct chain
        vector<dominoT> chain;
        // Print the new chain if it's  valid
        if (FormsDominoChain(domino, chain)) {
            cout << "A chain is formed successfully:\n";
            for (int i = 0; i < n; ++i) {
                cout << chain[i].leftDots << "|" << chain[i].rightDots;
                if (i != n - 1) {
                    cout << " - ";
                }
            }
            cout << endl;
        } else {
            cout << "No chain is formed\n";
        }
        break;
    }
}
int main() {
    cout << "Welcome, ";
    char choice;
    while(true){
        cout << "Choose the program you need:\na-Correct your sentence\n"
                "b-Get prime numbers to n\nc-Dominos game\nd-Message altering to avoid censorship\ne-Exit\n";
        cin >> choice;
        switch (tolower(choice)) {
            case 'a':
                correction();
                break;
            case 'b':
                SieveOfEratosthenes();
                break;
            case 'c':
                start();
                break;
            case 'd':
                censorShip();
                break;
            case 'e':
                break;
            default:
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Enter the right choice:";
                continue;
        }
        if(tolower(choice) == 'e'){
            cout << "Goodbye!";
            break;
        }
    }
    return 0;
}
