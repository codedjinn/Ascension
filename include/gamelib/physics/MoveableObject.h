#ifndef MOVEABLEOBJECT_H_INCLUDED
#define MOVEABLEOBJECT_H_INCLUDED

class MoveableObject {

public:
    MoveableObject() {
        CORValue(MoveableObject::COR_GOLF_BALL);
    }

    MoveableObject(float corVal) {
        CORValue(corVal);
    }

    virtual ~MoveableObject() {
    }

    static const float COR_TENNIS_BALL = 0.71f;
    static const float COR_GOLF_BALL = 0.85f;
    static const float COR_TABLE_TENNIS_BALL = 0.94f;
    static const float COR_POOL_BALL = 0.98f;
    static const float COR_NONELASTIC_ELASTIC = 0.0f;
    static const float COR_ELASTIC = 1.0f;

    void CORValue(float corVal) {
        this->corValue = corVal >= MoveableObject::COR_ELASTIC ?
                            MoveableObject::COR_ELASTIC
                            :
                            corVal <= MoveableObject::COR_NONELASTIC_ELASTIC ?
                               MoveableObject::COR_NONELASTIC_ELASTIC
                               :
                               corVal;
    }

    float CORValue() {
        return this->corValue;
    }
private:
    float corValue;
};

#endif // MOVEABLEOBJECT_H_INCLUDED
