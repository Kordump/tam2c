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
        struct if_must_at
            : if_must<at<t_rule...>, t_rule...>
            { };

        // Ensure that nothing is going on until eolf or comment.
        struct toend
            : at<sor<
                until<one<';'>, space>,
                until<eolf, space>
                >>
            { };

        // Matching ';' implies consuming tokens until eolf.
        struct comment
            : pad<if_must<one<';'>, until<eolf>>, space>
            { };

        // Match a decimal number, positive or negative.
        struct number
            : seq<opt<one<'-'>>, plus<digit>>
            { };

        // Match a label, from 1 to 255 alphanumeric chars.
        struct label
            : identifier
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

        // Match numbers wrapped in their syntax. (raw, (raw), raw[raw])
        struct atomic_number
            : sor<
                if_must_at<number>,
                if_must_at<one<'('>, number, one<')'>>,
                if_must_at<number, one<'['>, number, one<']'>>>
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

        // Match labels wrapped in string semantics. (raw, 'raw', "raw")
        struct atomic_label
            : sor<
                if_must_at<label>,
                if_must_at<one<'\"'>, label, one<'\"'>>,
                if_must_at<one<'\''>, label, one<'\''>>>
            { };

        struct atomic_subroutine
            : if_must_at<subroutine_name, toend>
            { };

        // Match the generic structure of a TAM instruction.
        struct inst_generic
            : if_must<
                at<inst_name, sor<space, toend>>,
                inst_name,
                rep_opt<2, pad<
                    sor<
                        atomic_register,
                        atomic_number,
                        atomic_subroutine,
                        atomic_label>,
                    space>>>
            { };

        // Proxy label for convenience
        struct add_label
            : label
            { } ;

        // Match a label definition.
        struct define_label
            : if_must_at<add_label, one<':'>>
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
                    star<space>,
                    comment
                >, opt<eolf>
              >
            { };
    }
}

#endif
