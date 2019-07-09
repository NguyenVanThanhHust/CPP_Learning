#include <iostream>
#include <vector>

using namespace std;

class BigArray
{
public:
    BigArray(int x);
    ~BigArray();
    int getItem(int index) const
    {
        //accessCount++;
        const_cast<BigArray*>(this)->accessCount++;
        return v[index];
    }
    void setV2Item(int index, int x) const
    {
        *(v2 + index) = x;
    }

private:
    vector<int> v; // huge vector
    int accessCount;
    int *v2;
};

BigArray::BigArray(int x)
{
    for (size_t i = 0; i < x; i++)
    {
        v.push_back(i * 2);
    }
}

BigArray::~BigArray()
{
}
int main()
{
    BigArray bigArray1 = BigArray(10);
    for (size_t i = 0; i < 10; i++)
    {
        int k = bigArray1.getItem(i);
        cout << "k_th value: " << k << endl;
    }
    return 0;
}