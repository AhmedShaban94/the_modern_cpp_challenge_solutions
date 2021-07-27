#include <iostream>
#include <vector>

template <typename T, std::size_t ROWS, std::size_t COLS>
class Array2D
{
private:
    std::vector<T> vec;

public:
    Array2D() = default;
    ~Array2D() = default;

    Array2D(const std::vector<T> &vec) : vec{vec} {}

    Array2D(const Array2D &) = default;
    Array2D &operator=(const Array2D &) = default;

    Array2D(Array2D &&) noexcept = default;
    Array2D &operator=(Array2D &&) noexcept = default;

    constexpr T &at(const std::size_t &r, const std::size_t &c)
    {
        return vec.at(r * ROWS + c);
    }

    constexpr const T &at(const std::size_t &r, const std::size_t &c) const
    {
        return vec.at(r * ROWS + c);
    }

    constexpr T &operator()(const std::size_t &r, const std::size_t &c)
    {
        return vec.at(r * ROWS + c);
    }

    constexpr const T &operator()(const std::size_t &r, const std::size_t &c) const
    {
        return vec.at(r * ROWS + c);
    }

    constexpr T *data() { return vec.data(); }

    constexpr T const *data() const { return vec.data(); }

    constexpr std::pair<std::size_t, std::size_t> size() const
    {
        return std::make_pair(ROWS, COLS);
    }

    constexpr T *begin() noexcept { return this->data(); }
    constexpr T const *begin() const { return this->data(); }

    constexpr T *end() noexcept { return this->data() + vec.size(); }
    constexpr T const *end() const { return this->data() + vec.size(); }

    void fill(const T &value) { std::fill(vec.begin(), vec.end(), value); }

    void swap(Array2D &other) { std::swap(other.vec, this->vec); }

    void print() const
    {
        for (std::size_t row = 0; row < ROWS; row++)
        {
            std::cout << "[ ";
            for (std::size_t col = 0; col < COLS; col++)
                std::cout << this->at(row, col) << ", ";
            std::cout << "]";
        }
    }
};