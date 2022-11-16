#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;


const int NUM_QUESTIONS = 5;
const int NUM_OPTIONS = 4;
const int NUM_TEAMS = 2;


struct FullQuestion {
        string question;
        string answers[NUM_OPTIONS]; // elem 0 == correct, all others incorrect
        
        char correctOption;
        bool visited = false;
};


struct Team {
        string name;
        int points = 0;
};


string train1[4] = {
        "____\n",
        "|DD|____T_\n",
        "|_ |_____|<\n",
        " @-@-@-oo\n"
};

string train2[5] = {
        "  _____                . . . . . o o o o o\n",
        "__|[_]|__ ___________ _______    ____      o\n",
        "|[] [] []| [] [] [] [] [_____(__  ][]]_n_n__][.\n",
        "_|________|_[_________]_[________]_|__|________)<\n",
        "oo    oo 'oo      oo ' oo    oo 'oo 0000---oo\n"
};

string tracks = "-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-";


struct FullQuestion allQuestions[NUM_QUESTIONS];

struct Team allTeams[NUM_TEAMS];


void drawTrain1(int cycles);
void drawTrain2();
int randomIndex();
struct FullQuestion formatQuestion(struct FullQuestion curr);
bool isCorrect(struct FullQuestion curr, char answer);
void checkAnswers(struct FullQuestion curr);
void getWinner();
void prepQuestions();
void cycleQuestions();


int main() 
{
        string response;
        cout << "Wilkommen! Bist du fertig? (ja/nein): ";
        cin >> response;

        while (response != "ja") {
                cout << "\n(ja/nein): ";
                cin >> response;
        }
        cout << "\n\n";       

        for (int i = 0; i < NUM_TEAMS; i++) {
                cout << "Gruppe " << i << ", wie heißt deine Mannschaft?: ";
                cin >> allTeams[i].name;
        }

        cout << "Perfekt, los geht's!";
        cout << "\n\n";

        prepQuestions();
        cycleQuestions();

        cout << "--------------------\n" << endl;

        drawTrain2();
        getWinner();

        return 0;
}


void cycleQuestions() 
{
        int numCycles = 0;

        while (numCycles < NUM_QUESTIONS) {
                struct FullQuestion curr;

                // get a question we haven't yet seen
                curr = allQuestions[randomIndex()];
                while (curr.visited) {
                        curr = allQuestions[randomIndex()];
                }
                curr.visited = true;

                cout << "--------------------\n" << endl;

                // draw train based on progress in game
                drawTrain1(numCycles);

                cout << "FRAGE " << numCycles + 1 << ":\n\n";

                struct FullQuestion editCurr = formatQuestion(curr);
                checkAnswers(editCurr);

                numCycles++;
        }
}


void drawTrain1(int cycles) 
{
        int partLength = tracks.length() / 5;
        int spaceCount = 0;
        string spaces = " ";

        while (spaceCount < cycles * partLength) {
                spaces += " ";
                spaceCount++;
        }

        for (int i = 0; i < 4; i++) {
                cout << spaces << train1[i];
        }
        cout << tracks << endl;
        cout << endl;
}


void drawTrain2()
{
        /* get midway positioning on tracks for large train */
        int partLength = (tracks.length() - train2[3].length()) / 2;
        int spaceCount = 0;
        string spaces = " ";

        while (spaceCount < partLength) {
                spaces += " ";
                spaceCount++;
        }

        for (int i = 0; i < 5; i++) {
                cout << spaces << train2[i];
        }
        cout << tracks << endl;
        cout << endl;
}


int randomIndex() 
{
        return rand() % NUM_QUESTIONS;
}


struct FullQuestion formatQuestion(struct FullQuestion curr) 
{
        cout << curr.question << endl;
        cout << endl;

        char options[NUM_OPTIONS] = {'A', 'B', 'C', 'D'};
        bool visited[NUM_OPTIONS] = {false};

        int optionIndex = -1;
        
        for (int i = 0; i < NUM_OPTIONS; i++) {
                cout << options[i] << ". ";

                // randomize presentation of answer options
                optionIndex = rand() % NUM_OPTIONS;
                while (visited[optionIndex]) {
                        optionIndex = rand() % NUM_OPTIONS;
                }
                visited[optionIndex] = true;

                if (optionIndex == 0) {
                        curr.correctOption = options[i];
                }

                cout << curr.answers[optionIndex] << endl;
        }
        cout << endl;

