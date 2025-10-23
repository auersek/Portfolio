// #pragma once

// #include "ast_node.hpp"

// namespace ast {

//     class TypedefDeclare : public Node
//     {
//     private:
//         NodePtr identifier_;
//         NodePtr type_specifier_;

//     public:
//         TypedefDeclare(NodePtr identifier, NodePtr type_specifier)
//             : identifier_(identifier), type_specifier_(type_specifier) {}

//         virtual ~TypedefDeclare()
//         {
//             delete type_specifier_;
//             delete identifier_;
//         }

//         virtual void EmitRISC(std::ostream &stream, Context &context, std::string &destReg) const override;
//         virtual void Print(std::ostream &stream) const override;
//         virtual std::string getId() const override;
//     };
// }
