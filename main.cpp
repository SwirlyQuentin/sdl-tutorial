#include <iostream>
#include <vector>
#include <fstream>
#include <string>
using namespace std;


// ----- AUTO GENERATED INCLUDES -----
// LESSON_INCLUDES_START
#include "lessons/Lesson1_HelloSDL/main.h"
#include "lessons/Lesson2_Images/main.h"
#include "lessons/Lesson3_EventDriving/main.h"
// LESSON_INCLUDES_END
// ----- END AUTO GENERATED INCLUDES -----


using LessonFunc = int (*)(int, char**);
vector<string> lessonNames;
vector<LessonFunc> lessonFunctions;

int main (int argc, char* args[]){

    ifstream lessonIndex("lessons_index.txt");

    string lessonName;
    while (getline(lessonIndex, lessonName))
    {
        lessonNames.push_back(lessonName);

        // --- AUTO GENERATED FUNCTION MAPPING ---
        // LESSON_MAPS_START
        if (lessonName == "Lesson1_HelloSDL") {
            lessonFunctions.push_back(run_Lesson1_HelloSDL);
        }
        if (lessonName == "Lesson2_Images") {
            lessonFunctions.push_back(run_Lesson2_Images);
        }
        if (lessonName == "Lesson3_EventDriving") {
            lessonFunctions.push_back(run_Lesson3_EventDriving);
        }
        // LESSON_MAPS_END
        // --- END AUTO GENERATED FUNCTION MAPPING ---
    }

    while (true)
    {
        cout << "\n\n ===== Lessons =====\n";
        for (int i = 0; i < lessonNames.size(); i++){
            cout << i + 1 << ". " << lessonNames[i] << endl;
        }
        cout << "0. Quit\n";
        cout << "\nEnter Lesson Number: ";
        int c;
        cin >> c;

        if (c == 0){
            break;
        }
        if (c < 1 || c > lessonNames.size()){
            continue;
        }

        lessonFunctions[c - 1](argc, args);
    }
    
    





    return 0;
}