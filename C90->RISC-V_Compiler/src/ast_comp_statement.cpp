#include "../include/ast_comp_statement.hpp"

namespace ast {


    void CompStatement::EmitRISC(std::ostream& stream, Context& context, std::string &destReg) const
    {
        context.addToScope(stream);
        if (dec_list_ != nullptr) {
            // stream << "#twice" << std::endl;
            dec_list_->EmitRISC(stream, context, destReg);
        }
        if (stat_list_ != nullptr) {
            // stream << "#once" << std::endl;
            stat_list_->EmitRISC(stream, context, destReg);
        }
        context.removeScope();
    }

    void CompStatement::Print(std::ostream& stream) const {
        stream << "SKIBIDI BOP" << std::endl;
    }

};


