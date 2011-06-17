#ifndef COLOR_H_INCLUDED
#define COLOR_H_INCLUDED

#include <iostream>

class Color {
    public:

        static const float CL_OPAQUE = 1.0f;
        static const float CL_TRANSLUCENT = 0.0f;
        static const float CL_COLOR_MAX = 1.0f;
        static const float CL_COLOR_MIN = 0.0f;

        Color(float _red, float _green, float _blue, float _alpha = Color::CL_OPAQUE)
        :
         cRed(_red < Color::CL_COLOR_MIN ? Color::CL_COLOR_MIN : _red > Color::CL_COLOR_MAX ? Color::CL_COLOR_MAX : _red),
         cGreen(_green < Color::CL_COLOR_MIN ? Color::CL_COLOR_MIN : _green > Color::CL_COLOR_MAX ? Color::CL_COLOR_MAX: _green),
         cBlue(_blue < Color::CL_COLOR_MIN ? Color::CL_COLOR_MIN : _blue > Color::CL_COLOR_MAX ? Color::CL_COLOR_MAX : _blue),
         cAlpha(_alpha < Color::CL_TRANSLUCENT ? Color::CL_TRANSLUCENT : _alpha > Color::CL_OPAQUE ? Color::CL_OPAQUE : _alpha)
        {
            Color::count++;
            Color::toString(this);
        }

        virtual ~Color() {
        }

        float gRed() {
            return this->cRed;
        }

        float gGreen() {
            return this->cGreen;
        }

        float gBlue() {
            return this->cBlue;
        }

        void sRed(float _red) {
            this->cRed = (_red < Color::CL_COLOR_MIN ? Color::CL_COLOR_MIN : _red > Color::CL_COLOR_MAX ? Color::CL_COLOR_MAX : _red);
        }

        void sGreen(float _green) {
            this->cGreen = (_green < Color::CL_COLOR_MIN ? Color::CL_COLOR_MIN : _green > Color::CL_COLOR_MAX ? Color::CL_COLOR_MAX: _green);
        }

        void sBlue(float _blue) {
            this->cBlue = (_blue < Color::CL_COLOR_MIN ? Color::CL_COLOR_MIN : _blue > Color::CL_COLOR_MAX ? Color::CL_COLOR_MAX : _blue);
        }

        float gAlpha() {
            return this->cAlpha;
        }

        void sAlpha(float _alpha) {
            this->cAlpha = (_alpha < Color::CL_TRANSLUCENT ? Color::CL_TRANSLUCENT : _alpha > Color::CL_OPAQUE ? Color::CL_OPAQUE : _alpha);
        }

        static void toString(Color* _color) {
            using namespace std;

            cout<< "Color (R" << _color->gRed() << ", G" << _color->gGreen() << ", B" << _color->gBlue() << ", A" << _color->gAlpha() << ")";
            cout<< " Instance Count " << Color::count << endl;
        }



    private:
        float cRed;
        float cGreen;
        float cBlue;
        float cAlpha;
        static int count;

};
int Color::count = 0;
#endif // COLOR_H_INCLUDED
