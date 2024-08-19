using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace CreateClassesObjs
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {

        Course choice;

        public MainWindow()
        {
            InitializeComponent();
        }

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            Course course1 = new Course();
            Course course2 = new Course();
            Course course3 = new Course();
            Course course4 = new Course();
            Course course5 = new Course();
            Course course6 = new Course();
            Course course7 = new Course();

            course1.SetName("IT 145");
            course2.SetName("IT 200");
            course3.SetName("IT 201");
            course4.SetName("IT 270");
            course5.SetName("IT 315");
            course6.SetName("IT 328");
            course7.SetName("IT 330");



            this.comboBox.Items.Add(course1);
            this.comboBox.Items.Add(course2);
            this.comboBox.Items.Add(course3);
            this.comboBox.Items.Add(course4);
            this.comboBox.Items.Add(course5);
            this.comboBox.Items.Add(course6);
            this.comboBox.Items.Add(course7);
        }

        private void button_Click(object sender, RoutedEventArgs e)
        {
            choice = (Course)(this.comboBox.SelectedItem);
            this.listBox.Items.Add(choice);
        }

    }
}
