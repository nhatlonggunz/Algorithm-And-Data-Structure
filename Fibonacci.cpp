#include <iostream>
#include <ctime>
#define MAX 100
#define NIL -1
using namespace std;

class Array
{
public:
    void SetupArr(int arr[], int length)
    {
        for(int i = 0; i < length; i++)
            arr[i] = NIL;
    }

    void OutputArr(int arr[], int length)
    {
        for(int i = 0; i < length; i++)
            std::cout << arr[i] << " ";
    }
};

class Fibonacci
{
public:
    Fibonacci()
    {
        Array objArray;
        objArray.SetupArr(lookup, MAX);
    }
    int num;
    int Memoization(int num)
    {
        if(lookup[num] == NIL) {
            if(num <= 1)
                lookup[num] = num;
            else
                lookup[num] = Memoization(num - 1) + Memoization(num - 2);
        }

        return lookup[num];
    }

    int Tabulation(int num)
    {
        lookup[0] = 0;
        lookup[1] = 1;
        for(int i = 2; i <= num; i++)
            lookup[i] = lookup[i - 1] + lookup[i - 2];

        return lookup[num];
    }

    int Normal(int num)
    {
        if(num <= 2)
            return 1;
        return Normal(num - 1) + Normal(num - 2);
    }

private:
    int lookup[MAX];
};

class TimeCounting
{
public:
    void TabulationTimeCounting(int result, Fibonacci objFibonacci)
    {
        std::cout << "Using Tabulation (bottom - up)" << std::endl;
        clock_t start = clock();
        for(int i = 0; i < 1000000; i++) {
            result = objFibonacci.Tabulation(objFibonacci.num);
        }
        clock_t finish = clock();
        std::cout << "The " << objFibonacci.num << "th fibo number is: " << result << endl;
        std::cout << "Time: " << (double)(finish - start) / CLOCKS_PER_SEC << endl;
        std::cout << std::endl;
    }

    void MemoizationTimeCounting(int result, Fibonacci objFibonacci)
    {
        std::cout << "Using memoization (top - down)" << std::endl;
        clock_t start = clock();
        for(int i = 0; i < 1000000; i++) {
            result = objFibonacci.Memoization(objFibonacci.num);
        }
        clock_t finish = clock();
        std::cout << "The " << objFibonacci.num << "th fibo number is: " << result << endl;
        std::cout << "Time: " << (double)(finish - start) / CLOCKS_PER_SEC << endl;
        std::cout << std::endl;
    }

    void NormalTimeCounting(int result, Fibonacci objFibonacci)
    {
        std::cout << "Using normal recursive" << std::endl;
        clock_t start = clock();
        for(int i = 0; i < 1000; i++) {
            result = objFibonacci.Normal(objFibonacci.num);
        }
        clock_t finish = clock();
        std::cout << "The " << objFibonacci.num << "th fibo number is: " << result << endl;
        std::cout << "Time: " << (double)(finish - start) / CLOCKS_PER_SEC << endl;
        std::cout << std::endl;
    }
};

int main()
{
    Fibonacci objFibonacci1, objFibonacci2, objFibonacci3;
    TimeCounting objTimeCounting1, objTimeCounting2;
    int num = 0, result = 0;
    std::cout << "Which fibo number do you want to find: ";
    std::cin >> num;
    objFibonacci1.num = num;
    objFibonacci2.num = num;
    objFibonacci3.num = num;

    // Normal
    // NormalTimeCounting(result, objFibonacci1);


    // Memoization (top - down)
    objTimeCounting1.MemoizationTimeCounting(result, objFibonacci2);

    // Tabulation (bottom - up)
    objTimeCounting2.TabulationTimeCounting(result, objFibonacci3);

    return 0;
}
