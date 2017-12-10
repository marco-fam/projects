// How to:
// Compile
// g++ -std=c++17 -Wall -Wpedantic -Wextra hardy_rama.cpp -g -o hardy.exe
//  
// What is hardy rama numbers?
//  A speial number which only has two different solutions of two qube numbers added together
//  will produce the result.
//  E.g.
//  2³ + 16³ = 4105 and 9³ + 15³ = 4105

#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <cmath>
#include <tuple>
#include <cstdint>
#include <algorithm>

using namespace std;

typedef tuple<uint64_t, std::pair<uint64_t, uint64_t>, std::pair<uint64_t, uint64_t>> result_tuple_t;

uint64_t calculate(uint64_t base1, uint64_t base2)
{
	return (pow(base1, 3) + pow(base2, 3));
}

int main(const int argc, const char **argv)
{
	vector<uint64_t> harman_numbers{ 1729, 4104, 20683, 39312, 40033, 64232, 65728 };
	vector<result_tuple_t> results_success;
	vector<result_tuple_t> results_failure;
	bool print_not_a_harman_number = true;

	if (argc == 2) {// one number
		harman_numbers.clear();
		harman_numbers.emplace_back(atoi(argv[1]));
	}
	else if (argc == 3) {// rang of numbers  
		print_not_a_harman_number = false;
		uint64_t lower_number = atoi(argv[1]);
		uint64_t upper_number = atoi(argv[2]);
		harman_numbers.clear();
		harman_numbers.resize(upper_number - lower_number + 1);
		std::generate(harman_numbers.begin(), harman_numbers.end(), [&lower_number] {return lower_number++; });
	}

	for (const auto& harman_number : harman_numbers) {
		bool found_first = false;
		bool found_second = false;
		size_t max_base1 = std::cbrt(harman_number / 2) + 1;
		size_t result = 0;
		result_tuple_t tmp = std::make_tuple(harman_number, std::make_pair<size_t, size_t>(0, 0), std::make_pair<size_t, size_t>(0, 0));
		for (size_t base1 = 1; base1 != max_base1; ++base1) {
			for (size_t base2 = 1; !found_first || !found_second; ++base2) {
				result = calculate(base1, base2);
				if (result == harman_number) {
					if (!found_first) {
						std::get<1>(tmp) = std::make_pair(base1, base2);
						found_first = true;
					}
					else if (!found_second) {
						std::get<2>(tmp) = std::make_pair(base1, base2);
						found_second = true;
						results_success.emplace_back(tmp);
					}
				}
				else if (result > harman_number) {
					break;
				}
			}

		}
		if (!found_first && !found_second) {
			results_failure.emplace_back(tmp);
		}
	}

	for (auto res : results_success) {
		cout << "Harman Number: " << get<0>(res) << " = " << get<1>(res).first << "^3 + " << get<1>(res).second << "^3" << \
			" = " << get<2>(res).first << "^3 + " << get<2>(res).second << "^3" << endl;
	}

	if (print_not_a_harman_number) {
		for (auto res : results_failure) {
			cout << "Not Harman Number: " << get<0>(res) << endl;
		}
	}
}
