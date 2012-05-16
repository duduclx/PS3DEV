//-*-C++-*-
//
// smint_array.h
//
// Store arrays of integers which can potentially be packed into sub-byte-sized bitfields.

#ifndef smint_array_H
#define smint_array_H

#if !defined(assert)
#include <cassert>
#endif

#include <stdint.h>
#include <limits>

#include <boost/integer.hpp>
#include <boost/integer/integer_mask.hpp>
#include <boost/integer/static_log2.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/comparison.hpp>
#include <boost/mpl/less_equal.hpp>
#include <boost/mpl/if.hpp>

template< boost::static_log2_argument_type M, size_t N, typename MaxType = uintmax_t >
struct smint_array
{
public:

  static const size_t size = N;

  static const size_t value_bits = boost::static_log2< M >::value + 1;

  // Total number of bits required:
  static const size_t total_bits = value_bits * size;

  // Maximum number of bits stored in an integer:
  static const size_t max_bits = std::numeric_limits< MaxType >::digits;

  typedef typename boost::uint_t< value_bits >::least value_type;

  // Everything fits into a single integer:
  struct scalar_impl {
    typedef typename boost::uint_t< total_bits >::least word_type;
    static const size_t num_words = 1;

    word_type values[1];
  };

  // 
  struct array_impl {
    typedef MaxType word_type;
    static const size_t num_words = (total_bits / max_bits) + ((total_bits % max_bits) ? 1 : 0);

    word_type values[num_words];
  };

  // If total_bits exceeds max_bits, need an array
  typedef typename boost::mpl::if_< boost::mpl::less_equal< boost::mpl::int_< total_bits >, boost::mpl::int_< max_bits > >, scalar_impl, array_impl >::type impl_type;

  impl_type impl;
  typedef typename impl_type::word_type word_type;
  static const word_type value_mask = boost::low_bits_mask_t< value_bits >::sig_bits;
  static const size_t word_bits = std::numeric_limits< typename impl_type::word_type >::digits;
  static const size_t values_per_word = word_bits / value_bits;
  static const size_t num_words = impl_type::num_words;

  typedef typename boost::uint_value_t< size >::least index_type;
  typedef typename boost::uint_value_t< num_words >::least word_index_type;
  typedef typename boost::uint_value_t< values_per_word >::least value_index_type;

  smint_array() {
    for(word_index_type i = 0;i < num_words;++i) {
      impl.values[i] = 0;
    }
  }

  smint_array(smint_array const & rhs) {
    for(word_index_type i = 0;i < num_words;++i) {
      impl.values[i] = rhs.impl.values[i];
    }
  }

  smint_array & operator =(smint_array const & rhs) {
    for(word_index_type i = 0;i < num_words;++i) {
      impl.values[i] = rhs.impl.values[i];
    }
    return *this;
  }

  inline
  void set(const index_type i,value_type x) {
    assert(i < size);
    const word_index_type ii = i / values_per_word;
    const value_index_type jj = i % values_per_word;
    const size_t shift_bits = jj * value_bits;
    impl.values[ii] = (impl.values[ii] & ~(value_mask << shift_bits)) | (((word_type)x & value_mask) << shift_bits);
  }

  inline
  value_type get(const index_type i) const {
    assert(i < size);
    const word_index_type ii = i / values_per_word;
    const value_index_type jj = i % values_per_word;
    const size_t shift_bits = jj * value_bits;
    return (value_type)((impl.values[ii] >> shift_bits) & value_mask);
  }

  inline
  value_type operator[](const index_type i) const {
    assert(i < size);
    const word_index_type ii = i / values_per_word;
    const value_index_type jj = i % values_per_word;
    const size_t shift_bits = jj * value_bits;
    return (value_type)((impl.values[ii] >> shift_bits) & value_mask);
  }

  template< typename Function >
  static void for_each(smint_array const & array,Function const & fn) {
    index_type j = 0;
    for(word_index_type i = 0;i < num_words && j < size;++i) {
      word_type word = array.impl.values[i];
      for(value_index_type k = 0;k < values_per_word && j < size;++k,++j,word >>= value_bits) {
	fn(j,(value_type)(word & value_mask));
      }
    }
  }

  struct const_iterator {
    word_index_type i;
    index_type j;
    value_index_type k;
    word_type word;

    const_iterator(const word_index_type _i,const index_type _j,const value_index_type _k,const word_type _word)
      : i(_i), j(_j), k(_k), word(_word) {
    }

    index_type index() const {
      return j;
    }

    value_type value() const {
      return (value_type)(word & value_mask);
    }

    void next(smint_array const & array) {
      ++j;
      if(j < size) {
	++k;
	if(k < values_per_word) {
	  word >>= value_bits;
	}
	else {
	  word = array.impl.values[++i];
	  k = 0;
	}
      }
    }

    bool done() const {
      return !(j < size);
    }
  };

  const_iterator begin() const {
    return const_iterator(0,0,0,impl.values[0]);
  }
};

#endif
