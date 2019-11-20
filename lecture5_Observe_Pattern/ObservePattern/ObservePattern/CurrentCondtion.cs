using System;
namespace ObservePattern
{
    public class CurrentCondtion:IObserve
    {
        private ISubject weather;
        public CurrentCondtion()
        {
            
           
        }

        public void update(float temp)
        {
            Console.WriteLine(temp);    
        }
        
    }
}
