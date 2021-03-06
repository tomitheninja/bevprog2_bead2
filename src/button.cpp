#include "button.h"

Button::Button(const std::string &text, const std::vector<Styler> &styles, const std::vector<Styler> &lbStyles) : Container({}, {new Label(text)})
{
    _lb = reinterpret_cast<Label *>(_children[0]);
    for (auto &mstyle : styles)
    {
        applyStyler(mstyle);
    }
    { // Label
        auto &s = _lb->style;
        s.isRelative = true;
        for (auto &style : lbStyles)
        {
            _lb->applyStyler(style);
        }
    }

    addEvent([](const genv::event &evt, const Vector2 &cursor, Widget &self) {
        self.style.bgMColor.first = self.containsPointM(cursor);
        return false;
    });
}

Button::~Button() = default;

std::string Button::getText() const { return _lb->getText(); }
void Button::setText(const std::string &newText) { _lb->setText(newText); };
