   M S B A M L   `   `   `  ����M  IWPFRegisterStudent, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null7 clr-namespace:WPFRegisterStudentWPFRegisterStudent  5   	   #    WPFRegisterStudent.MainWindow   5   	   R NWindowsBase, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35\ XPresentationFramework, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35W SPresentationCore, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35D 9http://schemas.microsoft.com/winfx/2006/xaml/presentation    5   	   R NSystem.Xaml, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089:x,http://schemas.microsoft.com/winfx/2006/xaml     5   	   @d2http://schemas.microsoft.com/expression/blend/2008     5   	   Jmc;http://schemas.openxmlformats.org/markup-compatibility/2006     5   	   2local clr-namespace:WPFRegisterStudent     5   	   -   5          � Title$*  $WPF Register Student - Hallam's Copy��5   	   $��395.902��66   $	��525��6G   .��5	      � .+�5
   
   �� -   5         ��Name$ cmbobx_courses��5
      $
��Left=�5      $��	66,37,0,0q�5      $	��Top=�5      $	��164��5       �� IsDropDownOpen . 5      �� 5   
   -   5         ��Name$ btn_register��5      $��Register for this course��5      $
��Left=�5      $��
283,39,0,0q�5      $	��Top=�5      $	��166��5      5      �� 5   
   -   5         ��Name$ lstbx_registeredCourses��5      $
��Left=�5      $��69��5      $��
66,276,0,0q�5      $	��Top=�5      $	��164��5      �� 5    
   -   5         ��Name$ txtbx_ttlCredits��5       $
��Left=�5!      $��23��5"      $��283,276,0,0q�5#       �� TextWrapping$
 Wrap=�5$      $��0��5%      $	��Top=�5&      $��73��5'       �� 
IsReadOnly . 5(      �� 5*   
   -   5         ��Name$ lbl_main��5*      $;��5Please select a course for which you want to register��5+      $
��Left=�5,      $��66,7,0,0q�5-      $	��Top=�5.      $	��383��5/      �� 51   
   -   5        $ lbl_registeredCourses��51      $'��!You are currently registered for:��52      $
��Left=�53      $��
66,245,0,0q�54      $	��Top=�55      $	��176��56      �� 58   
   -   5        $ lbl_ttlCredits��58      $��Total Credit Hours��59      $
��Left=�5:      $��283,245,0,0q�5;      $	��Top=�5<      $	��106��5=      �� 5?   
   -	   5        $ lbl_confirmation��5?      $�� ��5@      $
��Left=�5A      $��
66,213,0,0q�5B      $	��Top=�5C      $	��383��5D      ���	#FFEE0E0E5E      5G      5H      