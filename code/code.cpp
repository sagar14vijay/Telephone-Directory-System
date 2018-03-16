//TELEPHONE DIRECTORY SYSTEM PROJECT
//DONE BY:
//Vijayvargiya Sagar R. [15IT251]
#include <iostream>
#include <string.h>
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include <cstdio>
using namespace std;

struct userinfo{ //Structure containing user information
                char name[50];
                char address[50];
                char contact_no[50];
                char pancard_no[50];
                int login_id;
                char password[50];
                int login_status;
                };

class Userfile{ //Userfile class to handle saved contacts services for each user.

    struct userinfo userfile;

    public:
            void save(const char *fname, char *sname, char *sno){ //function to save contact to a unique user file.

                fstream saved;
                fstream workfile;
                workfile.open(fname, ios::app);
                
                for(int i=0;i<50;i++)
				{
					userfile.name[i] = sname[i];
               	
            	}
            	for(int i=0;i<10;i++)
				{
					
               		userfile.contact_no[i] = sno[i];
            	}
                //saved.open("directory.dat", ios::in);
				
                /*while(saved.read((char *)&userfile, sizeof(userinfo)))
                    {
                        if(!strcmp(sname, userfile.name) && !strcmp(sno, userfile.contact_no))
                            workfile.write((char *)&userfile, sizeof(userfile));
                    }*/
                workfile.write((char *)&userfile, sizeof(userfile));
                workfile.close();
                //saved.close();
            }

            void display(const char *fname){ //display the contacts that are saved.

                fstream readsaved;

                readsaved.open(fname, ios::in);
                cout<<"----------------------------------------------------\n";
                cout<<"Name     Number\n";
                cout<<"----------------------------------------------------\n";
                while(readsaved.read((char *)&userfile, sizeof(userinfo)))
                    {
                        cout<<userfile.name<<"\t"<<userfile.contact_no<<"\t"<<userfile.address<<endl;
                    }
                readsaved.close();
            }

            void delcontact(const char *fname){ //remove contacts from the user file as per user choice.

                fstream delsaved;
                fstream temp;
                char delname[50];
                char delno[50];

                cout<<"\tEnter name and number of contact to be deleted:";
                cin>>delname;
                cin>>delno;

                delsaved.open(fname, ios::in);
                temp.open("temp.dat", ios::out);

                while(delsaved.read((char *)&userfile, sizeof(userinfo)))
                {
                        if(!strcmp(delname, userfile.name) && !strcmp(delno, userfile.contact_no))
                            continue;
                        else
                            temp.write((char *)&userfile, sizeof(userfile));
                }
                delsaved.close();
                temp.close();
                cout<<"\n\tContact deleted from contacts list.\n";

                remove(fname);
                rename("temp.dat", fname);

            }
    };

class User{ //class to maintain user profile.

    public:


        struct userinfo user;

