using System;
namespace Interface
{
    public class WrapStaff : IParking
    {
        private StaffParkingKiosk _spk;
        public WrapStaff(decimal hour)
        {
            _spk = new StaffParkingKiosk(hour);
        }
        public decimal HoursParked => _spk.HoursParked;

        public decimal find()
        {
            return _spk.Find();
        }
    }
}
