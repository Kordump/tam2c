#ifndef TAM2C_GUARD_TAM_VISITOR_HPP
#define TAM2C_GUARD_TAM_VISITOR_HPP

namespace tam2c
{
    class tam_visitor
    {
        public:

        // Is pending instruction defined ?
        bool is_pending() { return false; } // TODO

        // Is pending instruction valid ?
        bool is_valid() { return true; } // TODO

        // If the pending instruction is valid,
        //      then, register it and return true,
        //      else, return false.
        bool commit()
        {
            if(!is_valid())
                return false;
            return true; // TODO
        }

        // Create a new instruction and overwrite the pending instruction.
        template<typename t_inst>
        void add(t_inst inst) { } // TODO

        // Add one or more argument to the pending instruction,
        // return true only if these arguments are semantically valid.
        template<typename t_arg>
        bool push_arg(t_arg arg){ return true; } // TODO

        // Details: Supports more than one parameter.
        template<typename... t_arg_pack>
        bool push_arg(t_arg_pack... args)
        {
            return push_arg_details<t_arg_pack...>(&args...);
        }

        // Details: Recursive expansion of the pack.
        template<typename t_head, typename... t_tail>
        bool push_arg_details(t_head arg, t_tail... others)
        {
            return true
                && push_arg<t_head>(arg)
                && push_arg_details<t_tail...>(others...);
        }
    };
}

#endif
