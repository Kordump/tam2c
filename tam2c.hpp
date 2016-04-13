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

        using namespace pegtl;

        struct comment
            : if_must<one<';'>, until<eolf>>
            { };
    }

    template<typename t_rule>
        struct tam_action
        : pegtl::nothing<t_rule>
        { };
}

#endif
