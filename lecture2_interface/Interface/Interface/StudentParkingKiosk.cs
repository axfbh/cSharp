using System;
namespace Interface
{
    public class StudentParkingKiosk:Park
    {
        public StudentParkingKiosk(decimal hour)
        {
            HoursParked = hour;
        }
        public override decimal Find()
        {
            var temp = Math.Ceiling(HoursParked);
            return temp*1;
        }
    }
}
