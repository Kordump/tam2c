#ifndef TAM2C_GUARD_TAMOP_GENERIC_HPP
#define TAM2C_GUARD_TAMOP_GENERIC_HPP

#include <tuple>
#include <stdexcept>
#include <initializer_list>
#include "tam2c.hpp"

namespace tam2c
{
    template<typename... t_op>
    struct opcode_details
    {
        template<typename t_this>
        struct wrap
        {
            using grammar = typename t_this::grammar;
        };

        using grammar = std::tuple<typename wrap<t_op>::grammar...>;
        static const size_t cardinal = sizeof...(t_op);

        template<typename t_this>
        struct crtp : t_this, op<crtp<t_this>>
        {
            template<typename t_serial>
            struct to_str;

            template<char... t_serial>
            struct to_str<pegtl::string<t_serial...>>
            {
                static constexpr std::initializer_list<char> value =
                    {t_serial...};
            };

            using type = t_this;
            static constexpr auto name = to_str<typename type::grammar>::value;

        };

        template<size_t t_opcode, typename t_match, typename... t_remaining>
        struct match_details
        {
            static std::unique_ptr<instruction> name(std::string of_this)
            {
                if(pegtl::parse<typename t_match::grammar>(of_this, of_this))
                    return std::make_unique<crtp<t_match>>();

                return
                    match_details<t_opcode - 1, t_remaining...>::name(of_this);
            }
        };

        template<typename t_match, typename... t_remaining>
        struct match_details<1, t_match, t_remaining...>
        {
            static std::unique_ptr<instruction> name(std::string of_this)
            {
                if(pegtl::parse<typename t_match::grammar>(of_this, of_this))
                    return std::make_unique<crtp<t_match>>();

                throw std::invalid_argument(instruction::invalid);
            }
        };

        static std::unique_ptr<instruction> match(std::string name)
        {
            return match_details<cardinal, t_op...>::name(name);
        };
    };
}

#endif
