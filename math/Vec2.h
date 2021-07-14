#pragma once

namespace math
{
    template<typename T>
    class Vec2
    {
    public:
        T x, y;
        
        Vec2(const T& _x, const T& _y) : x(_x), y(_y) {} // x and y are const values and that is the only time const values can be initialized. This is called an initialization list
        Vec2(const Vec2<T>& other) : x(other.x), y(other.y)
        {
            printf("%s\n", "copied");
        }
        Vec2(Vec2<T>&& other) {
            operator=(other);
            printf("%s\n", "moved");
        } //&&means can only pass R values i.e. values that do not have a memory address. E.g. 5,7 etc
        //but what does the operator=(other) mean?
        
        bool operator==(const Vec2<T>& other) const
        {
            return isZero(x - other.x) && isZero(y - other.y);
        }
        
        bool operator!=(const Vec2<T>& other) const
        {
            return !isZero(x - other.x) || isZero(y - other.y); //we could also do return !operator==(other)

        }
        Vec2<T>& operator=(const Vec2<T>& other)
        {
            x = other.x;
            y = other.y;
            return *this;
        }
        
        //ADD
        Vec2<T> operator+(const T& t) const
        {
            return { x + t, y + t}; //this is a vector
        }
        
        Vec2<T> operator+(const Vec2<T>& other) const
        {
            return { x + other.x, y + other.y}; //this is a vector
        }
        
        Vec2<T>& operator+=(const T& t) //We remove the const in these two functions because when we type something like a += 5 we expect a to change.
        { //Since wwe are changing the object itself we could have just defined this function as void instead of Vec2. However if we type something like b += (a += 5) that will not be evaluated
            x += t;
            y += t;
            return *this;
        }
        
        Vec2<T>& operator+=(const Vec2<T>& other)
        {
            x += other.x;
            y += other.y;
            return *this;
        }
        
        //SUBTRACT
        Vec2<T> operator-(const T& t) const
        {
            return { x - t, y - t}; //this is a vector
        }
        
        Vec2<T> operator-(const Vec2<T>& other) const
        {
            return { x - other.x, y - other.y}; //this is a vector
        }
        
        Vec2<T>& operator-=(const T& t) //We remove the const in these two functions because when we type something like a += 5 we expect a to change.
        { //Since wwe are changing the object itself we could have just defined this function as void instead of Vec2. However if we type something like b += (a += 5) that will not be evaluated
            x -= t;
            y -= t;
            return *this;
        }
        
        Vec2<T>& operator-=(const Vec2<T>& other)
        {
            x -= other.x;
            y -= other.y;
            return *this;
        }
        
        //MULTIPLY
        Vec2<T> operator*(const T& t) const
        {
            return { x * t, y * t}; //this is a vector
        }
        
        Vec2<T> operator*(const Vec2<T>& other) const
        {
            return { x * other.x, y * other.y}; //this is a vector
        }
        
        Vec2<T>& operator*=(const T& t) //We remove the const in these two functions because when we type something like a += 5 we expect a to change.
        { //Since wwe are changing the object itself we could have just defined this function as void instead of Vec2. However if we type something like b += (a += 5) that will not be evaluated
            x *= t;
            y *= t;
            return *this;
        }
        
        Vec2<T>& operator*=(const Vec2<T>& other)
        {
            x *= other.x;
            y *= other.y;
            return *this;
        }
        
        
        
        //DIVIDE
        Vec2<T> operator/(const T& t) const
        {
            return { x / t, y / t}; //this is a vector
        }
        
        Vec2<T> operator/(const Vec2<T>& other) const
        {
            return { x / other.x, y / other.y}; //this is a vector
        }
        
        Vec2<T>& operator/=(const T& t) //We remove the const in these two functions because when we type something like a += 5 we expect a to change.
        { //Since wwe are changing the object itself we could have just defined this function as void instead of Vec2. However if we type something like b += (a += 5) that will not be evaluated
            x /= t;
            y /= t;
            return *this;
        }
        
        Vec2<T>& operator/=(const Vec2<T>& other)
        {
            x /= other.x;
            y /= other.y;
            return *this;
        }
        
        T Magnitude() const
        {
            return dist(0.f, 0.f, x, y);
        }
        Vec2<T> Normalized() const
        {
            return operator/(Magnitude());
        }
        Vec2<T>& Normalize()
        {
            return operator/=(Magnitude());
        }
        T Dot(const Vec2<T>& other) const
        {
            return x * other.x + y * other.y;
        }
        T Angle() const
        {
            return atan(x, y);
        }
        T AngleBetween(const Vec2<T>& other) const
        {
            return acos(Dot(other) / (Magnitude() * other.Magnitude())); 
        }
    };
}