        void registration(){ //procedure of registration for each user.

                cout<<"---------------------------------------"<<endl;
                cout<<"\t\tWelcome to Registration\t\t"<<endl;
                cout<<"---------------------------------------"<<endl;

                char blank[10];
                cin.getline(blank, sizeof(blank));

                fstream registerfile;
                registerfile.open("adminbuffer.dat", ios::app|ios::binary);

                cout<<"\tEnter your name:";
                cin.getline(user.name, sizeof(user.name));

                cout<<"\n\tEnter your 10 digit contact number:";
                cin.getline(user.contact_no, sizeof(user.contact_no));


                while(strlen(user.contact_no)!=10){
                    cout<<"\n\tEnter your 10 digit contact number:";
                    cin.getline(user.contact_no, sizeof(user.contact_no));
                    //cout<<is_digits(user.contact_no);
                    if(strlen(user.contact_no)==10 && is_digits(user.contact_no)==1)
                        break;
                    else
                        strcpy(user.contact_no,"0");
                }

                cout<<"\n\tEnter address:";
                cin.getline(user.address, sizeof(user.address));

                cout<<"\n\tEnter your 10 character PAN card number:";
                cin.getline(user.pancard_no, sizeof(user.pancard_no));
                while(strlen(user.pancard_no)!=10){
                    cout<<"\n\tEnter your 10 character PAN card number:";
                    cin.getline(user.pancard_no, sizeof(user.pancard_no));
                }

                user.login_status=0;

                ifstream filelogin;
                filelogin.open("registration.txt", ios::in|ios::app ); //opening in read mode

                string line; //Stores first line of the file
                string login_id;
                string ps;

                getline(filelogin, line); //Reading first line
                stringstream iss(line);
                getline(iss, login_id, '|');//Parsing for login index, before |
                getline(iss, ps, '|' );
                stringstream convert(login_id);
                convert>>user.login_id; //converting login index string to int

                stringstream conv(ps);
                conv>>user.password; //Holds new user password
                filelogin.close();

                if(checkforuniqueness(user)==0)
                {
                    registerfile.write((char *)&user, sizeof(struct userinfo));
                    user.login_id=user.login_id+1;

                    ofstream loginupdate;
                    loginupdate.open("registration.txt", ios::out); //Opening in write mode
                    loginupdate << user.login_id <<"|"<<"iam"<<user.login_id<<"|"; //Stores login index on first line of file
                    loginupdate.close();

                    cout<<"\t"<<user.name<<", your credentials are:\n\tLogin ID:"<<user.login_id-1<<"\n\tPassword:"<<user.password<<"\n";
                    cout<<"\tAdd request sent to admin.\n\tIf you try to login without admin verification, these credentials will not be accepted.\n";
                }
                registerfile.close();
        }

        bool is_digits(const std::string &str) //check if entered values are only digits.
        {
            return str.find_first_not_of("0123456789") == std::string::npos;
        }

        int checkforuniqueness(struct userinfo entry){ //check if the user information provided for registration is unique.

            fstream CU;
            int signal=0;
            CU.open("directory.dat",ios::in);
            struct userinfo temp;

            while(CU.read((char *)&temp, sizeof(userinfo)))
            {
                if(!strcmp(temp.name, entry.name)&&!strcmp(temp.address,entry.address))
                {
                    signal=1;
                    cout<<"\tA record with this name and address already exists.\n";
                }
                else if(!strcmp(temp.pancard_no, entry.pancard_no))
                {
                    signal=1;
                    cout<<"\tInvalid entry. A user with this PAN card number already exists.\n";
                }
                else if(!strcmp(temp.contact_no, entry.contact_no))
                {
                    signal=1;
                    cout<<"\tA record with this contact number already exists in the directory.\n";
                }
            }

                return signal;
            CU.close();
        }

        int login(){ //login procedure for user.

            int lid;
            bool ok=false;
            int check=0;
            int flag=0;
            char pswd[50];

            while(!ok){

                    cout<<"\tEnter login id:";
                    cin>>lid;
                    if(!std::cin.fail() && (std::cin.peek()==EOF || std::cin.peek()=='\n'))
                    {
                        ok = true;
                    }
                    else
                        {
                        std::cin.clear();
                        std::cin.ignore(256,'\n');
                        std::cout << "\tEnter a valid numerical ID." << std::endl;
                        }
            }
            cout<<"\tPassword:";
            cin>>pswd;

            fstream userlogin;
            fstream uniquelogin;

            userlogin.open("directory.dat", ios::in);
            uniquelogin.open("tempdirectory.dat", ios::out);

            struct userinfo temp;
            struct userinfo prev=user;
            while(userlogin.read((char *)&temp, sizeof(userinfo)))
            {
                if(!strcmp(pswd, temp.password)&& lid==temp.login_id)
                    {
                    if(temp.login_status==1)
                    {
                        cout<<"\tUser already logged in.\n";
                    }
                    else
                    {
                        temp.login_status=1;
                    }
                    flag=1;
                    user=temp;
                    }

                else if(lid!=temp.login_id && temp.login_status==1)
                    {
                        check=1;
                        user=temp;
                    }

                uniquelogin.write((char *)&temp, sizeof(userinfo));
            }

            uniquelogin.close();
            userlogin.close();
            remove("directory.dat");
            rename("tempdirectory.dat", "directory.dat");

            if(check==1)
                {
                user=prev;
                cout<<"\tAnother user is logged in. Try later!\n";
                return 0;
                }
            else if(check==0 && flag==1)
                return 1;
            else
                return 0;

        }

