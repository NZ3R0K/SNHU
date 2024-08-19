namespace ConsoleApplication1
{
	class Program
	{
		static void Main(string[] args)
		{
			Course[] courses = new Course[7];

			courses[0] = new Course("IT 145");
			courses[1] = new Course("IT 200");
			courses[2] = new Course("IT 201");
			courses[3] = new Course("IT 270");
			courses[4] = new Course("IT 315");
			courses[5] = new Course("IT 328");
			courses[6] = new Course("IT 330");
			
			Console.WriteLine("Hallam's Copy");
			Console.WriteLine("List of courses:");
			
			Console.WriteLine(courses[0].getName());
			Console.WriteLine(courses[1].getName());
			Console.WriteLine(courses[2].getName());
			Console.WriteLine(courses[3].getName());
			Console.WriteLine(courses[4].getName());
			Console.WriteLine(courses[5].getName());
			Console.WriteLine(courses[6].getName());

			Console.WriteLine("Press any key to continue . . .");
			Console.ReadKey();
		}
	}


	class Course
	{
		private string name = "";

		public Course(string name)
		{
			this.name = name;
		}

		public string getName()
		{
			return name;
		}
	}
}