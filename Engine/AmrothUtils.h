#pragma once
#include "structs.h"
#include "Texture.h"

// Declaration
#pragma region Constants
const float GRAVITY{ -9.81f };
#pragma endregion Constants

#pragma region General
// Sin/Waves
double	WaveMovement		(int moved, int fullMovement = 100);
double	WaveMovement		(float moved, float fullMovement = 1.0f);
double	WaveMovement		(double moved, double fullMovement = 1.0);

// WaveMovement(90, 360)					// degrees
// WaveMovement(M_PI / 2, 2 * M_PI);		// radians
// WaveMovement(250, 1000);					// Mils
// WaveMovement(0.25);						// Percentage (out of 1.0)
// WaveMovement(25);						// Out of 100

void DrawCircle(float posX, float posY, float radius, int segments);

// Color Functions
enum class Color
{
	White,		// (255, 255, 255)
	Black,		// (0, 0, 0)
	Red,		// (255, 0, 0)
	Green,		// (0, 255, 0)
	Blue,		// (0, 0, 255)
	Cyan,		// (0, 255, 255)
	Pink,		// (255, 105, 180)
	Orange,		// (255, 165, 0)
	Yellow,		// (255, 255, 0)
	Magenta,	// (255, 0, 255)
	Purple,		// (128, 0, 128)
};

void	SetColor			(const Color& color, const float& alpha = 1);
#pragma endregion General

#pragma region MathCalculations
// Sum Functions
bool	IsEven(const int& a);
int		Modulo(const int& a, const int& b);
void	Clamp(float& value, const float& minValue, const float& maxValue);
void	Clamp(int& value, const int& minValue, const int& maxValue);
float	GetDistanceBetween(const Point2f& fromPoint, const Point2f& toPoint);
float	GetAngleDifference(const float& fromAngle, const float& toAngle);
float	GetAngleToPoint(const Point2f& fromPoint, const Point2f& toPoint);
float	RadiansToDegrees(const float& radians);
float	DegreesToRadians(const float& degrees);
int		GetNumberFromUser(const std::string& inputText, const std::string& invalidText, const int& min = INT_MIN, const int& max = INT_MAX);
float	RandomRange(float min, float max);
int		RandomRange(int min, int max);
float GetSpeed(const float& velocity, const float& acceleration, const float& time);
float GetSpeedByAcceleration(const float& initialVelocity, const float& acceleration, const float& initialPosition, const float& position);

#pragma endregion MathCalculations

#pragma region ConsoleFunctionality

// Variables
const HANDLE g_HConsole = GetStdHandle(STD_OUTPUT_HANDLE);

enum class TextColor
{
	Black,
	Blue,
	Green,
	Cyan,
	Red,
	Magenta,
	Brown,
	Lightgray,
	Darkgray,
	Lightblue,
	Lightgreen,
	Lightcyan,
	Lightred,
	Lightmagenta,
	Yellow,
	White
};

// Functions
void Print(const std::string& text, const TextColor& color = TextColor::White);

#pragma endregion ConsoleFunctionality

#pragma region Collision
bool PointCollision(const Point2f& point, const Circlef& circle);
bool PointCollision(const Point2f& point, const Rectf& rect);
bool ShapeCollision(const Rectf& rect1, const Rectf& rect2);
bool ShapeCollision(const Circlef& circle, const Rectf& rect);
bool ShapeCollision(const Circlef& circle1, const Circlef& circle2);
#pragma endregion Collision

// Properties of a wave:
// - How high does the wave go?		AMPLITUDE
// - How fast does the wave move?	FREQUENCY / WAVELENGTH
// - Where do we start?				PHASE