#pragma once

namespace game_framework
{
	class Vector2
	{
	private:
		int X, Y;

	public:
		Vector2(void);
		Vector2(int X, int Y);
		~Vector2(void);

		int getX();
		void setX(int X);
		int getY();
		void setY(int Y);
	};
}