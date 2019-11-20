using System;
namespace A2Z
{
    public class Customer
    {
        private int _lincenseYears;
        private Licenses _lincense;
        private int _twoYearsAddtion;

        public Customer(int year, Licenses licenses,int two)
        {
            _lincenseYears = year;
            _lincense = licenses;
            _twoYearsAddtion = two;
        }

        public int LincenseYears
        {
            get => _lincenseYears;
            set
            {
                _lincenseYears = value;
            }
        }
        public Licenses Licenses
        {
            get => _lincense;
            set
            {
                _lincense = value;
            }
        }
        public int TwoYearsAddtion
        {
            get => _twoYearsAddtion;
            set
            {
                _twoYearsAddtion = value;
            }
        }
    }
}
