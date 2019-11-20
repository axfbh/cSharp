using System;

namespace PTR
{
    class Program
    {
        static void Main(string[] args)
        {
            PTR pTR = new PTR();


            Customer a = new Customer(Size.small);
            a.addTopping(new Toppings(10));
            a.addTopping(new Toppings(10));
            Customer b = new Customer(Size.large);
            b.addTopping(new Toppings(10));
            b.addTopping(new Toppings(10));
            IService service = a;
            IService service1 = b;
            pTR.moreService(service);
            pTR.moreService(service1);
            Console.WriteLine(pTR.calculate());
            
        }
    }
}
