#ifndef _OXYBELIS_INPUT_DEVICE_KEYBOARD_H
#define _OXYBELIS_INPUT_DEVICE_KEYBOARD_H

#include <GLFW/glfw3.h>
#include "input/Action.h"
#include "input/Input.h"
#include "input/ActionMap.h"
#include "input/AxisMap.h"
#include "core/Window.h"

constexpr const double KEY_PRESS_VALUE = 1.0;
constexpr const double KEY_RELEASE_VALUE = 0.0;

template <typename I>
class InputManager;

using Key = int;

template <typename I>
class Keyboard {
    ActionMap<I, Key> action_map;
    AxisMap<I, Key> axis_map;
    Window& win;

public:
    Keyboard(InputManager<I>& manager, Window& win):
        action_map(manager), axis_map(manager),
        win(win) {

        win.key_callback = [this](int key, int, int action, int) {
            if (action != GLFW_REPEAT)
                this->dispatch(key, static_cast<Action>(action));
        };
    }

    ~Keyboard() {
        win.key_callback = nullptr;
    }

    void dispatch(Key key, Action action) {
        this->action_map.dispatch(key, action);
        this->axis_map.dispatch(key, action == Action::Press ? KEY_PRESS_VALUE : KEY_RELEASE_VALUE);
    }

    void bind_action(ActionInput<I>& action_input, Key key) {
        this->action_map.bind(action_input, key);
    }

    void bind_action(const I& input, Key key) {
        this->action_map.bind(input, key);
    }

    void bind_axis(AxisInput<I>& axis_input, Key key, double scale, bool reset_after_update = false) {
        this->axis_map.bind(axis_input, key, scale, reset_after_update);
    }

    void bind_axis(const I& input, Key key, double scale, bool reset_after_update = false) {
        this->axis_map.bind(input, key, scale, reset_after_update);
    }
};

#endif
