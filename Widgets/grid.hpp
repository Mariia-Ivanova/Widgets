#ifndef GRID_HPP_
#define GRID_HPP_

#include <memory>
#include <string>
#include <vector>
#include <typeinfo>
#include <type_traits>
#include "abstract_widgets.hpp"

namespace widgets {

	struct grid final : container {
		[[nodiscard]] int width() const final;
		[[nodiscard]] int height() const final;
		int rows() const;
		int columns() const;
		widgets::widget* get(int row, int column) const;
		widgets::widget* add(std::unique_ptr<widgets::widget> child, int row, int column);
		std::unique_ptr<widgets::widget> remove(int row, int column);

		explicit grid(int rows, int columns);

		widgets::widget* child_at(int x, int y) override;

		virtual void update_layout() override;

	private:
		int _rows;
		int _columns;
		std::vector<std::vector<std::unique_ptr<widgets::widget>>> children;
	};

	[[nodiscard]] std::unique_ptr<grid> make_grid(int rows, int columns);
}  // namespace widgets

#endif  // GRID_HPP_