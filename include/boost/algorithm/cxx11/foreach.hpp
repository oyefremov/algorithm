#pragma once

#include <tuple>
#include <iterator>
#include "detail/foreach.hpp"

namespace boost { namespace algorithm { 

	template <class ForwardIterator, class F>
	void for_each_pair(ForwardIterator begin, ForwardIterator end, F f) {
		detail::for_each_pair_iterator(begin, end, [&f](ForwardIterator i, ForwardIterator j) { f(*i, *j); });
	}

	template <class ForwardIterator, class F>
	void for_each_triple(ForwardIterator begin, ForwardIterator end, F f) {
		detail::for_each_triple_iterator(begin, end, [&f](ForwardIterator i, ForwardIterator j, ForwardIterator k) { f(*i, *j, *k); });
	}

	template <class ForwardIterator, class F>
	void for_each_quad(ForwardIterator begin, ForwardIterator end, F f) {
		detail::for_each_quad_iterator(begin, end, [&f](ForwardIterator i, ForwardIterator j, ForwardIterator k, ForwardIterator l) { f(*i, *j, *k, *l); });
	}

	template <class ForwardIterator, class F, class result_t>
	result_t count_pair_if(ForwardIterator begin, ForwardIterator end, F f) {
		result_t result = 0;
		for_each_pair(begin, end, [&f](const ForwardIterator::value_type& i, const ForwardIterator::value_type& j) { 
			if (f(i, j))
				++result; 
		});
		return result;
	}
		
	template <class ForwardIterator, class F, class result_t>
	result_t count_triple_if(ForwardIterator begin, ForwardIterator end, F f) {
		result_t result = 0;
		for_each_triple(begin, end, [&](const ForwardIterator::value_type& i, const ForwardIterator::value_type& j, const ForwardIterator::value_type& k) {
			if (f(i, j, k))
				++result;
		});
		return result;
	}
		
	template <class ForwardIterator, class F, class result_t>
	result_t count_quad_if(ForwardIterator begin, ForwardIterator end, F f) {
		result_t result = 0;
		for_each_quad(begin, end, [&](const ForwardIterator::value_type& i, const ForwardIterator::value_type& j, const ForwardIterator::value_type& k, const ForwardIterator::value_type& l) {
			if (f(i, j, k, l))
				++result;
		});
		return result;
	}
	
	template <class ForwardIterator, class F>
	std::pair<ForwardIterator, ForwardIterator> find_pair_if(ForwardIterator begin, ForwardIterator end, F f) {
		return detail::find_pair_if_iterator(begin, end, [&f](ForwardIterator i0, ForwardIterator i1){ 
			return f(*i0, *i1); 
		});
	}

	template <class ForwardIterator, class F>
	std::tuple<ForwardIterator, ForwardIterator, ForwardIterator> find_triple_if(ForwardIterator begin, ForwardIterator end, F f) {
		return detail::find_triple_if_iterator(begin, end, [&f](ForwardIterator i0, ForwardIterator i1, ForwardIterator i2){ 
			return f(*i0, *i1, *i2); 
		});
	}

	template <class ForwardIterator, class F>
	std::tuple<ForwardIterator, ForwardIterator, ForwardIterator, ForwardIterator> find_quad_if(ForwardIterator begin, ForwardIterator end, F f) {
		return detail::find_triple_if_iterator(begin, end, [&f](ForwardIterator i0, ForwardIterator i1, ForwardIterator i2, ForwardIterator i3){ 
			return f(*i0, *i1, *i2, *i3); 
		});
	}
}} // namespace boost { namespace algorithm { 