 #include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct user{
    char name[100];
    int roll;
    char mob[100];
    char gender[10];
    char pass[100];
    int room_no;
}user;

FILE *fp;
int ind=-1;

void reg()
{
    user us;
    printf("\nEnter Your Name : ");
    scanf("%s",&us.name);
    printf("Enter Your Roll No : ");
    scanf("%d",&us.roll);
    printf("Enter Your Mobile Number : ");
    scanf("%s",&us.mob);
    printf("Enter Your Gender : ");
    scanf("%s",&us.gender);
    printf("Create Password : ");
    scanf("%s",&us.pass);
    us.room_no=-1;
    fp=fopen("ac_info.txt", "a+b");
    fwrite(&us,sizeof(user),1,fp);
    fclose(fp);
    printf("Registration is done\n");
}

int log_in()
{
    user us;
    int r;
    char p[100];
    printf("Enter your Roll : ");
    scanf("%d",&r);
    printf("Enter your Password : ");
    scanf("%s",p);

    int in=0;
    fp=fopen("ac_info.txt","rb");

    while(fread(&us, sizeof(user),1,fp)){
        if(us.roll==r && strcmp(us.pass,p)==0){
            ind=in;
            return 1;
        }
        in++;
    }
    return 0;
}

void service(int a)
{
    if(a==1){
        int cho;
        do{ printf("\n1.Apply for new room\n");
        printf("2.Account details\n");
        printf("3.Exit\n");
        printf("Enter your Choice...");
        scanf("%d",&cho);
        switch (cho)
        {
        case 1:
            apply();
            break;
        case 2:
            ac_details();
            break;

        case 3:
            break;
        default:
            break;
        }
        }while(cho!=3);
}

else{
    printf("\nLogin failed\n");
}

}

void apply()
{
    fp=fopen("ac_info.txt", "rb");
    user us;
    int i=-1;
    do{
        fread(&us, sizeof(user),1,fp);
        i++;
    }while(i!=ind);
    fclose(fp);

    if(us.room_no>0){
        printf("\nRoom is already allocated.\n");
        return;
    }

    int r,test;
   printf("Enter the number of your desired room : ");
    scanf("%d",&r);

    fp =fopen("num.txt", "r+b");
    int bl=0;
    while(fread(&test,sizeof(int),1,fp)){
        if(test==r){
            printf("Room Number %d is Vacant\n", test);
            char temp[10];
            printf("Enter 'y' to confirm and 'n' to cancel...");
            scanf("%s",&temp);
            if(strcmp(temp,"y")==0){
                fclose(fp);
                fp=fopen("ac_info.txt","r+b");
                us.room_no=test;
                fseek(fp,ind*sizeof(user),SEEK_SET);
                fwrite(&us,sizeof(user),1,fp);
                fclose(fp);
                printf("\nRoom Allocated\n");

                fp=fopen("temp.txt", "a+b");

                for(i=1;i<=100;i++){
                    if(i==us.room_no){continue;}
                    fwrite(&i,sizeof(int),1,fp);
                }
                fclose(fp);
                remove("num.txt");
                rename("temp.txt","num.txt");
                    }
                    bl=1;
                    break;
        }
    }
    if(!bl){
        printf("\nRoom not available\n");
    }
}

void ac_details()
{
    fp=fopen("ac_info.txt", "rb");
    user us;
    int i=-1;
    do{
        fread(&us, sizeof(user),1,fp);
        i++;
    }while(i!=ind);
    fclose(fp);

    printf("\nName : %s\n",us.name);
    printf("Roll No : %d\n",us.roll);
    printf("Mobile Number : %s\n",us.mob);
    printf("Gender : %s\n",us.gender);
    if(us.room_no==-1){
        printf("Room is not allocated\n");
    }
    else{
        printf("Room no : %d\n",us.room_no);
    }
}
void p_all_ac()
{
    user us;
    fp = fopen("ac_info.txt", "rb");
    printf("\n----------------------------------------------------------------------------------------\n");
    printf("%-10s%-20s%-15s%-10s%-5s", "Roll No", "Name", "Mobile", "Gender", "Room No");
    printf("\n----------------------------------------------------------------------------------------\n");
    while (fread(&us, sizeof(user), 1, fp))
        printf("%-10d%-20s%-15s%-10s%-5d\n", us.roll,us.name, us.mob, us.gender, us.room_no);

    fclose(fp);
}

void reset()
{
    remove("num.txt");
    fp=fopen("num.txt", "a+b");

    for(int i=1;i<=100;i++){
        fwrite(&i,sizeof(int),1,fp);
    }
    fclose(fp);

    remove("ac_info.txt");
}
int main(){

    int ch;
    do{
        printf("Hostel Management System\n");
        printf("\n1.Register\n");
        printf("2.Log In\n");
        printf("3.All Account\n");
        printf("4.Reset system\n");
        printf("5.Exit\n");
        printf("Enter your choice...");
        scanf("%d",&ch);
        switch (ch)
        {
        case 1:
            reg();
            break;
        case 2:
            service(log_in());
            break;
        case 3:
            p_all_ac();
            break;
        case 4:
        reset();
            break;
        case 5:
            break;

        default:
            break;
        }
    }while(ch!=5);

    return 0;
}
