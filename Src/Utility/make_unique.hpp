#ifndef BOOST_PP_IS_ITERATING

#ifndef GPLUSNASITE_MAKE_UNIQUE_NVT_HPP_INCLUDED
#define GPLUSNASITE_MAKE_UNIQUE_NVT_HPP_INCLUDED

#include <memory>
#include <utility>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/repetition.hpp>

#ifndef GPLUSNASITE_MAKE_UNIQUE_MAX_ARITY
#define GPLUSNASITE_MAKE_UNIQUE_MAX_ARITY 10
#endif

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

#define BOOST_PP_ITERATION_LIMITS (0, GPLUSNASITE_MAKE_UNIQUE_MAX_ARITY - 1)
#define BOOST_PP_FILENAME_1 "make_unique.hpp"
#include BOOST_PP_ITERATE()

}// namespace GooglePlusLibrary
}// namespace Gplusnasite

#endif // GPLUSNASITE_MAKE_UNIQUE_HPP_INCLUDED

#else // BOOST_PP_IS_ITERATING

#define n BOOST_PP_ITERATION()

#define GPLUSNASITE_MAKE_UNIQUE_forward(z, m, data) \
    std::forward<BOOST_PP_CAT(A, m)>(BOOST_PP_CAT(a, m))

template <class T BOOST_PP_ENUM_TRAILING_PARAMS(n, class A)>
inline std::unique_ptr<T> make_unique(BOOST_PP_ENUM_BINARY_PARAMS(n, A, &&a))
{
    return std::unique_ptr<T>(new T(BOOST_PP_ENUM(n, GPLUSNASITE_MAKE_UNIQUE_forward, ~)));
}

#undef GPLUSNASITE_MAKE_UNIQUE_forward
#undef n

#endif // BOOST_PP_IS_ITERATING