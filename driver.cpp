/**
Driver for running sets of trials of the main solution algorithm.

Must be placed in a folder alongside a trial file and the main solver exe.
*/

/*
To do:
-Include another trial option that specifies whether the trials are allowed to reuse the same solution log. If so, then we need a way to process the solution log to reassess feasibility in case the constraint parameter changes. We also need a way to get the solution log from one location to another.
*/

#include <cmath>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <tuple>

// Problem parameter definitions
#define SOLVER "social_transit_solver.exe"
#define TRIAL_FILE "trials.txt"

using namespace std;

// Function prototypes
void load_trials();
string s2hms(double);

// Global variables
queue<tuple<int, string>> trial_queue; // queue of trials to process, each consisting of a tuple of ID and file path

/// Main driver.
int main()
{
	// Load the trial set
	load_trials();

	// Main trial loop
	while (trial_queue.empty() == false)
	{
		// Get the trial
		int id = get<0>(trial_queue.front());
		string path = get<1>(trial_queue.front());
		trial_queue.pop();

		//////////////////// run trial and time and print header, write log
		cout << id << '\t' << path << endl;
	}

	cin.get();
}

/// Reads parameters from trial file.
void load_trials()
{
	ifstream trial_file;
	trial_file.open(TRIAL_FILE);
	if (trial_file.is_open())
	{
		string line, piece; // whole line and line element being read
		getline(trial_file, line); // skip comment line

		while (trial_file.eof() == false)
		{
			// Get whole line as a string stream
			getline(trial_file, line);
			if (line.size() == 0)
				// Break for blank line at file end
				break;
			stringstream stream(line);

			// Go through each piece of the line
			getline(stream, piece, '\t'); // ID
			int trial_id = stoi(piece);
			getline(stream, piece, '\t'); // file path
			string trial_path = piece;

			// Add trial to queue
			trial_queue.push(make_tuple(trial_id, trial_path));
		}

		trial_file.close();
	}
	else
	{
		cout << "Trial file failed to open." << endl;
		exit(1);
	}
}

/// Converts a number of seconds to an HH:MM:SS string.
string s2hms(double sec)
{
	int h = floor(sec / 3600);
	int m = floor((sec - 3600 * h) / 60);
	double s = fmod(sec, 60);

	stringstream stream;
	stream << fixed << setprecision(2);
	stream << h << ':';
	if (m >= 10)
		stream << m;
	else
		stream << '0' << m;
	stream << ':' << s;

	return stream.str();
}
