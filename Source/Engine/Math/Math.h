#pragma once
#include <SDL3/SDL.h>
#include <algorithm>
#include <cmath>

namespace viper {


	constexpr float pi = 3.141592653589793238462643383279502884197169399375105820974944592307816406286f;
	constexpr float twopi = pi * 2;
	constexpr float halfpi = pi / 2;

	/// <summary>
	/// Converts an angle from radians to degrees
	/// </summary>
	/// <param name="rad">The radian angle to convert</param>
	/// <returns>The equivalent angle in degrees</returns>
	constexpr float RadToDeg(int rad) { return rad * (180 / pi); }

	/// <summary>
	/// Converts an angle from degrees to radians
	/// </summary>
	/// <param name="deg">The degrees angle to convert</param>
	/// <returns>The equivalent angle in radians</returns>
	constexpr float DegToRad(int deg) { return deg * (pi / 180); }

	/// <summary>
	/// 
	/// </summary>
	/// <param name="value"></param>
	/// <param name="min"></param>
	/// <param name="max"></param>
	/// <returns></returns>
	constexpr int Wrap(int value, int min, int max) {
		if (value > max) value = value - max;

		int range = max - min;
		int result = (value - min) % range;
		if (result < 0) {
			result += range;
		}
		return min + result;
	}

	/// <summary>
	/// wraps a float value to a specified range.
	/// </summary>
	/// <param name="value"> </param>
	/// <param name="min"></param>
	/// <param name="max"></param>
	/// <returns></returns>
	inline float Wrap(float value, float min, float max) {
		float range = max - min;
		float result = fmodf((value - min), range);
		if (result < 0) {
			result += range;
		}
		return min + result;
	}

	using std::min;
	using std::max;
	using std::sqrt;
	using std::sqrtf;
	using std::sin;
	using std::sinf;
	using std::cos;
	using std::cosf;
	using std::tan;
	using std::tanf;
	using std::atanf;
	using std::atan2f;
}