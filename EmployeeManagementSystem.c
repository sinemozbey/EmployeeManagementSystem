#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define MAX_EMPLOYEES 1000

#define FILENAME "employees.txt"
#define TEMPFILE "temp.txt"
#define ADMINFILE "adminaccount.txt"
#define USERFILE "useraccount.txt"
#define ADMINANNUALFILE "annualdayrequest.txt"

struct EmployeeCard {
    char name[50];
    char surname[50];
    char id[10];
};

struct IDCards {
    
    char username[20];
    char password[20];
};

struct Employee{
    
    char name[50];
    char surname[50];
    char age[50];
    char title[50];
    char gender[50];
    char call[3];
    char country[50];
    char city[50];
    char id[20];
    int annual;
    float salary;
    char AnnualRequest[10];
};

struct EmployeeAnnual {
    
    char name[50];
    char surname[50];
    char startDay[10];
    char startMonth[10];
    char startYear[10];
    char finishDay[10];
    char finishMonth[10];
    char finishYear[10];
    char id[20];
    int requestedDay;
    int totalDay;
        
};

struct EmployeeSurvey {
    
    char name[50];
    char surname[50];
    char id[10];
    char date_day[2];
    char date_month[2];
    char date_year[4];
    char title[20];
    char subject[20];
    char message[100];
    int requestedDay;
    int totalDay;
        
};

void removeEmployee();
void loginpage();
void userpage(char username[20]);
void adminpage(char username[20]);
int LineSelector(char username[20], FILE *file);
void Username_to_ID(char username[20],int LineNumber, FILE *file, struct EmployeeCard IDCard[1]);
void ID_to_Username(char ID[10], int LineNumber, FILE *file, struct IDCards IDCard[1]);
void ID_to_EmployeeInformation(char username[20],float updated_salary, int LineNumber);
void SalaryChangeEmployee();
void FileCopier();
void FileCopier_toAnnual();
void FileCopier_toUser();
void ID_to_EmployeeAnnualLeave(char username[20], char decision[10], int LineNumber);



//--------------------------------------------------------------------------------------------ADMINS-----------------------------------------------------------------------------------------------------

