#include <iostream>
#include <fstream>
#include <chrono>
#include <sstream>

#include "Board.h"
#include "Game.h"
#include "Player.h"

#include "HumanPlayer.h"
#include "BasicAI.h"
#include "MyAI.h"

using std::cout;
using std::cin;
using std::string;

void menu();

void menu_gen();
void generateSeedSet(std::string filepath, int seeds=1000, int width=20, int height=20, int colourCount=6, int totalMoves=100);

void menu_run();
void run_tests(string input, string save);

int main() {

    menu();

    return 0;
}

void menu() {
    cout << "========= Flood-It =========\n"
              << "Base code by Mitchell Merry\n"
              << "Choose an option below:\n"
              << "1) Run MyAI on seed set\n"
              << "2) Generate seed set\n";

    int choice = 0;
    while(choice < 1 || choice > 2) {
        cin >> choice;
    }

    if(choice == 1) menu_run();
    else if(choice == 2) menu_gen();
}

///////

void menu_run() {
    string input, save;
    cout << "Enter the filepath of the seedset to run (e.g. seedsets/test_set.txt):\n";
    cin >> input;
    cin.ignore();

    cout << "Enter the filepath for the results to save to (e.g. results/test_set_r.txt):\n";
    cin >> save;
    cin.ignore();

    run_tests(input, save);
}

void run_tests(string input, string save) {
    std::ifstream file(input);
    std::ofstream out(save);

    string line;
    getline(file, line);

    std::istringstream iss(line);
    int seeds, width, height, colourCount, totalMoves;
    getline(iss, line, ',');
    seeds = stoi(line);
    getline(iss, line, ',');
    width = stoi(line);
    getline(iss, line, ',');
    height = stoi(line);
    getline(iss, line, ',');
    colourCount = stoi(line);
    getline(iss, line, ',');
    totalMoves = stoi(line);

    int sum = 0;
    string str = "";
    while(getline(file, line)) {
        int s = stoi(line);
        Player *p = new BasicAI();
        Game game(p, width, height, colourCount, totalMoves, s);
        int moves = game.play();
        sum += moves;
        str += std::to_string(moves);
        str += "\n";
    }

    out << sum << "\n";
    out << str;


    out.close();
    file.close();
}

///////

void menu_gen() {
    string filepath;
    int seeds, width, height, colourCount, totalMoves;
    cout << "(use '1000 20 20 6 300 seedsets/[filename].txt' for quick setup)\n";
    cout << "Enter a number of seeds to generate:\n";
    cin >> seeds;
    cin.ignore();
    cout << "Enter the width of the boards:\n";
    cin >> width;
    cin.ignore();
    cout << "Enter the height of the boards:\n";
    cin >> height;
    cin.ignore();
    cout << "Enter the number of colours on the boards:\n";
    cin >> colourCount;
    cin.ignore();
    cout << "Enter the maximum number of moves per board allowed:\n";
    cin >> totalMoves;
    cin.ignore();

    cout << "Enter the filepath for the generated seed set (e.g. seedsets/test_set.txt):\n";
    cin >> filepath;
    cin.ignore();

    generateSeedSet(filepath, seeds, width, height, colourCount, totalMoves);
}

void generateSeedSet(std::string filepath, int seeds, int width, int height, int colourCount, int totalMoves) {
    std::ofstream out(filepath);

    // Write the settings of the set to the top of the file
    out << seeds << "," << width << "," << height << "," << colourCount << "," << totalMoves << "\n";

    // Write each generated seed to the file
    srand(time(NULL));
    for(int i = 0; i < seeds; i++) {
        out << rand()*rand() << "\n";
    }

    out.close();
}
