#include "gui_tetrix_gamefield.h"


void GUITetrixGameField::Update()
{
    if (size_t count_of_delleted_rows { GF->NextStep() }; count_of_delleted_rows > 0)
        emit DelletedRows(count_of_delleted_rows);
};


void GUITetrixGameField::Reprint()
{
    for(QGraphicsItem *item : _graphic_scene_game_field->items()) delete item;

    bool is_overup_position_any_element {false};

    if (GF != nullptr)
    {
        uint over_up_position = GF->GetMBoder();
        uint stop_line_height = over_up_position  * _one_element_size;
        _graphic_scene_game_field->addLine(QLine(QPoint(0, stop_line_height), QPoint(_fild_size_w  * _one_element_size, stop_line_height)), QPen(Qt::red));

        for (auto &[X, Y, Color, Brush, State] : GF->GetListViewvalentElement())
        {
            _graphic_scene_game_field->addRect(QRectF(X * _one_element_size, Y *_one_element_size, _one_element_size, _one_element_size), QPen(Color),  Brush);

            if ((Y < over_up_position) && (State != StateTetrixElement::Downing))
                is_overup_position_any_element = true;
        }
    }

     _graphic_scene_game_field->addRect(QRectF(0, 0, _fild_size_w  * _one_element_size, _fild_size_h  * _one_element_size), QPen(Qt::black));

     if(is_overup_position_any_element) {
         _graphic_scene_game_field->addRect(QRectF(0, 0, _fild_size_w  * _one_element_size, _fild_size_h  * _one_element_size), QPen(Qt::red), QBrush(Qt::red, Qt::Dense7Pattern));
         _timer_update->stop();
         _timer_show->stop();
     }
};


void GUITetrixGameField::resizeEvent(QResizeEvent* event)
{
    QSize current_size = event->size();

    _fild_size_h = static_cast<uint>(current_size.height() / static_cast<double>(_one_element_size)) - 1;
    _fild_size_w = static_cast<uint>(current_size.width()  / static_cast<double>(_one_element_size)) - 1;

    if (GF != nullptr)
        if(size_t count_of_delleted_elements {GF->Reconstruct(_fild_size_w, _fild_size_h)}; count_of_delleted_elements > 0)
            emit RemovedElements(count_of_delleted_elements);

    this->Reprint();
};
