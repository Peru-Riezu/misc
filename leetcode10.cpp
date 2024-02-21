#include <cstddef>
#include <iostream>
#include <string>

class Solution
{
	private:
		static bool size_could_be_zero(std::string::const_iterator pattern_begin, std::string::const_iterator const pattern_end)
		{
			const size_t	pattern_size = pattern_end - pattern_begin;

			if (pattern_size == 0)
			{
				return (true);
			}
			if ((pattern_size % 2) == 1)
			{
				return (false);
			}
			for (; pattern_begin != pattern_end; pattern_begin += 2)
			{
				if (*(pattern_begin + 1) != '*')
				{
					return (false);
				}
			}
			return (true);
		}

		static bool	is_match_internal(std::string::const_iterator string_begin, std::string::const_iterator const string_end,
										std::string::const_iterator pattern_begin, std::string::const_iterator const pattern_end)
		{
			size_t	string_size = string_end - string_begin;
			size_t	pattern_size = pattern_end - pattern_begin;

			
			while ((pattern_size != 0) && (string_size != 0))
			{
				if (*pattern_begin == '.')
				{
					if ((pattern_size > 1) && (*(pattern_begin + 1) == '*'))
					{
						if ((is_match_internal(string_begin, string_end, pattern_begin + 2, pattern_end) == true)
							||(is_match_internal(string_begin + 1, string_end, pattern_begin, pattern_end) == true))
						{
							return (true);
						}
						string_begin += 1;
						pattern_begin += 2;
					}
					else
					{
						string_begin++;
						pattern_begin++;
					}
				}
				else
				{
					if ((pattern_size > 1) && (*(pattern_begin + 1) == '*'))
					{
						if ((is_match_internal(string_begin, string_end, pattern_begin + 2, pattern_end) == true)
							||(is_match_internal(string_begin + 1, string_end, pattern_begin, pattern_end) == true))
						{
							return (true);
						}
						if (*string_begin != *pattern_begin)
						{
							return (false);
						}
						string_begin += 1;
						pattern_begin += 2;
					}
					else if (*string_begin != *pattern_begin)
					{
						return (false);
					}
					else
					{
						string_begin++;
						pattern_begin++;
					}
				}
				string_size = string_end - string_begin;
				pattern_size = pattern_end - pattern_begin;
			}
			if (string_size != 0)
			{
				return (false);
			}
			if (size_could_be_zero(pattern_begin, pattern_end) == true)
			{
				return (true);
			}
			return (false);
		}

	public:
		static bool isMatch(std::string const &string, std::string const &pattern)
		{
			return (is_match_internal(string.begin(), string.end(), pattern.begin(), pattern.end()));
		}
};

int main(void)
{
	typedef struct s_tests
	{
			std::string string;
			std::string pattern;
			bool        expected;
	} t_tests;

	t_tests test_cases[] = {
		{        .string = std::string("mississippi"),    .pattern = std::string("mis*is*p*."),  .expected = false},
		{       .string = std::string("aa"),      .pattern = std::string("a"), .expected = false},
		{       .string = std::string("aa"),     .pattern = std::string("a*"),  .expected = true},
		{       .string = std::string("ab"),     .pattern = std::string(".*"),  .expected = true},
		{      .string = std::string("aab"),    .pattern = std::string(".*b"),  .expected = true},
		{.string = std::string("baaaaazba"), .pattern = std::string("ba*zba"),  .expected = true},
		{		 .string = std::string(""),      .pattern = std::string("."), .expected = false},
		{   .string = std::string("faalse"),  .pattern = std::string("false"), .expected = false},
		{     .string = std::string("true"),   .pattern = std::string("true"),  .expected = true},
		{     .string = std::string("Null"),   .pattern = std::string("NUll"), .expected = false},
		{        .string = std::string("z"),    .pattern = std::string(".*z"),  .expected = true},
		{        .string = std::string("z"),     .pattern = std::string(".z"), .expected = false}
    };

	for (size_t i = 1; i <= sizeof(test_cases) / sizeof(t_tests); i++)
	{
		if (Solution::isMatch(test_cases[i - 1].string, test_cases[i - 1].pattern) != test_cases[i - 1].expected)
		{
			std::cout << "Test nº" << i << " error:\n\twhit input:\n\t\tstring=" << test_cases[i - 1].string
					  << "\n\t\tpattern=" << test_cases[i - 1].pattern << "\n\t\texpected:" << test_cases[i - 1].expected
					  << " but got:" << !test_cases[i - 1].expected << "\n";
		}
		else
		{
			std::cout << "Test nº" << i << " success\n";
		}
	}
}
