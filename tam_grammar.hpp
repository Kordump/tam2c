#ifndef TAM2C_GUARD_TAM_GRAMMAR_HPP
#define TAM2C_GUARD_TAM_GRAMMAR_HPP

#include <tuple>
#include "PEGTL/pegtl.hh"
#include "PEGTL/pegtl/contrib/alphabet.hh"

#include "tam2c.hpp"
#include "tam_generic.hpp"

namespace tam2c
{
    namespace grammar
    {
        // Grammar to parse **one line** of TAM
        using namespace pegtl;

        // Match a rule, then trigger it.
        template<typename... t_rule>
        struct if_must_at :
            if_must<at<t_rule...>, t_rule...>
            { };

        // Ensure that nothing is going on until eolf or comment.
        struct toend :
            at<sor<
                until<eolf, space>,
                until<plus<one<';'>>, space>
                >>
            { };

        // Matching ';' implies consuming tokens until end.
        struct comment
            : pad<if_must<plus<one<';'>>, until<at<eolf>>>, space>
            { };

        // Match a decimal number, positive or negative.
        struct number
            : seq<opt<one<'-'>>, plus<digit>>
            { };

        // Match a label.
        struct label
            : identifier
            { };

        // Match a string, quoted by t_quote.
        template<char t_quote>
        struct tam_string
            : star<
                sor<
                    if_must<one<'\\'>, one<'\"', '\'', '\\', 'n'>>,
                    not_one<t_quote>>
              >
            { };

        // Extract stored grammar pack, details.
        template<typename... t_grammar>
        struct inst_name_details;

        // (Extract stored grammar pack, details)
        template<typename... t_grammar>
        struct inst_name_details<std::tuple<t_grammar...>>
            : sor<t_grammar...>
            { };

        // Match legal instruction name.
        struct inst_name
            : inst_name_details<opcode::grammar>
            { };

        // Match legal register name.
        struct register_name
            : inst_name_details<registers::grammar>
            { };

        // Match legal subroutines name.
        struct subroutine_name
            : inst_name_details<subroutines::grammar>
            { };

        // Match numbers wrapped in their syntax. (raw, (raw))
        struct atomic_number
            : sor<
                if_must_at<number>,
                if_must_at<one<'('>, number, one<')'>>>
            { };

        // Match registers wrapped in their syntax. (raw, (raw), raw[raw])
        struct atomic_register
            : sor<
                if_must_at<register_name>,
                if_must_at<one<'('>, register_name, one<')'>>,
                if_must_at<number, one<'['>, register_name, one<']'>>,
                if_must_at<register_name, one<'['>, number, one<']'>>,
                if_must_at<register_name, one<'['>, register_name, one<']'>>>
            { };

        // Match labels wrapped in string semantics. (#raw, raw, raw:)
        struct atomic_label
            : if_must_at<opt<one<'#'>>, label, opt<one<':'>>>
            { };

        // Match t_quote-quoted strings.
        template<char t_quote>
        struct atomic_string_quoted
            : seq<
                one<t_quote>,
                tam_string<t_quote>,
                one<t_quote>>
            { };

        // Match const strings.
        struct atomic_string
            : sor<
                atomic_string_quoted<'\"'>,
                atomic_string_quoted<'\''>
              >
            { };

        // Match subroutines.
        struct atomic_subroutine
            : if_must_at<subroutine_name, toend>
            { };

        // Match the generic structure of a TAM instruction.
        struct inst_generic
            : if_must<
                at<inst_name, sor<toend, star<space>>>,
                inst_name,
                rep_opt<2, pad<
                    sor<
                        atomic_register,
                        atomic_number,
                        atomic_subroutine,
                        atomic_string,
                        atomic_label>,
                    space>>>
            { };

        // Proxy label for convenience
        struct add_label
            : disable<label>
            { };

        // Proxy label for convenience, emitting warnings.
        struct add_label_weak
            : add_label
            { };

        // Match a label definition.
        struct define_label
            : sor<
                if_must_at<
                    not_at<inst_name>,
                    add_label,
                    one<':'>>,
                if_must_at<
                    not_at<inst_name>,
                    add_label_weak>
                >
            { };

        // Match an instruction, a label definition, or the combination.
        struct inst
            : pad<sor<
                if_must_at<define_label, star<space>, inst_generic>,
                if_must_at<inst_generic, toend>,
                if_must_at<define_label, toend>
                >, space>
            { } ;

        // Match a line, empty, commented, or the combination.
        struct line
            : must<
                sor<
                    seq<inst, opt<comment>>,
                    comment,
                    star<space>
                >, until<eolf, space>
              >
            { };
    }
}

#endif
