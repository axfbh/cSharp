using System;
using System.Collections.Generic;

namespace Association
{
    public class VTNz:Store
    {
        private int _totalOrder;
        private decimal _qty;
        private WrapInspection wrapInspection;
        private List<WrapInspection> list;
        
        public VTNz(string name)
        {
            Name = name;


            list = new List<WrapInspection>();
        }

        public override string showStoreDetail()
        {
            return "the name of store is" + Name;
        }
        public void orderItem(WrapInspection wrapInspection)
        {
            this.wrapInspection = wrapInspection;
            list.Add(this.wrapInspection);
            _totalOrder++;
            _qty = _qty + wrapInspection.showPrice();
        }
        public int showTotalOrder()
        {
            return _totalOrder;
        }
        public string showItemDetail()
        {
            string temp = ""; 
            foreach(WrapInspection obj in list)
            {
                temp =temp+obj.showName() + "Price:" + obj.showPrice()+"\n";
            }

            return temp;
        }
    }
}
