#include <iostream>
#include "Vector3.h"
#include "utils.h"
#include "AmrothUtils.h"

//#define _USE_MATH_DEFINES
//#include <math.h>

// Definition
#pragma region General

// Sin/Waves
double WaveMovement	(int moved, int fullMovement)
{
	return WaveMovement	(double(moved), double(fullMovement));
}
double WaveMovement	(float moved, float fullMovement)
{
	return WaveMovement	(double(moved), double(fullMovement));
}
double WaveMovement	(double moved, double fullMovement)
{
	const double angle{ moved / fullMovement * (2 * M_PI) };
	return sin(angle);
}

void DrawCircle(float posX, float posY, float radius, int segments)
{
	const float theta = M_PI * 2 / float(segments);
	const float tangetial_factor = tanf(theta);//calculate the tangential factor 

	const float radial_factor = cosf(theta);//calculate the radial factor 

	float x = radius;//we start at angle = 0 

	float y = 0;
	glLineWidth(2);
	glBegin(GL_LINE_LOOP);
	glPolygonMode(GL_FRONT, GL_FILL);
	for (int ii = 0; ii < segments; ii++)
	{
		glVertex2f(x + posX, y + posY);//output vertex 

		//calculate the tangential vector 
		//remember, the radial vector is (x, y) 
		//to get the tangential vector we flip those coordinates and negate one of them 

		float tx = -y;
		float ty = x;

		//add the tangential vector 

		x += tx * tangetial_factor;
		y += ty * tangetial_factor;

		//correct using the radial factor 

		x *= radial_factor;
		y *= radial_factor;
	}
	glEnd();
}

// Color Functions
void SetColor(const Color& color, const float& alpha)
{
	Vector3 rgb{};

	switch (color)
	{
	case Color::White:
		rgb = Vector3(255, 255, 255);
		break;
	case Color::Black:
		rgb = Vector3(0, 0, 0);
		break;
	case Color::Red:
		rgb = Vector3(255, 0, 0);
		break;
	case Color::Green:
		rgb = Vector3(0, 255, 0);
		break;
	case Color::Blue:
		rgb = Vector3(0, 0, 255);
		break;
	case Color::Cyan:
		rgb = Vector3(0, 255, 255);
		break;
	case Color::Pink:
		rgb = Vector3(255, 105, 180);
		break;
	case Color::Orange:
		rgb = Vector3(255, 165, 0);
		break;
	case Color::Yellow:
		rgb = Vector3(255, 255, 0);
		break;
	case Color::Magenta:
		rgb = Vector3(255, 0, 255);
		break;
	case Color::Purple:
		rgb = Vector3(128, 0, 128);
		break;
	}

	glColor4f(rgb.x / 255, rgb.y / 255, rgb.z / 255, alpha);
}
#pragma endregion General

#pragma region MathCalculations

// Basic Math Functions
bool	IsEven(const int& a) { return a % 2 == 0; }

int		Modulo(const int& a, const int& b)
{
	//Divide one value by the other & round it to an int
	const int roundedDivisionValue{ int(round(a / b)) };

	//Multiply the divisor by the quotient
	const int multipliedValue{ roundedDivisionValue * b };

	//Subtract multiplied value from the initial number
	return a - multipliedValue;
}

void	Clamp(float& value, const float& minValue, const float& maxValue)
{
	if (value > maxValue) value = maxValue;
	else if (value < minValue) value = minValue;
}

void	Clamp(int& value, const int& minValue, const int& maxValue)
{
	if (value > maxValue) value = maxValue;
	else if (value < minValue) value = minValue;
}

float	GetDistanceBetween(const Point2f& fromPoint, const Point2f& toPoint)
{
	return sqrtf(powf(toPoint.x - fromPoint.x, 2) + powf(toPoint.y - fromPoint.y, 2));
}

float	GetAngleDifference(const float& fromAngle, const float& toAngle)
{
	return atan2f(sinf(toAngle - fromAngle), cosf(toAngle - fromAngle));
}

float	GetAngleToPoint(const Point2f& fromPoint, const Point2f& toPoint)
{
	return atan2(toPoint.y - fromPoint.y, toPoint.x - fromPoint.x);
}

