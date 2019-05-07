#include "game_filed.h"


GameFiled::GameFiled(const uint& x, const uint& y)
{
    X_size = x;
    Y_size = y;

    for(size_t i{0}; i<X_size; ++i)
        Field.push_back(vector<tuple<bool, uint64_t, uint8_t>>(Y_size, {false, 0, 0}));
};


size_t GameFiled::NextStep()
{
    for(auto& [id, figure] : Figures)
        if(figure.GetState() == StateTetrixElement::Downing)
        {
            for(auto& element : figure.GetFigureElement())
            {
                if (element.GetY() == (Y_size - 1) )
                {
                    figure.SetState(StateTetrixElement::Removed);
                    goto without_move;
                }

                if (const auto& [is_set, ID, id] = Field.at(element.GetX()).at(element.GetY() + 1);
                    (element.GetY() == Y_size - 1) or ((is_set == true) and (ID != element.GetID())))
                {
                    figure.SetState(StateTetrixElement::Removed);
                    goto without_move;
                }
            }

            figure.MoveTo(MoveVector::MoveDown);
            continue;

        without_move:
            this->AddFigure(static_cast<TetrixFigure>(qrand() % 4));
            continue;
        }

    return this->Update();
};


void GameFiled::AddFigure(const TetrixFigure& figure)
{
    uint8_t color[3] { static_cast<uint8_t>(qrand() % 255), static_cast<uint8_t>(qrand() % 255), static_cast<uint8_t>(qrand() % 255) };
    Figures.emplace(ID, GameFigure(figure, X_size / 2, 0, ID, color));
    ++ID;
};


size_t GameFiled::Update()
{
    for_each(Field.begin(),
             Field.end(),
             [](vector<tuple<bool, uint64_t, uint8_t>>& stolb){ for_each(stolb.begin(),
                                                                         stolb.end(),
                                                                         [](tuple<bool, uint64_t, uint8_t>& is_set) {is_set = {false, 0, 0}; } ); });

    for(const auto& [id, figure] : Figures)
        for (const auto& element : figure.GetFigureElementC())
            if (element.GetState() != StateTetrixElement::Deleted)
                Field.at(element.GetX()).at(element.GetY()) = {true, element.GetID(), element.GetId()};

    size_t cout_of_delleted_rows {this->DelletCompletedRows()};

    if (cout_of_delleted_rows != 0)
        for(const auto& [id, figure] : Figures)
            for (const auto& element : figure.GetFigureElementC())
                if (element.GetState() != StateTetrixElement::Deleted)
                    Field.at(element.GetX()).at(element.GetY()) = {true, element.GetID(), element.GetId()};

    return cout_of_delleted_rows;
};


size_t GameFiled::Reconstruct(const uint& x, const uint& y)
{
    size_t count_of_deletted_elements {0};

    Field.clear();
    for(size_t i{0}; i<x; ++i)
        Field.push_back( vector<tuple<bool, uint64_t, uint8_t>>(y, {false, 0, 0}) );

    for(auto& [id, figure] : Figures)
        for (auto& element : figure.GetFigureElement())
            if (element.GetState() != StateTetrixElement::Deleted)
                if(element.CheckCondition(x, y))
                    Field.at(element.GetX()).at(element.GetY()) = {true, element.GetID(), element.GetId()};
                else {
                    element.SetState(StateTetrixElement::Deleted);
                    ++count_of_deletted_elements;
                }

    X_size = x;
    Y_size = y;

    return count_of_deletted_elements;
};


void GameFiled::MoveTo(const MoveVector& vertor)
{
    for(auto& [id, figure] : Figures)
        if (figure.GetState() == StateTetrixElement::Downing)
        {
            auto save_figure_state = figure;
            save_figure_state.MoveTo(vertor);
            if (save_figure_state.CheckCondition(X_size, Y_size))
            {
                for(const auto& element : save_figure_state.GetFigureElementC())
                    if (const auto& [is_set, ID, id] = Field.at(element.GetX()).at(element.GetY()); (ID != element.GetID()) && (ID != 0) )
                            return;

                figure = save_figure_state;
                this->Update();
            }
        }
};


void GameFiled::RotateTo(const FigureDirection& direction)
{
    for(auto& [id, figure] : Figures)
        if (figure.GetState() == StateTetrixElement::Downing)
        {
            auto save_figure_state = figure;
            save_figure_state.RotateTo(direction);
            if (save_figure_state.CheckCondition(X_size, Y_size))
            {
                for(const auto& element : save_figure_state.GetFigureElementC())
                    if (const auto& [is_set, ID, id] = Field.at(element.GetX()).at(element.GetY()); (ID != element.GetID()) && (ID != 0) )
                        return;

                figure = save_figure_state;
                this->Update();
            }
        }
};


list<tuple<uint, uint, QColor, QBrush, StateTetrixElement>> GameFiled::GetListViewvalentElement() const
{
    list<tuple<uint, uint, QColor, QBrush, StateTetrixElement>> list_viewvalent_elements;

    for (size_t x{0}; x < X_size; ++x)
        for (size_t y{0}; y < Y_size; ++y)
            if (const auto& [is_set, ID, id] = Field.at(x).at(y); is_set){
                const auto& element = Figures.at(ID).GetFigureElementC().at(id);
                list_viewvalent_elements.push_back( {element.GetX(), element.GetY(), element.GetColor(), element.GetBrush(), element.GetState()} );
            }

    return list_viewvalent_elements;
};


void GameFiled::Clear()
{
    map<uint64_t, GameFigure> condition_figures;

    for(auto& [id, figures] : Figures)
        for (const auto& element : figures.GetFigureElement())
            if (element.GetState() != StateTetrixElement::Deleted) {
                condition_figures.emplace(id, figures);
                break;
            }

    Figures = condition_figures;
};


uint GameFiled::GetMBoder() const
{
    return M_size;
};


uint GameFiled::GetX() const
{
    return X_size;
};


uint GameFiled::GetY() const
{
    return Y_size;
};


size_t GameFiled::DelletCompletedRows()
{
    size_t count_of_deletted_rows{0}, y{0}, x{0}, sub_y{0};

    for (y = Y_size - 1; y > 0; --y)
    {
        for (x = 0; x < X_size; ++x)
            if (const auto& [is_set, ID, id] = Field.at(x).at(y); !is_set || (is_set && (Figures.at(ID).GetFigureElement().at(id).GetState() != StateTetrixElement::Removed)))
                    goto rows_with_unset_elements;

        for (x = 0; x < X_size; ++x)
        {
            const auto& [is_set, ID, id] = Field.at(x).at(y);
            Figures.at(ID).GetFigureElement().at(id).SetState(StateTetrixElement::Deleted);

            for(sub_y = y - 1; sub_y > 0; --sub_y)
            {
                const auto& [is_set, ID, id] = Field.at(x).at(sub_y);
                if (Figures.find(ID) != Figures.end()) {
                    auto& figure = Figures.at(ID).GetFigureElement().at(id);
                    if (figure.GetState() == StateTetrixElement::Removed)
                        figure.MoveTo(MoveVector::MoveDown);
                }
            }
        }

        ++count_of_deletted_rows;

    rows_with_unset_elements:
        continue;
    }

    return count_of_deletted_rows;
};

