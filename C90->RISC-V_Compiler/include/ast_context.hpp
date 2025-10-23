#pragma once
#include <iostream>
#include <ostream>
#include <stdexcept>
#include <unordered_map>
#include <string>
#include <unordered_set>
#include <vector>
// #include "ast_node.hpp"
#include "ast_type_specifier.hpp"

namespace ast {
// An object of class Context is passed between ast nodes during compilation.
// This can be used to pass around information about what's currently being
// compiled (e.g. function scope and variable names).

struct Variables {
    TypeSpecifier type;
    std::string memLocation;
    bool PointerOrNot;
    EntitySpecifier entity;
};

struct Parameters {
    TypeSpecifier type;
    std::string memLocation;
    bool PointerOrNot;
};


struct Switch_info {
    std::string              switch_start;
    std::vector<std::string> switch_cases;
    std::string              switch_default;
    bool cond_check_or_emit;
};

struct Loop_info {
    std::string loop_start;
    std::string loop_update;
    std::string loop_end;
};

struct enum_info {
    std::string enum_name;
    std::unordered_map<std::string, int> enum_members_and_vals;
};

struct arrays {
    TypeSpecifier type;
    std::string memLocation;
    bool IsPointer;
};


struct Registers {      // 1 is available, 0 is unavailable
    int regist[32] = {
        1,                   // x0      register 0 is always 0 cannot be modified
        1,                   // x1      register 1 Return address
        1,                   // x2      register 2 Stack Pointer
        1,                   // x3      register 3 Global Pointer
        1,                   // x4      register 4 Thread Pointer
        1, 1, 1,             // x5-7    register 5-7 Temporaries
        0,                   // x8      register 8 Frame pointer
        0,                   // x9      register 9 Saved register
        0, 0,                // x10-11  register 10-11 Function arguments / return values
        0, 0, 0, 0, 0, 0,    // x12-17  register 12-17 Function arguments
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,    // x18-27  register 18-27 Saved registers
        1, 1, 1, 1           // x28-31  register 28-31 Temporaries
    };
    void changeRegisterState(int regIndex, int val){         // Change Register state
        Registers::regist[regIndex] = val;     // maybe add if statement only allowing inputs (val) of 0/1
    }


    int getRegisterState(int regIndex){

        return Registers::regist[regIndex];
    }



    std::string countOnes() {
        int count = 0;
        for (int i = 0; i < 32; ++i) {
            if (regist[i] == 1) {
                count++;
            }
        }
        std::string result = std::to_string(count);
        std::cout << "Total number of 1s in registers: " << result << std::endl;
        return result;
    }


};
struct floatRegisters {      // 1 is available, 0 is unavailable
    int regist_float[32] = {
        1,                   // x0      register 0 is always 0 cannot be modified
        1,                   // x1      register 1 Return address
        1,                   // x2      register 2 Stack Pointer
        1,                   // x3      register 3 Global Pointer
        1,                   // x4      register 4 Thread Pointer
        1, 1, 1,             // x5-7    register 5-7 Temporaries
        0,                   // x8      register 8 Frame pointer
        0,                   // x9      register 9 Saved register
        0, 0,                // x10-11  register 10-11 Function arguments / return values
        0, 0, 0, 0, 0, 0,    // x12-17  register 12-17 Function arguments
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1,    // x18-27  register 18-27 Saved registers
        1, 1, 1, 1           // x28-31  register 28-31 Temporaries
    };
    void floatChangeRegisterState(int regIndex, int val){
        floatRegisters::regist_float[regIndex] = val;
    }

    int floatGetRegisterState(int regIndex){
        return floatRegisters::regist_float[regIndex];
    }
};

class Context
{
    private:
        Registers register_file;
        floatRegisters float_file;
        int makeLabelUnq = 0;

    public:
        int frame = 1024;
        int memory_size_left = 1024;
        int enum_value_g = -1;
        TypeSpecifier last_added_type;

        std::vector<std::unordered_map<std::string, Variables>>     scope_store; // scope  // Stores symbol tables
        std::vector<std::unordered_map<std::string, Parameters>>    parameter_stack;

        std::unordered_map<std::string, Parameters>                 parameters;       // Clear parameterss in exit
        std::unordered_map<std::string, Variables>                  LocalVariables;

        std::vector<Loop_info>                                      loop_list;  // stores loop info

        std::unordered_map<std::string, TypeSpecifier>              function_return_types;
        std::vector<std::string>                                    func_return_labels;

        std::vector<Switch_info>                                    switch_list; // stores switch info

        std::vector<std::vector<std::string>>                       registersUsed;

        std::vector<enum_info>                                      enum_list;

