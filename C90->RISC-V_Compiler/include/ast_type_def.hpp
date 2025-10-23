// #pragma once

// #include "ast_node.hpp"

// namespace ast {

//     class Typedef : public Node
//     {
//         private:
//         std::string identifier_;

//         public:
//         Typedef(std::string identifier) : identifier_(identifier){};
//         virtual ~Typedef(){};
//         virtual void EmitRISC(std::ostream &stream, Context &context, std::string &destReg) const override;
//         virtual void Print(std::ostream &stream) const override;

//         virtual std::string getId() const override;

//     };
// }
