using System;

namespace StrategyPattern
{
    class Program
    {
        static void Main(string[] args)
        {
            Duck mallard = new MallardDuck();
            Console.WriteLine(mallard.performFly());
        }
    }
}