void addEmployee(struct Employee employees[], int *numEmployees) {
    if (*numEmployees < MAX_EMPLOYEES) {
        struct Employee newEmployee;
        struct IDCards ID;

        printf("Enter employee ID: ");
        scanf("%s", newEmployee.id);

        printf("Enter employee name: ");
        scanf("%s", newEmployee.name);
        
        printf("Enter employee surname: ");
        scanf("%s", newEmployee.surname);
        
        bool IsOkey = true;
        int choicefortitle;
        do {
        printf("Enter employee title: \n");
        printf("1. CEO\n");
        printf("2. CFO\n");
        printf("3. Project Manager\n");
        printf("4. Team Leader\n");
        printf("5. Engineer\n");
        printf("6. Intern\n");
        scanf("%d", &choicefortitle);
     

     switch (choicefortitle) {
                case 1:
                    strcpy(newEmployee.title, "CEO");
                    IsOkey = false;
                    break;
                case 2:
                    strcpy(newEmployee.title, "CFO");
                    IsOkey = false;
                    break;
                case 3:
                    strcpy(newEmployee.title, "Project Manager");
                    IsOkey = false;
                    break;
                case 4:
                    strcpy(newEmployee.title, "Team Leader");
                    IsOkey = false;
                    break;
                case 5:
                    strcpy(newEmployee.title, "Engineer");
                    IsOkey = false;
                    break;
                case 6:
                    strcpy(newEmployee.title, "Intern");
                    IsOkey = false;
                    break;
                default:
                    printf("Invalid choice. Please try again.\n");
            }

        } while (IsOkey);
        
        printf("Enter employee age: ");
        scanf("%s", newEmployee.age);
        
        bool IsValid = true;
        int choiceforgender;
        do {
        printf("Enter employee gender: \n");
        printf("1. Male\n");
        printf("2. Female\n");
        scanf("%d", &choiceforgender);
     

     switch (choiceforgender) {
                case 1:
                    strcpy(newEmployee.gender, "Male");
                    strcpy(newEmployee.call, "Mr");
                    IsValid = false;
                    break;
                case 2:
                    strcpy(newEmployee.gender, "Female");
                    strcpy(newEmployee.call, "Ms");
                    IsValid = false;
                    break;
                default:
                    printf("Invalid choice. Please try again.\n");
            }

        } while (IsValid);
        
        
        printf("Enter employee country: ");
        scanf("%s", newEmployee.country);
        
        printf("Enter employee city: ");
        scanf("%s", newEmployee.city);
        
        printf("Enter employee total annual leave days: ");
        scanf("%d", &newEmployee.annual);

        printf("Enter employee monthly salary: ");
        scanf("%f", &newEmployee.salary);
        
        printf("You have to create account for your new employee.\n\n");
        
        printf("Enter employee username: ");
        scanf("%s", ID.username);
        
        printf("Enter employee password: ");
        scanf("%s", ID.password);
        
        strcpy(newEmployee.AnnualRequest, "False");
        
    printf("We have completed entering information about the %s and %s username is %s\n", newEmployee.name, newEmployee.call, ID.username);

        employees[*numEmployees] = newEmployee;
        (*numEmployees)++;

        // Open the file in append mode
        FILE *file = fopen(FILENAME, "a");
        if (file != NULL) {
            // Write the new employee information to the file
            fprintf(file, "%s %s %s %s %s %s %s %s %d %.2f %s\n", newEmployee.id, newEmployee.title, newEmployee.name, newEmployee.surname, newEmployee.age, newEmployee.gender, newEmployee.country, newEmployee.city, newEmployee.annual, newEmployee.salary, newEmployee.AnnualRequest);

            // Close the file
            fclose(file);
        } else {
            printf("Error opening file for writing!\n");
        }
   
    
            // Open the file in append mode
        FILE *userfile = fopen(USERFILE, "a");
        if (userfile != NULL) {
            // Write the new employee information to the file
            fprintf(userfile, "%s %s\n", ID.username, ID.password);

            // Close the file
            fclose(userfile);
        } else {
            printf("Error opening file for writing!\n");
        }
        
            

     printf("Employee added successfully!\n");
    
    
    } else {
        printf("Maximum number of employees reached!\n");
    }
    
    
}

void removeEmployee() {

    char line[256];
    char line2[256];
    int lineNumber = 0;
    int currentLine = 0;
      char employee_id[20];
      
        printf("Enter employee ID who you gonna remove: ");
        scanf("%s", employee_id);
    
        FILE *employeefile_r = fopen(FILENAME, "r");
       FILE *tempFile = fopen(TEMPFILE,"w");
       
       lineNumber = LineSelector(employee_id,employeefile_r);
       
       printf("ID is in %d. line",lineNumber);
       
    while (fgets(line, 256, employeefile_r) != NULL) {
            
            currentLine++;
            
        if (currentLine != lineNumber) {
        
            fputs(line, tempFile);
        
        }
    }
    fclose(employeefile_r);
    fclose(tempFile);
    FileCopier();
    
    FILE *userfile_r = fopen(USERFILE, "r");
    FILE *tempFile_2 = fopen(TEMPFILE,"w");
           
         while (fgets(line2, 256, userfile_r) != NULL) {
               
        currentLine++;
                    
        if (currentLine != lineNumber) {
        
            fputs(line2, tempFile_2);
        
        }
    }
    fclose(userfile_r);
    fclose(tempFile_2);
    FileCopier_toUser();
    
}

