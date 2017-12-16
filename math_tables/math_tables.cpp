// How to:
// Compile
// g++ -std=c++17 -Wall -Wpedantic -Wextra math_tables.cpp -g -o math_tables.exe
//  

#include <cmath>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>
#include <tuple>


using namespace std;

namespace {

const string matrix("matrix");
const string single("single");

/// removes the program name from the path.
/// return program_name as string
string program_name(string program_name)
{
    size_t pos = program_name.find_last_of("\\/");
    program_name = (pos == string::npos) ? program_name : program_name.substr(pos+1);
    return program_name;
} 

/// Outputs the help in case of invalid input arguments
void help(const string & full_program_name)
{
    cout << program_name(full_program_name) << " matrix 20 20, will print a matrix like math table of 20 x 20" << endl; 
    cout << program_name(full_program_name) << " single 20 10, will print a tables as individual rows of tables 20 with 10 numbers" << endl; 
}

/// Based on command line inputs the program options are transformed 
/// into a tuple<string, int, int> = (table_layout, rows, cols)
/// return tuple<string, int, int>
auto make_tuple_from_args(string table_selection, int rows, int cols)
{
    if (table_selection.compare(matrix) == 0) {
        return make_tuple(matrix, rows, cols);
    } else if (table_selection.compare(single) == 0) {
        return make_tuple(single, rows, cols);
    } else {
        throw std::invalid_argument("Illegal matrix or single argument!");
    }
}

/// Transforms the arguments based on argc and argv
auto parse_args(const int argc, const char **argv)
{
    if(argc == 1) {
        throw std::invalid_argument("Too few arguments!");
    } else if (argc == 2) {
        return make_tuple_from_args(argv[1], 10, 10);
    } else if (argc == 4) {
        return make_tuple_from_args(argv[1], atoi(argv[2]), atoi(argv[3]));
    } else {
        throw std::invalid_argument("Unsupported number of arguments!");
    }
    return make_tuple_from_args(string("illegal"), 0, 0);
}

/// helper types for selection of print_table template overloads
struct Single_layout{};
struct Matrix_layout{};

/// primary template for print_table. Note not implemented
template <typename T>
void print_table(int rows, int cols, T);

/// function specialization for single_table layout
template <>
void print_table(int rows, int table, Single_layout) 
{
    cout << "--------------"      << endl;
    cout << "   Tabel: " << table << endl;
    cout << "--------------"      << endl;
    for (int i=1; i<=rows;++i) {
        cout << std::setw(3) << i << " x " << table << " = " << std::setw(3) << i*table << endl;
    }  
}

/// function specialization for matrix_table layout
template <>
void print_table(int rows, int cols, Matrix_layout) 
{
    cout << std::setw(4) << " ";
    for (int i = 1 ;i <= cols; ++i) {
        cout << std::setw(3) << i << " ";
    }

    for (int i = 1; i <= rows; ++i) {
        cout << endl << std::setw(3) << i << " ";
        for (int j = 1; j <= cols ; ++j) {
            cout << std::setw(3) << i*j << " ";
        }
    }
}

/// Function for selection of print_table layout. Either matrix or single layout
void print_tables(tuple<string,int,int> const & table_layout)
{
    string layout = get<string>(table_layout);
    int rows = get<1>(table_layout);
    int cols = get<2>(table_layout);

    if (0==layout.compare(matrix)) {
        print_table(rows, cols, Matrix_layout());
    } else if (0==layout.compare(single)) {
        print_table(rows, cols, Single_layout());
    }
}

} // end unnamed namespace

int main(const int argc, const char **argv)
{
    try {
        // parse the arguments and collect results in tuple    
        auto table_layout = parse_args(argc, argv);

        // print the table layout depending on user input
        print_tables(table_layout);

    } catch (const std::exception& e) {
        // indicate exception and call help
        cout << e.what() << endl;    
        help(argv[0]);
    }
}