       void logout(){ //logout procedure for user

            fstream out;
            fstream updateout;
            struct userinfo temp;

            updateout.open("tempdirectory.dat", ios::out);
            out.open("directory.dat", ios::in);

            cout<<"\n\tUSER LOGIN STATUS\n";

            while(out.read((char *)&temp, sizeof(struct userinfo))){

                if(getlogin()==temp.login_id && !strcmp(temp.password, getpass())&&temp.login_status==1)
                    {
                        temp.login_status=0;
                        user=temp;
                    }
                updateout.write((char *)&temp, sizeof(struct userinfo));
                cout<<"\tUser:"<<temp.login_id<<"\tStatus:"<<temp.login_status<<endl;
            }

            out.close();
            updateout.close();

            remove("directory.dat");
            rename("tempdirectory.dat", "directory.dat");

        }

        int getlogin(){ //returns user login id

            if(user.login_status!=1)
                user.login_id=0;

            return user.login_id;
            }

        char * getpass(){ //return user password

            return user.password;

            }
        int getloginstatus(){

            return user.login_status;
        }
		
		 void Delete(){ //function to allow user to delete their record after authentication.

            fstream deletefile;
            fstream tempfile;
            stringstream ss;

            struct userinfo todelete;

            if(user.login_status!=1)
                cout<<"\tA user must login inorder to delete their record from the telephone directory.\n";
            
            const char *s;
    		string st;
            ss<<user.login_id;
            st = ss.str() + ".dat";
            s = st.c_str();
            remove(s);
			cout << "Your record is deleted from Telephone Directory\n";
            tempfile.open("tempdirectory.dat",ios::out);
            deletefile.open("directory.dat", ios::in|ios::out);

            while(deletefile.read((char *)&todelete, sizeof(userinfo)))
            {
                if(getlogin()==todelete.login_id && !strcmp(todelete.password, getpass()))
                    {
                        continue;
                    }

                tempfile.write((char *)&todelete, sizeof(userinfo));
            }
            user.login_id=0;
            tempfile.close();
            deletefile.close();

            remove("directory.dat");
            rename("tempdirectory.dat","directory.dat");

        }
        
        void Search(){ //search procedure for the directory

            int searchopt;
            char searchname[50];
            char searchno[50];
            char searchaddr[50];

            cout<<"\tYour options are, search by:\n\t1. Name\n\t2. Contact Number\n\t3. Address\n\tExit otherwise.\n\n\tEnter choice:";
            cin>>searchopt;

            if(searchopt==1)
            {
                cout<<"\tEnter name to be searched:";
                cin>>searchname;
            }
            else if(searchopt==2)
            {
                cout<<"\tEnter number to be searched for:";
                cin>>searchno;
            }
            else if(searchopt==3)
            {
                cout<<"\tEnter address to be searched from:";
                cin>>searchaddr;
            }
            else
                cout<<"\tInvalid choice.\n";

            fstream searchfile;
            searchfile.open("directory.dat", ios::in);

            struct userinfo tosearch;

            cout<<"----------------------------------------------------\n";

            cout<<"\tName\tNumber\t\tAddress\n";
            cout<<"----------------------------------------------------\n";

            while(searchfile.read((char *)&tosearch, sizeof(struct userinfo)))
            {
                if(searchopt==1 && !strcmp(tosearch.name, searchname))
                        cout<<"\t"<<tosearch.name<<"\t"<<tosearch.contact_no<<"\t"<<tosearch.address<<endl;
                else if(searchopt==2 && !strcmp(tosearch.contact_no, searchno))
                        cout<<"\t"<<tosearch.name<<"\t"<<tosearch.contact_no<<"\t"<<tosearch.address<<endl;
                else if(searchopt==3 && !strcmp(tosearch.address, searchaddr))
                        cout<<"\t"<<tosearch.name<<"\t"<<tosearch.contact_no<<"\t"<<tosearch.address<<endl;
            }
        }