void SalaryChangeEmployee() {

    char line[256];
      int lineNumber = 0;
      int currentLine = 0;
      
      char employee_id[20];
      float updated_salary;
      
      char name[20];
      char surname[20];
      char id[10];

        printf("Enter employee ID who you gonna remove: ");
        scanf("%s", employee_id);
        
        printf("Enter employee`s new salary: ");
        scanf("%f", &updated_salary);
    

        //FILE *tempfile_w = fopen(TEMPFILE, "a");
        FILE *employeefile_r = fopen(FILENAME, "r");
        
    lineNumber = LineSelector(employee_id,employeefile_r);
    
    //printf("ID is in %d \n", LineSelector(employee_id,employeefile_r));
    fclose(employeefile_r);

    ID_to_EmployeeInformation(employee_id , updated_salary,lineNumber);

}


void DisplayAnnualDayRequests() {


    int currentLine = 0;
    int lineNumber = 0;
    char line[256];
    char line2[256];
    char line3[256];
    struct EmployeeAnnual employeeAnnual[1];
    struct Employee employee[1];
    FILE *annualfile = fopen(ADMINANNUALFILE, "r");
    FILE *employeefile = fopen(FILENAME, "r");
    if (annualfile != NULL) {
    
        printf("\nEmployee List from File:\n");
        printf("ID\t\tName\t\tSurname\t\tStart Date\tFinish Date\tRequested Days\n");
        while (fscanf(annualfile, "%s %s %s %s %s %s %s %s %s %d", employeeAnnual[0].id, employeeAnnual[0].name, employeeAnnual[0].surname,  employeeAnnual[0].startDay, employeeAnnual[0].startMonth, employeeAnnual[0].startYear, employeeAnnual[0].finishDay, employeeAnnual[0].finishMonth, employeeAnnual[0].finishYear, &employeeAnnual[0].requestedDay) == 10) {
        

            
            printf("%s\t\t%-15s\t%-15s\t%-2s.%-2s.%-4s\t%-2s.%-2s.%-4s\t%d\t\t%d\t%s\n", employeeAnnual[0].id, employeeAnnual[0].name, employeeAnnual[0].surname, employeeAnnual[0].startDay, employeeAnnual[0].startMonth, employeeAnnual[0].startYear, employeeAnnual[0].finishDay, employeeAnnual[0].finishMonth, employeeAnnual[0].finishYear, employeeAnnual[0].requestedDay, employee[0].annual, employee[0].AnnualRequest);
                   
         }
        


    } else {
        printf("Error opening file for reading!\n");
    }
    
    
       fclose(annualfile);
        fclose(employeefile);
    
        FILE *annualfile_G = fopen(ADMINANNUALFILE, "r");

  while (fgets(line, sizeof(line), annualfile_G) != NULL) {

    FILE *employeefile_G = fopen(FILENAME, "r");

    sscanf(line, "%s %s %s %s %s %s %s %s %s %d", employeeAnnual[0].id, employeeAnnual[0].name, employeeAnnual[0].surname,  employeeAnnual[0].startDay, employeeAnnual[0].startMonth, employeeAnnual[0].startYear, employeeAnnual[0].finishDay, employeeAnnual[0].finishMonth, employeeAnnual[0].finishYear, &employeeAnnual[0].requestedDay);

        printf("\n----------------------------------\n");
        printf(")%s have an annual leave request from %s.%s.%s to %s.%s.%s, when you accept it is going to finish in %d days.", employeeAnnual[0].name, employeeAnnual[0].startDay, employeeAnnual[0].startMonth, employeeAnnual[0].startYear, employeeAnnual[0].finishDay, employeeAnnual[0].finishMonth, employeeAnnual[0].finishYear, employeeAnnual[0].requestedDay);
    
    printf("This is the ID of the checked holiday leave: %s \n", employeeAnnual[0].id);

    lineNumber = LineSelector(employeeAnnual[0].id,employeefile_G);
    
    printf("The Vacation leave you are currently checking is %d in the Employee List \n",lineNumber);
    
        
        bool IsValid = true;
        int choiceforselect;
        do {
        printf(")Decision \n");
        printf(")1. Accept\n");
        printf(")2. Reject\n");
        printf(")Your Decision: ");
        scanf("%d", &choiceforselect);
     


     switch (choiceforselect) {
                case 1:
                    strcpy(employee[0].AnnualRequest, "True");
                    IsValid = false;
                    break;
                case 2:
                    strcpy(employee[0].AnnualRequest, "False");
                    IsValid = false;
                    break;
                default:
                    printf("Invalid choice. Please try again.\n");
            }
            

                    } while (IsValid);
              printf("\n---------------------------------- ");


          FILE *tempFile = fopen(TEMPFILE,"w");
       FILE *annualfile_3 = fopen(ADMINANNUALFILE, "r");
    while (fgets(line3, sizeof(line3), annualfile_3) != NULL) {
        printf("Values %s \n",strstr(line3, employee[0].id ));

        if (strstr(line3, employeeAnnual[0].id) == NULL) {
            fputs(line3, tempFile);
        
        }
          }
          fclose(annualfile_3);
          fclose(tempFile);
          FileCopier_toAnnual();
 
          ID_to_EmployeeAnnualLeave(employeeAnnual[0].id , employee[0].AnnualRequest, lineNumber);


        fclose(employeefile_G);
    }
    fclose(annualfile_G);

}

