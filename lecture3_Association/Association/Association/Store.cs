using System;
namespace Association
{
    public abstract class Store
    {
        private string _name;

        public Store()
        {

        }
        public string Name
        {
            get => _name;
            set
            {
                _name = value;
            }
        }
        public virtual string showStoreDetail()
        {
            throw new NotImplementedException();
        }

    }
}
