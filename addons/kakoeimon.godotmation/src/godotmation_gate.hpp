#ifndef GODOTMATION_GATE_H
#define GODOTMATION_GATE_H

#include "godotmation_pool.hpp"

class GodotMation_Resource;
class GodotMation_State;

class GodotMation_Gate : public GodotMation_Pool{

public:
    GodotMation_Gate();
    ~GodotMation_Gate();
    int gate_type = 0;
    int output_i = 0;
    virtual bool trigger();
    virtual void change_input_state(int);
    virtual void change_output_state(int);
};

#endif