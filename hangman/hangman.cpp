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

void drawHangman(int stage) {
    // hangman stages (0–6)
    const vector<string> stages = {
        // 0: empty gallows
        "+-------+\n"
        "|       |\n"
        "|        \n"
        "|        \n"
        "|        \n"
        "|\n"
        "_________\n",

        // 1: head
        "+-------+\n"
        "|       |\n"
        "|       O\n"
        "|        \n"
        "|        \n"
        "|\n"
        "_________\n",

        // 2: head + body
        "+-------+\n"
        "|       |\n"
        "|       O\n"
        "|       |\n"
        "|        \n"
        "|\n"
        "_________\n",

        // 3: head + body + left arm
        "+-------+\n"
        "|       |\n"
        "|       O\n"
        "|      /|\n"
        "|        \n"
        "|\n"
        "_________\n",

        // 4: head + body + both arms
        "+-------+\n"
        "|       |\n"
        "|       O\n"
        "|      /|\\\n"
        "|        \n"
        "|\n"
        "_________\n",

        // 5: head + body + arms + one leg
        "+-------+\n"
        "|       |\n"
        "|       O\n"
        "|      /|\\\n"
        "|      / \n"
        "|\n"
        "_________\n",

        // 6: full hangman
        "+-------+\n"
        "|       |\n"
        "|       O\n"
        "|      /|\\\n"
        "|      / \\\n"
        "|\n"
        "_________\n"
    };

    // clamp stage to [0,6]
    if (stage < 0) stage = 0;
    if (stage > 6) stage = 6;

    cout << stages[stage];
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

    drawHangman(6); // draw full hangman

    cout << "-----------------------------" << endl;
    cout << "Rules:" << endl;
    cout << "- Guess the word by entering one letter at a time" << endl;
    cout << "- Each wrong Guess will add a part to the hangman" << endl;
    cout << "- You have 6 chances before the man is hanged!" << endl;
    cout << "-----------------------------" << endl;
}
 

int main() {
    srand(time(0)); // the rand();
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

