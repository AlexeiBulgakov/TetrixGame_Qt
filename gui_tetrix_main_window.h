/* Главная класс-виджет-gui приложения Tetrix: */

#pragma once

#include "stdafx.h"
#include "gui_tetrix_gamefield.h"

class GUITetrixMainWindow : public QMainWindow
{
	/* Внутренная семантика класса:
	 * [COLOR]	- указывает на то, что помеченный метод/функция класса приводит цветовую гамму управляющих кнопок в соответствие с текущим состоянием игрового процесса. 
	 * [GUI_GF] - указывает на то, что помеченный метод/функция класса приводит к вызову аналогичного метода/фукции в подконтрольном экземпляре класса GUITetrixGameField. */
	 
    Q_OBJECT

public:
	
	/* Конструктор Tetrix:
	 * ---> [size_of_game_element] - рамер одного игрового элемента (клеточки игрового поля). */
    explicit GUITetrixMainWindow(uint size_of_game_element);

public slots:
	
	/* [COLOR] Обработка события нажатия кнопки _push_button_start:
	 * Описание: стартует новую игровую сессию. */
    void StartGame();

	/* [COLOR] Обработка события нажатия кнопки _push_button_pause:
	 * Описание: приостанавливает текущую игровую сессию. */
    void PauseGame();

	/* [COLOR] Обработка события нажатия кнопки _push_button_stop:
	 * Описание: сбрасывает текущую игровую сессию до дефолтного состояния и приостанавливет её. */
    void StopGame();

	/* Обработка события GUITetrixGameField->DelletedRows(size_t):
	 * Описание: увеличивает счёт игры, согласно фомуле - [новый счёт] = [текущий счёт] + [количество удалённых строк] * [размерность поля по ширине].
	 * ---> [count_of_delleted_rows] - количество удалённых строк. */
    void ScooreIncrease(const size_t& count_of_delleted_rows);

	/* Обработка события GUITetrixGameField->RemovedElements(size_t):
	 * Описание: уменьшает счёт игры, согласно количеству дезактивированных игровых элементов.
	 * Замечание: данный обработчик срабатывает при изменении размерности игрового поля в процессе игры, когда не все элементы бывшие в игре, соотвествуют своими координатами новым размерам игрового поля. */
    void ScooreDecrease(const size_t& count_of_removed_elements);

	/* Обработка события нажатия клавиш (с английской раскладкой):
	 * Описание: обработчик вызывает соответствующие фукции согласно нажатым клавишам.
	 * Привязка клавиш: действия совершаемые с управляемыми игровыми фигурами (фигурами в состоянии Downing):
	 * [W] - перемещение вверх.
	 * [A] - перемещение влево.
	 * [S] - перемещение вниз.
	 * [D] - перемещение вправо.
	 * [O] - вращение на верх.
	 * [K] - вращение на лево.
	 * [L] - вращение вниз.
	 * [;] - вращение вправо. */
    void keyPressEvent(QKeyEvent *event) override;

private:

	/* Обравляет статистику игры (счёт, уровень, количество удалённых строк) на соответствующих информационных полях. */
    void TextInfoUpdate();
	
	/* [GUI_GF] */
    void RotateTo(const FigureDirection& direction);

	/* [GUI_GF] */
    void MoveTo(const MoveVector& vector);

protected:

	/* Показатели текущей игровой сессии. */
	
		/* Флаг первичной инициализации игровой сесии:
		 * Особенности: всегда true с момента первого нажатия на _push_button_start. */
		bool _is_started {false};

		/* Флаг приостановки текущей игры:
		 * Особенности: после перезапуска игры по нажатию кнопки _push_button_start, фраг равен false - игра запущена. */
		bool _is_pause {false};
		
		/* Текущий уровень игры, текущей игровой сессии. */
		uint _level {1};

		/* Текущее количество очков, текущей игровой сессии. */
		uint _score {0};

		/* Текущее количество удалённых строк, текущей игровой сессии. */
		uint _removed_lines {0};

		/* Размерность игровго поля, любой из подконтрольных классу игровых сессий: 
		 * Особенности: данный показатель устанавливается единственный раз в момент вызова конструктора класса. */
		uint _size_of_game_element {10};

private:

	/* Структурирование графических элементов класса. */
    void SetupUi();
	
	/* Соединение сигнал-слот логики класса. */
    void SetupSS();

	/* Иерахическая зависимость внутренних (подконтрольных) графических элементов. */
    QWidget* _widget_central;
        QVBoxLayout* _vertical_layout;
            QGridLayout* _grid_layout;
                GUITetrixGameField* _game_field;
                QPushButton* _push_button_start;
                QPushButton* _push_button_pause;
                QPushButton* _push_button_stop;
                QLineEdit* _line_edit_level;
                QLineEdit* _line_edit_score;
                QLineEdit* _line_edit_removed_line;
};
