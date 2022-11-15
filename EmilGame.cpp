#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;


const int NUM_QUESTIONS = 5;
const int NUM_OPTIONS = 4;
const int NUM_TEAMS = 2;


struct FullQuestion 
{
        string question;
        string answers[NUM_OPTIONS]; // elem 0 == correct, all others incorrect

        bool visited = false;
};


struct Team
{
        string name;
        int points = 0;

};


struct FullQuestion allQuestions[NUM_QUESTIONS];

struct Team allTeams[NUM_TEAMS];


int randomIndex();
void formatQuestion(struct FullQuestion curr);
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
        }
        cout << endl;
        

        for (int i = 0; i < NUM_TEAMS; i++) {
                cout << "Gruppe " << i << ", wie heißt deine Mannschaft?: ";
                cin >> allTeams[i].name;
        }


        cout << "Perfekt, los geht's!" << endl;

        prepQuestions();
        cycleQuestions();
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

                cout << "--------------------" << endl;
                cout << "FRAGE " << numCycles + 1 << ":\n\n";

                formatQuestion(curr);
                checkAnswers(curr);

                // function to draw train
                //
                //
                //
                //



                numCycles++;
        }



}


int randomIndex() 
{
        return rand(NUM_QUESTIONS - 1);
}


void formatQuestion(struct FullQuestion curr) 
{
        cout << curr.question << endl;
        cout << endl;

        char options[NUM_OPTIONS] = {'A', 'B', 'C', 'D'};
        bool visited[NUM_OPTIONS] = {false};
        
        for (int i = 0; i < NUM_OPTIONS; i++) {
                cout << options[i] << ". ";

                // randomize presentation of answer options
                int optionIndex = rand(NUM_OPTIONS - 1);
                while (visited[optionIndex]) {
                        optionIndex = rand(NUM_OPTIONS - 1);
                }
                visited[optionIndex] = true;

                cout << curr.answers[optionIndex] << endl;
        }
}


bool isCorrect(struct FullQuestion curr, char answer)
{
        if (answer == curr.answers[0]) {
                return true;
        }
        return false;
}


void checkAnswers(struct FullQuestion curr)
{
        char teamAnswer[NUM_TEAMS];
        string outcome = " das is FALSCH!\n\n"; // default message

        // handle teach team's guess
        for (int i = 0; i < NUM_TEAMS; i++) {
                cout << "Mannschaft *" << allTeams[i].name << "*,";
                cout << "was ist die Antwort?: ";
                cin >> teamAnswer[i];
                cout << "\n\n";
        }

        // verify each team's guess
        for (int i = 0; i < NUM_TEAMS; i++) {
                cout << "Mannschaft *" << allTeams[i].name << "*,";
                if (isCorrect(curr, teamAnswer[i])) {
                        outcome = "bist du ... RICHTIG!\n\n";
                        allTeams[i].points++; // increment points
                } 
                cout << outcome;
        }
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
                        cout << tiedWinners.back() << endl;
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
        q0.question = "";
        q0.answers[0] = "";
        q0.answers[1] = "";
        q0.answers[2] = "";
        q0.answers[3] = "";

        struct FullQuestion q1;
        q1.question = "";
        q1.answers[0] = "";
        q1.answers[1] = "";
        q1.answers[2] = "";
        q1.answers[3] = "";

        struct FullQuestion q2;
        q2.question = "";
        q2.answers[0] = "";
        q2.answers[1] = "";
        q2.answers[2] = "";
        q2.answers[3] = "";

        struct FullQuestion q3;
        q3.question = "";
        q3.answers[0] = "";
        q3.answers[1] = "";
        q3.answers[2] = "";
        q3.answers[3] = "";

        struct FullQuestion q4;
        q4.question = "";
        q4.answers[0] = "";
        q4.answers[1] = "";
        q4.answers[2] = "";
        q4.answers[3] = "";


        allQuestions[0] = q0;
        allQuestions[1] = q1;
        allQuestions[2] = q2;
        allQuestions[3] = q3;
        allQuestions[4] = q4;
}


