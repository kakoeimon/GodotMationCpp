#ifndef GODOTMATION_END_CONDITION_H
#define GODOTMATION_END_CONDITION_H

#include "godotmation_node.hpp"

class GodotMation_Resource;
class GodotMation_State;

class GodotMation_End_Condition : public GodotMation_Node{

public:
    GodotMation_End_Condition();
    ~GodotMation_End_Condition();
    bool signaller = false;
    virtual bool trigger();
    virtual void apply_state();
};

#endif