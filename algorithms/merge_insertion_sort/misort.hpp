/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: misort.hpp                                                     */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2024/01/11 11:48:15                                            */
/*   Updated:  2024/01/12 15:40:37                                            */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <climits>
#include <cstddef>
#include <iterator>
#include <sys/types.h>
#include <vector>

template<typename iterator_type>
void do_moves(iterator_type begin, iterator_type end, std::vector<std::size_t> moves)
{
	std::vector<typename std::iterator_traits<iterator_type>::value_type> v(begin, end);
	std::vector<std::size_t>::iterator									  it;

	for (it = moves.begin(); it != moves.end(); it = std::next(it))
	{
		*begin = v[*it];
		begin = std::next(begin);
	}
}

template<typename iterator_type, typename compare_function>
void set_up(iterator_type begin, iterator_type end, compare_function cmpr, std::vector<size_t> &moves,
			std::vector<size_t> &b_index, std::vector<typename std::iterator_traits<iterator_type>::value_type> &a,
			std::vector<typename std::iterator_traits<iterator_type>::value_type> &b)
{
	typename std::vector<typename std::iterator_traits<iterator_type>::value_type>::iterator a_it = a.begin();
	typename std::vector<typename std::iterator_traits<iterator_type>::value_type>::iterator b_it = b.begin();
	std::vector<size_t>::iterator															 moves_it = moves.begin();
	std::vector<size_t>::iterator b_indx_it = b_index.begin();

	for (ssize_t i = 0; i < std::distance(begin, end) / 2; i++)
	{
		if (cmpr(*std::next(begin, i * 2), *std::next(begin, i * 2 + 1)) == true)
		{
			*a_it = *std::next(begin, i * 2);
			*b_it = *std::next(begin, i * 2 + 1);
			*b_indx_it = static_cast<size_t>(i * 2 + 1);
			*moves_it = static_cast<size_t>(i * 2);
		}
		else
		{
			*a_it = *std::next(begin, i * 2 + 1);
			*b_it = *std::next(begin, i * 2);
			*b_indx_it = static_cast<size_t>(i * 2);
			*moves_it = static_cast<size_t>(i * 2 + 1);
		}
		a_it = std::next(a_it);
		b_it = std::next(b_it);
		b_indx_it = std::next(b_indx_it);
		moves_it = std::next(moves_it);
	}
	if (std::distance(begin, end) % 2 == 1)
	{
		*b_it = *std::next(end, -1);
		*b_indx_it = std::distance(begin, end) - 1;
	}
}

template<typename iterator_type>
void insert_first(std::vector<typename std::iterator_traits<iterator_type>::value_type> &a,
				  std::vector<typename std::iterator_traits<iterator_type>::value_type> &b, std::vector<size_t> &moves)
{
	a.insert(a.begin(), b[0]);
	if (moves[0] % 2 == 1)
	{
		moves.insert(moves.begin(), moves[0] - 1);
	}
	else
	{
		moves.insert(moves.begin(), moves[0] + 1);
	}
}

inline ssize_t jacobsthal_diff(size_t i, size_t j)
{
	ssize_t jacobsthal_diff_arr[][2] = {
		{				  1,				   2},
		{				  3,				   4},
		{				  5,				  11},
		{				 12,				  23},
		{				 24,				  50},
		{				 51,				 102},
		{				103,				 209},
		{				210,				 421},
		{				422,				 848},
		{				849,				1700},
		{			   1701,				3407},
		{			   3408,				6819},
		{			   6820,			   13646},
		{			  13647,				27298},
		{			  27299,				54605},
		{			  54606,				109217},
		{			 109218,				 218444},
		{			 218445,				 436896},
		{			 436897,				 873803},
		{			 873804,			 1747615},
		{			1747616,			  3495242},
		{			3495243,			  6990494},
		{			6990495,			  13981001},
		{		   13981002,			   27962013},
		{		   27962014,			   55924040},
		{		   55924041,		   111848092},
		{		  111848093,			223696199},
		{		  223696200,			447392411},
		{		  447392412,			894784838},
		{		  894784839,			1789569690},
		{		 1789569691,			 3579139397},
		{		 3579139398,			 7158278809},
		{		 7158278810,		 14316557636},
		{		 14316557637,		  28633115288},
		{		 28633115289,		  57266230595},
		{		 57266230596,		  114532461207},
		{		 114532461208,		   229064922434},
		{		 229064922435,		   458129844886},
		{		 458129844887,		   916259689793},
		{		 916259689794,	   1832519379605},
		{		 1832519379606,		3665038759232},
		{		 3665038759233,		7330077518484},
		{		 7330077518485,		14660155036991},
		{	 14660155036992,		 29320310074003},
		{	 29320310074004,		 58640620148030},
		{	 58640620148031,	 117281240296082},
		{	 117281240296083,	  234562480592189},
		{	 234562480592190,	  469124961184401},
		{	 469124961184402,	  938249922368828},
		{	 938249922368829,	  1876499844737680},
		{	 1876499844737681,	   3752999689475387},
		{	 3752999689475388,	   7505999378950799},
		{	 7505999378950800,   15011998757901626},
		{	 15011998757901627,	30023997515803278},
		{	 30023997515803279,	60047995031606585},
		{	 60047995031606586,	120095990063213197},
		{ 120095990063213198,	 240191980126426424},
		{ 240191980126426425,	 480383960252852876},
		{ 480383960252852877,	 960767920505705783},
		{ 960767920505705784, 1921535841011411595},
		{1921535841011411596, 3843071682022823222},
		{3843071682022823223, 7686143364045646474},
		{7686143364045646475,			  SSIZE_MAX}
	};

	return (jacobsthal_diff_arr[i][j]);
}

