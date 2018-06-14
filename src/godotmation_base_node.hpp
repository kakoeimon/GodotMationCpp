#ifndef GODOTMATION_BASE_NODE_H
#define GODOTMATION_BASE_NODE_H

#include "Godot.hpp"
#include "Node.hpp"

#include "godotmation_node.hpp"
#include "godotmation_resource.hpp"
#include "godotmation_state.hpp"

#include "godotmation_pool.hpp"
#include "godotmation_gate.hpp"
#include "godotmation_source.hpp"
#include "godotmation_drain.hpp"
#include "godotmation_converter.hpp"
#include "godotmation_delay.hpp"
#include "godotmation_end_condition.hpp"
#include "godotmation_function_call.hpp"




class GodotMation_Base_Node : public godot::GodotScript<godot::Node> {
	GODOT_CLASS(GodotMation_Base_Node)
public:
    GodotMation_Base_Node();
    ~GodotMation_Base_Node();
    static void _register_methods();
    int type = -1;
    GodotMation_Node *node;

    int get_type() const;
    void set_type(int); //This will set and the node based on the type.
    void trigger();
    godot::String get_caption() const;
    void set_caption(godot::String);
    int get_number() const;
    void set_number(int);

    int get_activation_mode() const;
    void set_activation_mode(int);

    int get_pull_mode() const;
    void set_pull_mode(int);
    
    int get_color() const;
    void set_color(int);
    int get_actions() const;
    void set_actions(int);
    int get_starting_resources() const;
    void set_starting_resources(int);
    int get_capacity() const;
    void set_capacity(int);
    float get_x() const;
    void set_x(float);
    float get_y() const;
    void set_y(float);

    int get_start() const;
    void set_start(int);
    int get_end() const;
    void set_end(int);

    bool get_emit_state_changed() const;
    void set_emit_state_changed(bool);

    //kakoeimon: You could have more luck with the `NOTIFICATION_PREDELETE` that you can get in _notification

};

#endif