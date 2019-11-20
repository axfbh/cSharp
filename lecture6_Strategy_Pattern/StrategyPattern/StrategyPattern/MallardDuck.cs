using System;
namespace StrategyPattern
{
    public class MallardDuck:Duck
    {

        public MallardDuck()
        {
            FlyBehavoir = new FlyWithWings();

        }
        public override string display()
        {
            return "MallarDuck";
        }

    }
}
