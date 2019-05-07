#include "game_element.h"


GameElement::GameElement(const uint& x, const uint& y, const uint8_t id_local, const uint64_t& id_global, const uint8_t color[3])
{
    X = x;
    Y = y;
    ID_local = id_local;
    ID_global = id_global;
    Color[0] = color[0]; Color[1] = color[1]; Color[2] = color[2];
    State = StateTetrixElement::Downing;
};


GameElement::GameElement(const uint& x, const uint& y, const uint8_t id_local, const uint64_t& id_global, const uint8_t color[3], const StateTetrixElement& state)
{
    X = x;
    Y = y;
    ID_local = id_local;
    ID_global = id_global;
    Color[0] = color[0]; Color[1] = color[1]; Color[2] = color[2];
    State = state;
};


QColor GameElement::GetColor() const
{
    return QColor(Qt::black);
};


QBrush GameElement::GetBrush() const
{
    return QBrush(QColor(Color[0], Color[1], Color[2]), Qt::SolidPattern);
};


void GameElement::MoveTo(const MoveVector& vector)
{
    switch (vector)
    {
        case MoveVector::MoveUp:
        {
            --Y;
            return;
        }
        case MoveVector::MoveDown:
        {
            ++Y;
            return;
        }
        case MoveVector::MoveLeft:
        {
            --X;
            return;
        }
        case MoveVector::MoveRight:
        {
            ++X;
            return;
        }
    }
};


void GameElement::SetX(const uint& x)
{
    X = x;
};


void GameElement::SetY(const uint& y)
{
    Y = y;
};


uint GameElement::GetX() const
{
    return X;
};


uint GameElement::GetY() const
{
    return Y;
};


uint64_t GameElement::GetID() const
{
    return ID_global;
};


uint8_t GameElement::GetId() const
{
    return ID_local;
};


void GameElement::SetState(const StateTetrixElement& state)
{
    State = state;
};


StateTetrixElement GameElement::GetState() const
{
    return State;
};


bool GameElement::CheckCondition(const uint& x_size, const uint& y_size) const
{
    if( (X < x_size) and (Y < y_size) )
        return true;

    return false;
};
