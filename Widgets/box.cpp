#include "box.hpp"

void widgets::box::update_layout()
{
}

int widgets::box::width() const
{
	int totalWidth = 0;
	std::vector<std::unique_ptr<widgets::widget>>::const_iterator it;
	for (it = this->children.begin(); it < this->children.end(); it++)
	{
		totalWidth += (*it).get()->width();
	}
	return totalWidth;
}

int widgets::box::height() const
{
	int totalHeight = 0;
	std::vector<std::unique_ptr<widgets::widget>>::const_iterator it;
	for (it = this->children.begin(); it < this->children.end(); it++)
	{
		totalHeight = std::max((*it).get()->height(), totalHeight);
	}
	return totalHeight;
}

int widgets::box::size() const
{
	return this->children.size();
}

widgets::widget* widgets::box::get(int index) const
{
	return (index < 0 || index > this->size() - 1 ? nullptr : this->children.at(index).get());
}

widgets::widget* widgets::box::add(std::unique_ptr<widgets::widget> child)
{
	children.push_back(std::move(child));
	return children.back().get();
}

std::unique_ptr<widgets::widget> widgets::box::remove(int index) const
{
	return nullptr;
}

widgets::box::box(kind kind)
{
}

widgets::widget* widgets::box::child_at(int x, int y)
{
	return nullptr;
}

std::unique_ptr<widgets::box> widgets::make_box(box::kind kind)
{
	return std::make_unique<widgets::box>(kind);
}
