#ifndef GODOTMATION_NODE_H
#define GODOTMATION_NODE_H

#include <vector>
#include "Godot.hpp"

class GodotMation_Base_Node;

class GodotMation_Resource;
class GodotMation_State;

class GodotMation;

class GodotMation_Node{

public:
    GodotMation_Node();
    virtual ~GodotMation_Node();
    GodotMation_Base_Node *owner;
    GodotMation *parent;
    int type = -1;
    godot::String caption = "";
    int activation_mode = 0;
    int pull_mode = 0;
    int number = 0;
    int color = 0;
    int actions = 0;
    int starting_resources = 0;
    int capacity = -1;
    float x = 0.0f;
    float y = 0.0f;

    int start = 0;
    int end = 0;

    bool pushed = false;
    bool emit_state_changed = false;

    std::vector<GodotMation_Resource*> input_resources;
    std::vector<GodotMation_Resource*> output_resources;
    std::vector<GodotMation_State*> input_states;
    std::vector<GodotMation_State*> output_states;

    std::vector<GodotMation_State*> trigger_states;
    std::vector<GodotMation_State*> reverse_trigger_states;

    std::vector<GodotMation_State*> input_conditional_states;

    bool active = true;
    bool satisfied = true;

    virtual bool trigger();
    virtual void pull_resources(GodotMation_Resource*);
    virtual void apply_satisfaction();
    virtual int can_push(int) const;
    virtual void change_input_state(int);
    virtual void change_output_state(int);
    virtual int get_input_number() const;
    virtual int get_output_number() const;
    virtual int get_changed_number() const;
    virtual void apply_state();


    virtual godot::Dictionary get_dict() const;

};

#endif