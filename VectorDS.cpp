#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

//Structure to represent a course with its number, title, and prerequisites
struct Course {
    string courseNumber;
    string title;
    vector<string> prerequisites;
};

//class that manages course information and operations
class CoursePlanner {
private:
    vector<Course> courses; //Stores a list of all courses

public:
    //Loads courses from a CSV file and updates the courses vector
    vector<Course> loadCoursesFromCSV(const string& filename);

    //Public method to load courses from file and handles success or failure
    void loadCoursesFromFile(const string& filename) {
        courses = loadCoursesFromCSV(filename);
        if (!courses.empty()) {
            cout << "Courses loaded successfully.\n";
            cout << "" << endl;
        }
        else {
            cout << "No courses loaded. Try again.\n";
        }
    }

    //Prints all loaded courses along with their details
    void printCourses() {
        if (courses.empty()) {
            cout << "No courses loaded.\n";
            return;
        }
        // sort method by alphanumerical order by course number
        // compares two course objects based on their courseNumber
        //utilizing lambda function
        sort(courses.begin(), courses.end(), [](const Course& a, const Course& b) {
            return a.courseNumber < b.courseNumber;
            });

        for (const auto& course : courses) {  //print details
            cout << "Course Number: " << course.courseNumber
                << ", Title: " << course.title
                << ", Prerequisites: ";
            //prints each prequisite for course if applicable
            for (const auto& prerequisite : course.prerequisites) {
                cout << prerequisite << " ";
            }
            cout << endl;
        }
    }

    //Public method to print details of a course by its course number
    void printCourse(const string& courseNumber) {
        findAndPrintCourse(courseNumber);
    }

private:
    //Helper  to find and print a course by its number
    void findAndPrintCourse(const string& courseNumber) {
        for (const auto& course : courses) {
            if (course.courseNumber == courseNumber) {
                cout << "Course Number: " << course.courseNumber <<  "\nTitle: " << course.title << "\nPrerequisites: ";
                for (const auto& preq : course.prerequisites) {
                    cout << preq << " ";
                }
                cout << endl;
                return;
            }
        }
        cout << "Course with number " << courseNumber << " not found." << endl;
    }
};

//Implementation of loadCoursesFromCSV method 
//MAKE SURE TO LOAD CourseFile.csv
vector<Course> CoursePlanner::loadCoursesFromCSV(const string& filename) {
    vector<Course> loadedCourses;
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Could not open the file - '" << filename << "'" << endl;
        return loadedCourses;
    }

    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        vector<string> tokens;
        string token;

        while (getline(iss, token, ',')) {
            //Manually remove leading and trailing spaces and quotes if present
            size_t start = token.find_first_not_of(" \t\"");
            size_t end = token.find_last_not_of(" \t\"");

            if (start != string::npos && end != string::npos) {
                token = token.substr(start, end - start + 1);
            }
            else {
                token = ""; //Handle tokens that are only whitespace or quotes
            }

            tokens.push_back(token);
        }

        if (tokens.size() >= 2) {
            //Constructing Course object with the extracted tokens
            loadedCourses.emplace_back(Course{ tokens[0], tokens[1], vector<string>(tokens.begin() + 2, tokens.end()) });
        }
    }

    file.close();
    return loadedCourses;
}

//Prints the main menu for the application
void printMenu() {
    cout << "Welcome to the ABCU Course Planner!" << endl;
    cout << "" << endl;
    cout << "1. Load filename" << endl;
    cout << "2. Print Course List" << endl;
    cout << "3. Print A Course" << endl;
    cout << "4. Exit" << endl;
    cout << "" << endl;
    cout << "Enter your choice: " << endl;
}

int main() { 
    CoursePlanner planner; // Create courseplanner object to manage courses
    bool running = true; // Control varaible for main loop

    //Main loop for processing user commands
    while (running) {
        printMenu(); 
        int choice;
        cin >> choice;

        switch (choice) {
        case 1: {
            cout << "" << endl;
            cout << "Load filename: \n";
            string filename;
            cin >> filename;
            planner.loadCoursesFromFile(filename);
            break;
        }
        case 2:
            planner.printCourses();
            cout << "" << endl;
            break;
        case 3: {
            cout << "" << endl;
            cout << "Enter course number: ";
            cout << "" << endl;
            string courseNumber;
            cin >> courseNumber;
            planner.printCourse(courseNumber);
            cout << "" << endl;
            break;
        }
        case 4:
            running = false;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
