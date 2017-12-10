// How to:
// Compile
// g++ -std=c++14 -Wall -Wpedantic -Wextra quiz.cpp -g -o quiz.exe
//  
//

#include <iostream>
#include <string>

using namespace std;

struct Spg {
  string question;
  string s1;
  string s2;
  string s3;
  int correct_answer;
};


Spg quiz_spg[] = 
{
  {"Marco's alder?","30","40","42",3},
  {"Ane's   alder?","30","40","43",3},
};


int main()
{
  int answer  = 0;
  int correct = 0;
  int wrong   = 0;

  for (auto s : quiz_spg) {
    cout << s.question  << endl;
    cout << s.s1  << endl;
    cout << s.s2  << endl;
    cout << s.s3  << endl;
    cout << "Answer 1, 2 or 3: ";
    cin  >> answer;
    
    if (answer == s.correct_answer) {
      ++correct;
    } else {
      ++wrong;
    }
   cout << endl;
  }

  cout << "Correct answers: " << correct << endl;
  cout << "Wrong answers: "   << wrong   << endl;
}