        return curr;
}


bool isCorrect(struct FullQuestion curr, char answer)
{
        if (toupper(answer) == curr.correctOption) {
                return true;
        }
        return false;
}


void checkAnswers(struct FullQuestion curr)
{
        char teamAnswer[NUM_TEAMS];

        // handle teach team's guess
        for (int i = 0; i < NUM_TEAMS; i++) {
                cout << "Mannschaft *" << allTeams[i].name << "*, ";
                cout << "was ist die Antwort?: ";
                cin >> teamAnswer[i];
                cout << "\n\n";
        }

        cout << "\n\n" << endl;

        // verify each team's guess
        for (int i = 0; i < NUM_TEAMS; i++) {
                cout << "Mannschaft *" << allTeams[i].name << "*, ";
                string outcome = "das ist ... FALSCH!"; // default message

                if (isCorrect(curr, teamAnswer[i])) {
                        outcome = "bist du ... RICHTIG!";
                        allTeams[i].points++; // increment points
                } 
                cout << outcome << endl;
        }

        cout << "\nDie Antwort ist: " << curr.answers[0];
        cout << "\n\n";
}


void getWinner()
{
        int winnerIndex = -1;
        vector<string> tiedWinners;

        // tally points & identify any ties
        for (int i = 0; i < NUM_TEAMS; i++) {
                if (allTeams[i].points > allTeams[winnerIndex].points) {
                        winnerIndex = i;
                        tiedWinners.clear();
                } else if (allTeams[i].points == allTeams[winnerIndex].points) {
                        tiedWinners.push_back(allTeams[i].name);
                }
        }

        // print all winners if there's a tie
        if (tiedWinners.size() > 0) {
                tiedWinners.push_back(allTeams[winnerIndex].name);

                cout << "Diese Mannschaften sind Gewinner!" << endl;
                while (!tiedWinners.empty()) {
                        cout << "** " << tiedWinners.back() << " **" << endl;
                        tiedWinners.pop_back();
                }
                
        } else { // or just 1 winner
                cout << "Die Mannschaft *" << allTeams[winnerIndex].name;
                cout << "* hat das Spiel gewonnen!" << endl;
        }
}


void prepQuestions() 
{
        struct FullQuestion q0;
        q0.question = "Als Emil trifft den Kriminalwachtmeister Lurje, er vergisst immer wieder Emils Nachnamen. Welchen falschen Nachname benutzt Herr Lurje?";
        q0.answers[0] = "Fischbein, Stuhlbein";
        q0.answers[1] = "Tellerbein, Menschbein";
        q0.answers[2] = "Menschbein, Fleischbein";
        q0.answers[3] = "Stuhlbein, Taschebein";

        struct FullQuestion q1;
        q1.question = "Als Emil Herr Kastner trifft, Emil sagt 'Kennen Sie mich denn nicht mehr?'. Warum fragt er das?";
        q1.answers[0] = "Herr Kastner hat gestern Emils Strassenbahnbillett bezahlt.";
        q1.answers[1] = "Herr Kastner ist sehr beruhmt.";
        q1.answers[2] = "Herr Kastner ist der gemeine Schaffner von Zug.";
        q1.answers[3] = "Herr Kastner hat die Droschke gefahrt.";

        struct FullQuestion q2;
        q2.question = "Wer isst NICHT den Kuchen in der Konditorei?";
        q2.answers[0] = "Pony";
        q2.answers[1] = "Herr Kastner";
        q2.answers[2] = "Der Professor";
        q2.answers[3] = "Gustav";

        struct FullQuestion q3;
        q3.question = "Wo ist das Polizeiprasidium?";
        q3.answers[0] = "Alexanderplatz";
        q3.answers[1] = "Potsdamer Platz";
        q3.answers[2] = "Pariser Platz";
        q3.answers[3] = "Bebelplatz";

        struct FullQuestion q4;
        q4.question = "Der Dieb benutzt viele verschiedene Namen. Welchen Namen benutzt er NICHT?";
        q4.answers[0] = "Kreid";
        q4.answers[1] = "Grundeis";
        q4.answers[2] = "Muller";
        q4.answers[3] = "Kiessling";


        allQuestions[0] = q0;
        allQuestions[1] = q1;
        allQuestions[2] = q2;
        allQuestions[3] = q3;
        allQuestions[4] = q4;
}


