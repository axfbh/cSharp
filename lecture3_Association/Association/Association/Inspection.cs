using System;
namespace Association
{
    public class Inspection
    {
        private string _inspectionName;
        private decimal _price;
        public Inspection(string name,decimal price)
        {
            _inspectionName = name;
            this._price = price;
        }
        public string InspectionName
        {
            get => _inspectionName;
        }
        public decimal Price
        {
            get => _price;
        }
    }
}
