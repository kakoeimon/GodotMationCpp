#ifndef GODOTMATION_FUNCTION_CALL_H
#define GODOTMATION_FUNCTION_CALL_H

#include "godotmation_node.hpp"

class GodotMation_Resource;
class GodotMation_State;

class GodotMation_Function_Call : public GodotMation_Node{

public:
    GodotMation_Function_Call();
    ~GodotMation_Function_Call();
    virtual bool trigger();
    virtual void apply_state();
    virtual int can_push(int) const;
};

#endif