#ifndef TAM2C_GUARD_TAMOP_HPP
#define TAM2C_GUARD_TAMOP_HPP

#include "tam2c.hpp"
#include "tamop_generic.hpp"

namespace tam2c
{
    // Implemented

    // Working on...
    struct subr;

    // NOT implemented.
    struct pop : op<pop>
    {
        using grammar = pegtl::string<'P', 'O', 'P'>;
        static constexpr auto name = "POP";
    };
    struct push : op<push>
    {
        using grammar = pegtl::string<'P', 'U', 'S', 'H'>;
        static constexpr auto name = "PUSH";
    };
    struct jump : op<jump>
    {
        using grammar = pegtl::string<'J', 'U', 'M', 'P'>;
        static constexpr auto name = "JUMP";
    };
    struct jumpif : op<jumpif>
    {
        using grammar = pegtl::string<'J', 'U', 'M', 'P', 'I', 'F'>;
        static constexpr auto name = "JUMPIF";
    };
    struct store : op<store>
    {
        using grammar = pegtl::string<'S', 'T', 'O', 'R', 'E'>;
        static constexpr auto name = "STORE";
    };
    struct storei : op<storei>
    {
        using grammar = pegtl::string<'S', 'T', 'O', 'R', 'E', 'I'>;
        static constexpr auto name = "STOREI";
    };
    struct halt : op<halt>
    {
        using grammar = pegtl::string<'H', 'A', 'L', 'T'>;
        static constexpr auto name = "HALT";
    };
    struct load : op<load>
    {
        using grammar = pegtl::string<'L', 'O', 'A', 'D'>;
        static constexpr auto name = "LOAD";
    };
    struct loadi : op<loadi>
    {
        using grammar = pegtl::string<'L', 'O', 'A', 'D', 'I'>;
        static constexpr auto name = "LOADI";
    };
    struct loadl : op<loadl>
    {
        using grammar = pegtl::string<'L', 'O', 'A', 'D', 'L'>;
        static constexpr auto name = "LOADL";
    };

    // SUBR op
    struct subr : op<subr>
    {
        using grammar = pegtl::string<'S', 'U', 'B', 'R'>;
        static constexpr auto name = "SUBR";

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
