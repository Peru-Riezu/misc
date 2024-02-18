/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: leetcode399.cpp                                                */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2024/02/18 02:01:31                                            */
/*   Updated:  2024/02/18 06:42:55                                            */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <map>
#include <set>
#include <string>
#include <sys/_types/_size_t.h>
#include <utility>
#include <vector>

;
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpragmas"
#pragma GCC diagnostic warning "-Weverything"
#pragma GCC diagnostic ignored "-Wempty-translation-unit"
#pragma GCC diagnostic ignored "-Wunused-macros"
#pragma GCC diagnostic ignored "-Wextra-semi"
#pragma GCC diagnostic ignored "-Wc++98-compat"
;

class Solution
{
	private:
		static std::string find_common_variable_in_equivalent_expresion(
			std::map<std::string, std::map<std::string, long double>> const &equivalent_expresions,
			std::vector<std::string> const                                  &query)
		{
			std::map<std::string, std::map<std::string, long double>>::const_iterator it1 =
				equivalent_expresions.find(query[0]);
			std::map<std::string, std::map<std::string, long double>>::const_iterator it2 =
				equivalent_expresions.find(query[1]);

			if (it1 == equivalent_expresions.end() || it2 == equivalent_expresions.end())
			{
				return ("");
			}
			for (std::map<std::string, long double>::const_iterator it = it1->second.begin(); it != it1->second.end();
				 it = std::next(it))
			{
				std::map<std::string, long double>::const_iterator found = it2->second.find(it->first);

				if (found != it2->second.end())
				{
					return (it->first);
				}
			}
			return ("");
		}

		static void give_all_relations_from_to(std::map<std::string, long double> const &from,
											   std::map<std::string, long double> &to, long double factor)
		{
			for (std::pair<std::string const, long double> const &elem : from)
			{
				to[elem.first] = from.at(elem.first) * factor;
			}
		}

		static std::map<std::string, std::map<std::string, long double>>
			get_equivalent_expresions(std::vector<std::vector<std::string>> const &equations,
									  std::vector<double> const                   &values)
		{
			std::map<std::string, std::map<std::string, long double>> equivalent_expresions;

			for (size_t i = 0; i < equations.size(); i++)
			{
				// each variable can be expressed as one time itself
				equivalent_expresions[equations[i][0]][equations[i][0]] = 1;
				equivalent_expresions[equations[i][1]][equations[i][1]] = 1;
				// the dividend can be expressed as the divisor times the result of the division (e.g. x / y = z | x = z
				// * y) therefor all equivalent expressions of the divisor times z are also equivalent expressions of
				// the dividend
				give_all_relations_from_to(equivalent_expresions[equations[i][1]],
										   equivalent_expresions[equations[i][0]], static_cast<long double>(values[i]));
				for (std::pair<std::string const, long double> const &elem : equivalent_expresions[equations[i][0]])
				{
					// as the relationships of the dividend have been updated the relationships of all elements who had
					// a relationships whit it must be upadated but due to how we operate if the dividen has a non
					// reciprocated relationships (this should not happen but it gets corrected latter) we dont update
					// the relationships of that variable
					if (equivalent_expresions.at(elem.first).count(equations[i][0]) == 0)
					{
						continue;
					}
					give_all_relations_from_to(equivalent_expresions[equations[i][0]],
											   equivalent_expresions[elem.first],
											   equivalent_expresions[elem.first][equations[i][0]]);
				}
				// same as above but the divisor can be expressed as the dividend divided by the result of the division
				// (e.g. x / y = z | y = x / z)
				give_all_relations_from_to(equivalent_expresions[equations[i][0]],
										   equivalent_expresions[equations[i][1]],
										   1.0L / static_cast<long double>(values[i]));
				for (std::pair<std::string const, long double> const &elem : equivalent_expresions[equations[i][1]])
				{
					give_all_relations_from_to(equivalent_expresions[equations[i][1]],
											   equivalent_expresions[elem.first],
											   equivalent_expresions[elem.first][equations[i][1]]);
				}
			}
			return (equivalent_expresions);
		}

	public:
		static std::vector<double> calcEquation(std::vector<std::vector<std::string>> const &equations,
												std::vector<double> const                   &values,
												std::vector<std::vector<std::string>> const &queries)
		{
			// equivalent expresion is a map of maps where each variable has a map of other variable on terms of which
			// they can be expressed
			std::map<std::string, std::map<std::string, long double>> equivalent_expresions =
				get_equivalent_expresions(equations, values);
			std::vector<double> results(queries.size());

			for (size_t i = 0; i < queries.size(); i++)
			{
				std::string common_variable =
					find_common_variable_in_equivalent_expresion(equivalent_expresions, queries[i]);

				if (common_variable.empty())
				{
					results[i] = -1;
					continue;
				}
				results[i] = static_cast<double>(equivalent_expresions[queries[i][0]][common_variable] /
												 equivalent_expresions[queries[i][1]][common_variable]);
			}
			return (results);
		}
};

