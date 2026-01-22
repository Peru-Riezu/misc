#include <cstddef>
#include <iostream>
#include <string>

class Solution
{
        private:
                static bool size_could_be_zero(std::string::const_iterator pattern_begin, std::string::const_iterator const pattern_end)
                {
                        const size_t    pattern_size = pattern_end - pattern_begin;

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

                static bool     is_match_internal(std::string::const_iterator string_begin, std::string::const_iterator const string_end,
                                                                                std::string::const_iterator pattern_begin, std::string::const_iterator const pattern_end)
                {
                        size_t  string_size = string_end - string_begin;
                        size_t  pattern_size = pattern_end - pattern_begin;


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
                                                if (is_match_internal(string_begin, string_end, pattern_begin + 2, pattern_end) == true)
                                                {
                                                        return (true);
                                                }
                                                if ((*string_begin == *pattern_begin)
                                                        && (is_match_internal(string_begin + 1, string_end, pattern_begin, pattern_end) == true))
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

        static void     simplify_pattern(std::string &pattern)
        {
                for (size_t i  = 0; i + 3 < pattern.size(); i++)
                {
                        if ((pattern[i + 1] == '*') && (pattern[i + 3] == '*'))
                        {
                                if (pattern[i] == '.' || pattern[i + 2] == '.')
                                {
                                        pattern.replace(i, 4, ".*");
                                }
                                else if (pattern[i] == pattern[i + 2])
                                {
                                        pattern.replace(i, 4, std::string({pattern[i], '*'}));
                                }
                        }
                }
        }

        public:
                static bool isMatch(std::string const &string, std::string &pattern)
                {
                        simplify_pattern(pattern);
                        return (is_match_internal(string.begin(), string.end(), pattern.begin(), pattern.end()));
                }
};