void DisplayEmployeesFromFile() {

    FILE *file = fopen(FILENAME, "r");
    if (file != NULL) {
        printf("\nEmployee List from File:\n");
        printf("ID\tTitle\t\tName\t\tSurname\t\tAge\tGender\t\tCountry\t\tCity\t\tAnnual\tSalary\n");
        printf("--------------------------------------------------------------------------------------------------------------------------\n");

        struct Employee employee;
        
        while (fscanf(file, "%s %s %s %s %s %s %s %s %d %f %s",  employee.id, employee.title, employee.name, employee.surname, employee.age, employee.gender, employee.country, employee.city, &employee.annual, &employee.salary, employee.AnnualRequest) == 11) {
        printf("%s\t%-15s\t%-15s\t%-15s\t%-3s\t%-6s\t\t%-15s\t%-15s\t%d\t%.2f\n\n",
                   employee.id, employee.title, employee.name, employee.surname, employee.age, employee.gender, employee.country, employee.city, employee.annual, employee.salary);
       
        printf("Annual Request: %s\n",employee.AnnualRequest);
    printf("--------------------------------------------------------------------------------------------------------------------------\n");
                    }
        } else {
        printf("Error opening file for reading!\n");
        }

        fclose(file);
}

//------------------------------------------------------------------------------------------USERS--------------------------------------------------------------------------------------------------------

void EmployeeAnnualDayRequest(char username[20]) {

    struct EmployeeCard IDCard[1];
    struct EmployeeAnnual employeeAnnual;
    char line[256];
      int lineNumber = 0;
      int currentLine = 0;
      char name[20];
      char surname[20];
        char id[10];
      
          FILE *accountfile = fopen(USERFILE, "r");
              lineNumber = LineSelector(username,accountfile);
                  
       FILE *employeefile = fopen(FILENAME, "r");
       Username_to_ID(username,lineNumber, employeefile, IDCard);
      
        printf("Enter employee annual start day: ");
        scanf("%s", employeeAnnual.startDay);

        printf("Enter employee annual start month: ");
        scanf("%s", employeeAnnual.startMonth);
        
        printf("Enter employee annual start year: ");
        scanf("%s", employeeAnnual.startYear);
        
        printf("Enter employee annual finish day: ");
        scanf("%s", employeeAnnual.finishDay);

        printf("Enter employee annual finish month: ");
        scanf("%s", employeeAnnual.finishMonth);
        
        printf("Enter employee annual finish year: ");
        scanf("%s", employeeAnnual.finishYear);
        
        printf("Enter employee requested annual day count: ");
        scanf("%d", &employeeAnnual.requestedDay);
  
    FILE *EmpAnnualfile = fopen(ADMINANNUALFILE, "a");
            
    if (EmpAnnualfile != NULL) {
                // Write the new employee information to the file
    fprintf(EmpAnnualfile, "%s %s %s %s %s %s %s %s %s %d \n",IDCard[0].id,  IDCard[0].name, IDCard[0].surname,  employeeAnnual.startDay, employeeAnnual.startMonth, employeeAnnual.startYear, employeeAnnual.finishDay, employeeAnnual.finishMonth, employeeAnnual.finishYear, employeeAnnual.requestedDay);
    } else {
        printf("Error opening file for writing!\n");
        }
            
            fclose(EmpAnnualfile);
            
}

