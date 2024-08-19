//removed unused using statements

namespace Classes
{
	class Program
	{
		static void Main()  //removed unused args parameter
		{
			Console.WriteLine("Hallam's Copy");

			Point origin = new Point();
			Point bottomRight = new Point(1366, 768);   //"another" is not a keyword, assuming it should be "new"

			double distance = origin.DistanceTo(bottomRight);

			Console.WriteLine("Distance is: {0}", distance);
			Console.WriteLine("Number of Point objects: {0}", Point.ObjectCount());

			WaitForKey();
		}


		static void WaitForKey()
		{
			Console.WriteLine("Press any key to continue . . .");
			Console.ReadKey();
		}
	}



	class Point
	{
		private int x, y;
		private static int objectCount = 0; //field is not static and thus can not be accessed by ObjectCount() method, added "static" keyword {pg 317}
		public static int ObjectCount() => objectCount; //Changed from normal method to lambda method {pg 319}


		#region Constructors

		public Point()  //Assuming this should be a constructor, removing void declaration
		{
			this.x = -1;
			this.y = -1;
			objectCount++;
		}

		public Point(int x, int y)
		{
			this.x = x;
			this.y = y;
			objectCount++;
		}

		#endregion


		public double DistanceTo(Point other)   //Can not access due to protection level private, changed to public
		{
			int xDiff = this.x - other.x;
			int yDiff = this.y - other.y;
			double distance = Math.Sqrt((xDiff * xDiff) + (yDiff * yDiff));
			return distance;
		}
	}
}