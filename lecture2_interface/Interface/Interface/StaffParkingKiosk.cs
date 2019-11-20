using System;
namespace Interface
{
    public class StaffParkingKiosk:Park
    {
        public StaffParkingKiosk(decimal hour)
        {
            HoursParked = hour;
        }
        public override decimal Find()
        {
            var temp = Math.Ceiling(HoursParked);
            if (temp <= 10&& temp > 0)
            {
               return 2;
            }
            return 2 + (temp - 10) * 2;

        }
    }
}
