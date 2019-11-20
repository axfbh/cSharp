using System;
namespace StrategyPattern
{
    public abstract class Duck
    {
        private IFlyBehavoir flyBehavoir;
        private IQuackBehavior quackBehavior;
        public Duck()
        {

        }
        public IFlyBehavoir FlyBehavoir
        {
            set
            {
                flyBehavoir = value;
            }
        }
        public IQuackBehavior QuackBehavior
        {
            set
            {
                quackBehavior = value;
            }
        }

        public string performFly()
        {
          return  flyBehavoir.fly();
        }
        public string performQuack()
        {
           return quackBehavior.Quack();
        }
        public virtual string display()
        {
            throw new NotImplementedException();
        }

    }
}
