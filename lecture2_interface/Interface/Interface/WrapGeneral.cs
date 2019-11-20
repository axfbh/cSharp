using System;
namespace Interface
{
    public class WrapGeneral:IParking
    {
        private GeneralParkingKiosk _gpk;
        public WrapGeneral(decimal hour)
        {
            _gpk = new GeneralParkingKiosk(hour);
        }

        public decimal HoursParked => _gpk.HoursParked;

        public decimal find()
        {
            return _gpk.Find();
        }
    }
}
