/* КЛАСС ОТВЕСТВЕННЫЙ НА ИГОВУЮ ФИГУРУ. */

#pragma once

#include "stdafx.h"
#include "game_element.h"
#include "tetrix_figures.h"
#include "tetrix_element_state.h"

/* Возможные направления "повёрнутость" игровой фигуры. */
enum FigureDirection
{
    DirectionUp,
    DirectionDown,
    DirectionLeft,
    DirectionRight
};


class GameFigure
{

public:

    /* Конструктор игровой фигуры:
     * Замечание: координаты X, Y фигуры не являются достаточными для опредления положения фигуры на игровом поле. Эти координаты назначаются в качестве координат одному из игровых элементов, составляющих фигуру, что формально считается первым.
     * [figure] - какая конкретно фигура будет управляться экземпляром класса.
     * [x]      - позиционирование фигуры по оси абсцис.
     * [y]      - позиционирование фигуры по оси ординат.
     * [id]     - глобальный идентификатор фигуры (уникальный в рамках всего временного периода игровой сессии).
     * [color]  - три числа в диапазоне целых числе от 0 до 255, отражающих цветовую палитру RGB - заливка игровой фигуры. */
    GameFigure(const TetrixFigure& figure, const uint& x, const uint& y, const uint64_t& id, const uint8_t color[3]);

    /* Возвращает текущее состояние игровой фигуры.
     * Замечание: состояние иговых элементов, привязанных к конкретной фигуре, может отличаться от состояния фигуры, после того как ей назначается состояние Removed. */
    StateTetrixElement GetState() const;

    /* Изменяет текущее состояние игровой фигуры и всех подконтрольных ей игровых элементов. */
    void SetState(const StateTetrixElement& state);

    /* Изменяет координаты игровой фигуры и всех подконтрольных ей игровых элементов в соотвествии с направлением движения. */
    void MoveTo(const MoveVector& vertor);

    /* Позиционируте игровую фигуру на игровом поле, относитльено её текущего положения, согласно указанному направлению. */
    void RotateTo(const FigureDirection& direction);

    /* Проверяет, попадают ли координаты подконтрольных игровых элементов в границы игрового поля.
     * Замечание: проверка считается успешно пройденной если все координаты всех подконтрольных игровых элементов попадают в границы игрового поля.
     * Замечание: попадание в пределы границ считается успешным если координаты всех из игровых элементов строго меньше размерностей игрового поля.
     * ---> [x_size] - ширина игрового поля.
     * ---> [y_size] - высота игрового поля. */
    bool CheckCondition(const uint& x_size, const uint& y_size) const;

    /* Возвращает константную ссылку на вектор подконтрольных игровых элементов. */
    const vector<GameElement>& GetFigureElementC() const;

    /* Возвращает ссылку на вектор подконтрольных игровых элементов. */
    vector<GameElement>& GetFigureElement();

private:

    /* Функции вращающие игровые фигуры:
     * RotateLongLine   - длинная линия.
     * RotateSquare     - квадрат.
     * RotateZigZag     - зиг-заг.
     * RotateGLine      - г-образная линия. */
    void RotateLongLine(const FigureDirection& direction);
    void RotateSquare(const FigureDirection& vertor);
    void RotateZigZag(const FigureDirection& vertor);
    void RotateGLine(const FigureDirection& vertor);

private:

    /* Текущая координата X игровой фигуры. */
    uint X;

    /* Текущая координата Y игровой фигуры. */
    uint Y;

    /* Глобальный идентификатор игровой фигуры в камках всего игрового поля (на протяжении всей игровой сессии). */
    uint64_t ID;

    /* Цветовая схема игровой фигуры. */
    uint8_t Color[3];

    /* Подконтрольный тип игровой фигуры. */
    TetrixFigure Figure;

    /* Вектор подконольных игровых элементов, составляющих игровую фигуру. */
    vector<GameElement> GE;

    /* Текущее состояние игровой фигуры. */
    StateTetrixElement State;

    /* Текущее направление игровой фигуры. */
    FigureDirection Direction;
};
