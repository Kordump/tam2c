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
    struct pop      { using grammar = pegtl::string<P, O, P>;               };
    struct push     { using grammar = pegtl::string<P, U, S, H>;            };
    struct jump     { using grammar = pegtl::string<J, U, M, P>;            };
    struct jumpif   { using grammar = pegtl::string<J, U, M, P, I, F>;      };
    struct store    { using grammar = pegtl::string<S, T, O, R, E>;         };
    struct storei   { using grammar = pegtl::string<S, T, O, R, E, I>;      };
    struct halt     { using grammar = pegtl::string<H, A, L, T>;            };
    struct load     { using grammar = pegtl::string<L, O, A, D>;            };
    struct loadi    { using grammar = pegtl::string<L, O, A, D, I>;         };
    struct loadl    { using grammar = pegtl::string<L, O, A, D, L>;         };

    // SUBR op
    struct subr
    {
        using grammar = pegtl::string<S, U, B, R>;

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
