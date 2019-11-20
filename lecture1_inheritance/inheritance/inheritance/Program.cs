using System;

namespace inheritance
{
    class Program
    {
        static void Main(string[] args)
        {
            Person student = new Student();

            student.Name = "ad";
   
            Console.WriteLine(student.showDetail());
        }
    }
}
