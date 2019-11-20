using System;
namespace StrategyPattern
{
    public class FlyWithWings:IFlyBehavoir
    {
        public FlyWithWings()
        {
        }

        public string fly()
        {
            return "flywithwing";
        }
    }
}
