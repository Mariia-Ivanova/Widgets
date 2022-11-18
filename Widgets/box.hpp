#ifndef BOX_HPP_
#define BOX_HPP_

#include <memory>
#include <string>
#include <vector>
#include <typeinfo>
#include <type_traits>
#include "abstract_widgets.hpp"

namespace widgets {

	struct box final : container {
		enum kind {
			HORIZONTAL, VERTICAL
		};
		[[nodiscard]] int width() const final;
		[[nodiscard]] int height() const final;

		int size() const;
		widgets::widget* get(int index) const;
		widgets::widget* add(std::unique_ptr<widgets::widget> child);
		std::unique_ptr<widgets::widget> remove(int index);

		explicit box(kind kind);

		widgets::widget* child_at(int x, int y) override;

		virtual void update_layout() override;

	private:
		box::kind _kind;
		std::vector<std::unique_ptr<widgets::widget>> children;
	};

	[[nodiscard]] std::unique_ptr<box> make_box(box::kind kind);
}  // namespace widgets

#endif  // BOX_HPP_