        void emergencyservices(){ //provides list of emergency services managed by the admin.

            fstream emerg;
            emerg.open("emergency.dat", ios::in);
            struct userinfo temp;

            cout<<"----------------------------------------------------\n";
            cout<<"\tName\tNumber\t\tAddress\n";
            cout<<"----------------------------------------------------\n";
            while(emerg.read((char *)&temp, sizeof(userinfo))){
                cout<<"\t"<<temp.name<<"\t"<<temp.contact_no<<"\t"<<temp.address<<endl;
            }

            emerg.close();
        }
};

class Admin{ //class to handle admin actions mainly to authorize the entries in the telephone directory.

    char admin_id[50];
    char admin_password[50];

    public:
        int login_status;
        void add_record(){

            int adminchoice;
            int choice;

            struct userinfo addrec;
            fstream adminfile;
            fstream admintodirec;
            fstream tempadminbuffer;

            cout<<"\tYour choices are:\n\t1. Accept or Reject User Record.\n\t2. Add Emergency Service\n\tEnter choice:";
            cin>>choice;

            if(choice==1)
            {

                cout<<"\tRequests:"<<endl;

                adminfile.open("adminbuffer.dat", ios::in|ios::out);
                tempadminbuffer.open("tempadminbuffer.dat", ios::out);

                cout<<"----------------------------------------------------\n";
                cout<<"\tLogin ID\tName\tNumber\tAddress\n";
                cout<<"----------------------------------------------------\n";

                while(adminfile.read((char *)&addrec, sizeof(userinfo)))
                {
                     cout<<"\t"<<addrec.login_id<<"\t"<<addrec.name<<"\t"<<addrec.contact_no<<"\t"<<addrec.address<<endl;
                     cout<<"\n1. Accept add request\n0. Skip request\n";
                     cin>>adminchoice;

                     if(adminchoice==1)
                        {   admintodirec.open("directory.dat", ios::app);
                            admintodirec.write((char *)&addrec, sizeof(userinfo));
                            admintodirec.close();
                        }
                    else
                    {
                        tempadminbuffer.write((char *)&addrec, sizeof(userinfo));
                        cout<<"\tThank you.\n";
                    }
                }
                adminfile.close();
                tempadminbuffer.close();
                remove("adminbuffer.dat");
                rename("tempadminbuffer.dat", "adminbuffer.dat");
            }

            else if(choice==2){

                fstream addemerg;
                addemerg.open("emergency.dat", ios::app);
                struct userinfo temp;

                cout<<"\tEnter name of emergency service:";
                cin>>temp.name;
                cout<<"\tEnter contact number:";
                cin>>temp.contact_no;
                cout<<"\tEnter address:";
                cin>>temp.address;

                addemerg.write((char *)&temp, sizeof(userinfo));
                addemerg.close();
            }
        }

        int login(){ //login procedure for admin. Currently credentials hard-coded to admin and admin.

            cout<<"\tEnter admin id:";
            cin>>admin_id;
            cout<<"\tEnter admin password:";
            cin>>admin_password;

            if(!strcmp(admin_id,"admin")&&!strcmp(admin_password,"admin"))
                {
                    login_status=1;
                    cout<<"\tLogin successful"<<endl;
                }
            else
                {   login_status=0;
                    cout<<"\tIncorrect credentials"<<endl;
                }
            return login_status;
            }
};

class Directory{

    public:

        void display(){ //function to display records in the directory

            fstream direc;
            direc.open("directory.dat", ios::in);
            struct userinfo directuse;
            cout<<"---------------------------------------\n";
            cout<<"\tName\tNumber\tAddress\n";
            cout<<"---------------------------------------\n";

            while(direc.read((char *)&directuse, sizeof(struct userinfo)))
            {
                cout<<"\t"<<directuse.name<<"\t"<<directuse.contact_no<<"\t"<<directuse.address<<"\n";
            }
            direc.close();

            }
};

