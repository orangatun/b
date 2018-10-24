  #include<stdio.h>
  #include<string.h>
  #include<stdlib.h> //Used for exit(0);
  #include<time.h>

  //Structure Definitions
  struct book {
    int id;
    //char authorName[20];
    //char bookName[20];
    //int rackno;
    char *category;
  }a;

  struct timeVal {
    int dd,mm,yyyy;
  };

  struct userID {
    int bkID,studentID;
    struct timeVal issued;
    //char studentName[20];
  }usr;

  //Function Declarations
  int getch(void);
  void mainMenu(void);
  void addBook(void);
  void removeBook(void);
  void searchBook(void);
  int checkBookExist(int);
  void issueBook(void);
  void returnBook(void);
  void displayBookList(void);
  void displayIssueList(void);

  FILE *fp,*ft,*fbk,*fbkt;

  //global variables
  int *tmpIn=&a.id;
  int ch;
  char cat[][3]={"CS","EC","EE","CV","ME"};

  int main(void) {
    //while(1)
    for(int i=0;i<20;i++)
      mainMenu();
    return 0;
  }

  void mainMenu(void) {
    //system("cls");
    printf("\n\n\t\tMAIN MENU \t\t\n\n");
    printf(" 1. Add Books\n 2. Remove Books\n 3. Search Books\n");
    printf(" 4. Issue Books\n 5. Return Books \n 6. Display books\n");
    printf(" 7. Display Issue\n 8. Close application\n\n Enter your choice: ");
    ch=getch();

    switch(ch) {
      case 1: addBook(); break;
      case 2: removeBook(); break;
      case 3: searchBook(); break;
      case 4: issueBook(); break;
      case 5: returnBook(); break;
      case 6: displayBookList(); break;
      case 7: displayIssueList(); break;

      case 8: {
        printf("\n\nLibrary Management System - O\n");
        exit(0);
      }break;
      default: printf("Wrong Entry!\nTry Again!\n\n");
    }
  }

  void addBook(void) {
    printf("\t\t\tADD BOOKS\t\t\t\nSelect Category\n");
    printf(" 1. CS\n 2. EC\n 3. EE\n 4. CV\n 5. ME\n");
    printf(" 6. Back to main menu\n\n Enter your choice: ");
    ch=getch();
    if((ch>=1)&&(ch<=5))
      a.category=cat[ch-1];//a.cat initially.. but the a is getting modified in checkBookExist()
    else if(ch==6)
      return;
    else {
      printf("Wrong Entry\n"); return;
    }
    printf(" Enter Book ID: ");
    scanf("%d",&a.id);
    if(checkBookExist(a.id)==1) {
      printf("Book with that ID already exists!\n");
      return;
    }	
    fp=fopen("LMS-book.dat","ab+");
    fseek(fp,0,SEEK_END);
    fwrite(&a,sizeof(a),1,fp);
    fclose(fp);
    printf("\nAdded Book to library\n\n");
    displayBookList();
  }

  int getch(void) {
    int cha;
    scanf("%d",&cha);
    return cha;
  }

  void removeBook(void) {
    int idRemove;
    printf("\n\n\t\tREMOVE BOOKS\t\t\n\n Enter Book ID to remove: ");
    scanf("%d",&idRemove);
    if(checkBookExist(idRemove)==0) {
      printf(" Book ID does not exist\n");
      return;
    }
    printf(" Continue deleting book ID #%d? (0=No): ",idRemove);
    ch=getch();
    if(ch==0) {
      printf("Deletion cancelled.\n");
      return;
    }
    fp=fopen("LMS-book.dat","ab+"); 
    ft=fopen("LMS-book-temp.dat","ab+"); //Creating temporary file
    if(ft!=NULL) {
      //rewind(fp);
      fseek(ft,0,SEEK_SET);
      fseek(fp,0,SEEK_SET);
      //printf("\nHere\n");
      while(fread(&a,sizeof(a),1,fp)>0) {
        if(a.id!=idRemove) {
          fseek(ft,0,SEEK_END);
          fwrite(&a,sizeof(a),1,ft);
        }
      }
      fclose(ft);
      fclose(fp);
      remove("LMS-book.dat");//Removing old dat file
      rename("LMS-book-temp.dat","LMS-book.dat");//Renaming tmp file
    }
    else
      fclose(fp);
    printf("Book #%d Removed from Library\n\n",idRemove);
    displayBookList();
  }

  int checkBookExist(int bkID) {
    struct book b;
    fp=fopen("LMS-book.dat","rb");
    fseek(fp,0,SEEK_SET);
    while(fread(&b,sizeof(b),1,fp)>0) 
      if(b.id==bkID) {
        fclose(fp);
        return 1; //Book Exists
      }
    fclose(fp);
    return 0; //Book Not found in record
  }

  int checkBookIssued(int bkID) {
    struct userID u;
    fbk=fopen("LMS-issue.dat","ab+");
    fseek(fbk,0,SEEK_SET);
    while(fread(&u,sizeof(u),1,fbk)==1) 
      if(u.bkID==bkID) {
        fclose(fbk);
        return 1; //Book Issued Already
      }
    fclose(fbk);
    return 0; //Book not issued
  }

  void searchBook(void) {
    int idSearch;
    printf("\t\t\tSEARCH BOOKS\t\t\t\n Enter Book ID to search for: ");
    scanf("%d",&idSearch);
    if(checkBookExist(idSearch)==1)
      printf("\nBook found!\n Category: %s\n",a.category);
    else
      printf("\nBook Not Found!\n");
  }

  void issueBook(void) {
    printf("\t\t\tISSUE BOOK\t\t\t\n"); //Issue a Book
    printf("\n Enter book ID: ");
    scanf("%d",&usr.bkID);
    if(checkBookExist(usr.bkID)==0) { //Book doesn't exist
      printf("Book #%d doesn't exist\n",usr.bkID);
      return;
    }
    else if(checkBookIssued(usr.bkID)==1) {
      printf("Book #%d already Issued\n",usr.bkID);
      return;
    }
    printf("Book is available for issue\n\n");
    printf(" Enter student ID: ");
    scanf("%d",&usr.studentID);
    printf(" Enter borrow date (dd/mm/yyyy): ");
    scanf("%d/%d/%d",&usr.issued.dd,&usr.issued.mm,&usr.issued.yyyy);
    fbk=fopen("LMS-issue.dat","ab+");
    fseek(fbk,0,SEEK_END);
    fwrite(&usr,sizeof(usr),1,fbk);
    fclose(fbk);
    printf("\nBook is Issued!\n\n");
    //printf("Return date is: %d/%d/%d",usr.issued.dd

  }

  void returnBook(void) { //Return a book
    int idReturn;
    printf("\t\t\tRETURN BOOK\t\t\t\n"); //Issue a Book
    printf("\n Enter book ID: ");
    scanf("%d",&idReturn);
    if(checkBookExist(idReturn)==0) { //Book doesn't exist
      printf("\nBook #%d doesn't belong to the Library\n",idReturn);
      return;
    }
    else if(checkBookIssued(idReturn)==0) {
      printf("\nBook #%d has not been Issued\n",idReturn);
      return;
    }
    fbk=fopen("LMS-issue.dat","ab+"); 
    fbkt=fopen("LMS-issue-temp.dat","ab+"); //Creating temporary file
    if(fbkt!=NULL) {
      fseek(fbkt,0,SEEK_SET);
      fseek(fbk,0,SEEK_SET);
      printf("\nHere\n");
      while(fread(&usr,sizeof(usr),1,fbk)>0) {
        if(usr.bkID!=idReturn) {
          fseek(ft,0,SEEK_END);
          fwrite(&usr,sizeof(usr),1,fbkt);
        }
      }
      fclose(fbkt);
      fclose(fbk);
      remove("LMS-issue.dat");//Removing old dat file
      rename("LMS-issue-temp.dat","LMS-issue.dat");//Renaming tmp file
    }
    else
      fclose(fbk);
    printf("\nBook Returned\n\n");
    displayIssueList();
  }


  void displayBookList(void) {
    printf("\n\n--------Book List--------\n");
    printf(" CATEGORY       BOOK ID          \n");//BOOK NAME ");
    int j=0;
    fp=fopen("LMS-book.dat","rb");
    rewind(fp);
    while(fread(&a,sizeof(a),1,fp)==1) {
      printf("    %s\t\t",a.category);
      printf("%5d\n",a.id);
      j++;
    }
    printf("\nTotal Books in Library: %d\n\n",j);
    fclose(fp);
  }


  void displayIssueList(void) {
    printf("\n\n----------------Book List----------------\n");
    printf(" BOOK ID    STUDENT ID      BORROWED TIME\n");
    int j=0;
    fbk=fopen("LMS-issue.dat","rb");
    rewind(fbk);
    while(fread(&usr,sizeof(usr),1,fbk)==1) {
      printf("    %d\t\t",usr.bkID);
      printf("%d\t",usr.studentID);
      printf("      %d/%d/%d\n",usr.issued.dd,usr.issued.mm,usr.issued.yyyy);
      j++;
    }
    printf("\nTotal Books Issued: %d\n\n",j);
    fclose(fbk);
  }
