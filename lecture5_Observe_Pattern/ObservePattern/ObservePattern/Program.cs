using System;

namespace ObservePattern
{
    class Program
    {
        static void Main(string[] args)
        {
            ISubject obj = new WrapWeatherData(1,1);
            obj.registerSubscriber(new CurrentCondtion());
            
            obj.registerSubscriber(new Statistic());
            obj.notifySubscriber();
        }
    }
}
