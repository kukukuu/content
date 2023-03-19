#include <iostream>
#include <complex>
#include <random>

class Vector
{
public:
    int size;
    std::vector<int> dimensions;
    std::complex<double> *data;
    template <typename... Args>
    Vector(Args... args) : dimensions{args...}
    {
        size = (... * args);
        data = new std::complex<double>[size];
    }
    Vector(const std::vector<int> &dim) : dimensions(dim)
    {
        size = 1;
        for (int d : dim)
        {
            size *= d;
        }
        data = new std::complex<double>[size];
    }

    ~Vector()
    {
        delete[] data;
    }

    template <typename... Args>
    std::complex<double> &operator()(Args... args)
    {
        int index = 0;
        int temp[] = {args...};
        int stride = 1;
        for (int i = sizeof...(args) - 1; i >= 0; --i)
        {
            index += temp[i] * stride;
            stride *= dimensions[i];
        }
        return data[index];
    }

    Vector &operator=(const Vector &other)
    {
        if (this != &other)
        {
            if (size != other.size)
            {
                delete[] data;
                size = other.size;
                data = new std::complex<double>[size];
            }
            dimensions = other.dimensions;
            for (int i = 0; i < size; ++i)
            {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    Vector operator+(const double scalar) const
    {
        Vector result(dimensions);
        for (int i = 0; i < size; ++i)
        {
            result.data[i] = data[i] + scalar;
        }
        return result;
    }

    Vector operator-(const double scalar) const
    {
        Vector result(dimensions);
        for (int i = 0; i < size; ++i)
        {
            result.data[i] = data[i] - scalar;
        }
        return result;
    }

    Vector operator*(const double scalar) const
    {
        Vector result(dimensions);
        for (int i = 0; i < size; ++i)
        {
            result.data[i] = data[i] * scalar;
        }
        return result;
    }

    Vector operator/(const double scalar) const
    {
        if (scalar == 0)
            throw std::invalid_argument("Divisor cannot be zero.");

        Vector result(dimensions);
        for (int i = 0; i < size; ++i)
        {
            result.data[i] = data[i] / scalar;
        }

        return result;
    }

    Vector operator+(const std::complex<double> scalar) const
    {
        Vector result(dimensions);
        for (int i = 0; i < size; ++i)
        {
            result.data[i] = data[i] + scalar;
        }
        return result;
    }

    Vector operator-(const std::complex<double> scalar) const
    {
        Vector result(dimensions);
        for (int i = 0; i < size; ++i)
        {
            result.data[i] = data[i] - scalar;
        }
        return result;
    }

    Vector operator*(const std::complex<double> scalar) const
    {
        Vector result(dimensions);
        for (int i = 0; i < size; ++i)
        {
            result.data[i] = data[i] * scalar;
        }
        return result;
    }

    Vector operator/(const std::complex<double> scalar) const
    {
        if (scalar == std::complex<double>(0, 0))
            throw std::invalid_argument("Divisor cannot be zero.");

        Vector result(dimensions);
        for (int i = 0; i < size; ++i)
        {
            result.data[i] = data[i] / scalar;
        }

        return result;
    }

    Vector operator+(const Vector &other)
    {
        if (size != other.size)
        {
            throw std::invalid_argument("Vectors must have the same size.");
        }

        Vector result(dimensions);

        for (int i = 0; i < size; ++i)
        {
            result.data[i] = data[i] + other.data[i];
        }

        return result;
    }

    Vector operator-(const Vector &other)
    {
        if (size != other.size)
        {
            throw std::invalid_argument("Vectors must have the same size.");
        }

        Vector result(dimensions);

        for (int i = 0; i < size; ++i)
        {
            result.data[i] = data[i] - other.data[i];
        }

        return result;
    }

    Vector operator*(const Vector &other)
    {
        if (size != other.size)
        {
            throw std::invalid_argument("Vectors must have the same size.");
        }

        Vector result(dimensions);

        for (int i = 0; i < size; ++i)
        {
            result.data[i] = data[i] * other.data[i];
        }

        return result;
    }

    Vector operator/(const Vector &other)
    {
        if (size != other.size)
        {
            throw std::invalid_argument("Vectors must have the same size.");
        }

        for (int i = 0; i < other.size; ++i)
        {
            if (other.data[i] == std::complex<double>(0.0))
            {
                throw std::invalid_argument("Cannot divide by zero.");
            }
        }

        Vector result(dimensions);

        for (int i = 0; i < size; ++i)
        {
            result.data[i] = data[i] / other.data[i];
        }

        return result;
    }

    void assign_zero()
    {
        for (int i = 0; i < size; ++i)
            data[i] = 0;
    }

    void assign_unit()
    {
        for (int i = 0; i < size; ++i)
            data[i] = 1;
    }

    void assign_random()
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(0.0, 1.0);
        for (int i = 0; i < size; ++i)
            data[i] = {dis(gen), dis(gen)};
    }

    double magnitude()
    {
        double sum = 0.0;
        for (int i = 0; i < size; ++i)
        {
            sum += std::norm(data[i]);
        }
        return sqrt(sum);
    }

    Vector dot_product(const Vector &other)
    {
        if (size != other.size)
        {
            throw std::invalid_argument("Vectors must have the same size.");
        }

        Vector result(dimensions);

        for (int i = 0; i < size; ++i)
        {
            result.data[i] = data[i] * std::conj(other.data[i]);
        }

        return result;
    }

    std::complex<double> dot(const Vector &other)
    {
        if (size != other.size)
        {
            throw std::invalid_argument("Vectors must have the same size.");
        }

        std::complex<double> sum(0.0, 0.0);

        for (int i = 0; i < size; ++i)
        {
            sum += data[i] * std::conj(other.data[i]);
        }

        return sum;
    }

    Vector cross_product(const Vector &other)
    {
        if (size != 3 || other.size != 3)
        {
            throw std::invalid_argument("Cross product is only defined for vectors of size 3.");
        }

        Vector result(dimensions);

        result.data[0] = data[1] * other.data[2] - data[2] * other.data[1];
        result.data[1] = data[2] * other.data[0] - data[0] * other.data[2];
        result.data[2] = data[0] * other.data[1] - data[1] * other.data[0];

        return result;
    }

    void display()
    {
        std::cout << "Dimensions: ";
        for (auto d : dimensions)
            std::cout << d << ' ';
        std::cout << '\n';

        std::cout << "Data: ";
        for (int i = 0; i < size && i < 10; ++i)
            std::cout << data[i] << ' ';

        if (size > 10)
        {
            std::cout << "...";
        }

        std::cout << '\n';
    }

};

