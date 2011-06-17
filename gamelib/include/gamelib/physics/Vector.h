#ifndef VECTOR_H
#define VECTOR_H


class Vector
{
    public:
        Vector(float _xm = 0, float _ym = 0) : x(_xm), y(_ym) {}
        virtual ~Vector() {}

        Vector* operator +(Vector* vector) {
            //todo refact to not create a new instance this will cause a mem leak
            return new Vector(this->x + vector->x, this->y + vector->y);
        }

        float x;
        float y;

};

#endif // VECTOR_H
