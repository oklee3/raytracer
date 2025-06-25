#ifndef VEC3_H
#define VEC3_H

// to store and perform operations on vectors
class vec3 {
    public:
        double v[3];

        vec3() {}
        vec3(double x, double y, double z) : v{x,y,z} {}

        double x() const { return v[0]; }
        double y() const { return v[1]; }
        double z() const { return v[2]; }

        // operator overloads on obj
        double& operator[](int i) { return v[i]; }
        double operator[](int i) const { return v[i]; }

        vec3 operator-() const { return vec3(-v[0], -v[1], -v[2]); }
        vec3& operator+=(const vec3& vec) {
            v[0] += vec[0];
            v[1] += vec[1];
            v[2] += vec[2];
            return *this;
        }
        vec3& operator-=(const vec3& vec) {
            v[0] -= vec[0];
            v[1] -= vec[1];
            v[2] -= vec[2];
            return *this;
        }
        vec3& operator*=(double s) {
            v[0] *= s;
            v[1] *= s;
            v[2] *= s;
            return *this;
        }
        vec3 operator/=(double s) {
            v[0] /= s;
            v[1] /= s;
            v[2] /= s;
            return *this;
        }

        double len() const {
            return std::sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
        }
};

using point3 = vec3;

std::ostream& operator<<(std::ostream& out, const vec3& x) {
    return out << x[0] << ' ' << x[1] << ' ' << x[2];
}

// operator overloads passing in obj
vec3 operator+(const vec3& x, const vec3& w) {
    return vec3(x[0]+w[0], x[1]+w[1], x[2]+w[2]);
}
vec3 operator-(const vec3& x, const vec3& w) {
    return vec3(x[0]-w[0], x[1]-w[1], x[2]-w[2]);
}
vec3 operator*(const vec3& x, const vec3& w) {
    return vec3(x[0]*w[0], x[1]*w[1], x[2]*w[2]);
}
vec3 operator*(const vec3& x, double s) {
    return vec3(x[0]*s, x[1]*s, x[2]*s);
}
vec3 operator*(double s, const vec3& x) {
    return vec3(x[0]*s, x[1]*s, x[2]*s);
}
vec3 operator/(const vec3& x, double s) {
    return vec3(x[0]/s, x[1]/s, x[2]/s);
}

double dot(const vec3& x, const vec3& w) {
    return x[0]*w[0] + x[1]*w[1] + x[2]*w[2];
}

vec3 unit_vector(const vec3& x) {
    return x / x.len();
}

#endif