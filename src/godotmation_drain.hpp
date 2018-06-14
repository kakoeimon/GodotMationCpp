#ifndef GODOTMATION_DRAIN_H
#define GODOTMATION_DRAIN_H

#include "godotmation_node.hpp"

class GodotMation_Resource;
class GodotMation_State;

class GodotMation_Drain : public GodotMation_Node{

public:
    GodotMation_Drain();
    ~GodotMation_Drain();
    virtual bool trigger();
    virtual int can_push(int) const;
    virtual void apply_state();
};

#endif