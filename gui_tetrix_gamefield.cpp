#include "gui_tetrix_gamefield.h"


GUITetrixGameField::GUITetrixGameField(QWidget* parent, uint one_element_size)
{
    _one_element_size = one_element_size;

    this->SetupUi(parent);
    this->SetupSS();
};


void GUITetrixGameField::Start()
{
    if (GF == nullptr)
    {
        GF = new GameFiled(_fild_size_w, _fild_size_h);

        GF->AddFigure(TetrixFigure::long_line);

        _timer_update->start(_current_speed);

        _timer_show->start();
    }
    else
    {
        _timer_update->start();

        _timer_show->start();
    }
};


void GUITetrixGameField::Pause()
{
    _timer_update->stop();

    _timer_show->stop();
};


void GUITetrixGameField::Restart()
{
    if (GF == nullptr)
    {
        GF = new GameFiled(_fild_size_w, _fild_size_h);

        GF->AddFigure(TetrixFigure::long_line);

        _timer_update->start(_current_speed);

        _timer_show->start();
    }
    else
    {
        delete GF;

        GF = new GameFiled(_fild_size_w, _fild_size_h);

        GF->AddFigure(TetrixFigure::long_line);

        _timer_update->start(_current_speed);

        _timer_show->start();
    }
};


void GUITetrixGameField::MoveTo(const MoveVector& vertor)
{
    GF->MoveTo(vertor);
};


void GUITetrixGameField::RotateTo(const FigureDirection& direction)
{
    GF->RotateTo(direction);
};


void GUITetrixGameField::SpeedUpdate(size_t current_level)
{
    if(uint updated_speed {_up_limit_current_speed - (current_level * 10)}; updated_speed > 10)
        _current_speed = updated_speed;
    else
        _current_speed = 10;

    _timer_update->setInterval(_current_speed);
};


uint GUITetrixGameField::GetXSize() const
{
    return GF->GetX();
};


uint GUITetrixGameField::GetYSize() const
{
    return GF->GetY();
};


void GUITetrixGameField::SetupUi(QWidget* parent)
{
    _timer_show = new QTimer();
    _timer_update = new QTimer();

    this->setParent(parent);
    this->setAlignment(Qt::AlignCenter);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
        _graphic_scene_game_field = new QGraphicsScene(this);
            _graphic_items_tetrix_elements = new QGraphicsItemGroup();

    this->setScene(_graphic_scene_game_field);

    _timer_show->start(32); //обновление области отрисовки игрового поля происходит с переодичностью - 30 раз в 1 секунду.
};


void GUITetrixGameField::SetupSS()
{
    QObject::connect(_timer_show, SIGNAL(timeout()), this, SLOT(Reprint()));

    QObject::connect(_timer_update, SIGNAL(timeout()), this, SLOT(Update()));

    //QObject::connect(this, SIGNAL(timeout()), this, SLOT(SlotUpdate()));
};
