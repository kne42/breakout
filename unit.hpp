#ifndef UNIT_HPP
#define UNIT_HPP

enum edge
{
    EDGE_LEFT = 0b1000,
    EDGE_RIGHT = 0b0100,
    EDGE_TOP = 0b0010,
    EDGE_BOTTOM = 0b0001,
    EDGE_TOP_LEFT = EDGE_TOP | EDGE_LEFT,
    EDGE_TOP_RIGHT = EDGE_TOP | EDGE_RIGHT,
    EDGE_BOTTOM_LEFT = EDGE_BOTTOM | EDGE_LEFT,
    EDGE_BOTTOM_RIGHT = EDGE_BOTTOM | EDGE_RIGHT,
};

struct coordinates
{
    double x;
    double y;
};

class unit
{
    coordinates pos;
    int width;
    int height;

protected:
    void set_pos(const coordinates &pos);
    void set_x(const double &x);
    void set_y(const double &y);
    void set_width(const int &width);
    void set_height(const int &height);

public:
    int get_width() const;
    int get_height() const;
    coordinates get_pos() const;
    double get_x() const;
    double get_y() const;
    coordinates calculate_edge(edge edges) const;

    double get_left() const;
    double get_right() const;
    double get_top() const;
    double get_bottom() const;
};

#endif