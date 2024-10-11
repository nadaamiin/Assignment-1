#include <iostream>
#include <vector>
#include <limits>
#include <string>
#include <fstream>
#include <sstream>
#include <codecvt>
#include <unordered_map>

using namespace std;
void correction(){
    char c;
    string output;
    // Bool var to control spaces in the sentence
    bool space = false;
    // Bool var to control first space in the sentence
    bool first_space = true;
    cout << "Enter your sentence that ends with a '.' :-\n";
    for (int i = 0; i < 100; ++i) {
        cin.get(c);
        if(c == '.'){
            // To remove the last character before space in output if it's dot
            if(isspace(output.back())){
                output.pop_back();
            }
            output += c;
            break;
        }
        // Check if it's space at the beginning
        if(isspace(c) && first_space){
            continue;
        }
        // If it's more than one space set it to one space
        if(isspace(c)){
            if(!space){
                // Add one space to the output then set space to true to stop adding spaces
                output += ' ';
                space = true;
            }
        }else if(isalpha(c)){
            // Set all characters to lower case
            output += (char)tolower(c);
            // Set first space to default
            space = false;
            first_space = false;
        }else{
            // No condition existed
            output += c;
            space = false;
        }
    }
    output[0] = (char)toupper(output[0]);
    if(output.back() != '.'){
        output.push_back('.');
    }
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

// Recursive function that compare each side of the domino with others
bool trackDomino(const vector<dominoT>& domino, vector<bool>& used, vector<dominoT>& chain, int len) {
    // when the len var reaches the size of domino vector; so the chain is successfully formed
    if (len == domino.size()) {
        return true;
    }

    // Loop on all the unused dominoes
    for (int i = 0; i < domino.size(); i++) {
        if (!used[i]) {
            // Check if the current domino can be placed in the chain
            if (len == 0 || chain.back().rightDots == domino[i].leftDots) {
                // When the domino can be placed; add it to the chain and mark as used
                used[i] = true;
                chain.push_back(domino[i]);

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

void censorShip(){
    // To support unicode and handle arabic text
    locale::global(locale(""));
    wifstream censorFile("censorFile.txt");

    // Ignore program crashing
    if (!censorFile.is_open()) {
        cout << "Error: Unable to open the censor file." << endl;
        return;
    }
    
    string inFileName;
    wcout << L"Enter the file name that contain the arabic text:\n";
    wifstream inFile;
    char ch;
    while(true){
        cout << "Do want to\na.Use the default arabic file        b.Open your own file:\n";
        cin >> ch;
        cin.ignore();
        if(tolower(ch) == 'a'){
            inFile.open("arabic text.txt");
            cout << "The default file is opened!\n";
            break;
        }else if(tolower(ch) == 'b'){
            cout << "Enter the name of your own file:\n";
            getline(cin, inFileName);
            inFile.open(inFileName);
            if (inFile.fail()) {
                cout << "Opening failed, enter the name correctly!" << endl;
                continue;
            } else {
                cout << "File opened successfully!\n";
                break;
            }
        }else{
            cout << "Enter a valid option";
            continue;
        }
    }
    inFile.imbue(locale(inFile.getloc(), new codecvt_utf8<wchar_t>));
//    cin.ignore();
    wstring arabic_text, sentence;
    censorFile.imbue(locale(censorFile.getloc(), new codecvt_utf8<wchar_t>));
    while (getline(inFile, sentence)) {
        arabic_text += sentence + L"\n";
    }
    // A map to store all the censored words and their alternatives
    unordered_map<wstring, wstring> censorMap;
    wstring wordKey, alter;
    while (censorFile >> wordKey >> alter) {
        censorMap[wordKey] = alter;
    }
    for (const auto& words : censorMap) {
        size_t pos = arabic_text.find(words.first);
        // Replace all the censored words
        while (pos != wstring::npos) {
            arabic_text.replace(pos, words.first.length(), words.second);
            pos = arabic_text.find(words.first, pos + words.second.length());
        }
    }

    string outFileName;
    cout << "Enter the name of the new file:\n";
    getline(cin, outFileName);
    wofstream outFile(outFileName);

    cout << "File is formed successfully\n";
    // Output file for the censored Arabic text
    outFile.imbue(locale(outFile.getloc(), new codecvt_utf8<wchar_t>));

    // Write the modified text to the output file
    outFile << arabic_text;
    // Close all opened files
    inFile.close();
    censorFile.close();
    outFile.close();
}
int main() {
    cout << "Welcome to the program :)\n";
    char choice;
    while(true){
        cout << "------------------------------------------------\n";
        cout << "Choose the program you need:\na-Correct your sentence\n"
                "b-Get prime numbers to n\nc-Dominoes game\nd-Message altering to avoid censorship\ne-Exit\n";
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
