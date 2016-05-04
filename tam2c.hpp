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
            jump,       halt,       load,
            calli,      call,       ret
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

    // Please order subroutines by average frequency and avoid collisions.
    using subroutines =
        opcode_details<
            BNeg,            BOr,            BAnd,            BOut,
            BIn,             B2C,            B2I,             B2S,
            COut,            CIn,            C2B,             C2I,
            C2S,             INeg,           IAdd,            ISub,
            IMul,            IDiv,           IMod,            IEq,
            INeq,            ILss,           ILeq,            IGtr,
            IGeq,            IOut,           IIn,             I2B,
            I2C,             I2S,            MVoid,           MAlloc,
            MFree,           MCompare,       MCopy,           SAlloc,
            SCopy,           SConcat,        SOut,            SIn,
            S2B,             S2C,            S2I
                >;
}

#include "tam_grammar.hpp"
#include "tam_visitor.hpp"

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

    template<> struct tam_action<grammar::label>
    {
        static void apply(const pegtl::input& in, std::string& name)
        {
            std::cout << " +etiq[" << in.string() << "] ";
        }
    };

    template<> struct tam_action<grammar::tam_string<'\"'>>
    {
        static void apply(const pegtl::input& in, std::string& name)
        {
            std::cout << " +str[" << in.string() << "] ";
        }
    };

    template<> struct tam_action<grammar::tam_string<'\''>>
    {
        static void apply(const pegtl::input& in, std::string& name)
        {
            tam_action<grammar::tam_string<'\"'>>::apply(in, name);
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

    template<> struct tam_action<grammar::subroutine_name>
    {
        static void apply(const pegtl::input& in, std::string& name)
        {
            auto sub = subroutines::match(in.string());
            std::cout << " +sub[" << sub->get_ident() << "] ";
        }
    };

    template<> struct tam_action<grammar::add_label>
    {
        static void apply(const pegtl::input& in, std::string& name)
        {
            std::cout << " add[" << in.string() << "] ";
        }
    };

    template<> struct tam_action<grammar::add_label_weak>
    {
        static void apply(const pegtl::input& in, std::string& name)
        {
            std::cout << " Warning -> ";
            tam_action<grammar::add_label>::apply(in, name);
        }
    };

}

#endif
