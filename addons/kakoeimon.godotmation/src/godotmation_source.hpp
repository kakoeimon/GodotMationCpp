#ifndef GODOTMATION_SOURCE_H
#define GODOTMATION_SOURCE_H

#include "godotmation_node.hpp"

class GodotMation_Resource;
class GodotMation_State;

class GodotMation_Source : public GodotMation_Node{

public:
    GodotMation_Source();
    ~GodotMation_Source();
    virtual bool trigger();
    virtual int can_push(int) const;
    virtual void apply_state();
};

#endif