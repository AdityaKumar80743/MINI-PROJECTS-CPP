#include <iostream>
#include <vector>
#include <string>
#include <cstdlib> // for rand()
#include <cctype> // for toupper()

using namespace std;

// global variables
vector<vector<string>> hints = {{"LION","TIGER","ELEPHANT","ZEBRA","KANGAROO","GIRAFFE","CHEETAH","PANDA","BEAR","RHINOCEROS","CROCODILE","WOLF","FOX","HIPPOPOTAMUS","LEOPARD","ANIMAL"}, // animal
                                {"PIZZA","BURGER","SUSHI","PASTA","SANDWICH","STEAK","TACOS","NOODLES","FRIEDRICE","SALAD","PANCAKES","CURRY","SOUP","KEBAB","OMELETTE", "FOOD"}, // food
                                {"APPLE","BANANA","ORANGE","MANGO","GRAPES","PINEAPPLE","STRAWBERRY","WATERMELON","CHERRY","PEACH","KIWI","LEMON","PAPAYA","COCONUT","GUAVA","FRUIT"}}; // fruit

void drawHangman(int n=6) {
    // hangman body parts 
    vector<vector<string>> parts = {{" "," "," ","|"," "},
                                    {" "," "," ","O"," "},
                                    {" "," ","/","|","\\"},
                                    {" "," ","/"," ","\\"}};
                            
    int count = -1; // should show at least one part

    cout << "+-------+" << endl;
    for (int i=0; i<parts.size(); i++) {
        for (int j=0; j<parts[i].size(); j++) {
            cout << parts[i][j];
            if (parts[i][j] != " ") { // body part found
                count++;
            }
            if (count >= n) { 
                cout << "\n_________" << endl;
                return;
            }
        }
        cout << endl;
    }
}

void game() {
    vector<string> category = hints[rand() % (hints.size()-1)]; // get random category of words
    string categoryHints = category[category.size()-1];
    string hint = category[rand() % (category.size()-1)]; // get random in that caterogy
    string guessed (hint.length(),'-'); // initialiy no words are guessed

    int attempts = 6;
    while (attempts > 0) { // until 6 wrong attempts, loop runs
        string input; 
        bool gotGuess = false;

        drawHangman(6-attempts);
        cout << "HINT: " << categoryHints << endl;
        cout << "WORDS: " << guessed << endl; 

        cout << "Your Guess: ";
        cin >> input;
        if (input.size() != 1 || !isalpha(input[0])) {
            cout << "Invalid Input - Enter only one letter...." << endl;
            continue;
        }
        char guess = toupper(input[0]); // convert to upper case letter

        for (int i=0; i<hint.length(); i++) {
            if (hint[i] == guess) { // correct guess
                guessed[i] = hint[i]; // change all "-" with the correct letter of respective places 
                gotGuess = true;
            }
        }

        if (guessed == hint) { // all letter are gussed
            cout << "word was: " << hint << endl;
            cout << "hurray! you guessed the word....." << endl;
            cout << "--------------------------" << endl;
            return;
        }
      
        if (!gotGuess) attempts--; // wrong guess
    }
    // lost
    drawHangman();
    cout << "word was: " << hint << endl;
    cout << "Game Over! the man is hanged...." << endl;
}

void rules() { // game rules
    cout << "-----------------------------" << endl;
    cout << "  WELCOME TO HANGMAN GAME    " << endl;
    cout << "-----------------------------" << endl;

    drawHangman(); // draw full hangman

    cout << "-----------------------------" << endl;
    cout << "Rules:" << endl;
    cout << "- Guess the word by entering one letter at a time" << endl;
    cout << "- Each wrong Guess will add a part to the hangman" << endl;
    cout << "- You have 6 chances before the man is hanged!" << endl;
    cout << "-----------------------------" << endl;
}

int main() {
    rules();
    while (true) {
        game();

        char action;
        cout << "Play Again: (ENTER/N) - ";
        cin >> action;

        if (toupper(action) == 'N') break; 
    }

    return 0;
}
