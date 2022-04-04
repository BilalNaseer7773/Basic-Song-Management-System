#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

struct Date_Time     //stucture for date and time
{
    int day;
    int month;
    int year;
    int hours;
    int minutes;
};

struct Node        //structure for linked list node
{
    int song_ID;
    char song_name[50];
    char song_genre[50];
    char album_name[50];
    char artist_name[50];
    int year_release;
    struct Date_Time date;
    struct Node *next;
};


struct ListRecord     //structure for linked list
{
	struct Node *head;
	struct Node *tail;
	int size;
};

//function prototypes
typedef struct ListRecord *List;
void Add_Song(List,char[50],char[50],char[50],char[50],int);
void Print_Songs(List);
void Delete_Song(List,int);
void OverWrite(List);
void Search_song(List);
void create_Playlist(List,char[50],char[50],char[50],int);
List initializeSongs(List);


int main()
{
    int option=0,DEL_ID,Year_Release,playlist_id=0;
    char name[50],album_name[50],artist_name[50],genre[50];
    char song1[50],song2[50],song3[50];
    List my_list;
    my_list=initializeSongs(my_list);      //initialising the list
    while(option!=6)
    {
        printf("\n\n------MENU------\n1. Add Song.\n2. Delete Songs.\n3. Print Songs.\n4. Search Songs.\n5. Create Playlist\n6. EXIT\nEnter the option of your choice:");
        scanf("%d",&option);
        switch(option)
        {
            case 1:   //adding the song.
                printf("You chose option 1.\n");
                fflush(stdin);
                printf("Enter the name of the song:");
                gets(name);
                fflush(stdin);
                printf("Enter the genre of the song:");
                gets(genre);
                fflush(stdin);
                printf("Enter name of the album:");
                gets(album_name);
                fflush(stdin);
                printf("Enter the name of the artist:");
                gets(artist_name);
                fflush(stdin);
                printf("Enter year of the song:");
                scanf(" %d",&Year_Release);
                Add_Song(my_list,name,genre,album_name,artist_name,Year_Release);
                break;
            case 2:     //deleting the song.
                printf("Enter the id you want to delete:");
                scanf("%d",&DEL_ID);
                Delete_Song(my_list,DEL_ID);
                break;
            case 3:    //printing the list
                printf("You chose option 3.");
                Print_Songs(my_list);
                break;
            case 4:    //searching for a specific song
                printf("You chose option 4.");
                Search_song(my_list);
                break;
            case 5:    //creating a playlist.
                printf("You chose option 5.");
                fflush(stdin);
                printf("Enter the names of the songs for your playlist.\nEnter (1) song name:");
                scanf(" %s",song1);
                fflush(stdin);
                printf("Enter (2) song name:");
                scanf(" %s",song2);
                fflush(stdin);
                printf("Enter (3) song name:");
                scanf(" %s",song3);
                create_Playlist(my_list,song1,song2,song3,playlist_id);
                break;
            case 6:     //exiting and overwriting the file.
                OverWrite(my_list);
                printf("\nThe SonMan.txt file has been updated successfully!!\n\n\nGOOD BYE !");
                break;
            default:
                printf("You chose the wrong option.");
        }
    }

    return 0;
}

List initializeSongs(List my_list)
{
    struct Node *temp;
    FILE *infile;
    infile=fopen("SongMan.txt","r+");    //opening the file
    if(infile==NULL)
    {
        printf("Unable to Open the file!");
        exit(1);
    }
	my_list = (struct ListRecord *) malloc(sizeof(struct ListRecord));   //creating the list
	if (my_list == NULL)
    {
        printf("Out of memory!\n");
        exit(1);
    }
    my_list->head = (struct Node *) malloc(sizeof(struct Node));
    if (my_list->head == NULL)
    {
        printf("Out of memory!\n");
        exit(1);
    }
    my_list->head->next = NULL;
    my_list->tail = my_list->head;
    my_list->size = 0;
    temp=malloc(sizeof(struct Node));

    while(fscanf(infile,"%d;%[^;];%[^;];%[^;];%[^;];%d;%d/%d/%d %d:%d",&temp->song_ID,temp->song_name,temp->song_genre,temp->album_name,temp->artist_name,&temp->year_release,&temp->date.day, &temp->date.month,&temp->date.year,&temp->date.hours,&temp->date.minutes)!=EOF)    //reading from the file to the list
    {
        my_list->tail->next=temp;
        temp->next=NULL;
        my_list->tail=my_list->tail->next;
        temp=malloc(sizeof(struct Node));
    }

	printf("\nList has been initialized\n");
    fclose(infile);
    return my_list;
}