int main(){

    int user_choice;
    bool var=false;

    Admin ad;
    User U;
    Directory D;
    Userfile uf;

    const char *s;
    string st;

    cout<<"------------------------------------------------------------------------------------------\n";
    cout<<"\tInstructions:"<<endl;
    cout<<"------------------------------------------------------------------------------------------\n";
    cout<<"\t- Each user must register to add themselves to the telephone directory.\n";
    cout<<"\t- After registration, the admin decides whether to add or reject the user's request.\n";
    cout<<"\t- After logging in, the User can modify or delete their records in the directory.\n";
    cout<<"\t- Services of saving contacts and emergency are also provided.\n";
    cout<<"\t- Contact number must be a 10 digit number.\n";
    cout<<"\t- PAN Card number must be of 10 characters.\n";

	
    do{

        cout<<"------------------------------------------------------------------------------------------\n";
        cout<<"\t\tTELEPHONE DIRECTORY SYSTEM\n";
        cout<<"------------------------------------------------------------------------------------------\n";
        cout<<"\tCURRENT USER:"<<U.getlogin()<<endl;
        cout<<"------------------------------------------------------------------------------------------\n\n";
        cout<<"\tThe Telephone Directory System offers the following features:\n"<<endl;
        cout<<"\t1. User Registration "<<endl;
        cout<<"\t2. Login "<<endl;
        cout<<"\t3. Display Directory (All directories present in Telephone Directory System[TDS])"<<endl;
        cout<<"\t4. Delete record (Delete their record after authentication and Deleted from Telephone Directory)"<<endl;
        cout<<"\t5. Search directory"<<endl;
        cout<<"\t6. Saved Contacts Services (User can save, modify and delete contact.)"<<endl;
        cout<<"\t7. Emergency Services"<<endl;
        cout<<"\t8. Logout"<<endl;
        cout<<"\tExit otherwise.\n";

        while(!var){ cout<<"\n\tEnter choice:"; //checking for valid user entry
                    cin>>user_choice;
                    if(!std::cin.fail() && (std::cin.peek()==EOF || std::cin.peek()=='\n'))
                    {
                        var = true;
                    }
                    else
                        {
                        std::cin.clear();
                        std::cin.ignore(256,'\n');
                        std::cout << "\tEnter a valid numerical choice." << std::endl;
                        }
        }

        var=false;

        stringstream ss;

        switch(user_choice){

            case 1:
                User user_reg;
                user_reg.registration(); //completed
                break;

            case 2:
                int login_type;
                cout<<"\n\tLogin type:\n\t1. Admin\n\t2. User\n\t";
                cout<<"Enter your choice:";
                cin>>login_type;
                if(login_type==1&&ad.login_status!=1)
                        {
                        if(ad.login()==1)
                            {
                            	
                                ad.add_record();
                                ad.login_status=1;
                            }
                        else
                            cout<<"\tIncorrect admin credentials.\n";
                        }

                else if(login_type==1&&ad.login_status==1)
                        ad.add_record();

                else if(login_type==2)
                    {
                        if(U.login()==1)
                            cout<<"\n\t*****Login successful*****\n";
                        else
                            cout<<"\tIncorrect credentials.\n";
                    }

                break;

            case 3:
                D.display();
                break;

            case 4:
                U.Delete();
                break;

            case 5:
                U.Search();
                break;

            case 6:
                if(U.getloginstatus()==1)
                {
                    //D.display();
                    char savename[50];
                    char saveno[50];
                    int savechoice;

                    ss<<U.getlogin();
                    st = ss.str() + ".dat";
                    //cout << st;
                    s = st.c_str();

                    cout<<"\t\n\tYour options are:\n\t1. Save Contact\n\t2. Display Saved Contacts\n\t3. Remove Contact\n\tEnter choice:";
                    cin>>savechoice;
                    if(savechoice==1)
                    {
                        cout<<"\tEnter name and number of contact to be saved:\n";
                        cin>>savename;
                        cin>>saveno;
                        uf.save(s,savename, saveno);
                    }
                    else if(savechoice==2){
                        uf.display(s);
                    }
                    else if(savechoice==3){
                        uf.delcontact(s);
                    }
                }
				else
                    cout<<"\tCannot save or remove contacts without user authentication.\n";
                break;

            case 7:
                U.emergencyservices();
                break;

            case 8:
                U.logout();
                break;

            default:
                exit(0);
                }
    } while(user_choice <= 8);

   return 0;
}
