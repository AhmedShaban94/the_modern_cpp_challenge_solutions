#include <algorithm>
#include <experimental/iterator>
#include <iostream>
#include <iterator>
#include <vector>

template <typename T, std::size_t ROWS, std::size_t COLS>
class Array2D
{
private:
    std::vector<T> vec{};

public:
    Array2D() = default;
    ~Array2D() = default;

    Array2D(std::vector<T> vec) 
    : vec{ROWS * COLS == vec.size() ? std::move(vec) 
    : throw std::runtime_error{"dimension mismatch"}} {}
    
    Array2D(const std::initializer_list<T> &il) 
    : vec{ROWS * COLS == il.size() ? il 
    : throw std::runtime_error{"dimension mismatch"}} {}
    
    Array2D(const std::vector<std::vector<T>> &vec2d)
    {
        if (not(vec2d.size() == ROWS and vec2d.at(0).size() == COLS))
            throw std::runtime_error{"dimension mismatch"};
        std::for_each(vec2d.begin(), vec2d.end(), [this](const auto &row) { this->vec.insert(vec.end(), row.begin(), row.end()); });
    }

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

    [[nodiscard]] constexpr std::pair<std::size_t, std::size_t> size() const
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
        for (std::size_t r = 0; r < ROWS; r++)
        {
            const std::vector<std::size_t> row(begin() + r * COLS, begin() + r * COLS + COLS);
            std::cout << "[ ";
            std::copy(row.begin(), row.end(), std::experimental::make_ostream_joiner(std::cout, ", "));
            std::cout << "]\n";
        }
    }
};