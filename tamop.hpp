#ifndef TAM2C_GUARD_TAMOP_HPP
#define TAM2C_GUARD_TAMOP_HPP

#include "tam2c.hpp"
#include "tam_generic.hpp"

namespace tam2c
{
    using namespace pegtl::alphabet;
    struct mixed;

    // Registers
    struct CP : op_register<C, P>   { }; // code pointer    (     )
    struct CB : op_register<C, B>   { }; // code base       (const)
    struct CT : op_register<C, T>   { }; // code top        (const)
    struct PB : op_register<P, B>   { }; // primitive base  (const)
    struct PT : op_register<P, T>   { }; // primitive top   (const)
    struct SB : op_register<S, B>   { }; // stack base      (const)
    struct ST : op_register<S, T>   { }; // stack top       (     )
    struct HB : op_register<H, B>   { }; // heap base       (const)
    struct HT : op_register<H, T>   { }; // heap top        (     )
    struct LB : op_register<L, B>   { }; // local base      (     )
    struct L1 : op_register<L, '1'> { }; // local base 1    (     )
    struct L2 : op_register<L, '2'> { }; // local base 2    (     )
    struct L3 : op_register<L, '3'> { }; // local base 3    (     )
    struct L4 : op_register<L, '4'> { }; // local base 4    (     )
    struct L5 : op_register<L, '5'> { }; // local base 5    (     )
    struct L6 : op_register<L, '6'> { }; // local base 6    (     )

    // Implemented

    // Working on...

    // NOT implemented.
    struct store  : op_name<S, T, O, R, E>,    op_args<int, int, int> { };
    struct ret    : op_name<R, E, T, U, R, N>, op_args<int, int>      { };
    struct call   : op_name<C, A, L, L>,       op_args<int, char[]>   { };
    struct calli  : op_name<C, A, L, L, I>,    op_args<>              { };
    struct load   : op_name<L, O, A, D>,       op_args<int, int, int> { };
    struct loada  : op_name<L, O, A, D, A>,    op_args<int, int>      { };
    struct pop    : op_name<P, O, P>,          op_args<int, int>      { };
    struct push   : op_name<P, U, S, H>,       op_args<int>           { };
    struct storei : op_name<S, T, O, R, E, I>, op_args<int>           { };
    struct loadi  : op_name<L, O, A, D, I>,    op_args<int>           { };
    struct loadl  : op_name<L, O, A, D, L>,    op_args<mixed>         { };
    struct halt   : op_name<H, A, L, T>,       op_args<>              { };
    struct jump   : op_name<J, U, M, P>,       op_args<char[]>        { };
    struct jumpif : op_name<J, U, M, P, I, F>, op_args<int, char[]>   { };
    struct subr   : op_name<S, U, B, R>,       op_args<char[]>        { };
}

#include "tam_subr.hpp"

#endif