void EmployeeSearchRequests(char username[20]) {
    
    FILE *file = fopen(FILENAME, "r");
    if (file != NULL) {
        printf("\nEmployee List from File:\n");
        printf("ID\tTitle\t\tName\t\tSurname\t\tAge\tGender\t\tCountry\t\tCity\t\tAnnual\tSalary\n");

        // Read and display employee information from the file
        struct Employee employee;

        while (fscanf(file, "%s %s %s %s %s %s %s %s %d %f ",  employee.id, employee.title, employee.name, employee.surname, employee.age, employee.gender, employee.country, employee.city, &employee.annual, &employee.salary) == 10) {
            printf("%s\t%-15s\t%-15s\t%-15s\t%-3s\t%-6s\t\t%-15s\t%-15s\t%d\t%.2f\n",
                   employee.id, employee.title, employee.name, employee.surname, employee.age, employee.gender, employee.country, employee.city, employee.annual, employee.salary);
        }

        // Close the file
        fclose(file);
        } else {
        printf("Error opening file for reading!\n");
        }

}
//------------------------------------------------------------------------------------------USEFULL FUNC--------------------------------------------------------------------------------------------------------
int LineSelector(char username[20], FILE *file)
{
    int LineNumber = 0;
    char line[256];
    if (file == NULL) {
        perror("File opening error");
        return -1;

        }
            while (fgets(line, sizeof(line), file) != NULL) {
         
            LineNumber++;
        
            if (strstr(line, username) != NULL) {
                return LineNumber;
            }
            }
        
    return -1;
}


void Username_to_ID(char username[20],int LineNumber, FILE *file, struct EmployeeCard IDCard[1])
{
    char line[256];
    int currentLine = 0;
        if (file == NULL) {
        perror("File opening error");
        return;
        }

        while (fgets(line, sizeof(line), file) != NULL) {
        currentLine++;
        if (currentLine == LineNumber) {
            sscanf(line, "%s %s %s", IDCard[0].id, IDCard[0].name, IDCard[0].surname);
        }
        }
        fclose(file);
}



void ID_to_EmployeeInformation(char username[20], float updated_salary, int LineNumber)
{
        char line[256];
        int currentLine = 0;
        struct Employee Temp[1];
        FILE *infofile = fopen(FILENAME, "r");
        FILE *tempfile = fopen(TEMPFILE, "a");
        if (infofile == NULL) {
        perror("File opening error");
        return;
    }
    if (tempfile == NULL) {
        perror("File opening error");
           return;
    }
    while (fgets(line, sizeof(line), infofile) != NULL) {
        currentLine++;
        if (currentLine == LineNumber) {
                         sscanf(line, "%s %s %s %s %s %s %s %s %d %f %s", Temp[0].id, Temp[0].title, Temp[0].name, Temp[0].surname,  Temp[0].age, Temp[0].gender, Temp[0].country, Temp[0].city, &Temp[0].annual, &Temp[0].salary, Temp[0].AnnualRequest);
      
                   fprintf(tempfile,"%s %s %s %s %s %s %s %s %d %f %s\n", Temp[0].id, Temp[0].title, Temp[0].name, Temp[0].surname, Temp[0].age, Temp[0].gender, Temp[0].country, Temp[0].city, Temp[0].annual, updated_salary, Temp[0].AnnualRequest);
                    
        printf("It was updated and put because LineNumber: %d CurrentLine: %d \n",LineNumber,currentLine);
        } else {
        printf("It was put because LineNumber: %d CurrentLine: %d \n",LineNumber,currentLine);
        fputs(line, tempfile);
        }
    }
        fclose(tempfile);
    fclose(infofile);
    FileCopier();
}
    

