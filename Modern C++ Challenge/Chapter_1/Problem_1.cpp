#include <iostream>
#include <cmath>
using std::cin;
using std::cout;
using std::endl;


int main()
{
    unsigned long long int user_input;
    cin>>user_input;

    cout<<"Naive method"<<endl;

    unsigned long long int sum=0;

    for (unsigned long long i = 1; i <= user_input; i++)
    {
        if (i%3 == 0 | i%5 == 0)
        {
            sum+=i;
        }
    }
    cout<<"Sum: "<<sum<<endl;
    
    cout<<"Optimized method"<<endl;
    unsigned long long int n3, n5, n15;
    n3 = std::ceil((user_input-3) / 3) + 1;
    n5 = std::ceil((user_input-5) / 5) + 1 ;
    n15 = std::ceil((user_input-15) / 15) + 1;

    unsigned long long int s3, s5, s15;
    s3 = n3*(n3+1) / 2 *3;
    s5 = n5*(n5+1) /2 *5;
    s15 = n15*(n15+1)/ 2 *15;

    unsigned long long int opt_sum=0;
    opt_sum = s3 + s5 -s15;
    cout<<"Sum: "<<opt_sum<<endl;
    return 0;
}