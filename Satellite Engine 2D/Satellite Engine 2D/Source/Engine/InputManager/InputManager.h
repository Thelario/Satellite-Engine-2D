#pragma once

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

	public:
		static void SetKey(KeyCode keyCode, bool value);
		static bool GetKey(KeyCode keyCode);
};