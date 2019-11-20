using System;
using System.Collections.Generic;

namespace ObservePattern
{
    public class WrapWeatherData:ISubject
    {
        private WeatherData weather;
     
        private List<IObserve> list;
        public WrapWeatherData(float temp, int pressure)
        {
            weather = new WeatherData(temp ,pressure);
            list = new List<IObserve>();
        }
        public WrapWeatherData() { }

        public void notifySubscriber()
        {
            foreach(IObserve obj in list)
            {
                obj.update(weather.Temp);
            }
        }

        public void registerSubscriber(IObserve observe)
        {
            list.Add(observe);
        }

        public void removeSubscriber(IObserve observe)
        {
            list.Remove(observe);
        }
        public float GetTemp
        {
            set
            {
                weather.Temp = value;
            }
        }
        public int GetPressure
        {
            set
            {
                weather.Pressure = value;
            }
        }
    }
}
