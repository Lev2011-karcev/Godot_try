#include "gdexample.h"
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/input_event_mouse_button.hpp>
#include <godot_cpp/classes/input_event_mouse_motion.hpp>
#include <godot_cpp/classes/input_event_key.hpp>
#include <godot_cpp/classes/spring_arm3d.hpp>

using namespace godot;

void GDExample::_bind_methods() {}

GDExample::GDExample() {
    speed = 20.0;
    jump_velocity = 10.0;
    mouse_sens = 0.002f;
}

GDExample::~GDExample() {}

void GDExample::_ready() {
    // 1. ПРОВЕРЬТЕ: В gdexample.h переменная должна называться иначе, чем класс.
    // Если в .h написано Node3D* SpringArm3D, то ок, но лучше использовать spring_arm.
    SpringArm3D = get_node<Node3D>("SpringArm3D"); // Имя переменной должно совпадать с .h
    Input::get_singleton()->set_mouse_mode(Input::MOUSE_MODE_CAPTURED);
    mouse_captured = true;
}

void GDExample::_unhandled_input(const Ref<InputEvent>& event) {
    Ref<InputEventKey> key = event;
    if (key.is_valid() && key->get_keycode() == Key::KEY_ESCAPE) {
        Input::get_singleton()->set_mouse_mode(Input::MOUSE_MODE_VISIBLE);
        mouse_captured = false;
        return;
    }

    Ref<InputEventMouseButton> btn = event;
    if (btn.is_valid() && btn->is_pressed()) {
        Input::get_singleton()->set_mouse_mode(Input::MOUSE_MODE_CAPTURED);
        mouse_captured = true;
        return;
    }

    Ref<InputEventMouseMotion> motion = event;
    if (motion.is_valid() && mouse_captured) {
        Vector2 rel = motion->get_relative();
        rotate_y(-rel.x * mouse_sens);

        // 2. ИСПРАВЛЕНИЕ CLAMP и ТИПОВ
        if (SpringArm3D) {
            Vector3 rot = SpringArm3D->get_rotation();
            float new_x = rot.x - rel.y * mouse_sens;
            rot.x = Math::clamp(new_x, (float)Math::deg_to_rad(-89.0f), (float)Math::deg_to_rad(89.0f));
            SpringArm3D->set_rotation(rot);
        }

    }
}

void GDExample::_physics_process(double p_delta) {
    Input* input = Input::get_singleton();
    Vector3 velocity = get_velocity();
    float delta = (float)p_delta;

    if (!is_on_floor()) {
        velocity.y -= 11.0f * delta;
    }

    if (input->is_action_just_pressed("ui_accept") && is_on_floor()) {
        velocity.y = (float)jump_velocity;
    }

    Vector2 input_dir = input->get_vector("ui_left", "ui_right", "ui_up", "ui_down");

    if (input_dir == Vector2(0, 0)) {
        if (input->is_key_pressed(Key::KEY_S)) input_dir.y -= 1.0f;
        if (input->is_key_pressed(Key::KEY_W)) input_dir.y += 1.0f;
        if (input->is_key_pressed(Key::KEY_A)) input_dir.x -= 1.0f;
        if (input->is_key_pressed(Key::KEY_D)) input_dir.x += 1.0f;
    }

    // 3. ИСПРАВЛЕНИЕ DIRECTION
    Basis basis = get_basis();
    // В Godot 4 направление вперед - это отрицательная ось Z (column 2)
    Vector3 direction = (basis.get_column(2) * -input_dir.y + basis.get_column(0) * input_dir.x).normalized();

    if (direction != Vector3(0, 0, 0)) {
        velocity.x = direction.x * (float)speed;
        velocity.z = direction.z * (float)speed;
    }
    else {
        velocity.x = Math::move_toward(velocity.x, 0.0f, (float)speed * delta * 10.0f);
        velocity.z = Math::move_toward(velocity.z, 0.0f, (float)speed * delta * 10.0f);
    }

    set_velocity(velocity);
    move_and_slide();
}
