#ifndef GODOTMATION_POOL_H
#define GODOTMATION_POOL_H

#include "godotmation_node.hpp"

class GodotMation_Resource;
class GodotMation_State;

class GodotMation_Pool : public GodotMation_Node{

public:
    GodotMation_Pool();
    virtual ~GodotMation_Pool();
    int input_number = 0;
    int output_number = 0;


    virtual bool trigger();
    virtual void pull_resources(GodotMation_Resource*);
    virtual int can_push(int) const;
    virtual void change_input_state(int);
    virtual void change_output_state(int);
    virtual int get_input_number() const;
    virtual int get_output_number() const;
    virtual int get_changed_number() const;
    virtual void apply_state();
    virtual void force_number(int);

};

#endif