using System;

namespace Association
{
    class Program
    {
       

        static void Main(string[] args)
        {
            WrapInspection wrap;
            VTNz vtnz = new VTNz("yellow store");

            wrap = new WrapInspection("yellow book",100);
            vtnz.orderItem(wrap);
            //Console.WriteLine(vtnz.showItemDetail());
            wrap = new WrapInspection("blue book", 100);
            vtnz.orderItem(wrap);
            Console.WriteLine(vtnz.showItemDetail());
            Console.WriteLine(vtnz.showTotalOrder());
        }
    }
}
