#include "placeholder.hpp"

namespace widgets {
	placeholder::placeholder(int width_, int height_)
		: m_width(width_), m_height(height_) {
	}

	widget* placeholder::child_at(int x, int y)
	{
		if (x >= this->width() || y >= this->height())
			return nullptr;
		return this;
	}

	[[nodiscard]] std::unique_ptr<placeholder>
		make_placeholder(int width, int height) {
		return std::make_unique<placeholder>(width, height);
	}
}  // namespace widgets
