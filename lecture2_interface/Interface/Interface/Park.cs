using System;
namespace Interface
{
    public abstract class Park
    {
        private decimal _HoursParked;
        public decimal HoursParked
        {
            get => _HoursParked;
            set { _HoursParked = value; }
        }
        public Park()
        {

        }

        public virtual decimal Find()
        {
            throw new NotImplementedException();
        }
    }
}
