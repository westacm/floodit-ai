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

void Menu();

void Menu_GenerateSeedset();

void GenerateSeedset(std::string _path, int _seedCount = 1000, int _width = 20, int _height = 20, int _colorCount = 6, int _maxMoves = 100);

void Menu_RunAI();

void RunTests(string _seedsetFile, string _resultsFile);

int main()
{
    Menu();
    return 0;
}

void Menu()
{
    cout << "========= Flood-It =========\n"
         << "Base code by Mitchell Merry, Edits by Broderick Westrope\n"
         << "Choose an option below:\n"
         << "[1] Run AI test using a seed set\n"
         << "[2] Generate a new seed set\n";

    char choice;
    cin >> choice;
    while (choice < '1' || choice > '2')
    {
        cout << "Please enter valid input.\n";
        cin >> choice;
    }

    if (choice == '1')
    { Menu_RunAI(); }
    else if (choice == '2')
    { Menu_GenerateSeedset(); }
    else
    { cout << "ERROR: Invalid input passed through.\n"; }
}

void Menu_RunAI()
{
    string seedset, results;
    cout << "Enter the filepath of the seedset to run (e.g. seedsets/test_set.txt):\n";
    cin >> seedset;
    cin.ignore();

    cout << "Enter the filepath for the results to results to (e.g. results/test_set_r.txt):\n";
    cin >> results;
    cin.ignore();

    RunTests(seedset, results);
}

void RunTests(string _seedsetFile, string _resultsFile)
{
    std::ifstream seedsetInput(_seedsetFile);

    string line;
    getline(seedsetInput, line);

    std::istringstream iss(line);
    int seedCount, width, height, colourCount, maxMoves;
    getline(iss, line, ',');
    seedCount = stoi(line);
    getline(iss, line, ',');
    width = stoi(line);
    getline(iss, line, ',');
    height = stoi(line);
    getline(iss, line, ',');
    colourCount = stoi(line);
    getline(iss, line, ',');
    maxMoves = stoi(line);

    int sum = 0;
    int errorCount = 0;
    string str = "";
    for (int i = 0; i < seedCount; i++)
    {
        getline(seedsetInput, line);
        if (line.empty())
        {
            cout << "ERROR: The test found an empty line in the given seedset.\n";
            return;
        }
        int s = stoi(line);

        Player *p = new BasicAI();
        Game game(p, width, height, colourCount, maxMoves, s);
        int moves = game.play();

        if (moves == -1)
        {
            errorCount++;
            str += "GAME " + std::to_string(i + 1) + ": **TOO MANY MOVES**\n";
        }
        else
        {
            sum += moves;
            str += "GAME " + std::to_string(i + 1) + ": " + std::to_string(moves) + "\n";
        }
    }

    std::ofstream out(_resultsFile);
    out << "TOTAL MOVES: " << std::to_string(sum) << "\n";
    out << "AVG. MOVES: " << std::to_string(sum / seedCount) << "\n";
    out << str;

    out.close();
    seedsetInput.close();
}

void Menu_GenerateSeedset()
{
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

    cout << "Enter the filepath for the generated seed set (e.g. seedsets/[filename].txt):\n";
    cin >> filepath;
    cin.ignore();

    GenerateSeedset(filepath, seeds, width, height, colourCount, totalMoves);
}

void GenerateSeedset(std::string _path, int _seedCount, int _width, int _height, int _colorCount, int _maxMoves)
{
    std::ofstream seedsetOutput(_path);

    // Write the settings of the set to the top of the file
    seedsetOutput << _seedCount << "," << _width << "," << _height << "," << _colorCount << "," << _maxMoves;

    // Write each generated seed to the file
    srand(time(NULL));
    for (int i = 0; i < _seedCount; i++)
    {
        seedsetOutput << "\n" << rand() * rand();
    }

    seedsetOutput.close();
}
