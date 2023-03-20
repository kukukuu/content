#include <iostream>
#include <vector>
#include <math.h>
class znum
{
public:
    std::vector<int> factors;
    int size;
    znum(int num)
    {
        std::vector<int> factors;
        while (num % 2 == 0)
        {
            factors.push_back(2);
            num = num / 2;
        }
        for (int i = 3; i <= sqrt(num); i = i + 2)
        {
            while (num % i == 0)
            {
                factors.push_back(i);
                num = num / i;
            }
        }
        if (num > 2)
            factors.push_back(num);
        size = factors.size();
    }
    ~znum()
    {
    }
}
class block
{
public:
    block(int smallNum, std::vector<int> largeNums) 
    {
        for (int i(1); i < s)
    }
    ~block() {}
    int size;
    std::vector<int> dimensions;
    std::complex<double> *data;
    template <typename... Args>
    zvector(Args... args) : dimensions{args...}
    {
        size = (... * args);
        data = new std::complex<double>[size];
    }

private:
    znum smallNum;
    znum *largeNums;
}

int
main()
{
    int smallNum = 24;
    std::vector<int> largeNums = {48, 36, 60};
    int num(largeNums.size());
    std::vector<int> result = findFactors(num, smallNum, largeNums);
    for (int i : result)
        std::cout << i << ' ';
    return 0;
}