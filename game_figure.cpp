#include "game_figure.h"

GameFigure::GameFigure(const TetrixFigure& figure, const uint& x, const uint& y, const uint64_t& id, const uint8_t color[3])
{
    Figure = figure;
    X = x;
    Y = y;
    ID = id;
    Color[0] = color[0]; Color[1] = color[1]; Color[2] = color[3];
    Direction = FigureDirection::DirectionRight;
    State = StateTetrixElement::Downing;

    switch (figure)
    {
        case (TetrixFigure::long_line):
        {
            GE.push_back(GameElement(X,     Y, 0, ID, Color));
            GE.push_back(GameElement(X + 1, Y, 1, ID, Color));
            GE.push_back(GameElement(X + 2, Y, 2, ID, Color));
            GE.push_back(GameElement(X + 3, Y, 3, ID, Color));
            return;
        }
        case (TetrixFigure::square):
        {
            GE.push_back(GameElement(X,     Y,     0, ID, Color));
            GE.push_back(GameElement(X + 1, Y,     1, ID, Color));
            GE.push_back(GameElement(X    , Y + 1, 2, ID, Color));
            GE.push_back(GameElement(X + 1, Y + 1, 3, ID, Color));
            return;
        }
        case (TetrixFigure::zig_zag):
        {
            GE.push_back(GameElement(X,     Y,     0, ID, Color));
            GE.push_back(GameElement(X + 1, Y,     1, ID, Color));
            GE.push_back(GameElement(X + 1, Y + 1, 2, ID, Color));
            GE.push_back(GameElement(X + 2, Y + 1, 3, ID, Color));
            return;
        }
        case (TetrixFigure::g_line):
        {
            GE.push_back(GameElement(X,     Y,     0, ID, Color));
            GE.push_back(GameElement(X + 1, Y,     1, ID, Color));
            GE.push_back(GameElement(X + 2, Y,     2, ID, Color));
            GE.push_back(GameElement(X + 2, Y + 1, 3, ID, Color));
            return;
        }

    }//switch
};


StateTetrixElement GameFigure::GetState() const
{
    return State;
};


void GameFigure::SetState(const StateTetrixElement& state)
{
    State = state;
    for(auto& game_element : GE)
        game_element.SetState(state);
};


void GameFigure::MoveTo(const MoveVector& vertor)
{
    if (State == StateTetrixElement::Downing)
    {
        switch (vertor)
        {
            case MoveVector::MoveUp:
            {
                --Y;
                break;
            }
            case MoveVector::MoveDown:
            {
                ++Y;
                break;
            }
            case MoveVector::MoveLeft:
            {
                --X;
                break;
            }
            case MoveVector::MoveRight:
            {
                ++X;
                break;
            }
        }//switch

        for(auto& game_element : GE)
            game_element.MoveTo(vertor);

        return;

    }//if
};


void GameFigure::RotateTo(const FigureDirection& direction)
{
    if (State == StateTetrixElement::Downing)
    {
        switch (Figure)
        {
            case (TetrixFigure::long_line):
            {
                this->RotateLongLine(direction);
                return;
            }//long_line

            case (TetrixFigure::square):
            {
                this->RotateSquare(direction);
                return;
            }//square

            case (TetrixFigure::zig_zag):
            {
                this->RotateZigZag(direction);
                return;
            }//zig_zag

            case (TetrixFigure::g_line):
            {
                this->RotateGLine(direction);
                return;
            }//g_line

        }//switch-figure

    }//if
};


bool GameFigure::CheckCondition(const uint& x_size, const uint& y_size) const
{
    for(const auto& element : GE)
        if (!element.CheckCondition(x_size, y_size))
            return false;

    return true;
};


const vector<GameElement>& GameFigure::GetFigureElementC() const
{
    return GE;
};


vector<GameElement>& GameFigure::GetFigureElement()
{
    return GE;
};


void GameFigure::RotateLongLine(const FigureDirection& direction)
{
    switch (direction)
    {
        case (FigureDirection::DirectionUp):
        {
            GE.at(0).SetX(X); GE.at(0).SetY(Y);
            GE.at(1).SetX(X); GE.at(1).SetY(Y - 1);
            GE.at(2).SetX(X); GE.at(2).SetY(Y - 2);
            GE.at(3).SetX(X); GE.at(3).SetY(Y - 3);
            Direction = FigureDirection::DirectionUp;
            return;
        }
        case (FigureDirection::DirectionDown):
        {
            GE.at(0).SetX(X); GE.at(0).SetY(Y);
            GE.at(1).SetX(X); GE.at(1).SetY(Y + 1);
            GE.at(2).SetX(X); GE.at(2).SetY(Y + 2);
            GE.at(3).SetX(X); GE.at(3).SetY(Y + 3);
            Direction = FigureDirection::DirectionDown;
            return;
        }
        case (FigureDirection::DirectionLeft):
        {
            GE.at(0).SetX(X);     GE.at(0).SetY(Y);
            GE.at(1).SetX(X - 1); GE.at(1).SetY(Y);
            GE.at(2).SetX(X - 2); GE.at(2).SetY(Y);
            GE.at(3).SetX(X - 3); GE.at(3).SetY(Y);
            Direction = FigureDirection::DirectionLeft;
            return;
        }
        case (FigureDirection::DirectionRight):
        {
            GE.at(0).SetX(X);     GE.at(0).SetY(Y);
            GE.at(1).SetX(X + 1); GE.at(1).SetY(Y);
            GE.at(2).SetX(X + 2); GE.at(2).SetY(Y);
            GE.at(3).SetX(X + 3); GE.at(3).SetY(Y);
            Direction = FigureDirection::DirectionRight;
            return;
        }

    }//switch-Direction
};


