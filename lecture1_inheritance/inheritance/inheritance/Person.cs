using System;
namespace inheritance
{
    public class Person
    {
        private string _name;

        public string Name
        {
            get => _name;
            set
            {
                _name = value;
            }
        }

        public Person()
        {
        }

        public string showLove()
        {
            return "i love you";
        }

        public virtual string showDetail()
        {
            throw new NotImplementedException();
        }
    }
}
