// program to store student details
#include <iostream>
#include <istream>
#include <string.h>
#include <fstream>

using namespace std;

class student
{
    private:
        int getrollno(){return rollno;}
        char getname() {return name[100];}
        int sn,yy,mm,dd,eng,nep,math,sci,com,total,rollno;
        float per;
        char name[100],email[30],sem[10],answer;

        // Just to show the Roll No., Name and Semester in list
        void showlist() {cout<<"\t"<<rollno<<"\t\t"<<name<<"\t"<<sem<<endl;}

    public:

        // Getting Information from User
        void getdata()
        {
            cout<<"Roll No. : ";cin>>rollno;
            cin.ignore();
            cout<<"Enter Full Name of Student: ";cin.getline(name, 100);
            cout<<"Enter Semester: ";cin.getline(sem, 10);
            cout<<"Enter Email : ";cin>>email;
            cout<<"Date Of Birth: "<<endl;
            cout<<"Year: ";cin>>yy; cout<<"Month: ";cin>>mm; cout<<"Day: ";cin>>dd;
            cout<<"Enter marks obtained in English: ";cin>>eng;
            cout<<"Enter marks obtained in Nepali: ";cin>>nep;
            cout<<"Enter marks obtained in Mathematics: ";cin>>math;
            cout<<"Enter marks obtained in Science: ";cin>>sci;
            cout<<"Enter marks obtained in Computer: ";cin>>com;
        }

        // To show the students details
        void displaydata()
        {
            cout<<"\n\n\t\t\t\tD.P College"<<endl<<endl;
            cout<<"\tRoll No.: "<<rollno<<"\t\t\t\t\tDate of Birth: "<<yy<<"/"<<mm<<"/"<<dd<<endl;
            cout<<"\tStudent Full Name: "<<name<<"\t\t\t\tSemester: "<<sem<<endl;
            cout<<"\tEmail: "<<email<<endl<<endl;
            cout<<"\t\t\t\tMARKSHEET";
            cout<<"\n";
            cout<<"\n";
            cout<<"\tSubjects\tFullmark\tPassmark\tObtained Marks ";
            cout<<"\n";
            cout<<"\t--------------------------------------------------------------";
            cout<<"\n\tEnglish\t\t100\t\t32\t\t "<<eng;
            cout<<"\n\tNepali\t\t100\t\t32\t\t "<<nep;
            cout<<"\n\tMathematics\t100\t\t32\t\t "<<math;
            cout<<"\n\tScience\t\t100\t\t32\t\t "<<sci;
            cout<<"\n\tComputer\t100\t\t32\t\t "<<com;
            cout<<"\n\n\t\t\t\t\t\t\tTotal : "<<eng+ nep+math+sci+com;
            cout<<"\n\t\t\t\t\t\t\tPercentage: "<<(eng+ nep+math+sci+com) * 100 / 500<<"%";
        }

        // Different question for User display as Menu
        void askquestions()
        {
            cout<<"\n\tChoose the options from below:";
            cout<<"\n\t a: Wants to Add Student Details?";
            cout<<"\n\t b: Wants to View Student Details?";
            cout<<"\n\t c: Wants to Search Student Details?";
            cout<<"\n\t d: Wants to Delete Student Details?";
            cout<<"\n\t e: Wants to See the Deleted Student Details?";
            cout<<"\n\n\t    Enter Your Answer: ";cin>>answer;

            switch(answer)
                {
                    case 'a' :
                        getdata();
                        storedata();
                        break;
                    case 'b' :
                        listofdetails();
                        break;
                    case 'c' :
                        findsrecord();
                        break;
                    case 'd':
                        deleterecord();
                        break;
                    case 'e' :
                        recyclebin();
                        break;
                    default :
                        cout<<"\n\tHey Hey you there. Choose From above Options\n\n";
                }
        }

        // store information in file(records.txt)
        void storedata()
        {
            ofstream fout;
            fout.open("records.txt", ios::app|ios::binary);
            fout.write((char*)this,sizeof(*this));
            fout.close();
        }

        // shows the list of the saved details from file name records.txt
        void listofdetails()
        {
            int t;
            ifstream fin;
            fin.open("records.txt", ios::in|ios::binary);
            cout<<"\n\t\tList of the Students"<<endl;
            cout<<"\t*************************************************\n";
            cout<<"\tRoll No.\tName\t\tSemester"<<endl;
            if(!fin)
                cout<<"\nFile not found.";
            else
            {
                fin.read((char*)this,sizeof(*this));
                while(!fin.eof())
                {
                    showlist();
                    fin.read((char*)this,sizeof(*this));
                }
                fin.close();
            }
            cout<<"\n\tEnter Student Roll No. to view details: ";
            cin>>t;
            machingdata(t); //calling to open the full description of the students
        }

        // Shows detail Information of a Student of that Roll No. entered by the user
        void machingdata(int t)
        {
            int counter=0;
            ifstream fout;
            fout.open("records.txt",ios::in|ios::binary);
            if(!fout)
            cout<<"File not found";
            else
            {
                fout.read((char*)this,sizeof(*this));
                while(!fout.eof())
                {
                    if(t==rollno)
                    {
                        displaydata();
                        counter++;
                    }
                    fout.read((char*)this,sizeof(*this));
                }
            if(counter==0)
            cout<<"\n\tRecord not found of Roll No. "<<endl;
            fout.close();
            }
        }

        // for searching the details of the student in the file records.txt
        void findsrecord()
        {
            int t;
            cout<<"Enter the Roll Number of the student: ";
            cin>>t;
            machingdata(t); //calling machingdata as it works same as for showing entire details of students
        }

        // for deleting the student information in the file records.txt
        void deleterecord()
        {
            int srollno;
            int count = 0;
            cout<<"Enter the Roll Number of the student which you want to delete: ";
            cin>>srollno;
            fstream fio("records.txt",ios::in|ios::out|ios::binary|ios::app); // open original existing file
            ofstream fout("tempfile.txt",ios::out|ios::binary|ios::app); // creating new file
            ofstream out("recyclebin.txt",ios::out|ios::binary|ios::app); // open to write the deleted data from original file

            while(fio.read((char*)this,sizeof(*this)))
            {
                if(srollno==rollno)
                {
                    out.write((char*)this,sizeof(*this));
                    count++;
                }
                else
                {
                    fout.write((char*)this,sizeof(*this));
                }
            }
            if(count==0) cout<<"\nThe Roll No."<<srollno<<" is not in the file...\n";
            fio.close();
            fout.close();

            // removing the original "records.txt" and rename the "tempfile.txt" with "records.txt"
            remove("records.txt");
            rename("tempfile.txt","records.txt");
        }

        // for storing the deleted data from original
        void recyclebin()
        {
            ifstream fin("recyclebin.txt", ios::in|ios::binary);
            while(fin.read((char*)this, sizeof(*this)))
            {
                displaydata();
            }
            fin.close();
        }
};
int main()
{
    char loop;
    student s;

    // creating the loop to continue to working
    do
        {
            s.askquestions();
            cout << "\n\n\tTo continue Please press Y, To Exit program Press E: ";
            cin >> loop;
        }
    while(loop =='Y' || loop =='y');
        {
            return 0;
        }
     return 0;
}
