#pragma once

#ifndef BOOST_ALGORITHM_DETAIL_FOREACH_HPP
#define BOOST_ALGORITHM_DETAIL_FOREACH_HPP

namespace boost { namespace algorithm { namespace detail {

	template<class Iterator> 
	inline typename std::iterator_traits<Iterator>::iterator_category iterator_category() {	
		return std::iterator_traits<Iterator>::iterator_category();
	}

	template<class ForwardIterator>
	ForwardIterator prev_if_bidirectional_iterator(const ForwardIterator& i, const std::bidirectional_iterator_tag&) {return prev(i);}

	template<class ForwardIterator>
	ForwardIterator prev_if_bidirectional_iterator(const ForwardIterator& i, const std::forward_iterator_tag&) {return i;}

	template<class ForwardIterator>
	ForwardIterator prev_if_bidirectional_iterator(const ForwardIterator& i){
		return prev_if_bidirectional_iterator(i, iterator_category<ForwardIterator>());
	}

	template <class InputIterator, class F>
	void for_each_iterator(InputIterator begin, InputIterator end, F f) {
		for ( ; begin != end; ++begin )
			f(const_cast<const InputIterator&>(begin));
	}

#if 0 // std::for_each is preffered
	template <class InputIterator, class F>
	void for_each(InputIterator begin, InputIterator end, F f) {
		for_each_iterator(begin, end, [&f](InputIterator i){ f(*i); });
	}
#endif

	template <class ForwardIterator, class F>
	void for_each_pair_iterator(ForwardIterator begin, ForwardIterator end, F f) {
		if (begin == end) return;
		const ForwardIterator before_end = prev_if_bidirectional_iterator(end);
		for_each_iterator(begin, before_end, [&](ForwardIterator i) {
			for_each_iterator(std::next(i), end, [&](ForwardIterator j) { f(i, j); });
		});
	}

	template <class ForwardIterator, class F>
	void for_each_triple_iterator(ForwardIterator begin, ForwardIterator end, F f) {
		if (begin == end) return;
		const ForwardIterator before_end = prev_if_bidirectional_iterator(end);
		for_each_pair_iterator(begin, before_end, [&](ForwardIterator i, ForwardIterator j) {
			for_each_iterator(std::next(j), end, [&](ForwardIterator k) { f(i, j, k); });
		});
	}

	template <class ForwardIterator, class F>
	void for_each_quad_iterator(ForwardIterator begin, ForwardIterator end, F f) {
		if (begin == end) return;
		const ForwardIterator before_end = prev_if_bidirectional_iterator(end);
		for_each_triple_iterator(begin, before_end, [&](ForwardIterator i, ForwardIterator j, ForwardIterator k) {
			for_each_iterator(std::next(k), end, [&](ForwardIterator l) { f(i, j, k, l); });
		});
	}

	template <class InputIterator, class F>
	InputIterator find_if_iterator(InputIterator begin, InputIterator end, F f) {
		for (; begin != end; ++begin)
			if (f(begin)) 
				break;
		return begin;
	}

	template <class ForwardIterator, class F>
	std::pair<ForwardIterator, ForwardIterator> find_pair_if_iterator(ForwardIterator begin, ForwardIterator end, F f) {
		ForwardIterator i0 = end, i1 = end;
		if (begin != end) {
			const ForwardIterator before_end = prev_if_bidirectional_iterator(end);
			i0 = find_if_iterator(begin, before_end, [&](ForwardIterator i) -> bool {
				i1 = find_if_iterator(next(i), end, [&](ForwardIterator j){
					return f(i, j);
				});
				return end != i1;
			});
		}
		return std::make_pair(i0, i1);
	}

	template <class ForwardIterator, class F>
	std::tuple<ForwardIterator, ForwardIterator, ForwardIterator> find_triple_if_iterator(ForwardIterator begin, ForwardIterator end, F f) {
		ForwardIterator i0 = end, i1 = end, i2 = end;
		if (begin != end) {
			const ForwardIterator before_end = prev_if_bidirectional_iterator(end);
			i0 = find_if_iterator(begin, before_end, [&](ForwardIterator i) -> bool {
				std::tie(i1, i2) = find_pair_if_iterator(next(i), end, [&](ForwardIterator j, ForwardIterator k){
					return f(i, j, k);
				});
				return end != i2;
			});
		}
		return std::make_tuple(i0, i1, i2);
	}

	template <class ForwardIterator, class F>
	std::tuple<ForwardIterator, ForwardIterator, ForwardIterator, ForwardIterator> find_quad_if_iterator(ForwardIterator begin, ForwardIterator end, F f) {
		ForwardIterator i0 = end, i1 = end, i2 = end, i3 = end;
		if (begin != end) {
			const ForwardIterator before_end = prev_if_bidirectional_iterator(end);
			i0 = find_if_iterator(begin, before_end, [&](ForwardIterator i) -> bool {
				std::tie(i1, i2, i3) = find_triple_if_iterator(next(i), end, [&](ForwardIterator j, ForwardIterator k, ForwardIterator l){
					return f(i, j, k, l);
				});
				return end != i3;
			});
		}
		return std::make_tuple(i0, i1, i2, i3);
	}

}}} // namespace boost { namespace algorithm { namespace detail {

#endif // BOOST_ALGORITHM_DETAIL_FOREACH_HPP
