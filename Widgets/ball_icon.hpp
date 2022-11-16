#ifndef BALL_ICON_HPP_
#define BALL_ICON_HPP_

#include <memory>
#include <string>
#include "abstract_widgets.hpp"

namespace widgets {
	struct ball_icon final : widget {
		[[nodiscard]] int width() const final;
		[[nodiscard]] int height() const final;
		[[nodiscard]] int radius() const;
		[[nodiscard]] void radius(int radius);

		explicit ball_icon(int radius);

		widget* child_at(int x, int y) override;

	private:
		std::string m_label;
		int _radius;
	};

	[[nodiscard]] std::unique_ptr<ball_icon> make_ball_icon(int radius);
}  // namespace widgets

#endif  // BALL_ICON_HPP_