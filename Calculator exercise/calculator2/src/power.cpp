int powerOf(int base, int power)
{
    if (power == 0)
    {
        return 1;
    }
    else if(power == 1)
    {
        return 10;
    }else
    {
        for (int i = 0; i < power; i++)
        {
            base *= base;
        }
        return base;
    }
}