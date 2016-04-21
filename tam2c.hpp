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
        std::string label;

        virtual std::string get_ident() = 0;
        virtual ~instruction() = default;
    };

    // Templated operator, use CRTP when specialized.
    template<typename t_op>
    struct op;
}

#include "tamop.hpp"

namespace tam2c
{
    template<typename t_op>
        struct op : instruction
    {
        std::string get_ident()
        {
            return t_op::name;
        };
    };

    // Please order keywords by average frequency and avoid collisions.
    using opcode =
        opcode_details<
            pop,        storei,     loadl,
            push,       store,      loadi,
            jumpif,     subr,       loada,
            jump,       halt,       load
                >;

    // Please order registers by average frequency and avoid collisions.
    using registers =
        opcode_details<
            CP,     CB, CT,
                    PB, PT,
                    SB, ST,
                    HB, HT,
            LB, L1, L2, L3, L4, L5, L6
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
            std::cout << " op[" << inst->get_ident() << "] ";
        }
    };

    template<> struct tam_action<grammar::atomic_label>
    {
        static void apply(const pegtl::input& in, std::string& name)
        {
            std::cout << " +str[" << in.string() << "] ";
        }
    };

    template<> struct tam_action<grammar::number>
    {
        static void apply(const pegtl::input& in, std::string& name)
        {
            std::cout << " +int[" << in.string() << "] ";
        }
    };

    template<> struct tam_action<grammar::register_name>
    {
        static void apply(const pegtl::input& in, std::string& name)
        {
            auto reg = registers::match(in.string());
            std::cout << " +reg[" << reg->get_ident() << "] ";
        }
    };

    template<> struct tam_action<grammar::add_label>
    {
        static void apply(const pegtl::input& in, std::string& name)
        {
            std::cout << " add[" << in.string() << "] ";
        }
    };
}

#endif
