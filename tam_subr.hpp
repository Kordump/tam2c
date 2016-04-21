#ifndef TAM2C_GUARD_TAM_SUBR_HPP
#define TAM2C_GUARD_TAM_SUBR_HPP

#include "tamop.hpp"

namespace tam2c
{
    // Defining subroutines
    struct BNeg       : op_subr<B, N, e, g>             { };
    struct BOr        : op_subr<B, O, r>                { };
    struct BAnd       : op_subr<B, A, n, d>             { };
    struct BOut       : op_subr<B, O, u, t>             { };
    struct BIn        : op_subr<B, I, n>                { };
    struct B2C        : op_subr<B, '2', C>              { };
    struct B2I        : op_subr<B, '2', I>              { };
    struct B2S        : op_subr<B, '2', S>              { };
    struct COut       : op_subr<C, O, u, t>             { };
    struct CIn        : op_subr<C, I, n>                { };
    struct C2B        : op_subr<C, '2', B>              { };
    struct C2I        : op_subr<C, '2', I>              { };
    struct C2S        : op_subr<C, '2', S>              { };
    struct INeg       : op_subr<I, N, e, g>             { };
    struct IAdd       : op_subr<I, A, d, d>             { };
    struct ISub       : op_subr<I, S, u, b>             { };
    struct IMul       : op_subr<I, M, u, l>             { };
    struct IDiv       : op_subr<I, D, i, v>             { };
    struct IMod       : op_subr<I, M, o, d>             { };
    struct IEq        : op_subr<I, E, q>                { };
    struct INeq       : op_subr<I, N, e, q>             { };
    struct ILss       : op_subr<I, L, s, s>             { };
    struct ILeq       : op_subr<I, L, e, q>             { };
    struct IGtr       : op_subr<I, G, t, r>             { };
    struct IGeq       : op_subr<I, G, e, q>             { };
    struct IOut       : op_subr<I, O, u, t>             { };
    struct IIn        : op_subr<I, I, n>                { };
    struct I2B        : op_subr<I, '2', B>              { };
    struct I2C        : op_subr<I, '2', C>              { };
    struct I2S        : op_subr<I, '2', S>              { };
    struct MVoid      : op_subr<M, V, o, i, d>          { };
    struct MAlloc     : op_subr<M, A, l, l, o, c>       { };
    struct MFree      : op_subr<M, F, r, e, e>          { };
    struct MCompare   : op_subr<M, C, o, m, p, a, r, e> { };
    struct MCopy      : op_subr<M, C, o, p, y>          { };
    struct SAlloc     : op_subr<S, A, l, l, o, c>       { };
    struct SCopy      : op_subr<S, C, o, p, y>          { };
    struct SConcat    : op_subr<S, C, o, n, c , a, t>   { };
    struct SOut       : op_subr<S, O, u, t>             { };
    struct SIn        : op_subr<S, I, n>                { };
    struct S2B        : op_subr<S, 2, B>                { };
    struct S2C        : op_subr<S, 2, C>                { };
    struct S2I        : op_subr<S, 2, I>                { };
}

#endif
