#ifndef TAM2C_GUARD_TAMOP_HPP
#define TAM2C_GUARD_TAMOP_HPP

#include <string>
#include "tam2c.hpp"

namespace tam2c
{
    namespace tam
    {
        // PUSH n
        struct push : public op<push>
        { int_type n; };

        // POP (d) n
        struct pop : public op<pop>
        { int_type d, n; };

        // LOADL n
        struct loadl : public op<loadl>
        { int_type n; };

        // LOADA d[r]
        struct loada : public op<loada>
        { int_type d, r; };

        // LOAD (n) d[r]
        struct load : public op<load>
        { int_type n, d, r; };

        // STORE (n) d[r]
        struct store : public op<store>
        { int_type n, d, r; };

        // JUMP etiq
        struct jump_label : public op<jump_label>
        { std::string etiq; };

        // JUMPIF (n) etiq
        struct jumpif_label : public op<jumpif_label>
        { int_type n; std::string etiq; };

        // JUMP d[r]
        struct jump_addr : public op<jump_addr>
        { int_type d, r; };

        // JUMPIF (n) d[r]
        struct jumpif_addr : public op<jumpif_addr>
        { int_type n, d, r; };

        // LOADI (n)
        struct loadi : public op<loadi>
        { int_type n; };

        // STOREI (n)
        struct storei : public op<storei>
        { int_type n; };

        // Defining subroutines
        enum class subr_enum : int
        {
            //////////////////// Implemented ?
            BNeg        =  0, // --
            BOr         =  1, // --
            BAnd        =  2, // --
            BOut        =  3, // --
            BIn         =  4, // --
            B2C         =  5, // --
            B2I         =  6, // --
            B2S         =  7, // --
            COut        =  8, // --
            CIn         =  9, // --
            C2B         = 10, // --
            C2I         = 11, // --
            C2S         = 12, // --
            INeg        = 13, // --
            IAdd        = 14, // --
            ISub        = 15, // --
            IMul        = 16, // --
            IDiv        = 17, // --
            IMod        = 18, // --
            IEq         = 19, // --
            INeq        = 20, // --
            ILss        = 21, // --
            ILeq        = 22, // --
            IGtr        = 23, // --
            IGeq        = 24, // --
            IOut        = 25, // --
            IIn         = 26, // --
            I2B         = 27, // --
            I2C         = 28, // --
            I2S         = 29, // --
            MVoid       = 30, // --
            MAlloc      = 31, // --
            MFree       = 32, // --
            MCompare    = 33, // --
            MCopy       = 34, // --
            SAlloc      = 35, // --
            SCopy       = 36, // --
            SConcat     = 37, // --
            SOut        = 38, // --
            SIn         = 39, // --
            S2B         = 40, // --
            S2C         = 41, // --
            S2I         = 42  // --
        };

        // SUBR op
        template<int t_subr>
        struct subr : public op<subr<t_subr>>
        { };
    }
}

#endif
