#ifndef UNIT_HPP
#define UNIT_HPP

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
    virtual int get_width() const;
    virtual int get_height() const;
    virtual coordinates get_pos() const;
    virtual double get_x() const;
    virtual double get_y() const;

    virtual double get_left() const;
    virtual double get_right() const;
    virtual double get_top() const;
    virtual double get_bottom() const;
    virtual coordinates get_middle() const;
};

#endif