void Add_Song(List my_list,char name[50],char genre[50],char album_name[50],char artist_name[50],int Year_Release)
{
    struct Node *temp;
    time_t ti = time(NULL);
    struct tm t = *localtime(&ti);

    temp=malloc(sizeof(struct Node));
    temp->next=NULL;
    temp->song_ID=my_list->tail->song_ID+1;
    strcpy(temp->song_name,name);
    strcpy(temp->song_genre,genre);
    strcpy(temp->album_name,album_name);
    strcpy(temp->artist_name,artist_name);
    temp->year_release=Year_Release;
    temp->date.day=t.tm_mday;
    temp->date.month=t.tm_mon+1;
    temp->date.year=t.tm_year+1900;
    temp->date.hours=t.tm_hour;
    temp->date.minutes=t.tm_min;
    my_list->tail->next=temp;
    my_list->tail=my_list->tail->next;


    printf("The Song has been added!!!");
}

void Print_Songs(List my_list)
{
    printf("\nSongs in your Database:\n-----------------\n");
    struct Node *temp;
    temp=malloc(sizeof(struct Node));
    temp=my_list->head->next;
    while(temp != NULL)
    {
        printf("\nID: %d\nSong Name: %s\nSong Genre: %s\nAlbum Name: %s\nArtist Name: %s\nYear:%d\ndate:%d/%d/%d\nTime: %d:%d\n",temp->song_ID,temp->song_name,temp->song_genre,temp->album_name,temp->artist_name,temp->year_release,temp->date.day,temp->date.month,temp->date.year,temp->date.hours,temp->date.minutes);
        temp=temp->next;
    }
}

void Delete_Song(List my_list, int n)
{
    struct Node *temp,*deleted_node;
    temp=my_list->head;
    while(temp->next!=NULL && temp->next->song_ID!=n)
    {
        temp=temp->next;
    }
    if(temp->next==NULL)
        printf("NO song present in the list with the entered ID number.");
    else if(temp->next->song_ID==n)
    {
        deleted_node=temp->next;
        temp->next=temp->next->next;
        printf("Song with ID %d has been deleted.",n);
    }

}

void Search_song(List my_list)
{
    int s_option;
    char Song_name[50],Artist_name[50],Genre[50];
    struct Node *temp;
    temp=malloc(sizeof(struct Node));
    temp=my_list->head->next;

    printf("\n----Searching by----\n(1) song name.\n(2) artist name.\n(3) genre\nEnter Search by option:");
    scanf("%d",&s_option);
    switch(s_option)
    {
        case 1:
            printf("Enter the name of the song:");    //search with song name
            fflush(stdin);
            gets(Song_name);
            while(temp->next!=NULL)
            {
                if(strstr(temp->song_name,Song_name)!=NULL || strcmp(temp->song_name,Song_name)==0)
                    printf("\nID: %d\nSong Name: %s\nSong Genre: %s\nAlbum Name: %s\nArtist Name: %s\nYear:%d\ndate:%d/%d/%d\nTime: %d:%d\n",temp->song_ID,temp->song_name,temp->song_genre,temp->album_name,temp->artist_name,temp->year_release,temp->date.day,temp->date.month,temp->date.year,temp->date.hours,temp->date.minutes);
                temp=temp->next;
            }
            break;
        case 2:
            printf("Enter the name of the artist:");     //search with artist name
            fflush(stdin);
            gets(Artist_name);
            while(temp!=NULL)
            {
                if(strstr(temp->artist_name,Artist_name)!=NULL || strcmp(temp->artist_name,Artist_name)==0)
                    printf("\nID: %d\nSong Name: %s\nSong Genre: %s\nAlbum Name: %s\nArtist Name: %s\nYear:%d\ndate:%d/%d/%d\nTime: %d:%d\n",temp->song_ID,temp->song_name,temp->song_genre,temp->album_name,temp->artist_name,temp->year_release,temp->date.day,temp->date.month,temp->date.year,temp->date.hours,temp->date.minutes);
                temp=temp->next;
            }
            break;
        case 3:
            printf("Enter the genre of the song:");      //search with genre name
            fflush(stdin);
            gets(Genre);
            while(temp!=NULL)
            {
                if(strstr(temp->song_genre,Genre)!=NULL || strcmp(temp->song_genre,Genre)==0 )
                    printf("\nID: %d\nSong Name: %s\nSong Genre: %s\nAlbum Name: %s\nArtist Name: %s\nYear:%d\ndate:%d/%d/%d\nTime: %d:%d\n",temp->song_ID,temp->song_name,temp->song_genre,temp->album_name,temp->artist_name,temp->year_release,temp->date.day,temp->date.month,temp->date.year,temp->date.hours,temp->date.minutes);
                temp=temp->next;

            }
            break;
        default:
            printf("Invalid option selected !");
    }
}

