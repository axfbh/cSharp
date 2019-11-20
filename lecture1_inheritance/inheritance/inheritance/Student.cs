using System;
namespace inheritance
{
    public class Student:Person
    {
        //子类是可以使用父类的成员变量和成员方法以及可以重载virtul成员方法
        public Student() { }

        public Student(string name)
        {
            Name = name;
        }

        public override string showDetail()
        {
            return "my name is " + Name+showLove();
        }
    }
}
