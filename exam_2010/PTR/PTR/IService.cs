using System;
using System.Collections.Generic;

namespace PTR
{
    public interface IService
    {
        int Toppings
        {
            get;
        }
        Size Size
        {
            get;
        }
        double TotalPrice();

    }
}
