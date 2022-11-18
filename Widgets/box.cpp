#include "box.hpp"

void widgets::box::update_layout()
{

}

int widgets::box::width() const
{
	int totalWidth = 0;
	std::vector<std::unique_ptr<widgets::widget>>::const_iterator it;
	if (this->_kind == kind::HORIZONTAL)
		for (it = this->children.begin(); it < this->children.end(); it++)
			totalWidth += (*it).get()->width();
	if (this->_kind == kind::VERTICAL)
		for (it = this->children.begin(); it < this->children.end(); it++)
			totalWidth = std::max((*it).get()->width(), totalWidth);
	return totalWidth;
}

int widgets::box::height() const
{
	int totalHeight = 0;
	std::vector<std::unique_ptr<widgets::widget>>::const_iterator it;
	if (this->_kind == kind::HORIZONTAL)
		for (it = this->children.begin(); it < this->children.end(); it++)
			totalHeight = std::max((*it).get()->height(), totalHeight);
	if (this->_kind == kind::VERTICAL)
		for (it = this->children.begin(); it < this->children.end(); it++)
			totalHeight += (*it).get()->height();
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

std::unique_ptr<widgets::widget> widgets::box::remove(int index)
{
	if (index >= this->size())
		return nullptr;
	std::unique_ptr<widgets::widget> elem = std::move(this->children.at(index));
	this->children.erase(this->children.begin() + index);
	return elem;
}

widgets::box::box(kind kind)
{
	this->_kind = kind;
}

widgets::widget* widgets::box::child_at(int x, int y)
{
	/*if (x >= this->width() || y >= this->height())
		return nullptr;*/
	if (this->_kind == kind::HORIZONTAL)
	{
		int middleLine = this->height() / 2;
		int sumWidth = 0;
		std::vector<std::unique_ptr<widgets::widget>>::iterator it;
		for (it = this->children.begin(); it < this->children.end(); it++)
		{
			widgets::widget* obj = std::move(*it).get();
			widgets::widget* isBox = dynamic_cast<widgets::box*>(obj);
			if (isBox)
				// TODO: Либо прибавить к x
				return (*it)->child_at(x - sumWidth, y);
			if (typeid(*it) == typeid(widgets::box))
				return (*it)->child_at(x, y);
			int h = (*it).get()->height() / 2;
			sumWidth += (*it).get()->width();
			if ((y >= middleLine - h && y <= middleLine + h) && x <= sumWidth && (*it).get()->width() != x)
				return (*it).get();
			if (sumWidth > x)
				return nullptr;
		}
	}

	if (this->_kind == kind::VERTICAL)
	{
		int middleLine = this->width() / 2;
		int sumHeight = 0;
		std::vector<std::unique_ptr<widgets::widget>>::iterator it;
		for (it = this->children.begin(); it < this->children.end(); it++)
		{
			widgets::widget* obj = std::move(*it).get();
			widgets::widget* isBox = dynamic_cast<widgets::box*>(obj);
			if (isBox)
				return (*it)->child_at(x, y - sumHeight);
			int w = (*it).get()->width() / 2;
			sumHeight += (*it).get()->height();
			if ((x >= middleLine - w && x <= middleLine + w) && y < sumHeight && (*it).get()->height() != y)
				return (*it).get();
			if (sumHeight > y)
				return nullptr;
		}
	}

	return nullptr;
}

std::unique_ptr<widgets::box> widgets::make_box(box::kind kind)
{
	return std::make_unique<widgets::box>(kind);
}
