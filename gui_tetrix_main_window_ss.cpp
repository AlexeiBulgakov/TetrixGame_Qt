#include "gui_tetrix_main_window.h"


void GUITetrixMainWindow::StartGame()
{
    if(!_is_started)
    {
        _game_field->Start();

        _is_started = true;

        _is_pause = false;

        _push_button_pause->setEnabled(true);

        _push_button_stop->setEnabled(true);

        _push_button_start->setStyleSheet("QPushButton { background-color: rgb(0, 200, 0) }");

        _push_button_pause->setStyleSheet("QPushButton { background-color: rgb(200, 200, 0) }");

        _push_button_stop->setStyleSheet("QPushButton { background-color: rgb(200, 200, 0) }");
    }
    else
    {
        _is_pause = false;

        _game_field->Restart();

        _push_button_start->setStyleSheet("QPushButton { background-color: rgb(0, 200, 0) }");

        _push_button_pause->setStyleSheet("QPushButton { background-color: rgb(200, 200, 0) }");

        _push_button_stop->setStyleSheet("QPushButton { background-color: rgb(200, 200, 0) }");
    }
};


void GUITetrixMainWindow::PauseGame()
{
    if(!_is_pause)
    {
        _game_field->Pause();

        _is_pause = true;

        _push_button_start->setStyleSheet("QPushButton { background-color: rgb(200, 200, 0) }");

        _push_button_pause->setStyleSheet("QPushButton { background-color: rgb(0, 200, 0) }");

        _push_button_stop->setStyleSheet("QPushButton { background-color: rgb(200, 200, 0) }");
    }
    else
    {
        _game_field->Start();

        _is_pause = false;

        _push_button_start->setStyleSheet("QPushButton { background-color: rgb(0, 200, 0) }");

        _push_button_pause->setStyleSheet("QPushButton { background-color: rgb(200, 200, 0) }");

        _push_button_stop->setStyleSheet("QPushButton { background-color: rgb(200, 200, 0) }");
    }
};


void GUITetrixMainWindow::StopGame()
{
    _game_field->Restart();

    _game_field->Pause();

    _is_pause = true;

    _score = 0;

    _level = 0;

    _removed_lines = 0;

    _game_field->SpeedUpdate(_level);

    this->TextInfoUpdate();

    _push_button_start->setStyleSheet("QPushButton { background-color: rgb(200, 200, 0) }");

    _push_button_pause->setStyleSheet("QPushButton { background-color: rgb(200, 200, 0) }");

    _push_button_stop->setStyleSheet("QPushButton { background-color: rgb(0, 200, 0) }");
};


void GUITetrixMainWindow::keyPressEvent(QKeyEvent *event)
{
    if (_is_started && !_is_pause)
    {
        switch (event->key())
        {
            //W-A-S-D (Moving)
            case (Qt::Key::Key_W):
            {
                this->MoveTo(MoveVector::MoveUp);
                return;
            }
            case (Qt::Key::Key_S):
            {
                this->MoveTo(MoveVector::MoveDown);
                return;
            }
            case (Qt::Key::Key_A):
            {
                this->MoveTo(MoveVector::MoveLeft);
                return;
            }
            case (Qt::Key::Key_D):
            {
                this->MoveTo(MoveVector::MoveRight);
                return;
            }

            //Up(O)-Down(L)-Right(K)-Left(;) (Rotating)
            case (Qt::Key::Key_O):
            {
                this->RotateTo(FigureDirection::DirectionUp);
                return;
            }
            case (Qt::Key::Key_L):
            {
                this->RotateTo(FigureDirection::DirectionDown);
                return;
            }
            case (Qt::Key::Key_K):
            {
                this->RotateTo(FigureDirection::DirectionLeft);
                return;
            }
            case (Qt::Key::Key_Semicolon):
            {
                this->RotateTo(FigureDirection::DirectionRight);
                return;
            }

        }//switch (event->key())

    }//if (_is_started && !_is_pause)
};


void GUITetrixMainWindow::ScooreIncrease(const size_t& count_of_delleted_rows)
{
    _removed_lines += count_of_delleted_rows;
    _score += (count_of_delleted_rows * _game_field->GetXSize());
    _level = (_score / 10);

    _game_field->SpeedUpdate(_level);

    this->TextInfoUpdate();
};


void GUITetrixMainWindow::ScooreDecrease(const size_t& count_of_removed_elements)
{
    _score -= count_of_removed_elements;

    this->TextInfoUpdate();
};
