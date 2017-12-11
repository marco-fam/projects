// How to:
// Compile
// g++ -std=c++17 -Wall -Wpedantic -Wextra math_tables.cpp -g -o math_tables.exe
//  

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <stdexcept>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

namespace {

const string matrix("matrix");
const string single("single");

string program_name(string program_name)
{
    size_t pos = program_name.find_last_of("\\/");
    program_name = (pos == string::npos) ? program_name : program_name.substr(pos+1);
    return program_name;
} 

void help(const string & full_program_name)
{
    cout << program_name(full_program_name) << " matrix 20 20, will print a matrix like math table of 20 x 20" << endl; 
    cout << program_name(full_program_name) << " single 20 10, will print a tables as individual rows of tables 20 with 10 numbers" << endl; 
}



auto parse_args(const int argc, const char **argv)
{
    if(argc == 1) {
        throw std::invalid_argument("Too few arguments!");
    } else if (argc == 2){
        if (string(argv[1]).compare(matrix) == 0) {
            return make_tuple(matrix,10,10);
        } else if (string(argv[1]).compare(single) == 0) {
            return make_tuple(single,10,10);
        } else {
            throw std::invalid_argument("Illegal matrix or single argument!");
        }
    }
    return make_tuple(string("illegal"),0,0);
}

void print_tables(const tuple<string,int,int> & table_layout)
{
    string layout = get<string>(table_layout);
    int rows = get<1>(table_layout);
    int cols = get<2>(table_layout);
    
    cout << "  ";
    for (int i = 1 ;i <= cols; ++i) {
        cout << i << " ";
    }

    for (int i = 1; i <= rows; ++i) {
        cout << endl << i << " ";
        for (int j = 1; j <= cols ; ++j) {
            cout << i*j << " ";
        }
    }
}

} // end unnamed namespace

int main(const int argc, const char **argv)
{
    try {
        // parse the arguments and collect results in tuple    
        auto table_layout = parse_args(argc, argv);

        // infor user
        cout << "Layout: " << get<string>(table_layout) << ", Rows: " << get<1>(table_layout) << ", Tables: " << get<2>(table_layout) << endl;

        // print the table layout depending on user input
        print_tables(table_layout);

    } catch (const std::exception& e) {
        cout << e.what() << endl;    
        help(argv[0]);
    }
}
