using System;
using System.Collections.Generic;

namespace PTR
{
    public class PTR
    {
        List<IService> list;
        
        public PTR()
        {
            list = new List<IService>();
        }
        public void moreService(IService service)
        {
            list.Add(service);

        }
        public string calculate()
        {
            string path="";
            foreach(IService a in list)
            {
                if (a.Toppings >= 2)
                {
                    path = path + "Total Topping " + a.TotalPrice().ToString() + " Size of Pizze " + a.Size.ToString() + "\n";
                } else {
                    path = path + "Total Topping minimum of two" + " Size of Pizze " + a.Size.ToString() + "\n";
                }
            }
            return path;
        }

    }
}