void create_Playlist(List my_list,char song1[50],char song2[50],char song3[50],int playlist_id)
{
    FILE *outfile;
    struct Node *temp;
    temp=malloc(sizeof(struct Node));
    temp=my_list->head->next;
    int a,b,c;
    while(temp->next!=NULL)
            {
                if(strstr(temp->song_name,song1)!=NULL || strcmp(temp->song_name,song1)==0)
                    a=1;
                if(strstr(temp->song_name,song2)!=NULL || strcmp(temp->song_name,song2)==0)
                    b=1;
                if(strstr(temp->song_name,song3)!=NULL || strcmp(temp->song_name,song3)==0)
                    c=1;
                temp=temp->next;
            }
    if(a==1 && b==1 && c==1)
    {
        playlist_id++;
        outfile=fopen("Playlist.txt","w");
        if(outfile==NULL)
            {
                printf("Unable to Open the file for Over writing!");
                exit(1);
            }
        temp=my_list->head->next;
        while(temp->next!=NULL)
        {
            if(strstr(temp->song_name,song1)!=NULL || strcmp(temp->song_name,song1)==0)
                fprintf(outfile,"%d;%s;%s;%s;%s;%d;%d/%d/%d;%d:%d\n",temp->song_ID,temp->song_name,temp->song_genre,temp->album_name,temp->artist_name,temp->year_release,temp->date.day,temp->date.month,temp->date.year,temp->date.hours,temp->date.minutes);
            if(strstr(temp->song_name,song2)!=NULL || strcmp(temp->song_name,song2)==0)
                fprintf(outfile,"%d;%s;%s;%s;%s;%d;%d/%d/%d;%d:%d\n",temp->song_ID,temp->song_name,temp->song_genre,temp->album_name,temp->artist_name,temp->year_release,temp->date.day,temp->date.month,temp->date.year,temp->date.hours,temp->date.minutes);
            if(strstr(temp->song_name,song3)!=NULL || strcmp(temp->song_name,song3)==0)
                fprintf(outfile,"%d;%s;%s;%s;%s;%d;%d/%d/%d;%d:%d\n",temp->song_ID,temp->song_name,temp->song_genre,temp->album_name,temp->artist_name,temp->year_release,temp->date.day,temp->date.month,temp->date.year,temp->date.hours,temp->date.minutes);
            temp=temp->next;
        }
    }
    else
        printf("The songs do not exists in the list.");

    fclose(outfile);
}

void OverWrite(List my_list)
{
    struct Node *temp;
    FILE *outfile;
    outfile=fopen("SongMan.txt","r+");
    if(outfile==NULL)
    {
        printf("Unable to Open the file for Over writing!");
        exit(1);
    }
    temp=malloc(sizeof(struct Node));
    temp=my_list->head->next;
    while(temp!=NULL)
    {
        fprintf(outfile,"%d;%s;%s;%s;%s;%d;%d/%d/%d;%d:%d\n",temp->song_ID,temp->song_name,temp->song_genre,temp->album_name,temp->artist_name,temp->year_release,temp->date.day,temp->date.month,temp->date.year,temp->date.hours,temp->date.minutes);
        temp=temp->next;
    }
    fclose(outfile);
}

