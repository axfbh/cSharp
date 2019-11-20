using System;
namespace PTR
{
    public class Toppings
    {
 
        private double _toppingPrice;
        public Toppings(double price)
        {
            _toppingPrice = price;
        }

        public double ToppPrice
        {
            get => _toppingPrice;
        }
    }
}
