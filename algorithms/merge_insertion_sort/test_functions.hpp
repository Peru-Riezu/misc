/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: test_functions.hpp                                             */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2024/01/12 15:45:33                                            */
/*   Updated:  2024/01/12 16:19:02                                            */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <cstddef>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <iterator>
#include <string>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

static size_t g_count = 0;

inline bool	  compare(int x, int y)
{
	g_count++;
	return (x < y);
}

template<typename container_type>
void random_initialization(container_type &c)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	// NOLINTNEXTLINE
	srand(tv.tv_usec);
	// NOLINTNEXTLINE
	std::size_t size = (rand() % 2998) + 2;

	for (size_t i = 0; i < size; i++)
	{
		// NOLINTNEXTLINE
		c.push_back(rand());
	}
}

template<typename function_type, typename iterator, typename compare_function_type>
void time_internal(function_type f, iterator b, iterator e, compare_function_type cmp, std::string const &name)
{
	struct timeval tvo;
	struct timeval tvd;
	struct timeval tvr;

	g_count = 0;
	gettimeofday(&tvo, NULL);
	f(b, e, cmp);
	gettimeofday(&tvd, NULL);
	timersub(&tvd, &tvo, &tvr);
	std::cout << "time to sort " << std::distance(b, e) << " numbers, contained in a " << name << " "
			  << std::fixed << tvr.tv_sec + (tvr.tv_usec) / 1000000.0L << "us and " << g_count << " comparasons\n";
}