        std::unordered_map<std::string, std::string>                string_list;

        //array helpers
        std::unordered_map<std::string, arrays>                     Array_list;
        std::string array_index = "";
        bool set = false;


// Label maker
    std::string labelAlloc(std::string label_to_make){
        return label_to_make + "_" + std::to_string(makeLabelUnq++);
    }


// Loop context things
    void createForLoop(std::string start, std::string end, std::string update)
    {
        Loop_info new_for_loop;
        new_for_loop.loop_start = start;
        new_for_loop.loop_end = end;
        new_for_loop.loop_update = update;
        loop_list.push_back(new_for_loop);
    }

    void createLoop(std::string startOfLoop, std::string endOfLoop) {
        Loop_info newLoop;
        newLoop.loop_start = startOfLoop;
        newLoop.loop_end = endOfLoop;
        loop_list.push_back(newLoop);
    }
    std::string loopConditionLabel() {
        if (!loop_list.empty()) {
            return loop_list.back().loop_start;
        } else {
            throw std::runtime_error("loop_list is empty");
        }
    }

    std::string loopStatementLabel(){
        if (!loop_list.empty()) {
            return loop_list.back().loop_end;
        } else {
            throw std::runtime_error("loop_list is empty");
        }
    }

    void exitLoop() {
        loop_list.pop_back();

    }

    // Handling registers

    std::string regAlloc(){
        for (int i = 0; i < 11; i++){
            if (register_file.getRegisterState(i)){
                register_file.changeRegisterState(i, 0);
                std::string register_allocated = "a" + std::to_string(i);
                return register_allocated;
            }
        }
        throw std::runtime_error("No available registers");
    }



    void regDalloc(std::string regis_num){
        if (regis_num.size() <= 1) {
            throw std::runtime_error("Invalid register name: '" + regis_num + "'");
        }
        int reg_num = std::stoi(regis_num.substr(1));
        register_file.changeRegisterState(reg_num, 1);
    }

    std::string floatRegAlloc(){
        for (int i = 4; i < 32; i++){
            if (float_file.floatGetRegisterState(i)){
                float_file.floatChangeRegisterState(i, 0);
                std::string register_allocated = "f" + std::to_string(i);
                // stream << "mv " << register_allocated << ", zero" << std::endl;
                return register_allocated;
            }
        }
        throw std::runtime_error("No available registers");
    }

    void floatRegDalloc(std::string regis_num){
        int reg_num = std::stoi(regis_num.substr(1));
        float_file.floatChangeRegisterState(reg_num, 1);
    }


    void useRegister(std::ostream &stream){
        std::vector<std::string> registerUsedhere;
        for(int i = 5; i <= 7; i++){
            if(register_file.getRegisterState(i) == 1){
                std::string temporaryRegister = "a" + std::to_string(i);
                registerUsedhere.push_back(temporaryRegister);
                register_file.changeRegisterState(i, 0);
                stream << "sw " << temporaryRegister << ", " << takeMemory(TYPE_SIZE_INT) << "(s0)" << std::endl;
            }
        }
        for(int i = 28; i <= 31; i++){
            if(register_file.getRegisterState(i) == 1){
                std::string temporaryRegister = "a" + std::to_string(i);
                registerUsedhere.push_back(temporaryRegister);
                register_file.changeRegisterState(i, 0);
                stream << "sw " << temporaryRegister << ", " << takeMemory(TYPE_SIZE_INT) << "(s0)" << std::endl;
            }
        }
        registersUsed.push_back(registerUsedhere);

    }


    // Memory stuff

    void initalizeStack(std::ostream &stream){                
        stream << "addi sp, sp,-" << frame << std::endl;
        stream << "sw ra, " << frame - 4 << "(sp)" << std::endl;
        stream << "sw s0, " << frame - 8 << "(sp)" << std::endl;
        stream << "addi s0, sp," << frame << std::endl;
    }

    void endStack(std::ostream &stream) {
        stream << "lw s0," << frame - 8 << "(sp)" << std::endl;
        stream << "lw ra," << frame - 4 << "(sp)" << std::endl;
        stream << "addi sp, sp," << frame << std::endl;
    }

    std::string takeMemory(int mem_size)
    {
        if (memory_size_left - mem_size >= 0) {
            memory_size_left -= mem_size;
            int loc = -(1024 - memory_size_left);
            return std::to_string(loc*2);
        }
        throw std::runtime_error("no memory");
    }



    void deallocateMemory(int mem_size)
    {
        memory_size_left += mem_size;
    }

