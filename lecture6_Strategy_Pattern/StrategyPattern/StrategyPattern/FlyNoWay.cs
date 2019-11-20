using System;
namespace StrategyPattern
{
    public class FlyNoWay:IFlyBehavoir
    {
        public FlyNoWay()
        {
        }

        public string fly()
        {
            return "flynoway";
        }
    }
}
