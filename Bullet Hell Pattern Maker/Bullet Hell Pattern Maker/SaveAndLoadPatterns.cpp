#include "SaveAndLoadPatterns.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <utility> // std::pair
#include <stdexcept> // std::runtime_error
#include <sstream> // std::stringstream

void SaveAndLoadPatterns::SavePattern(Pattern* pattern)
{
	std::ofstream pattern_file;
	pattern_file.open("patterns/" + pattern->GetName() + ".csv");
	pattern_file << pattern->GetName() << "\n";
	for (int i = 0; i < pattern->Time_Pieces_.size(); i++) {
		pattern->Time_Pieces_[i]->SaveTimePiece(&pattern_file);
	}
	pattern_file.close();
}

Pattern* SaveAndLoadPatterns::LoadPattern(std::string filename)
{
    //Initiate the pattern to be loaded.
    Pattern* pattern = new Pattern("temp");

    // Create an input filestream
    std::ifstream myFile(filename);

    // Make sure the file is open
    if (!myFile.is_open()) throw std::runtime_error("Could not open file");

    // Helper vars
    std::string line, colname;
    std::string val;

    // Read the column names
    if (myFile.good())
    {
        // Extract the first line in the file which should be the name of the pattern.
        // As we already have the name of the pattern, this is not needed and therefore not saved.
        std::getline(myFile, line);
    }

    // Read data, line by line
    while (std::getline(myFile, line))
    {
        // Create a stringstream of the current line
        std::stringstream ss(line);

        std::vector<std::string> results;

        // Extract each integer
        while (std::getline(ss, val, ',')) {
            results.push_back(val);
        }

        if (results[0] == "Time") {
            pattern->AddTimePiece(std::stod(results[1]));
        }
        else {
            pattern->Time_Pieces_.back()->LoadBullet(
                sf::Vector2f(std::stod(results[0]), std::stod(results[1])),
                sf::Vector2f(std::stod(results[2]), std::stod(results[3])),
                sf::Vector2f(std::stod(results[4]), std::stod(results[5])));
        }
    }

    // Close file
    myFile.close();

    std::string name = filename.erase(0, 9);
    name = filename.erase(filename.size() - 4, filename.size() - 1);
    pattern->SetName(name);

	return pattern;
}
