#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

string readFileIntoString(string& path) {
    path = "../" + path;
    ifstream input_file(path);
    if (!input_file.is_open()) {
        cerr << "Could not open the file - '"
             << path << "'" << endl;
        exit(EXIT_FAILURE);
    }
    return string((istreambuf_iterator<char>(input_file)), istreambuf_iterator<char>());
}