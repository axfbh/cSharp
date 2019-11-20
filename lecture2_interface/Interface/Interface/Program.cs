using System;

namespace Interface
{
    class Program
    {
        //Wrap类需要包含被包裹的类的实例。
        //接口在Wrap类上执行
        static void Main(string[] args)
        {

            IParking parking1 = new WrapGeneral(10);
            Console.WriteLine(parking1.find());
        }
    }
}
