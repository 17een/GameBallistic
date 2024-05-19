#include "Stone.h"

BallisticGame::Stone::Stone(System::Drawing::Color color, int x, int y, bool left)
{
    this->Color = color;
    this->Angle = 45;
    this->Speed = 75;
    this->Mass = 50;
    this->X = x;
    this->Y = y;
    this->Left = left;
}

int BallisticGame::Stone::getAngle()
{
    return this->Angle;
}

void BallisticGame::Stone::setAngle(int angle)
{
    // Установка ограничений на угол (от 0 до 90)
    if (angle >= 90 || angle <= 0)
        throw gcnew System::ArgumentException("Angle should be more than 0 and less than 90");
    this->Angle = angle;
}

int BallisticGame::Stone::getSpeed()
{
    return this->Speed;
}

void BallisticGame::Stone::setSpeed(int speed)
{
    // Установка ограничений на скорость (от 0 до 150)
    if (speed > 150 || speed <= 0)
        throw gcnew System::ArgumentException("Speed should be more than 0 and less than 150");
    this->Speed = speed;
}

int BallisticGame::Stone::getMass()
{
    return this->Mass;
}

void BallisticGame::Stone::setMass(int mass)
{
    // Установка ограничений на массу (от 0 до 100)
    if (mass > 100 || mass <= 0)
        throw gcnew System::ArgumentException("Mass should be more than 0 and less than 100");
    this->Mass = mass;
}

bool BallisticGame::Stone::shoot(Graphics^ graphics, int xtarget, int ytarget, int size)
{
    double deg = Math::PI / 180;
    double angle = this->getAngle() * deg;
    double g = 9.81 * this->getMass() / 50;
    double t = 0;
    int v = this->getSpeed();

    int offset = 260 + size / 2;

    Pen^ pen = gcnew Pen(this->Color, 3.0f);
    double x = this->X;
    double y = this->Y;


    int x1 = xtarget;
    int y1 = ytarget + 260 + size / 2;
    int x2 = x1 + size / 2;
    int y2 = y1 - size / 2;
    
    if (this->isLeft())
    {
        x2 = x1 - size / 2;
    }

    while (y >= 0)
    {
        int xDrawing = (int) x;
        int yDrawing = (int) (offset - y);

        if (this->isLeft())
        {
            xDrawing = this->X + xDrawing;
            yDrawing = this->Y + yDrawing;
            if (xDrawing > x2 && xDrawing < x1 && yDrawing > y2 && yDrawing < y1)
                return true;
        }
        else
        {
            xDrawing = this->X - xDrawing;
            yDrawing = this->Y + yDrawing;
            if (xDrawing < x2 && xDrawing > x1 && yDrawing > y2 && yDrawing < y1)
                return true;
        }

        if (this->isLeft())
        {
            graphics->DrawLine(pen, xDrawing, yDrawing, xDrawing + 1, yDrawing + 1);
        }
        else
        {
            graphics->DrawLine(pen, xDrawing, yDrawing, xDrawing + 1, yDrawing + 1);
        }
        x = t * v * Math::Cos(angle);
        y = t * v * Math::Sin(angle) - g * (( t * t ) / 2);

        t += 0.1;
    }

    return false;
}

bool BallisticGame::Stone::isLeft()
{
    return this->Left;
}
