#ifndef VECTOR_H
#define VECTOR_H


class Vector
{
    public:
        Vector(float _xm = 0, float _ym = 0) : x(_xm), y(_ym) {}
        virtual ~Vector() {}
        Vector* operator +(Vector* vector) {
            return new Vector(this->x + vector->x, this->y + vector->y);
        }

//        Vector* operator +(Vector* a, Vector* b) {
//            return new Vector(a->x + b->x, a->y + b->y);
//        }

        float x;
        float y;

};

#endif // VECTOR_H
