using System;

namespace A2Z
{
    class Program
    {
        static void Main(string[] args)
        {
            IItem a = new WrapCustomer(5,Licenses.nzFullLicense,1);
            IItem b = new WrapCustomer(5, Licenses.nzFullLicense, 3);
            Insurance insurance = new CarInsurance();
            Console.WriteLine("Rate:"+insurance.calculateRate(a));
            Console.WriteLine("Rate:" + insurance.calculateRate(b));
        }
    }
}
