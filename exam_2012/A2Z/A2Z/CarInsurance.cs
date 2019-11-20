using System;
namespace A2Z
{
    public class CarInsurance:Insurance
    {
        public CarInsurance()
        {

        }
        public override double calculateRate(IItem item)
        {
           if(item.showTime()>=2)
            {
                return _twoYearNoInsuranceRate;
            }else if(item.showYear()>=5) {
                return _fiveYearsRate;
            }
            return 0;
        }
    }
}
