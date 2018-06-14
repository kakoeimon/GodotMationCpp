#ifndef GODOTMATION_STATE_H
#define GODOTMATION_STATE_H


#include "godotmation_base_node.hpp"



class GodotMation_State : public GodotMation_Node{

public:
    GodotMation_State();
    ~GodotMation_State();
    float state_number = 0.0f;
    int other_number = 0;
    int used = false;
    int state_type = 0;

    GodotMation_Node *start_node = nullptr;
    GodotMation_Node *end_node = nullptr;

    virtual bool trigger();
    virtual bool trigger(int);
    virtual void change_input_state(int);
    virtual void change_output_state(int);
    virtual void apply_state();
    virtual void convert_label();
    virtual void get_label_data(godot::String);

};

#endif