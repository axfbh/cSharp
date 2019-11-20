using System;
namespace A2Z
{
    public class WrapCustomer:IItem
    {
        private Customer customer;
        public WrapCustomer(int year, Licenses licenses,int time)
        {
            customer = new Customer(year,licenses,time);
        }
        public int showYear()
        {
            return customer.LincenseYears;
        }
        public int showTime()
        {
            return customer.TwoYearsAddtion;
        }
    }
}