template<typename iterator_type, typename compare_function>
void insert(std::vector<size_t> &moves, std::vector<size_t> &a_paring_index,
			std::vector<typename std::iterator_traits<iterator_type>::value_type> &a,
			typename std::iterator_traits<iterator_type>::value_type val, size_t pos, size_t index,
			compare_function cmpr)
{
	ssize_t max_index;
	ssize_t min_index = 0;
	ssize_t curr_index = 0;

	if (pos == a_paring_index.size())
	{
		max_index = a.size() - 1;
	}
	else
	{
		max_index = static_cast<ssize_t>((pos + a_paring_index[pos] - 1));
	}
	curr_index = ((min_index + max_index) / 2);
	while (min_index < max_index)
	{
		if (cmpr(a[curr_index], val) == true)
		{
			max_index = curr_index - 1;
		}
		else
		{
			min_index = curr_index + 1;
		}
		curr_index = ((min_index + max_index) / 2);
	}
	if (cmpr(val, a[curr_index]) == true)
	{
		curr_index++;
	}
	a.insert(std::next(a.begin(), curr_index), val);
	moves.insert(std::next(moves.begin(), static_cast<long>(curr_index)), index);
	for (size_t i = 0; i < a_paring_index.size(); i++)
	{
		if (i + a_paring_index[i] >= static_cast<size_t>(curr_index))
		{
			a_paring_index[i]++;
		}
	}
}

template<typename iterator_type, typename compare_function>
std::vector<std::size_t> get_moves_misort(iterator_type begin, iterator_type end, compare_function cmpr)
{
	std::vector<typename std::iterator_traits<iterator_type>::value_type> a(std::distance(begin, end) / 2);
	std::vector<size_t>													  moves(a.size());
	std::vector<size_t>													  recursive_moves(a.size());
	std::vector<size_t>													  a_paring_index(a.size(), 1);
	std::vector<typename std::iterator_traits<iterator_type>::value_type> b(a.size() + std::distance(begin, end) % 2);
	std::vector<size_t>													  b_index(b.size());

	if (std::distance(begin, end) < 2)
	{
		return (std::vector<size_t>(0));
	}
	set_up(begin, end, cmpr, moves, b_index, a, b);
	recursive_moves = get_moves_misort(a.begin(), a.end(), cmpr);
	do_moves(moves.begin(), moves.end(), recursive_moves);
	do_moves(a.begin(), a.end(), recursive_moves);
	do_moves(b.begin(), b.end(), recursive_moves);
	do_moves(b_index.begin(), b_index.end(), recursive_moves);
	a.reserve(std::distance(begin, end));
	moves.reserve(std::distance(begin, end));
	insert_first<iterator_type>(a, b, moves);
	for (size_t i = 0; true; i++)
	{
		ssize_t curr = std::min(static_cast<size_t>(jacobsthal_diff(i, 1)), b.size() - 1);
		ssize_t prev = jacobsthal_diff(i, 0);

		for (; curr >= prev; curr--)
		{
			insert<iterator_type, compare_function>(moves, a_paring_index, a, b[curr], curr, b_index[curr], cmpr);
		}
		if (static_cast<size_t>(jacobsthal_diff(i, 1)) >= b.size())
		{
			break;
		}
	}
	return (moves);
}

template<typename iterator_type, typename compare_function>
void misort(iterator_type begin, iterator_type end, compare_function cmpr)
{
	do_moves(begin, end, get_moves_misort(begin, end, cmpr));
}
