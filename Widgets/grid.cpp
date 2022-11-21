#include "grid.hpp"

int widgets::grid::width() const
{
	int maxWidth = 0;
	for (size_t i = 0; i < _columns; i++)
	{
		int maxElem = 0;
		for (size_t j = 0; j < _rows; j++)
		{
			if (this->children[j][i])
				maxElem = std::max(maxElem, this->children[j][i]->width());
		}
		maxWidth += maxElem;
	}
	return maxWidth;
}

int widgets::grid::height() const
{
	int maxHeight = 0;
	for (size_t i = 0; i < _rows; i++)
	{
		int maxElem = 0;
		for (size_t j = 0; j < _columns; j++)
		{
			if (this->children[i][j])
				maxElem = std::max(maxElem, this->children[i][j]->height());
		}
		maxHeight += maxElem;
	}
	return maxHeight;
}

int widgets::grid::rows() const
{
	return this->_rows;
}

int widgets::grid::columns() const
{
	return this->_columns;
}

widgets::widget* widgets::grid::get(int row, int column) const
{
	if (row < _rows && column < _columns)
		return children[row][column].get();
	return nullptr;
}

widgets::widget* widgets::grid::add(std::unique_ptr<widgets::widget> child, int row, int column)
{
	this->children[row][column] = std::move(child);
	return this->children[row][column].get();
}

std::unique_ptr<widgets::widget> widgets::grid::remove(int row, int column)
{
	return nullptr;
}

widgets::grid::grid(int rows, int columns) : _rows(rows), _columns(columns)
{
	this->children.resize(rows);
	for (size_t i = 0; i < rows; i++)
		this->children[i].resize(columns);
}

widgets::widget* widgets::grid::child_at(int x, int y)
{
	return nullptr;
}

void widgets::grid::update_layout()
{
}

std::unique_ptr<widgets::grid> widgets::make_grid(int rows, int columns)
{
	return std::make_unique<widgets::grid>(rows, columns);
}
