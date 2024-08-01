#include <stdint.h>
#include <values.h>

typedef double TARGET_TYPE;
typedef uint8_t TARGET_INDEX;

TARGET_TYPE modulo(TARGET_TYPE x, TARGET_TYPE y)
{
    TARGET_TYPE result = x; 
      
    while (result >= y)
        result -= y;

    return result;
}

TARGET_TYPE gcd()
{

    TARGET_TYPE r = 0;

    if(m == 0 && n == 0)
        return -1;

    if(m < 0) 
        m = -m;
    if(n < 0)
        n = -n;


    while(n) 
    {
        r = modulo(m,n);
        m = n;
        n = r;
    }

    return m;
}


void main()
{
    gcd();
}