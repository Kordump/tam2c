#ifndef TAM2C_GUARD_TAMOP_HPP
#define TAM2C_GUARD_TAMOP_HPP

#include "tam2c.hpp"
#include "tam_generic.hpp"

namespace tam2c
{
    using namespace pegtl::alphabet;

    // Implemented

    // Working on...
    struct subr;

    // NOT implemented.
    struct store  : op_name<S, T, O, R, E>,    op_args<int, int, int> { };
    struct load   : op_name<L, O, A, D>,       op_args<int, int, int> { };
    struct pop    : op_name<P, O, P>,          op_args<int, int>      { };
    struct push   : op_name<P, U, S, H>,       op_args<int>           { };
    struct storei : op_name<S, T, O, R, E, I>, op_args<int>           { };
    struct loadi  : op_name<L, O, A, D, I>,    op_args<int>           { };
    struct loadl  : op_name<L, O, A, D, L>,    op_args<int>           { };
    struct halt   : op_name<H, A, L, T>,       op_args<>              { };
    struct jump   : op_name<J, U, M, P>,       op_args<char[]>        { };
    struct jumpif : op_name<J, U, M, P, I, F>, op_args<int, char[]>   { };

    // SUBR op
    struct subr : op_name<S, U, B, R>, op_args<char[]>
    {
        template<size_t t_code> struct op { };
        static constexpr auto invalid = "_subr_invalid";

        template<size_t t_code = 0>
        struct match
        {
            static std::string name(std::string of_this)
            {
                if(of_this == subr::op<t_code>::name)
                    return subr::op<t_code>::name;

                return match<t_code + 1>::name(of_this);
            };
        };
    };
}

#include "tam_subr.hpp"

#endif