    std::string getMemLocation(std::string id)
    {
        if (parameters.find(id) != parameters.end()) {
            return parameters[id].memLocation;
        }
        if (LocalVariables.find(id) != LocalVariables.end()) {
            return LocalVariables[id].memLocation;
        }
        std::vector<std::unordered_map<std::string, Variables>>::reverse_iterator reversevars;
        for (reversevars = scope_store.rbegin(); reversevars != scope_store.rend(); ++reversevars) {
            if (reversevars->find(id) != reversevars->end()) {
                return (*reversevars)[id].memLocation;
            }
        }
        return "null";
    }

    void allocateStackSpace(std::string id, TypeSpecifier type, bool pointer)
    {
        std::string offset;
        if (type == TypeSpecifier::INT)
        {
            offset = takeMemory(TYPE_SIZE_INT);
        }
        else if (type == TypeSpecifier::FLOAT)
        {
            offset = takeMemory(TYPE_SIZE_FLOAT);
        }
        else if (type == TypeSpecifier::DOUBLE)
        {
            offset = takeMemory(TYPE_SIZE_DOUBLE);
        }
        else if (type == TypeSpecifier::CHAR && pointer)
        {
            offset = takeMemory(TYPE_SIZE_INT);
        }
        else if (type == TypeSpecifier::CHAR && !pointer)
        {
            offset = takeMemory(TYPE_SIZE_CHAR);
        }
        else
        {
            offset = takeMemory(TYPE_SIZE_INT);
        }
        Variables newVar;
        newVar.memLocation = offset;
        newVar.type = type;
        newVar.PointerOrNot = pointer;
        newVar.entity = EntitySpecifier::VARIABLE;
        LocalVariables[id] = newVar;
    }


    // void addMemLocation(Variables var, std::string off){

    //     var.memLocation = off;
    // }

    Variables getVariable(const std::string& id) {
        auto found = LocalVariables.find(id);
        if (found != LocalVariables.end()) {
            return found->second;
        }
        return Variables();
    }



    Parameters getParam(const std::string& id) {
        auto found = parameters.find(id);
        if (found != parameters.end()) {
            return found->second;
        }
        return Parameters();
    }

 // Functions   not done
    void makeFuncReturnType(std::string function_name, TypeSpecifier return_type) {
        function_return_types[function_name] = return_type;
        last_added_type = return_type;
    }

    TypeSpecifier getFuncReturnType(std::string function_name) {
        if (function_return_types.find(function_name) != function_return_types.end()) {
            return function_return_types[function_name];
        }
        return TypeSpecifier::INVALID;
    }

    TypeSpecifier getLastAddedReturnType() {
        return last_added_type;
    }

    void addToScope(std::ostream &stream){
        (void)stream;
        scope_store.push_back(LocalVariables);
        LocalVariables.clear();
        // memory_size_left = frame;
        // stream << "addi sp, sp,-" << frame << std::endl;
    }

    void removeScope(){
        LocalVariables = scope_store.back();
        scope_store.pop_back();
    }

    EntitySpecifier getEntity(const std::string& id) {
        for (auto it = scope_store.rbegin(); it != scope_store.rend(); ++it) {
            const auto& scope = *it;
            if (scope.find(id) != scope.end()) {
                return EntitySpecifier::VARIABLE;
            }
        }
        for (auto it = parameter_stack.rbegin(); it != parameter_stack.rend(); ++it) {
            const auto& scope = *it;
            if (scope.find(id) != scope.end()) {
                return EntitySpecifier::PARAMETER;
            }
        }
        return EntitySpecifier::INVALID;
    }


    std::string funcReturn() {
        return func_return_labels.back();
    }

