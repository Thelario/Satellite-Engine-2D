#pragma once

#include <glm/glm.hpp>
#include <unordered_map>

// TODO: implementar un método que convierta el KeyCode a string para poder loggear con el valor de la key

enum class KeyCode
{
	A, B, C, D, E, F, G, H, I, J, K, L, M, N, Ñ, O, P, Q, R, S, T, U, V, W, X, Y, Z,
	ESCAPE, TAB, CTRL, ALT, INTRO, ZERO, ONE, TWO, THREE, FOUR, FIVE, SIXE, SEVEN, EIGHT, NINE
};

static class InputManager
{
	private:
		static std::unordered_map<KeyCode, bool> keys;
		static glm::vec2 mouse_position;

		static bool left_mouse_button_down;
		static bool right_mouse_button_down;
		static bool left_mouse_button_up;
		static bool right_mouse_button_up;

	public:
		static void SetKey(KeyCode key_code, bool value);
		static bool GetKey(KeyCode key_code);

		static void SetMousePosition(glm::vec2 mouse_pos);
		static glm::vec2 GetMousePosition();

		static void SetMouseButtonDown(short int button, bool value);
		static void SetMouseButtonUp(short int button, bool value);
		static bool GetMouseButtonDown(short int button);
		static bool GetMouseButtonUp(short int button);
};