// main for testing
//  NOLINTNEXTLINE
int main(void)
{
	int test_number = 1;

	{
		std::vector<std::vector<std::string>> equations({
			{"a", "b"},
            {"b", "c"}
        });
		std::vector<double>                   values({2.0, 3.0});
		std::vector<std::vector<std::string>> queries({
			{"a", "c"},
            {"b", "a"},
            {"a", "e"},
            {"a", "a"},
            {"x", "x"}
        });
		std::vector<double>                   expected({6.00000, 0.50000, -1.00000, 1.00000, -1.00000});
		std::vector<double>                   output(Solution::calcEquation(equations, values, queries));

		if (output != expected)
		{
			std::cout << "Error in test nº" << test_number << '\n';
			std::cout << "\texpected: {";
			for (size_t i = 0; i < expected.size(); i++)
			{
				std::cout << expected[i];
				if (i != expected.size() - 1)
				{
					std::cout << ", ";
				}
			}
			std::cout << "}\n\tgoten: {";
			for (size_t i = 0; i < output.size(); i++)
			{
				std::cout << output[i];
				if (i != expected.size() - 1)
				{
					std::cout << ", ";
				}
			}
			std::cout << "}\n";
		}
		test_number++;
	}
	{
		std::vector<std::vector<std::string>> equations({
			{ "a",  "b"},
            { "b",  "c"},
            {"bc", "cd"}
        });
		std::vector<double>                   values({1.5, 2.5, 5.0});
		std::vector<std::vector<std::string>> queries({
			{ "a",  "c"},
            { "c",  "b"},
            {"bc", "cd"},
            {"cd", "bc"}
        });
		std::vector<double>                   expected({3.75000, 0.40000, 5.00000, 0.20000});
		std::vector<double>                   output(Solution::calcEquation(equations, values, queries));

		if (output != expected)
		{
			std::cout << "Error in test nº" << test_number << '\n';
			std::cout << "\texpected: {";
			for (size_t i = 0; i < expected.size(); i++)
			{
				std::cout << expected[i];
				if (i != expected.size() - 1)
				{
					std::cout << ", ";
				}
			}
			std::cout << "}\n\tgoten: {";
			for (size_t i = 0; i < output.size(); i++)
			{
				std::cout << output[i];
				if (i != expected.size() - 1)
				{
					std::cout << ", ";
				}
			}
			std::cout << "}\n";
		}
		test_number++;
	}
	{
		std::vector<std::vector<std::string>> equations({
			{"a", "b"}
        });
		std::vector<double>                   values({0.5});
		std::vector<std::vector<std::string>> queries({
			{"a", "b"},
            {"b", "a"},
            {"a", "c"},
            {"x", "y"}
        });
		std::vector<double>                   expected({0.50000, 2.00000, -1.00000, -1.00000});
		std::vector<double>                   output(Solution::calcEquation(equations, values, queries));

		if (output != expected)
		{
			std::cout << "Error in test nº" << test_number << '\n';
			std::cout << "\texpected: {";
			for (size_t i = 0; i < expected.size(); i++)
			{
				std::cout << expected[i];
				if (i != expected.size() - 1)
				{
					std::cout << ", ";
				}
			}
			std::cout << "}\n\tgoten: {";
			for (size_t i = 0; i < output.size(); i++)
			{
				std::cout << output[i];
				if (i != expected.size() - 1)
				{
					std::cout << ", ";
				}
			}
			std::cout << "}\n";
		}
		test_number++;
	}
	{
		std::vector<std::vector<std::string>> equations({
			{"a", "e"},
            {"b", "e"}
        });
		std::vector<double>                   values({4.0, 3.0});
		std::vector<std::vector<std::string>> queries({
			{"a", "b"},
            {"e", "e"},
            {"x", "x"}
        });
		std::vector<double>                   expected({1.33333, 1.00000, -1.00000});
		std::vector<double>                   output(Solution::calcEquation(equations, values, queries));

		if (output != expected)
		{
			std::cout << "Error in test nº" << test_number << '\n';
			std::cout << "\texpected: {";
			for (size_t i = 0; i < expected.size(); i++)
			{
				std::cout << expected[i];
				if (i != expected.size() - 1)
				{
					std::cout << ", ";
				}
			}
			std::cout << "}\n\tgoten: {";
			for (size_t i = 0; i < output.size(); i++)
			{
				std::cout << output[i];
				if (i != expected.size() - 1)
				{
					std::cout << ", ";
				}
			}
			std::cout << "}\n";
		}
		test_number++;
	}
	{
		std::vector<std::vector<std::string>> equations({
			{"x1", "x2"},
            {"x2", "x3"},
            {"x3", "x4"},
            {"x4", "x5"}
        });
		std::vector<double>                   values({3.0, 4.0, 5.0, 6.0});
		std::vector<std::vector<std::string>> queries({
			{"x1", "x5"},
            {"x5", "x2"},
            {"x2", "x4"},
            {"x2", "x2"},
            {"x2", "x9"},
            {"x9", "x9"}
        });
		std::vector<double>                   expected({360.00000, 0.00833, 20.00000, 1.00000, -1.00000, -1.00000});
		std::vector<double>                   output(Solution::calcEquation(equations, values, queries));

		if (output != expected)
		{
			std::cout << "Error in test nº" << test_number << '\n';
			std::cout << "\texpected: {";
			for (size_t i = 0; i < expected.size(); i++)
			{
				std::cout << expected[i];
				if (i != expected.size() - 1)
				{
					std::cout << ", ";
				}
			}
			std::cout << "}\n\tgoten: {";
			for (size_t i = 0; i < output.size(); i++)
			{
				std::cout << output[i];
				if (i != expected.size() - 1)
				{
					std::cout << ", ";
				}
			}
			std::cout << "}\n";
		}
		test_number++;
	}
}

#pragma GCC diagnostic pop