float	RadiansToDegrees(const float& radians)
{
	return radians / utils::g_Pi * 180;
}

float	DegreesToRadians(const float& degrees)
{
	return degrees / 180 * utils::g_Pi;
}

int		GetNumberFromUser(const std::string& inputText, const std::string& invalidText, const int& min,  const int& max)
{
	int number{};

	while (true)
	{
		std::cout << inputText;
		std::cin >> number;

		if (std::cin.fail() || std::cin.peek() != '\n' || number < min || number > max)
		{
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
			std::cout << invalidText << std::endl;

			continue;
		}

		return number;
	}
	return 0;
}

float	RandomRange(float min, float max)
{
	// Inverse in case of the opposite
	if (min > max)
	{
		const float tempMax = max;
		max = min;
		min = tempMax;
	}

	const float randomAlpha{ float(rand()) / RAND_MAX };
	const float range{ max - min };

	return randomAlpha * range + min;
}

int		RandomRange(int min, int max)
{
	// Inverse in case of the opposite
	if (min > max)
	{
		const int tempMax = max;
		max = min;
		min = tempMax;
	}

	return rand() % (max - min + 1) + min;
}

float GetSpeed(const float& velocity, const float& acceleration, const float& time)
{
	return velocity + (acceleration * time);
}

float GetSpeedByAcceleration(const float& initialVelocity, const float& acceleration, const float& initialPosition, const float& position)
{
	const float powerOf{ 2 };
	return pow(initialVelocity, powerOf) + 2 * acceleration * (position - initialPosition);
}

#pragma endregion MathCalculations

#pragma region ConsoleFunctions
void Print(const std::string& text, const TextColor& color)
{
	SetConsoleTextAttribute(g_HConsole, 0 | static_cast<int>(color));
	std::cout << text;
	SetConsoleTextAttribute(g_HConsole, 0 | static_cast<int>(TextColor::White));
}
#pragma endregion ConsoleFunctions

#pragma region Collision
bool PointCollision(const Point2f& point, const Circlef& circle)
{
	const float xBounds = point.x - circle.center.x;
	const float yBounds = point.y - circle.center.y;

	const float distanceCompared = float(sqrt(pow(xBounds, 2) + pow(yBounds, 2)));

	return distanceCompared <= circle.radius ? true : false;
}
bool PointCollision(const Point2f& point, const Rectf& rect)
{
	const bool xWithinBoundary = point.x >= rect.left && point.x <= rect.left + rect.width;
	const bool yWithinBoundary = point.y >= rect.bottom && point.y <= rect.bottom + rect.height;

	return xWithinBoundary && yWithinBoundary ? true : false;
}
bool ShapeCollision(const Rectf& rect1, const Rectf& rect2)
{
	if (rect1.left < rect2.left + rect2.width &&
		rect1.left + rect1.width > rect2.left &&
		rect1.bottom < rect2.bottom + rect2.height &&
		rect1.height + rect1.bottom > rect2.bottom)
	{
		return true;
	}
	return false;
}
bool ShapeCollision(const Circlef& circle, const Rectf& rect)
{
	const float distX = std::abs(circle.center.x - (rect.left + rect.width / 2));
	const float distY = std::abs(circle.center.y - (rect.bottom + rect.height / 2));

	if (distX > (rect.width / 2 + circle.radius)) { return false; }
	if (distY > (rect.height / 2 + circle.radius)) { return false; }

	if (distX <= (rect.width / 2)) { return true; }
	if (distY <= (rect.height / 2)) { return true; }

	float dx = distX - rect.width / 2;
	float dy = distY - rect.height / 2;

	return (dx * dx) + (dy * dy) <= (circle.radius * circle.radius);
}
bool ShapeCollision(const Circlef& circle1, const Circlef& circle2)
{
	const float xBounds = circle1.center.x - circle2.center.x;
	const float yBounds = circle1.center.y - circle2.center.y;

	const float boundsCompared = float(pow(xBounds, 2) + pow(yBounds, 2));

	const bool distanceCompared = boundsCompared <= pow(circle1.radius + circle2.radius, 2);

	return distanceCompared;
}
#pragma endregion Collision