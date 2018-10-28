  #include<stdio.h>
  #include<string.h>
  #include<stdlib.h> //Used for exit(0);

  //Structure Definitions
  struct timeVal {
    int dd,mm,yyyy;
  };

  struct customer {
    int ID;
    struct timeVal lastPurchase;
    float phNo;
    int currentBalance;
    char name[20];
  }cust,b;

  //Function Declarations
  int getch(void);
  void addCustomer(void);
  void billCustomer(void);
  void removeCustomer(void);
  void searchCustomer(void);
  int checkCustomerExist(int);
  void updateCustomerFile(void);
  void displayCustomerList(void);

  FILE *fp,*ft;

  //global variables
  int ch;
  char c;
  int newID;
  int customerExists;

  int main(void) {
    //while(1)
    for(int i=0;i<20;i++) {
      printf("\n\n--------CUSTOMER BILLING SYSTEM--------\n\n");
      printf(" 1. Bill Customer\n");
      printf(" 2. Search Customers\n");
      printf(" 3. Display Customers\n");
      printf(" 4. Close application\n\n");
      printf(" Enter your choice: ");
      ch=getch();
      switch(ch) {
        case 1: billCustomer(); break;
        case 2: searchCustomer(); break;
        case 3: displayCustomerList(); break;
        case 4: {
          printf("\n\nCustomer Billing System - MiniProject\n");
          printf(" <Name 1>\t\t__________\n");
          printf(" <Name 2>\t\t__________\n");
          printf(" <Name 3>\t\t1_________\n");
          printf(" <Name 4>\t\t1_________\n");//ADD NAMES HERE
          exit(0);
        }break;
        default: printf("Wrong Entry!\nTry Again!\n\n");
      }
    }
    return 0;
  }

  void addCustomer(void) {
    printf("\nADD CUSTOMERS\n\n");
    printf("\nEnter Customer details:\n");
    printf("Customer ID: %d\n",newID);
    b.ID=newID;
    printf("Name: ");
    scanf("%s",b.name);
    printf("Phone Number: ");
    scanf("%f",&b.phNo);
    b.currentBalance=0;
  }

  void billCustomer(void) {	
    int purchaseAmount=0;
    customerExists=1;
    int payableAmount=0;
    int paidAmount=0;
    printf(" Enter Customer ID: ");
    scanf("%d",&newID);
    if(checkCustomerExist(newID)==0) {
      printf("Customer with that ID doesn't exist!\n");
      printf("Continue by adding customer(1 to continue)? ");
      ch=getch();
      customerExists=0;
      if(ch==1)
        addCustomer();
      else {
        ch=0;
        return;
      }
    }
    printf("Enter date(dd/mm/yyyy): ");
    scanf("%d/%d/%d",&b.lastPurchase.dd,&b.lastPurchase.mm,&b.lastPurchase.yyyy);
    printf("Enter Purchase Amount: ");
    scanf("%d", &purchaseAmount);
    payableAmount=purchaseAmount-b.currentBalance;
    printf("\nCurrent Balance: %d",b.currentBalance);
    printf("\nPayable Amount: %d",payableAmount);
    printf("\n\nEnter Amount Paid: ");
    scanf("%d",&paidAmount);
    b.currentBalance=paidAmount-payableAmount;
    printf("\nCustomer Balance after transaction: %d",b.currentBalance);
    updateCustomerFile();
  }
  void updateCustomerFile(void) {
    struct customer btemp;
    if(customerExists==1) {
      fp=fopen("CBS-Customer.dat","ab+"); 
      ft=fopen("CBS-Customer-temp.dat","ab+"); //Creating temporary file
      printf("Comes till here\n");
      b.ID=newID;
      if(ft!=NULL) {
        fseek(ft,0,SEEK_SET);
        fseek(fp,0,SEEK_SET);		
        printf("LLere\n");

        while(fread(&btemp,sizeof(btemp),1,fp)>0) {
          printf("\nTemp file ID: %d\n",btemp.ID);
          if(btemp.ID!=b.ID) {
            fseek(ft,0,SEEK_END);
            printf("\n Writing Unmatched ID: #%d\n",btemp.ID);
            fwrite(&btemp,sizeof(btemp),1,ft);
          }
        }
        fseek(ft,0,SEEK_END);
        printf("\n Writing Matched ID : #%d\n",b.ID);
        fwrite(&b,sizeof(b),1,ft);
      }
      fclose(ft);
      fclose(fp);
      remove("CBS-Customer.dat");//Removing old dat file
      rename("CBS-Customer-temp.dat","CBS-Customer.dat");//Renaming tmp file
    }
    else if(customerExists==0) {
      fp=fopen("CBS-Customer.dat","ab+");
      fseek(fp,0,SEEK_END);
      fwrite(&b,sizeof(b),1,fp);
      fclose(fp);
    }
    printf("\nBilled Customer\n\n");
  }

  int getch(void) {
    int cha;
    scanf("%d",&cha);
    return cha;
  }

  int checkCustomerExist(int custID) {
    struct customer btemp;
    fp=fopen("CBS-Customer.dat","ab+");
    fseek(fp,0,SEEK_SET);
    while(fread(&btemp,sizeof(btemp),1,fp)>0) 
      if(btemp.ID==custID) {
        b.currentBalance=btemp.currentBalance;
        strcpy(b.name,btemp.name);
        b.phNo=btemp.phNo;
        fclose(fp);
        return 1;
      }
    fclose(fp);
    return 0; //Customer Not found in record
  }

  void searchCustomer(void) {
    int idSearch;
    printf("\t\t\tSEARCH CUSTOMERS\t\t\t\n Enter Customer ID to search for: ");
    scanf("%d",&idSearch);
    if(checkCustomerExist(idSearch)==1) {
      printf("\nCustomer found!\n");
      printf(" ID: %d\n",b.ID);
      printf(" Name: %s\n",b.name);
      printf(" lastPurchase: %d/%d/%d\n",b.lastPurchase.dd,b.lastPurchase.mm,b.lastPurchase.yyyy);
      printf(" Current Balance: %d\n\n",b.currentBalance);
    }
    else
      printf("\nCustomer Not Found!\n");
  }

  void displayCustomerList(void) {
    struct customer a;
    printf("\n\n--------Customer List--------\n");
    printf("Customer ID\t\tName\t\tLastPurchase\tCurrent Balance\n");
    int j=0;
    fp=fopen("CBS-Customer.dat","ab+");
    rewind(fp);
    while(fread(&a,sizeof(a),1,fp)==1) {
      printf(" \t%d\t\t",a.ID);
      printf(" %s\t\t",a.name);
      printf(" %d/%d/%d\t\t",a.lastPurchase.dd,a.lastPurchase.mm,a.lastPurchase.yyyy);
      printf(" %5d\n\n",a.currentBalance);
      j++;
    }
    printf("\nTotal Customers in File: %d\n\n",j);
    fclose(fp);
  }

