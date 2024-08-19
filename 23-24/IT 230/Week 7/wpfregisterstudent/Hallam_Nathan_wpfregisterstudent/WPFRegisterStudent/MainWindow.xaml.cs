using System.Windows;

namespace WPFRegisterStudent
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        Course choice;
        int credits = 0;

        public MainWindow()
        {
            InitializeComponent();
        }


        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
			#region Create Courses
			Course course1 = new Course("IT 145");
            Course course2 = new Course("IT 200");
            Course course3 = new Course("IT 201");
            Course course4 = new Course("IT 270");
            Course course5 = new Course("IT 315");
            Course course6 = new Course("IT 328");
            Course course7 = new Course("IT 330");
			#endregion

			#region Add Courses to Combo Box
			this.cmbobx_courses.Items.Add(course1);
            this.cmbobx_courses.Items.Add(course2);
            this.cmbobx_courses.Items.Add(course3);
            this.cmbobx_courses.Items.Add(course4);
            this.cmbobx_courses.Items.Add(course5);
            this.cmbobx_courses.Items.Add(course6);
            this.cmbobx_courses.Items.Add(course7);
			#endregion


			SetCreditText(credits.ToString());
		}


        /// <summary>
        /// Adds a course to the list of registered courses given it is not already in the list.
        /// </summary>
        /// <param name="course">Course to add to the registered list.</param>
        /// <returns>True if added to list, otherwise false.</returns>
        private bool AddCourseToList(Course course)
        {
            if (course.IsRegisteredAlready())
				return false;

			lstbx_registeredCourses.Items.Add(course);
            return true;
        }


		/// <summary>
		/// Sets the confirmation labels text
		/// </summary>
		/// <param name="text">String to set the labels text.</param>
		private void SetConfirmLabelText(string text)
        {
			this.lbl_confirmation.Content = text;
		}


		/// <summary>
		/// Sets the credit textbox text
		/// </summary>
		/// <param name="text">String to set the textbox's text to.</param>
		private void SetCreditText(string text)
		{
			this.txtbx_ttlCredits.Text = text;
		}


		private void RegisterForCourse(Course course)
		{
			SetConfirmLabelText($"Registration Confirmed for course {course.getName()}.");

			course.SetToRegistered();

			credits += 3;

			SetCreditText(credits.ToString());

		}


		#region Callbacks
		private void btn_register_Click(object sender, RoutedEventArgs e)
		{
			choice = (Course)(this.cmbobx_courses.SelectedItem);

			//If equal or over max credits
			if (credits >= 9)
			{
				SetConfirmLabelText($"You can not register for more than 9 credit hours.");
				return;
			}
			//If course was unable to add to the list (already registered)
			else if (!AddCourseToList(choice))
			{
				SetConfirmLabelText($"You have already registered for this {choice.getName()} course.");
				return;
			}

			RegisterForCourse(choice);
		}
		#endregion
	}
}