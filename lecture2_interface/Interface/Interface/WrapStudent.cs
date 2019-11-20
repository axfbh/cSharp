using System;
namespace Interface
{
    public class WrapStudent : IParking
    {
        private StudentParkingKiosk spk;
        public WrapStudent(decimal hour)
        {
            spk = new StudentParkingKiosk(hour);
        }
        public decimal HoursParked => spk.HoursParked;

        public decimal find()
        {
            return spk.Find();
        }
    }
}
