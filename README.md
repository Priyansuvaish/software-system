# International Institute of Information Technology, Bangalore
## CS-513 System Software – Mini Project

### Project Title: Design and Development of Course Registration Portal (Academia)

#### Project Description
The CS-513 System Software Mini Project aims to design and develop an Academia Portal, a user-friendly and multifunctional system for managing course registration, students, faculty, and course information. The project involves creating a secure and efficient platform to cater to the needs of students, faculty, and administrators.

#### Functionalities
The project should incorporate the following key functionalities:

- All student and faculty details, as well as course information, are stored in files.
- Account holders must pass through a login system to access their accounts. User accounts are managed by the Administrator.
- Roles to implement: Faculty, Student, and Admin.
- The application should possess password-protected administrative access, preventing unauthorized access to the management system.
- Upon successful login, users should be presented with a menu tailored to their role:

  **Admin Menu:**
  - Add Student
  - Add Faculty
  - Activate/Deactivate Student
  - Update Student/Faculty details
  - Exit

  **Student Menu:**
  - Enroll in new Courses
  - Unenroll from already enrolled Courses
  - View enrolled Courses
  - Password Change
  - Exit

  **Faculty Menu:**
  - Add new Course
  - Remove offered Course
  - View enrollments in Courses
  - Password Change
  - Exit

- Course details access control: Read lock is used for viewing course details, while write lock is employed for enrolling and unenrolling to protect critical data.
- The project utilizes socket programming. The server maintains the database and serves multiple clients concurrently. Clients can connect to the server and access their specific academic details.
- System calls are preferred over library functions wherever possible in the project. This includes Process Management, File Management, File Locking, Semaphores, Multithreading, and Inter-Process Communication Mechanisms.
