#pragma once

namespace math
{
    struct RangeContainsParams
    {
        bool left = false, right = false;
    };
    struct RangeOverlapParams
    {
        RangeContainsParams left ={}, right ={};
    };
    template<typename T>
    class Range
    {
        public:
            Range(const T& min, const T& max) :
                m_Min(min),
                m_Max(max)
            {
                if(min > max)
                    printf("Range min must be less than max\n");
            }
            Range(const Range<T>& other) { operator=(other); }
            Range(Range<T>&& other) { operator=(other); }
            
            bool operator==(const Range<T>& other) const
            {
                return isZero(m_Min - other.m_Min) && isZero(m_Max - other.m_Max);
            }
            bool operator!=(const Range<T>& other) const
            {
                return !isZero(m_Min - other.m_Min) || !isZero(m_Max - other.m_Max);
            }
            Range<T> operator+(const T& t) const
            {
                return Range<T>(m_Min + t, m_Max + t);
            }
            bool Contains(const T& t, int i = 10, const RangeContainsParams& params = {}) const
            {
                return (params.left ? m_Min <= t : m_Min < t) && (params.right ? m_Max >= t : m_Max > t);
            }
            bool Overlaps(const Range<T>& other, const RangeOverlapParams& params={}) const //contains the minimum or maximum of the other
            {
                return Contains(other.m_Min, params.left) || Contains(other.m_Max, params.right);
            }
            const T& GetMin() const
            {
                return m_Min;
            }
            const T& GetMax() const
            {
                return m_Max;
            }
            T Clamp(const T& t) //if object in range return object. if below return min. if above return max
            {
                return clamp(t, m_Min, m_Max);
            }
            T GetSpan() const //get the range
            {
                return m_Max - m_Min;
            }
            
        private:
            T m_Min, m_Max;
    };
}