void ID_to_EmployeeAnnualLeave(char username[20], char decision[10], int LineNumber)
{
    char line[256];
    int currentLine = 0;
    struct Employee Temp[1];

        FILE *infofile = fopen(FILENAME, "r");
        FILE *tempfile = fopen(TEMPFILE, "a");
        if (infofile == NULL) {
        perror("File opening error");
        return;
    }
    if (tempfile == NULL) {
        perror("File opening error");
           return;
    }

    while (fgets(line, sizeof(line), infofile) != NULL) {
        
        currentLine++;
    
        if (currentLine == LineNumber) {
            
                         sscanf(line, "%s %s %s %s %s %s %s %s %d %f %s", Temp[0].id, Temp[0].title, Temp[0].name, Temp[0].surname,  Temp[0].age, Temp[0].gender, Temp[0].country, Temp[0].city, &Temp[0].annual, &Temp[0].salary, Temp[0].AnnualRequest);
      
                   fprintf(tempfile,"%s %s %s %s %s %s %s %s %d %f %s\n", Temp[0].id, Temp[0].title, Temp[0].name, Temp[0].surname, Temp[0].age, Temp[0].gender, Temp[0].country, Temp[0].city, Temp[0].annual, Temp[0].salary, decision);
                    
        } else {
        fputs(line, tempfile);
        }
    }
        fclose(tempfile);
    fclose(infofile);
    FileCopier();
}


void ID_to_Username(char ID[10], int LineNumber, FILE *file, struct IDCards IDCard[1])
{
    char line[256];
        if (file == NULL) {
        perror("File opening error");
        return;
        }

        while (fgets(line, sizeof(line), file) != NULL) {
        if (strstr(line, ID) != NULL) {
        
        sscanf(line, "%s %s", IDCard[0].username, IDCard[0].password);
        }
        }
        fclose(file);
}


void FileCopier()
{

    char ch;

    // Open the source file for reading
    FILE *sourceFile = fopen(FILENAME, "w");
    if (sourceFile == NULL) {
        perror("Error opening source file");
        return;
    }

    // Open the destination file for writing
    FILE *destinationFile = fopen(TEMPFILE, "r");
    if (destinationFile == NULL) {
        perror("Error opening destination file");
        fclose(sourceFile);
      
    }

    // Read from the source file and write to the destination file
    while ((ch = fgetc(destinationFile)) != EOF) {
        fputc(ch, sourceFile);
    }

    // Close both files
    fclose(sourceFile);
    fclose(destinationFile);

    printf("File copied successfully.\n");
    
    fclose(fopen(TEMPFILE,"w"));
    return;
 
}

void FileCopier_toAnnual()
{
    char ch;

    // Open the source file for reading
    FILE *sourceFile = fopen(ADMINANNUALFILE, "w");
    if (sourceFile == NULL) {
        perror("Error opening source file");
        return;
    }

    // Open the destination file for writing
    FILE *destinationFile = fopen(TEMPFILE, "r");
    if (destinationFile == NULL) {
        perror("Error opening destination file");
        fclose(sourceFile);
      
    }

    // Read from the source file and write to the destination file
    while ((ch = fgetc(destinationFile)) != EOF) {
        fputc(ch, sourceFile);
    }

    // Close both files
    fclose(sourceFile);
    fclose(destinationFile);

    printf("File copied successfully.\n");
    
    fclose(fopen(TEMPFILE,"w"));
    return;
 
}

