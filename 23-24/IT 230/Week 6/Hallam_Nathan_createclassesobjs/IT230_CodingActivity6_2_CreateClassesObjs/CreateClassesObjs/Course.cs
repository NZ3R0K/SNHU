namespace CreateClassesObjs
{
	internal class Course
	{
		private string _courseName;

		public void SetName(string name) => _courseName = name;

		public string GetName() => _courseName;

		public override string ToString()
		{
			return _courseName;
		}
	}
}
