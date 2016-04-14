#ifndef TAM2C_GUARD_TAMOP_HPP
#define TAM2C_GUARD_TAMOP_HPP

#include "tam2c.hpp"

namespace tam2c
{
    template<typename... t_op>
    struct opcode_details
    {
        static const size_t cardinal = sizeof...(t_op);

        template<size_t t_opcode, typename t_match, typename... t_remaining>
        struct match_details
        {
            static std::unique_ptr<instruction> name(std::string of_this)
            {
                if(of_this == op<t_match>::name)
                    return std::make_unique<op<t_match>>();

                return
                    match_details<t_opcode - 1, t_remaining...>::name(of_this);
            }
        };

        template<typename t_match, typename... t_remaining>
        struct match_details<1, t_match, t_remaining...>
        {
            static std::unique_ptr<instruction> name(std::string of_this)
            {
                if(of_this == op<t_match>::name)
                    return std::make_unique<op<t_match>>();

                return std::make_unique<op<instruction::invalid>>();
            }
        };

        static std::unique_ptr<instruction> match(std::string name)
        {
            return match_details<cardinal, t_op...>::name(name);
        };
    };

    // Implemented

    // Working on...
    struct subr;

    // NOT implemented.
    struct pop		    { static constexpr auto name = "POP";       };
    struct push		    { static constexpr auto name = "PUSH";      };
    struct jump		    { static constexpr auto name = "JUMP";      };
    struct jumpif		{ static constexpr auto name = "JUMPIF";    };
    struct store		{ static constexpr auto name = "STORE";     };
    struct storei		{ static constexpr auto name = "STOREI";    };
    struct halt		    { static constexpr auto name = "HALT";      };
    struct load		    { static constexpr auto name = "LOAD";      };
    struct loadi		{ static constexpr auto name = "LOADI";     };
    struct loadl		{ static constexpr auto name = "LOADL";     };

    // Please order keywords by average frequency.
    using opcode =
        opcode_details<
            pop,        store,      load,
            push,       storei,     loadi,
            jump,       subr,       loadl,
            jumpif,     halt
                >;

    // SUBR op
    struct subr
    {
        static constexpr auto name = "SUBR";

        template<size_t t_code> struct op { };
        static constexpr auto invalid = "_subr_invalid";

        template<size_t t_code = 0>
        struct match
        {
            static std::string name(std::string of_this)
            {
                if(of_this == subr::op<t_code>::name)
                    return subr::op<t_code>::name;

                return match<t_code + 1>::name(of_this);
            };
        };
    };

    // Defining subroutines
    template<> struct subr::op< 0> { static constexpr auto name = "BNeg";     };
    template<> struct subr::op< 1> { static constexpr auto name = "BOr";      };
    template<> struct subr::op< 2> { static constexpr auto name = "BAnd";     };
    template<> struct subr::op< 3> { static constexpr auto name = "BOut";     };
    template<> struct subr::op< 4> { static constexpr auto name = "BIn";      };
    template<> struct subr::op< 5> { static constexpr auto name = "B2C";      };
    template<> struct subr::op< 6> { static constexpr auto name = "B2I";      };
    template<> struct subr::op< 7> { static constexpr auto name = "B2S";      };
    template<> struct subr::op< 8> { static constexpr auto name = "COut";     };
    template<> struct subr::op< 9> { static constexpr auto name = "CIn";      };
    template<> struct subr::op<10> { static constexpr auto name = "C2B";      };
    template<> struct subr::op<11> { static constexpr auto name = "C2I";      };
    template<> struct subr::op<12> { static constexpr auto name = "C2S";      };
    template<> struct subr::op<13> { static constexpr auto name = "INeg";     };
    template<> struct subr::op<14> { static constexpr auto name = "IAdd";     };
    template<> struct subr::op<15> { static constexpr auto name = "ISub";     };
    template<> struct subr::op<16> { static constexpr auto name = "IMul";     };
    template<> struct subr::op<17> { static constexpr auto name = "IDiv";     };
    template<> struct subr::op<18> { static constexpr auto name = "IMod";     };
    template<> struct subr::op<19> { static constexpr auto name = "IEq";      };
    template<> struct subr::op<20> { static constexpr auto name = "INeq";     };
    template<> struct subr::op<21> { static constexpr auto name = "ILss";     };
    template<> struct subr::op<22> { static constexpr auto name = "ILeq";     };
    template<> struct subr::op<23> { static constexpr auto name = "IGtr";     };
    template<> struct subr::op<24> { static constexpr auto name = "IGeq";     };
    template<> struct subr::op<25> { static constexpr auto name = "IOut";     };
    template<> struct subr::op<26> { static constexpr auto name = "IIn";      };
    template<> struct subr::op<27> { static constexpr auto name = "I2B";      };
    template<> struct subr::op<28> { static constexpr auto name = "I2C";      };
    template<> struct subr::op<29> { static constexpr auto name = "I2S";      };
    template<> struct subr::op<30> { static constexpr auto name = "MVoid";    };
    template<> struct subr::op<31> { static constexpr auto name = "MAlloc";   };
    template<> struct subr::op<32> { static constexpr auto name = "MFree";    };
    template<> struct subr::op<33> { static constexpr auto name = "MCompare"; };
    template<> struct subr::op<34> { static constexpr auto name = "MCopy";    };
    template<> struct subr::op<35> { static constexpr auto name = "SAlloc";   };
    template<> struct subr::op<36> { static constexpr auto name = "SCopy";    };
    template<> struct subr::op<37> { static constexpr auto name = "SConcat";  };
    template<> struct subr::op<38> { static constexpr auto name = "SOut";     };
    template<> struct subr::op<39> { static constexpr auto name = "SIn";      };
    template<> struct subr::op<40> { static constexpr auto name = "S2B";      };
    template<> struct subr::op<41> { static constexpr auto name = "S2C";      };
    template<> struct subr::op<42> { static constexpr auto name = "S2I";      };
    template<> struct subr::op<43> { static constexpr auto name = invalid;    };

}

#endif
