#ifndef Color_hpp
#define Color_hpp

class Color
{
    public:
        Uint8 r, g, b, a;

    Color(Uint8 r, Uint8 g, Uint8 b, Uint8 a) : r(r), g(g), b(b), a(a) {};
};

#endif