void FileCopier_toUser()
{
    char ch;

    // Open the source file for reading
    FILE *sourceFile = fopen(USERFILE, "w");
    if (sourceFile == NULL) {
        perror("Error opening source file");
        return;
    }

    // Open the destination file for writing
    FILE *destinationFile = fopen(TEMPFILE, "r");
    if (destinationFile == NULL) {
        perror("Error opening destination file");
        fclose(sourceFile);
      
    }

    // Read from the source file and write to the destination file
    while ((ch = fgetc(destinationFile)) != EOF) {
        fputc(ch, sourceFile);
    }

    // Close both files
    fclose(sourceFile);
    fclose(destinationFile);

    printf("File copied successfully.\n");
    
    fclose(fopen(TEMPFILE,"w"));
    return;
 
}
//------------------------------------------------------------------------------------------PAGES--------------------------------------------------------------------------------------------------------



void adminpage(char username[20]) {
    
    struct Employee employees[MAX_EMPLOYEES];
    int numEmployees = 0;
    int choice;
    
   do {
        printf("\n%s Admin Page \n\n", username);
        printf("1. Add Employee\n");
        printf("2. Remove Employee\n");
        printf("3. Display Employees\n");
        printf("4. Annual Day Requests\n");
        printf("5. Employee Salary Change\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addEmployee(employees, &numEmployees);
                break;
            case 2:
                removeEmployee();
                break;
            case 3:
                DisplayEmployeesFromFile();
                break;
            case 4:
                DisplayAnnualDayRequests();
                break;
            case 5:
                SalaryChangeEmployee();
                break;
            case 6:
                loginpage();
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 6);

}

void userpage(char username[20]) {


    struct Employee employees[MAX_EMPLOYEES];
    int numEmployees = 0;
    int choice;
    

   do {
        printf("\n%s User Page \n\n", username);
        printf("1. Annual Day Request\n");
        printf("2. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                EmployeeAnnualDayRequest(username);
                break;
            case 2:
                loginpage;
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 2);
   
}

void loginpage() {
    struct IDCards ID;
    int choice;
    
   do {
        printf("\nEmployee Detect System\n");
        printf("1. Admin Login\n");
        printf("2. User Login\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
            char username[20];
            char password[20];

        switch (choice) {
            case 1:
            printf("Enter your username: ");
            scanf("%s", username);
            printf("Enter your password: ");
            scanf("%s", password);
            
            FILE *adminfile = fopen(ADMINFILE, "r");
            if (adminfile != NULL) {
                while (fscanf(adminfile, "%s %s", ID.username, ID.password) == 2) {
                    if (strcmp(username, ID.username) == 0 && strcmp(password, ID.password) == 0) {
                        fclose(adminfile);
                        adminpage(ID.username);
                    }
                }
                printf("Invalid username or password!\n");
                fclose(adminfile);
            } else {
                printf("Error opening file for reading!\n");
            }
            
            break;
                break;
            case 2:

            printf("Enter your username: ");
            scanf("%s", username);
            printf("Enter your password: ");
            scanf("%s", password);
            
            FILE *userfile = fopen(USERFILE, "r");
            if (userfile != NULL) {
                while (fscanf(userfile, "%s %s", ID.username, ID.password) == 2) {
                    if (strcmp(username, ID.username) == 0 && strcmp(password, ID.password) == 0) {
                        fclose(userfile);
                        userpage(ID.username);
                    }
                }

                printf("Invalid username or password!\n");
                fclose(userfile);
            } else {
                printf("Error opening file for reading!\n");
            }
                break;
            case 3:
                printf("Exiting the program. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 3);

}

//------------------------------------------------------------------------------------------------------MAIN------------------------------------------------------------------------------------------
int main() {
    
    loginpage();

return 0;
}
