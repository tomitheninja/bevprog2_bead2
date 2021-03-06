#ifndef WIDGET_H
#define WIDGET_H

#include "styles.h"

class Widget;

/// A function that takes an event and the cursor location and the widget, which the event is listening on
/// And returns true if the event is handled and no other widgets should not get this event
typedef std::function<bool(const genv::event &evt, const Vector2 &cursor, Widget &self)> Handler;

class Widget
{
public:
    Widget(const std::vector<Styler> &styles = {}, const std::vector<Widget *> &children = {});
    virtual ~Widget();

    void applyStyler(Styler sr);

    bool containsPoint(const Vector2 &point) const;
    bool containsPointM(const Vector2 &point) const;

    // Single position values
    int top() const;
    int bottom() const;
    int left() const;
    int right() const;

    // Single position values (including margin)
    int topM() const;
    int bottomM() const;
    int leftM() const;
    int rightM() const;

    // Edges of the widget
    Vector2 topLeft() const;
    Vector2 topRight() const;
    Vector2 btmRight() const;
    Vector2 btmLeft() const;

    // Edges of the widget (including margin)
    Vector2 topLeftM() const;
    Vector2 topRightM() const;
    Vector2 btmRightM() const;
    Vector2 btmLeftM() const;

    // calls draw events
    void draw() const; // calls drawers

    // events
    void addEvent(Handler handler);
    bool handle(const genv::event &evt, const Vector2 cursor, bool &canCaptureFocus);
    bool handle(const genv::event &evt, const Vector2 cursor);

    Widget *getParent();

    bool isFocused() const;

    void update(); // recalculate properties

    static void clearFocus();

    Style style;

    void enable();
    void disable();
    bool isEnabled() const;

protected:
    // draw events
    virtual void preDraw() const;
    virtual void preChildDraw() const;
    virtual void postChildDraw() const;
    virtual void postDraw() const;

    void _drawBg() const;
    void _drawBorders() const; // Call be called any time to fix the borders

    std::vector<Widget *> _children;
    std::vector<Handler> _events;

private:
    // 0 = enabled
    // 0+ = number of widgets needs to be enabled
    unsigned int _disabled = 0;
    bool _self_disabled = false;
    Widget *_parent = nullptr;
    static Widget *_focused;
};

#endif // WIDGET_H
