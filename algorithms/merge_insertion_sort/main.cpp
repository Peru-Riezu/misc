/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: main.cpp                                                       */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2024/01/11 11:46:07                                            */
/*   Updated:  2024/01/12 16:12:36                                            */
/*                                                                            */
/* ************************************************************************** */

#include "misort.hpp"
#include "test_functions.hpp"
#include <deque>
#include <functional>
#include <iostream>
#include <list>
#include <vector>

;
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpragmas"
#pragma GCC diagnostic warning "-Weverything"
#pragma GCC diagnostic ignored "-Wempty-translation-unit"
#pragma GCC diagnostic ignored "-Wunused-macros"
#pragma GCC diagnostic ignored "-Wextra-semi"
;



int main(void)
{
	std::vector<int> v;
	std::list<int>	 l;
	std::deque<int>	 dq;

	random_initialization(v);
	time_internal(misort<std::vector<int>::iterator, bool (int x, int y)>, v.begin(), v.end(), compare, "std::vector");
	random_initialization(l);
	time_internal(misort<std::list<int>::iterator, bool (int x, int y)>, l.begin(), l.end(), compare, "std::list");
	random_initialization(dq);
	time_internal(misort<std::deque<int>::iterator, bool (int x, int y)>, dq.begin(), dq.end(), compare, "std::deque");
}

#pragma GCC diagnostic pop