    void leaveFunc(std::ostream &stream){
        parameter_stack.pop_back();
        func_return_labels.pop_back();
        stream << "addi sp, sp, " << frame << std::endl;
    }


// Arrays
void newArray(std::string id, int arraysize){

    std::string mem;

    TypeSpecifier type1 = getVarType(id);
    if(type1 == TypeSpecifier::FLOAT){
        for (int i = 0; i < arraysize - 1; i++)
        {
            mem = takeMemory(TYPE_SIZE_INT);
        }
    }
    else if(type1 == TypeSpecifier::DOUBLE){
        for (int i = 0; i < arraysize - 1; i++)
        {
            mem = takeMemory(TYPE_SIZE_INT);
        }
    }
    else if (type1 == TypeSpecifier::INT){
        for (int i = 0; i < arraysize - 1; i++)
        {
            mem = takeMemory(TYPE_SIZE_INT);
        }
    }
    else if (type1 == TypeSpecifier::CHAR){
        for (int i = 0; i < arraysize - 1; i++)
        {
            mem = takeMemory(TYPE_SIZE_CHAR);
        }
    }
    else{
        for (int i = 0; i < arraysize - 1; i++)
        {
            mem = takeMemory(TYPE_SIZE_INT);
        }
    }

}


void setArrayFlag(bool setTrue){
    set = setTrue;
}

bool getArrayFlag(){
    return set;
}


std::string getArrIndex()
{
    return array_index;
}

void setArrIndex(std::string index_reg) {
    array_index = index_reg;
}

void createArray(std::string array_name, TypeSpecifier type, std::string offset, bool pointer){
    arrays newArray;
    newArray.type = type;
    newArray.memLocation = offset;
    newArray.IsPointer = pointer;
    Array_list[array_name] = newArray;
}


// is pointer
    bool getIsPointer(std::string id)
    {
        if (parameters.find(id) != parameters.end())
        {
            return parameters[id].PointerOrNot;
        }
        if (LocalVariables.find(id) != LocalVariables.end())
        {
            return LocalVariables[id].PointerOrNot;
        }
        return false;
    }

// Variables
    TypeSpecifier getVarType(std::string variabl){
        if (parameters.find(variabl) != parameters.end())
        {
            return parameters[variabl].type;
        }
        if (LocalVariables.find(variabl) != LocalVariables.end())
        {
            return LocalVariables[variabl].type;
        }
        return TypeSpecifier::INVALID;
    }



// Parameter
    void makeParam(std::string nameParam, TypeSpecifier type, std::string offset, bool pointer){
        Parameters newParam;
        newParam.type = type;
        newParam.memLocation = offset;
        newParam.PointerOrNot = pointer;
        parameters[nameParam] = newParam;
    }

// Local Variables
    TypeSpecifier getLocalVariables(std::string id)
    {
        if (!parameter_stack.empty()) {
        std::unordered_map<std::string, Parameters>& currentParams = parameter_stack.back();
        if (currentParams.find(id) != currentParams.end()) {
            return currentParams[id].type;
        }
        }
        if (LocalVariables.find(id) != LocalVariables.end()) {
            return LocalVariables[id].type;
        }
        std::vector<std::unordered_map<std::string, Variables>>::reverse_iterator reversevars;
        for (reversevars = scope_store.rbegin(); reversevars != scope_store.rend(); ++reversevars) {
            if (reversevars->find(id) != reversevars->end()) {
                return (*reversevars)[id].type;
            }
        }
        return TypeSpecifier::INVALID;
    }

    // enums

    void createEnum(std::string enumName){
        enum_info madeEnum;
        madeEnum.enum_name = enumName;
        enum_list.push_back(madeEnum);
    }

    bool isEnumVal(const std::string& name) const {
        for (auto it = enum_list.rbegin(); it != enum_list.rend(); ++it) {
            if (it->enum_members_and_vals.find(name) != it->enum_members_and_vals.end()) {
                return true;
            }
        }
        return false;
    }

    int setEnumValue() {
        std::unordered_set<int> existing_values;

        for (const auto& search : enum_list.back().enum_members_and_vals) {
            existing_values.insert(search.second);
        }

        while (existing_values.count(++enum_value_g)) {}

        return enum_value_g;
    }

    void enumAddValue(std::string name, int value){
        enum_list.back().enum_members_and_vals[std::move(name)] = value;
    }
    void resEnum(){
        enum_value_g = -1;
    }

    int lookupEnumValue(const std::string& name) const {
        for (auto it = enum_list.rbegin(); it != enum_list.rend(); ++it) {
            auto found = it->enum_members_and_vals.find(name);
            if (found != it->enum_members_and_vals.end()) {
                // Found it, return the actual enum value
                return found->second;
            }
        }
        // If not found, throw instead of returning 0
        throw std::runtime_error("No such enum constant: " + name);
    }



    void setCaseCond(bool emit_condition){
        switch_list.back().cond_check_or_emit = emit_condition;
    }

    void createSwitch() {
        Switch_info new_switch;
        std::string switch_label = labelAlloc("end_");
        new_switch.switch_start = switch_label;
        new_switch.switch_default = "";
        new_switch.cond_check_or_emit = false;
        switch_list.push_back(new_switch);
        Loop_info switch_loop;
        switch_loop.loop_start = "";
        loop_list.push_back(switch_loop);
    }

    // struct Switch_info {
    //     std::string              switch_start;
    //     std::vector<std::string> switch_cases;
    //     std::string              switch_default;
    //     bool cond_check_or_emit;
    // };




    // Literals
    void newStringList(std::string string_key, std::string string_literal)
    {
        string_list[string_key] = string_literal;
    }


};

}  // namespace ast
