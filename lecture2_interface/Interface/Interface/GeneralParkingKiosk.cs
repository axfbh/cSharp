using System;
namespace Interface
{
    public class GeneralParkingKiosk :Park
    {

        public GeneralParkingKiosk(decimal hour)
        {
            HoursParked = hour;
        }
        public override decimal Find()
        {
            var temp = Math.Ceiling(HoursParked);
            return temp * 2;
        }

    }
}
