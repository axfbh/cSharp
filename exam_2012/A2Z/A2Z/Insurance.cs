using System;
namespace A2Z
{
    public abstract class Insurance
    {


        protected const double _fiveYearsRate=0.1;
        protected const double _twoYearNoInsuranceRate = 0.15;
        public Insurance()
        {
        }
        public virtual double calculateRate(IItem item)
        {
            throw new NotImplementedException();
        }
    }
}
