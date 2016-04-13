#ifndef TAM2C_GUARD_TAM2C_HPP
#define TAM2C_GUARD_TAM2C_HPP

#include <string>
#include <memory>
#include "PEGTL/pegtl.hh"
#include "PEGTL/pegtl/contrib/alphabet.hh"

namespace tam2c
{
    using int_type = size_t;
    template<typename t_op>
        struct op
        { std::string label; };
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
        struct inst_name
            : sor<
                string<P, U, S, H>,
                string<P, O, P>,
                string<L, O, A, D, L>,
                string<L, O, A, D, A>,
                string<L, O, A, D, I>,
                string<L, O, A, D>,
                string<S, T, O, R, E, I>,
                string<S, T, O, R, E>,
                string<J, U, M, P, I, F>,
                string<J, U, M, P>,
                string<S, U, B, R>,
                string<H, A, L, T>
              >
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
            std::cout << " [" << in.string() << "] ";
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
