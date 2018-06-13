#ifndef GODOTMATION_DELAY_H
#define GODOTMATION_DELAY_H

#include "godotmation_pool.hpp"

class GodotMation_Resource;
class GodotMation_State;

class GodotMation_Delay : public GodotMation_Pool{

public:
    GodotMation_Delay();
    ~GodotMation_Delay();
    bool queue = false;
    int interval_i = 0;
    std::vector<int> resources_line;
    virtual bool trigger();
    virtual void apply_satisfaction();
    virtual void apply_state();
    virtual int can_push(int) const;
};

#endif