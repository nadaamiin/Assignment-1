#include <iostream>
#include <vector>
#include <limits>
#include <string>
//#include <fstream>

using namespace std;
//void write_file(){
//    fstream file;
//    string fileName, text;
//    // Check if the file is opened.
//    while (true) {
//        cout << "Enter file name:";
//        getline(cin, fileName);
//        file.open(fileName, ios::out);
//        if (file.fail()) {
//            cout << "Opening failed, please try again!" << endl;
//            continue;
//        } else {
//            cout << "File opened successfully!\n";
//            break;
//        }
//    }
//    cout << "Enter your text\n";
//    while(true){
//        // Read until there is a new line "getline"
//        // Uses /n as a delimiter.
//        getline(file, text);
//        if (text == "exit"){
//            break;
//        }
//        file << text << endl;
//    }
//    file.close();
//}
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
struct dominoT {
    int leftDots;
    int rightDots;
};
bool trackDomino(vector<dominoT> & domino, vector<bool> &done,int pos){
    if (pos == size(domino)) {
        // All domino are used, we formed a valid chain
        return true;
    }
    for (int i = 0; i < size(domino); i++) {
        if (!done[i]) {
            if (domino[i].leftDots == domino[i-1].rightDots) {
                // Place this domino and mark it used
                done[i] = true;
                if (trackDomino(domino, done,pos + 1)) {
                    return true;
                }
                done[i] = false; // Backtrack
            }
        }
    }

    return false; // No valid chain from this configuration
}

bool FormsDominoChain(vector<dominoT> & domino){
    for (int i = 0; i < size(domino); ++i) {
        vector<bool> done(size(domino), false);
        done[i] = true;
        if (trackDomino(domino, done,1)) {
        return true;
        }
    }
    return false;
}

void start(){
    while(true){
        int n;
        cout << "Enter the number of domino(more than 2):\n";
        cin >> n;
        if (cin.fail() || n <= 2)
        {
            // Clear n input
            cin.clear();
            // Ignore n input
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Please, enter a valid number!" << endl;
            continue;
        }
        vector<dominoT> domino(n);

        cout << "Enter the left then right number of each domino(1 -> 6)\n";
        for (int i = 0; i < n; ++i) {
            cin >> domino[i].leftDots >> domino[i].rightDots;
            // Input failed
            if (cin.fail() || domino[i].leftDots < 0 || domino[i].leftDots > 6
                || domino[i].rightDots < 0 || domino[i].rightDots > 6) {
                // Clear invalid input
                cin.clear();
                // Ignore invalid input
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Please, enter a valid number!" << endl;
                // To return back to the right index
                --i;
                continue;
            }
        }
        if(FormsDominoChain(domino)){
            cout << "A chain is formed successfully\n";
            for (int i = 0; i < n; ++i) {
                cout << domino[i].leftDots << "|" << domino[i].rightDots;
                if(i != n-1){
                    cout << " - ";
                }
            }
            cout << endl;
        } else{
            cout << "No chain is formed";
        }
        break;
    }
}
int main() {
//    cout << "Welcome, ";
//    char choice;
//    while(true){
//        cout << "Choose the program you need:\na-Correct your sentence\n"
//                "b-Get prime numbers to n\nc-Dominos game\nd-Message altering to avoid censorship\ne-Exit\n";
//        cin >> choice;
//        switch (tolower(choice)) {
//            case 'a':
//                correction();
//                break;
//            case 'b':
//                SieveOfEratosthenes();
//                break;
//            case 'e':
//                break;
//            default:
//                cin.ignore(numeric_limits<streamsize>::max(), '\n');
//                cout << "Enter the right choice:";
//                continue;
//        }
//        if(tolower(choice) == 'e'){
//            cout << "Goodbye!";
//            break;
//        }
//    }
//    start();
    correction();
    return 0;
}
