using System;
namespace ObservePattern
{
    public class WeatherData
    {
        private float _temp;
        private int _pressure;
        public WeatherData(float temp,int pressure)
        {
            _temp = temp;
            _pressure = pressure;
        }
        public float Temp
        {
            get => _temp;
            set
            {
                _temp = value;
            }
        }
        public int Pressure
        {
            get => _pressure;
            set
            {
                _pressure = value;
            }
        }
    }
}
