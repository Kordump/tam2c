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
    namespace grammar
    {
        // Grammar to parse **one line** of TAM
        using namespace pegtl;

        // Matching ';' implies consuming tokens until eolf.
        struct comment
            : if_must<one<';'>, until<eolf>>
            { };

        // Match a number, decimal or hexadecimal.
        struct number
            : sor<plus<digit>, seq<string<'0', x>, plus<digit>>>
            { };

        // Match a label, from 1 to 255 alphanumeric chars.
        struct label
            : rep_min_max<1, 255, alpha>
            { };

        // Match numbers wrapped in their syntax. (raw, (raw), raw[raw])
        struct atomic_number
            : sor<
                number,
                seq<one<'('>, number, one<')'>>,
                seq<number, one<'['>, number, one<']'>>>
            { };

        // Match labels wrapped in string semantics. (raw, 'raw', "raw")
        struct atomic_label
            : sor<
                label,
                seq<one<'\"'>, label, one<'\"'>>,
                seq<one<'\''>, label, one<'\''>>>
            { };

        // Match legal instruction names.
        template<typename... t_grammar>
        struct inst_name_details;

        template<typename... t_grammar>
        struct inst_name_details<std::tuple<t_grammar...>>
            : sor<t_grammar...>
            { };

        struct inst_name
            : inst_name_details<opcode::grammar>
            { };

        // Match the generic structure of a TAM instruction.
        struct inst_generic
            : if_must<
                inst_name,
                rep_opt<2, pad<
                    sor<atomic_number, atomic_label>,
                    space>>>
            { };

        // Match a label definition.
        struct define_label
            : pad<
                seq<label, one<':'>>,
                space>
            { };

        // Match an instruction, a label definition, or the combination.
        struct inst
            : sor<
                inst_generic,
                define_label,
                if_must<
                    define_label,
                    pad<inst_generic, space>>>
            { } ;

        // Match a line, empty, commented, or the combination.
        struct line
            : must<
                sor<
                    seq<pad<inst, space>, opt<comment>>,
                    pad<comment, space>,
                    seq<star<space>, eof>>
              >
            { };
    }

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
