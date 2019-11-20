using System;
using System.Collections.Generic;
using System.Linq;

namespace PTR
{
    public class Customer:IService
    {
        private Size _pzSize;
        private List<Toppings> _toppings;
        public Customer(Size pzSize)
        {
            _toppings = new List<Toppings>();

            _pzSize = pzSize;

        }
        public void addTopping(Toppings a)
        {
            if(_toppings.Count()<=5)
            {
                _toppings.Add(a);
              
            }
        }
        public double TotalPrice()
        {
            double _total=0;
            foreach (Toppings p in _toppings)
            {
                _total = _total + p.ToppPrice;
            }
            return _total;
        }

        public int Toppings
        {
            get => _toppings.Count();
        }

        public Size Size
        {
            get => _pzSize;
        }
    }
}