void GameFigure::RotateSquare(const FigureDirection& direction)
{
    switch (direction)
    {
        case (FigureDirection::DirectionUp):
        {
            GE.at(0).SetX(X);     GE.at(0).SetY(Y);
            GE.at(1).SetX(X);     GE.at(1).SetY(Y - 1);
            GE.at(2).SetX(X + 1); GE.at(2).SetY(Y);
            GE.at(3).SetX(X + 1); GE.at(3).SetY(Y - 1);
            Direction = FigureDirection::DirectionUp;
            return;
        }
        case (FigureDirection::DirectionDown):
        {
            GE.at(0).SetX(X);     GE.at(0).SetY(Y);
            GE.at(1).SetX(X);     GE.at(1).SetY(Y + 1);
            GE.at(2).SetX(X - 1); GE.at(2).SetY(Y);
            GE.at(3).SetX(X - 1); GE.at(3).SetY(Y + 1);
            Direction = FigureDirection::DirectionDown;
            return;
        }
        case (FigureDirection::DirectionLeft):
        {
            GE.at(0).SetX(X);     GE.at(0).SetY(Y);
            GE.at(1).SetX(X - 1); GE.at(1).SetY(Y);
            GE.at(2).SetX(X);     GE.at(2).SetY(Y - 1);
            GE.at(3).SetX(X - 1); GE.at(3).SetY(Y - 1);
            Direction = FigureDirection::DirectionLeft;
            return;
        }
        case (FigureDirection::DirectionRight):
        {
            GE.at(0).SetX(X);     GE.at(0).SetY(Y);
            GE.at(1).SetX(X + 1); GE.at(1).SetY(Y);
            GE.at(2).SetX(X);     GE.at(2).SetY(Y + 1);
            GE.at(3).SetX(X + 1); GE.at(3).SetY(Y + 1);
            Direction = FigureDirection::DirectionRight;
            return;
        }

    }//switch-Direction
};


void GameFigure::RotateZigZag(const FigureDirection& direction)
{
    switch (direction)
    {
        case (FigureDirection::DirectionUp):
        {
            GE.at(0).SetX(X);     GE.at(0).SetY(Y);
            GE.at(1).SetX(X);     GE.at(1).SetY(Y - 1);
            GE.at(2).SetX(X + 1); GE.at(2).SetY(Y - 1);
            GE.at(3).SetX(X + 1); GE.at(3).SetY(Y - 2);
            Direction = FigureDirection::DirectionUp;
            return;
        }
        case (FigureDirection::DirectionDown):
        {
            GE.at(0).SetX(X);     GE.at(0).SetY(Y);
            GE.at(1).SetX(X);     GE.at(1).SetY(Y + 1);
            GE.at(2).SetX(X - 1); GE.at(2).SetY(Y + 1);
            GE.at(3).SetX(X - 1); GE.at(3).SetY(Y + 2);
            Direction = FigureDirection::DirectionDown;
            return;
        }
        case (FigureDirection::DirectionLeft):
        {
            GE.at(0).SetX(X);     GE.at(0).SetY(Y);
            GE.at(1).SetX(X - 1); GE.at(1).SetY(Y);
            GE.at(2).SetX(X - 1); GE.at(2).SetY(Y + 1);
            GE.at(3).SetX(X - 2); GE.at(3).SetY(Y + 1);
            Direction = FigureDirection::DirectionLeft;
            return;
        }
        case (FigureDirection::DirectionRight):
        {
            GE.at(0).SetX(X);     GE.at(0).SetY(Y);
            GE.at(1).SetX(X + 1); GE.at(1).SetY(Y);
            GE.at(2).SetX(X + 1); GE.at(2).SetY(Y + 1);
            GE.at(3).SetX(X + 2); GE.at(3).SetY(Y + 1);
            Direction = FigureDirection::DirectionRight;
            return;
        }

    }//switch-Direction
};


void GameFigure::RotateGLine(const FigureDirection& direction)
{
    switch (direction)
    {
        case (FigureDirection::DirectionUp):
        {
            GE.at(0).SetX(X);     GE.at(0).SetY(Y);
            GE.at(1).SetX(X);     GE.at(1).SetY(Y - 1);
            GE.at(2).SetX(X);     GE.at(2).SetY(Y - 2);
            GE.at(3).SetX(X + 1); GE.at(3).SetY(Y - 2);
            Direction = FigureDirection::DirectionUp;
            return;
        }
        case (FigureDirection::DirectionDown):
        {
            GE.at(0).SetX(X);     GE.at(0).SetY(Y);
            GE.at(1).SetX(X);     GE.at(1).SetY(Y + 1);
            GE.at(2).SetX(X);     GE.at(2).SetY(Y + 2);
            GE.at(3).SetX(X - 1); GE.at(3).SetY(Y + 2);
            Direction = FigureDirection::DirectionDown;
            return;
        }
        case (FigureDirection::DirectionLeft):
        {
            GE.at(0).SetX(X);     GE.at(0).SetY(Y);
            GE.at(1).SetX(X - 1); GE.at(1).SetY(Y);
            GE.at(2).SetX(X - 2); GE.at(2).SetY(Y);
            GE.at(3).SetX(X - 2); GE.at(3).SetY(Y - 1);
            Direction = FigureDirection::DirectionLeft;
            return;
        }
        case (FigureDirection::DirectionRight):
        {
            GE.at(0).SetX(X);     GE.at(0).SetY(Y);
            GE.at(1).SetX(X + 1); GE.at(1).SetY(Y);
            GE.at(2).SetX(X + 2); GE.at(2).SetY(Y);
            GE.at(3).SetX(X + 2); GE.at(3).SetY(Y + 1);
            Direction = FigureDirection::DirectionRight;
            return;
        }

    }//switch-Direction
};
