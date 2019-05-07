#include "gui_tetrix_main_window.h"


GUITetrixMainWindow::GUITetrixMainWindow(uint size_of_game_element)
{
    this->_size_of_game_element = size_of_game_element;

    this->SetupUi();
    this->SetupSS();
};


void GUITetrixMainWindow::RotateTo(const FigureDirection& direction)
{
    _game_field->RotateTo(direction);
};


void GUITetrixMainWindow::MoveTo(const MoveVector& vector)
{
    _game_field->MoveTo(vector);
};


 void GUITetrixMainWindow::TextInfoUpdate()
 {
    _line_edit_level->setText("level = " + QString::number(_level));

    _line_edit_score->setText("scoore = " + QString::number(_score));

    _line_edit_removed_line->setText("removed = " + QString::number(_removed_lines));
 };


void GUITetrixMainWindow::SetupUi()
{
    this->resize(_size_of_game_element * 20, _size_of_game_element * 40);
    this->setMinimumSize(_size_of_game_element * 10, _size_of_game_element * 20);
        _widget_central = new QWidget(this);
            _vertical_layout = new QVBoxLayout(_widget_central);
                _grid_layout = new QGridLayout(_widget_central);
                    _game_field = new GUITetrixGameField(_widget_central, _size_of_game_element);
                _grid_layout->addWidget(_game_field, 0, 0, 1, 2);
                    _push_button_start = new QPushButton("START", _widget_central);
                _grid_layout->addWidget(_push_button_start, 1, 0, 1, 1);
                    _push_button_pause = new QPushButton("PAUSE", _widget_central);
                    _push_button_pause->setEnabled(false);
                _grid_layout->addWidget(_push_button_pause, 2, 0, 1, 1);
                    _push_button_stop = new QPushButton("STOP", _widget_central);
                    _push_button_stop->setEnabled(false);
                _grid_layout->addWidget(_push_button_stop, 3, 0, 1, 1);
                    _line_edit_level = new QLineEdit("level = 0", _widget_central);
                    _line_edit_level->setAlignment(Qt::AlignCenter);
                _grid_layout->addWidget(_line_edit_level, 1, 1, 1, 1);
                    _line_edit_score = new QLineEdit("score = 0", _widget_central);
                    _line_edit_score->setAlignment(Qt::AlignCenter);
                _grid_layout->addWidget(_line_edit_score, 2, 1, 1, 1);
                    _line_edit_removed_line = new QLineEdit("removed = 0", _widget_central);
                    _line_edit_removed_line->setAlignment(Qt::AlignCenter);
                _grid_layout->addWidget(_line_edit_removed_line, 3, 1, 1, 1);
            _vertical_layout->addLayout(_grid_layout);

    this->setCentralWidget(_widget_central);
};


void GUITetrixMainWindow::SetupSS()
{
    QObject::connect(_push_button_start, SIGNAL( clicked() ), this, SLOT( StartGame() ));

    QObject::connect(_push_button_pause, SIGNAL( clicked() ), this, SLOT( PauseGame() ));

    QObject::connect(_push_button_stop, SIGNAL( clicked() ), this, SLOT( StopGame() ));

    QObject::connect(_game_field, SIGNAL( DelletedRows(size_t) ), this, SLOT( ScooreIncrease(size_t) ));

    QObject::connect(_game_field, SIGNAL( RemovedElements(size_t) ), this, SLOT( ScooreDecrease(size_t) ));
};
