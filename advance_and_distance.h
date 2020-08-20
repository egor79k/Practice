#include <iostream>
  //////////////////
 // std::advance //
//////////////////
namespace detail
{

template <typename It>
constexpr void do_advance (It &it, typename std::iterator_traits<It>::difference_type n, std::input_iterator_tag)
{
	while (n > 0)
	{
		--n;
		++it;
	}
}


template <typename It>
constexpr void do_advance (It &it, typename std::iterator_traits<It>::difference_type n, std::bidirectional_iterator_tag)
{
	while (n > 0)
	{
		--n;
		++it;
	}

	while (n < 0)
	{
		++n;
		--it;
	}
}


template <typename It>
constexpr void do_advance (It &it, typename std::iterator_traits<It>::difference_type n, std::random_access_iterator_tag)
{
	it += n;
	return 0;
}

} // namespace detail


template <typename It, typename Distance>
constexpr void advance (It &it, Distance n)
{
	detail::do_advance (it, typename std::iterator_traits<It>::difference_type (n), typename std::iterator_traits<It>::iterator_category ());
}


  ///////////////////
 // std::distance //
///////////////////
namespace detail
{

template <typename It>
constexpr typename std::iterator_traits<It>::difference_type do_distance (It first, It last, std::input_iterator_tag)
{
	typename std::iterator_traits<It>::difference_type n = 0;

	while (first != last)
	{
		++first;
		++n;
	}

	return n;
}


template <typename It>
constexpr typename std::iterator_traits<It>::difference_type do_distance (It first, It last, std::random_access_iterator_tag)
{
	return last - first;
}

} // namespace detail

template <typename It>
constexpr typename std::iterator_traits<It>::difference_type distance (It first, It last)
{
	return detail::do_distance (first, last, typename std::iterator_traits<It>::iterator_category ());
}