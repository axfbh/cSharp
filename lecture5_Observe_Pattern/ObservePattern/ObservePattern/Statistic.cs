using System;
namespace ObservePattern
{
    public class Statistic:IObserve
    {
        private ISubject weather;
        public Statistic()
        {
          
        }
        public void update(float temp)
        {
            Console.WriteLine(temp);
        }

        
    }
}
