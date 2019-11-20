using System;
namespace Association
{
    public class WrapInspection:IServiceItem
    {
        private Inspection inspection;
        public WrapInspection(string name, decimal price)
        {
            inspection = new Inspection(name,price);
        }

        public string showName()
        {
            return inspection.InspectionName;
        }

        public decimal showPrice()
        {
            return inspection.Price;
        }
    }
}
