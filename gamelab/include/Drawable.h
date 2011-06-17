#ifndef DRAWABLE_H
#define DRAWABLE_H


class Drawable
{
    public:
        Drawable() {}
        virtual ~Drawable() {}
    protected:
        virtual void draw(float interpolation) = 0;
    private:
};

#endif // DRAWABLE_H
