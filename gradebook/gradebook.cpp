// Adding Header files
#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;

// Structure to store all vaulues in a row
struct Student {
	string fname, lname, cms;
	double quiz1, quiz2, quiz3, a1, a2, a3, oht1, oht2, ese;
	double aggr;
};

// *** GLOBAL VARS
// FILE TO READ
string fileAdd = "Sample-Gradebook.csv";
// Reading The csv file to arry students
Student students[100];

// *** CUSTOM METHODS HEADERS
double s2i(string); // Method to convert std::string to int (Handle blanks)
bool aggSort(Student, Student); // Sort by Aggrigate
void writeToFile(string, int, int); // Write to File

// *** MAIN
int main(string fName) {

	// Remove commenting when giving arguments using commandline
	// fileAdd = fName;

	// Opening File
	ifstream file(fileAdd);
	if (!file.is_open()) cout << "Not Open";
	
	int n = 0; // Number of valid students
	string ch;

	// Total (will later read from file)
	const int quiz = 30, assignment = 30, oht = 100, eseT = 100;

	// First two lines are header
	getline(file, ch, '\n');
	getline(file, ch, '\n');

	// The actual reading
	while (getline(file, students[n].cms, ',')) {

		if (students[n].cms.empty()) break; //Break when encounter empty row

		// Read vals and store them in students variables
		getline(file, students[n].fname, ',');
		getline(file, students[n].lname, ',');
		getline(file, ch, ',');
		students[n].quiz1 = s2i(ch);
		getline(file, ch, ',');
		students[n].a1 = s2i(ch);
		getline(file, ch, ',');
		students[n].a2 = s2i(ch);
		getline(file, ch, ',');
		students[n].a3 = s2i(ch);
		getline(file, ch, ',');
		students[n].quiz2 = s2i(ch);
		getline(file, ch, ',');
		students[n].quiz3 = s2i(ch);
		getline(file, ch, ',');
		students[n].oht1 = s2i(ch);
		getline(file, ch, ',');
		students[n].oht2 = s2i(ch);
		getline(file, ch, ',');
		students[n].ese = s2i(ch);
		getline(file, ch, '\n');

		// Calculating Aggrigate
		students[n].aggr = (students[n].quiz1 + students[n].quiz2 + students[n].quiz3) / quiz * 10
			+ (students[n].a1 + students[n].a2 + students[n].a3) / assignment * 10
			+ (students[n].oht1 + students[n].oht2) / oht * 40
			+ students[n].ese / eseT * 40;
		
		//cout << students[n].fname << " " << students[n].aggr << endl;
		n++;
	}

	// Closing File
	file.close();

	// Sorting with respect to aggrigate
	sort(students, students + n, aggSort); // N being the number of valid students

	// *** Writing files for each grade.
	// The deciding points are
	// A - 90 <
	// Bplus - 70 <
	// B - 45 <
	// Cplus - 35 <
	// C - 30 <
	// Dplus 20 <
	// D - 12 <
	// F - 12>
	writeToFile("A", 0, (int)(n*.1));
	writeToFile("Bplus", (int)(n*0.1), (int)(n*0.3));
	writeToFile("B", (int)(n*0.3), (int)(n*0.55));
	writeToFile("Cplus", (int)(n*0.55), (int)(n*0.65));
	writeToFile("C", (int)(n*0.65), (int)(n*0.7));
	writeToFile("Dplus", (int)(n*0.7), (int)(n*0.8));
	writeToFile("D", (int)(n*0.8), (int)(n*0.88));
	writeToFile("F", (int)(n*0.88), n);
}


// Method to convert std::string to double (Handle blanks)
double s2i(string s) {
	if (s.empty()) return 0;
	return stod(s);
}

// Sort by Aggrigate
bool aggSort(Student lhs, Student rhs) {
	return lhs.aggr > rhs.aggr; 
}

// Write to File
// fun (grade of file, starting position, ending position)
void writeToFile(string grade, int sPos, int ePos) {
	
	// Name of the file on which to write
	string fileName = fileAdd.substr(0, fileAdd.length() - 4) + "-" + grade + ".csv";
	
	// Creating and opening file
	ofstream file(fileName);
	if (!file.is_open()) cout << "Not Open";

	// Wrint names and cms to file
	file << "FirstName,LastName,CMS\n";
	for (int i = sPos; i < ePos; i++) {
		file << students[i].fname << "," << students[i].lname << "," << students[i].cms << "\n";
	}
	
	//closing file
	file.close();
	cout << grade << " done" << endl;
}