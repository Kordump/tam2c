#ifndef TAM2C_GUARD_TAM2C_HPP
#define TAM2C_GUARD_TAM2C_HPP

#include <string>
#include <memory>
#include "PEGTL/pegtl.hh"
#include "PEGTL/pegtl/contrib/alphabet.hh"

namespace tam2c
{
    using int_type = size_t;

    struct tag : public std::unique_ptr<std::string>
    {
        using type = std::unique_ptr<std::string>;
        using type::unique_ptr;

        void operator=(const std::string& value)
        { type::operator=(std::make_unique<std::string>(value)); };

        bool operator==(const std::string& value)
        { return (this->get()) && (value == *(this->get())); }

        bool operator!=(const std::string& value)
        { return (this->get()) && (value != *(this->get())); }
    };

    template<typename t_op>
    struct op
    { tag label; };
}

#include "tamop.hpp"

namespace tam2c
{
   namespace grammar
   {
        using namespace pegtl;

        // Comments.
        //  - comment{;.*$}
        struct comment
            : if_must<one<';'>, until<eolf>>
        { };

        struct g_push
            : seq<
                string<P, U, S, H>, plus<space>,
                plus<digit>>
        { };

        struct g_pop
            : seq<
                string<P, O, P>, plus<space>,
                one<'('>, plus<digit>, one<')'>, plus<space>,
                plus<digit>>
        { };

        struct g_op
            : sor<g_push, g_pop>
        { };

        struct g_line
            : seq<opt<g_op>, opt<plus<space>>, opt<comment>>
        { };

        struct g_lines
            : list<g_line, eolf, space>
        { };

        struct g_file
            : until<eof, g_lines>
        { };
    }

    template<typename t_rule>
    struct tam_action
        : pegtl::nothing<t_rule>
    { };
}

#endif
