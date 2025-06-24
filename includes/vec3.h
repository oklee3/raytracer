#ifndef VEC3_H
#define VEC3_h

class vec3 {
    public:
        double v[3];

        vec3() {}
        vec3(double v1, double v2, double v3) : v{v1,v2,v3} {}
        
};

#endif