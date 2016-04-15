#ifndef TAM2C_GUARD_TAM2C_HPP
#define TAM2C_GUARD_TAM2C_HPP

#include <string>
#include <memory>
#include <tuple>
#include "PEGTL/pegtl.hh"
#include "PEGTL/pegtl/contrib/alphabet.hh"

namespace tam2c
{
    // Generic instruction, should be used with polymorphism.
    struct instruction
    {
        struct invalid { static constexpr auto name = "_tamop_invalid"; };

        virtual std::string get_ident() = 0;
        virtual ~instruction() = default;
    };

    // Templated operator, use CRTP when specialized.
    template<typename t_op>
        struct op : public instruction
        {
            static const std::string name;
            std::string label;

            virtual std::string get_ident()
            { return name; };
        };

    template<typename t_op>
        const std::string op<t_op>::name = t_op::name;
}

#include "tamop.hpp"

namespace tam2c
{
    // Please order keywords by average frequency.
    using opcode =
        opcode_details<
            pop,        store,      load,
            push,       storei,     loadi,
            jump,       subr,       loadl,
            jumpif,     halt
                >;
}

#include "tam_grammar.hpp"

namespace tam2c
{
    template<typename t_rule>
        struct tam_action
        : pegtl::nothing<t_rule>
        { };

    template<> struct tam_action<grammar::inst_name>
    {
        static void apply(const pegtl::input& in, std::string& name)
        {
            auto inst = opcode::match(in.string());
            std::cout << " [" << inst->get_ident() << "] ";
        }
    };

    template<> struct tam_action<grammar::label>
    {
        static void apply(const pegtl::input& in, std::string& name)
        {
            std::cout << " [" << in.string() << "] ";
        }
    };

    template<> struct tam_action<grammar::number>
    {
        static void apply(const pegtl::input& in, std::string& name)
        {
            std::cout << " [" << in.string() << "] ";
        }
    };
}

#endif
