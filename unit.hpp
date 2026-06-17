#ifndef UNIT_HPP
#define UNIT_HPP

struct coordinates
{
    int x;
    int y;
};

class unit
{
    coordinates pos;
    int width;
    int height;

protected:
    void set_pos(const coordinates &pos);
    void set_x(const int &x);
    void set_y(const int &y);
    void set_width(const int &width);
    void set_height(const int &height);

public:
    virtual coordinates get_pos() const;
    virtual int get_x() const;
    virtual int get_y() const;
    virtual int get_width() const;
    virtual int get_height() const;

    virtual int get_left() const;
    virtual int get_right() const;
    virtual int get_top() const;
    virtual int get_bottom() const;
    virtual coordinates get_middle() const;

    virtual bool check_collision(const unit &u) const;
};

#endif