#ifndef GODOTMATION_RESOURCE_H
#define GODOTMATION_RESOURCE_H


#include "godotmation_node.hpp"
#include "godotmation_base_number.hpp"


class GodotMation_Resource : public GodotMation_Node{

public:
    GodotMation_Resource();
    ~GodotMation_Resource();
    GodotMation_Node *start_node;
    GodotMation_Node *end_node;
    GodotMation_Base_Number *object_number = nullptr;
    GodotMation_Base_Number *other_object_number = nullptr;

    int used = false;
    int resource_type = 0;
    int pushed_resources = 0;
    int ticks = 0;
    int previous_interval = 0;
    //virtual void change_input_state(int);
    virtual void convert_label();
    virtual bool trigger();
    virtual bool check_flow() const;
    virtual void update_flow();
    virtual bool can_push_all() const;
    virtual void apply_state();
    virtual void apply_number();

    virtual void change_input_state(float);
};

#endif