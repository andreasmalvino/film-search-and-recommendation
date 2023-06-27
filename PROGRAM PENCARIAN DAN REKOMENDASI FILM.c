/*
Project Akhir Struktur Data dan Algoritma
IMPLEMENTASI MERGER SORTING PADA PROGRAM PENCARIAN DAN REKOMENDASI FILM
KELOMPOK 6
1. Renatha Adzuria Arimaya (2110512098)
2. Muhamad Fikri Rahmayandi (2110512099)
3. Andreas Malvino Simbolon (2110512100)
4. Bintang Dwi Wahyu Mulyo (2110512107)
5. Alika Nirwasita Kalani Zulkarnaen (2110512108)
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>
#include <windows.h>

typedef struct{
    char nama[50];
    char genre[100];
    char kategori[50];
    float rating;
    int thn_rilis;
    int views;
}data_film;

typedef struct elmt *alamatelmt;

typedef struct elmt{
    data_film kontainer;
    alamatelmt prev;
    alamatelmt next;
}elemen;

typedef struct{
    elemen *first;
    elemen *tail;
}list;

typedef struct{
    char nama[50];
    char genre[100];
    char kategori[50];
    float rating;
    int thn_rilis;
    int views;
}temporary;

void createList(list *L){
    (*L).first=NULL;
    (*L).tail=NULL;
}

void input(char nama[], char genre[], char kategori[], float rating,  int thn_rilis, int views, list *L){
    elemen *baru;
    baru=(elemen*) malloc(sizeof(elemen));

    strcpy(baru->kontainer.nama, nama);
    strcpy(baru->kontainer.genre, genre);
    strcpy(baru->kontainer.kategori, kategori);
    baru->kontainer.rating = rating;
    baru->kontainer.thn_rilis = thn_rilis;
    baru->kontainer.views = views;

    if((*L).first==NULL)
    {
        (*L).first=baru;
        (*L).tail=baru;
        baru->next=NULL;
        baru->prev=NULL;
    }
    else
    {
        (*L).tail->next=baru;
        baru->prev=(*L).tail;
        baru->next=NULL;
        (*L).tail=baru;
    }
    baru=NULL;
}

int countElement (list L){
    int hasil=0;
    if(L.first != NULL){
        elemen *bantu =L.first;
        while(bantu!=NULL){
            hasil=hasil+1;
            bantu=bantu->next;
        }
    }
    else{
        hasil=0;
    }
    return hasil;
}

void print(elemen *tunjuk){
    printf("===================================\n");
    printf("Nama Film\t: %s\n", tunjuk->kontainer.nama);
    printf("Genre Film\t: %s\n", tunjuk->kontainer.genre);
    printf("Kategori Usia\t: %s\n", tunjuk->kontainer.kategori);
    printf("Rating\t\t: %.1f/10\n", tunjuk->kontainer.rating);
    printf("Tahun Rilis\t: %d\n", tunjuk->kontainer.thn_rilis);
    printf("Views\t\t: %d\n", tunjuk->kontainer.views);
}

void loading1(){
    for (int percent = 10; percent <= 100; percent += 5)
    {
        const int mul = 2;
        percent = min(100, percent);

        static int spin_index = 0;
        char spinning[] = "_-\\|/-";

        int len = (percent * mul / 10) + 1;
        char *bar = malloc(len);
        memset(bar, '\xc4', len - 1);
        bar[len - 1] = 0;

        printf("%c Loading: [%*s] %*d%%\r",
        percent == 100 ? ' ' : spinning[spin_index],
        mul * 10, bar, 3, percent);
        spin_index = (spin_index + 1) % strlen(spinning);

        free(bar);
        Sleep(50);
    }
    printf("\nDone...\n");
}

void loading2(){
    int i;
    for (i = 0; i <=38; i++)
        {
            printf("\xc4");
            Sleep(14);
        }
}

void printElement(list L){
    elemen *tunjuk=L.first;
    loading1();
    while(tunjuk!=NULL){
        printf("===================================\n");
        printf("Nama Film\t: %s\n", tunjuk->kontainer.nama);
        printf("Genre Film\t: %s\n", tunjuk->kontainer.genre);
        printf("Kategori Usia\t: %s\n", tunjuk->kontainer.kategori);
        printf("Rating\t\t: %.1f/10\n", tunjuk->kontainer.rating);
        printf("Tahun Rilis\t: %d\n", tunjuk->kontainer.thn_rilis);
        printf("Views\t\t: %d\n", tunjuk->kontainer.views);
        tunjuk = tunjuk->next;
    }
    printf("===================================");
}

void array_pass(int n, temporary *film, list *L){
    int i=0;
    elemen *bantu = (*L).first;
    while(bantu!=NULL){
        strcpy(film[i].nama,bantu->kontainer.nama);
        strcpy(film[i].genre,bantu->kontainer.genre);
        strcpy(film[i].kategori,bantu->kontainer.kategori);
        film[i].rating=bantu->kontainer.rating;
        film[i].thn_rilis=bantu->kontainer.thn_rilis;
        film[i].views=bantu->kontainer.views;
        i++;
        bantu=bantu->next;
    }
}

void merge_sort_nama_asc(int l, int r, temporary film[], list *L){
    int m;
    if(l<r){
        m=(l+r)/2;
        merge_sort_nama_asc(l,m,film,L);
        merge_sort_nama_asc(m+1,r,film,L);
        merge_nama_asc(l,m,r,film,L);
    }
}

void merge_nama_asc(int l, int m, int r, temporary film[], list *L){
    int left_length = m - l + 1;
    int right_length = r - m;

    temporary left[left_length];
    temporary right[right_length];

    int i;
    for (int i = 0; i < left_length; i++){
        left[i]=film[l + i];
    }
    for (int i = 0; i < right_length; i++){
        right[i]=film[m + 1 + i];
    }
    int j=0,k;
    i=0;k=l;
    while(i<left_length && j<right_length){
        if(strcmp(left[i].nama,right[j].nama)<0){
            film[k++]=left[i++];
        }
        else{
            film[k++]=right[j++];
        }
    }
    while(i<left_length){
            film[k++]=left[i++];
    }
    while(j<right_length){
            film[k++]=right[j++];
    }
    //mengganti nilai list dengan array yang sudah disorting
    elemen *bantu = (*L).first;
    k=0;
    while(bantu!=NULL){
        strcpy(bantu->kontainer.nama,film[k].nama);
        strcpy(bantu->kontainer.genre,film[k].genre);
        strcpy(bantu->kontainer.kategori,film[k].kategori);
        bantu->kontainer.rating=film[k].rating;
        bantu->kontainer.thn_rilis=film[k].thn_rilis;
        bantu->kontainer.views=film[k].views;
        k++;
        bantu=bantu->next;
    }
}

void merge_sort_nama_dsc(int l, int r, temporary film[], list *L){
    int m;
    if(l<r){
        m=(l+r)/2;
        merge_sort_nama_dsc(l,m,film,L);
        merge_sort_nama_dsc(m+1,r,film,L);
        merge_nama_dsc(l,m,r,film,L);
    }
}

void merge_nama_dsc(int l, int m, int r, temporary film[], list *L){
    int left_length = m - l + 1;
    int right_length = r - m;

    temporary left[left_length];
    temporary right[right_length];

    int i;
    for (int i = 0; i < left_length; i++){
        left[i]=film[l + i];
    }
    for (int i = 0; i < right_length; i++){
        right[i]=film[m + 1 + i];
    }
    int j=0,k;
    i=0; k=l;
    while(i<left_length && j<right_length){
        if(strcmp(left[i].nama,right[j].nama)>0){
            film[k++]=left[i++];
        }
        else{
            film[k++]=right[j++];
        }
    }
    while(i<left_length){
            film[k++]=left[i++];
    }
    while(j<right_length){
            film[k++]=right[j++];
    }
    //mengganti nilai list dengan array yang sudah disorting
    elemen *bantu = (*L).first;
    k=0;
    while(bantu!=NULL){
        strcpy(bantu->kontainer.nama,film[k].nama);
        strcpy(bantu->kontainer.genre,film[k].genre);
        strcpy(bantu->kontainer.kategori,film[k].kategori);
        bantu->kontainer.rating=film[k].rating;
        bantu->kontainer.thn_rilis=film[k].thn_rilis;
        bantu->kontainer.views=film[k].views;
        k++;
        bantu=bantu->next;
    }
}

void merge_sort_rtg_asc(int l, int r, temporary film[], list *L){
    int m;
    if(l<r){
        m=(l+r)/2;
        merge_sort_rtg_asc(l,m,film,L);
        merge_sort_rtg_asc(m+1,r,film,L);
        merge_rtg_asc(l,m,r,film,L);
    }
}

void merge_rtg_asc(int l, int m, int r, temporary film[], list *L){
    int left_length = m - l + 1;
    int right_length = r - m;

    temporary left[left_length];
    temporary right[right_length];

    int i, j, k;
    for (int i = 0; i < left_length; i++){
        left[i]=film[l + i];
    }
    for (int i = 0; i < right_length; i++){
        right[i]=film[m + 1 + i];
    }
    for (i = 0, j = 0, k = l; k <= r; k++){
        if ((i < left_length) && (j >= right_length || left[i].rating <= right[j].rating)){
            film[k]=left[i];
            i++;
        }
        else{
            film[k]=right[j];
            j++;
        }
    }
    //mengganti nilai list dengan array yang sudah disorting
    elemen *bantu = (*L).first;
    k=0;
    while(bantu!=NULL){
        strcpy(bantu->kontainer.nama,film[k].nama);
        strcpy(bantu->kontainer.genre,film[k].genre);
        strcpy(bantu->kontainer.kategori,film[k].kategori);
        bantu->kontainer.rating=film[k].rating;
        bantu->kontainer.thn_rilis=film[k].thn_rilis;
        bantu->kontainer.views=film[k].views;
        k++;
        bantu=bantu->next;
    }
}

void merge_sort_rtg_dsc(int l, int r, temporary film[], list *L){
    int m;
    if(l<r){
        m=(l+r)/2;
        merge_sort_rtg_dsc(l,m,film,L);
        merge_sort_rtg_dsc(m+1,r,film,L);
        merge_rtg_dsc(l,m,r,film,L);
    }
}

void merge_rtg_dsc(int l, int m, int r, temporary film[], list *L){
    int left_length = m - l + 1;
    int right_length = r - m;

    temporary left[left_length];
    temporary right[right_length];

    int i, j, k;
    for (int i = 0; i < left_length; i++){
        left[i]=film[l + i];
    }
    for (int i = 0; i < right_length; i++){
        right[i]=film[m + 1 + i];
    }
    for (i = 0, j = 0, k = l; k <= r; k++)
    {
        if ((i < left_length) && (j >= right_length || left[i].rating >= right[j].rating)){
            film[k] = left[i];
            i++;
        }
        else{
            film[k] = right[j];
            j++;
        }
    }
    //mengganti nilai list dengan array yang sudah disorting
    elemen *bantu = (*L).first;
    k=0;
    while(bantu!=NULL){
        strcpy(bantu->kontainer.nama,film[k].nama);
        strcpy(bantu->kontainer.genre,film[k].genre);
        strcpy(bantu->kontainer.kategori,film[k].kategori);
        bantu->kontainer.rating=film[k].rating;
        bantu->kontainer.thn_rilis=film[k].thn_rilis;
        bantu->kontainer.views=film[k].views;
        k++;
        bantu=bantu->next;
    }
}

void merge_sort_view_asc(int l, int r, temporary film[], list *L){
    int m;
    if(l<r){
        m=(l+r)/2;
        merge_sort_view_asc(l,m,film,L);
        merge_sort_view_asc(m+1,r,film,L);
        merge_view_asc(l,m,r,film,L);
    }
}

void merge_view_asc(int l, int m, int r, temporary film[], list *L){
    int left_length = m - l + 1;
    int right_length = r - m;

    temporary left[left_length];
    temporary right[right_length];

    int i, j, k;
    for (int i = 0; i < left_length; i++){
        left[i]=film[l + i];
    }
    for (int i = 0; i < right_length; i++){
        right[i]=film[m + 1 + i];
    }
    for (i = 0, j = 0, k = l; k <= r; k++)
    {
        if ((i < left_length) && (j >= right_length || left[i].views <= right[j].views)){
            film[k]=left[i];
            i++;
        }
        else{
            film[k]=right[j];
            j++;
        }
    }
    //mengganti nilai list dengan array yang sudah disorting
    elemen *bantu = (*L).first;
    k=0;
    while(bantu!=NULL){
        strcpy(bantu->kontainer.nama,film[k].nama);
        strcpy(bantu->kontainer.genre,film[k].genre);
        strcpy(bantu->kontainer.kategori,film[k].kategori);
        bantu->kontainer.rating=film[k].rating;
        bantu->kontainer.thn_rilis=film[k].thn_rilis;
        bantu->kontainer.views=film[k].views;
        k++;
        bantu=bantu->next;
    }
}

void merge_sort_view_dsc(int l, int r, temporary film[], list *L){
    int m;
    if(l<r){
        m=(l+r)/2;
        merge_sort_view_dsc(l,m,film,L);
        merge_sort_view_dsc(m+1,r,film,L);
        merge_view_dsc(l,m,r,film,L);
    }
}

void merge_view_dsc(int l, int m, int r, temporary film[], list *L){
    int left_length = m - l + 1;
    int right_length = r - m;

    temporary left[left_length];
    temporary right[right_length];

    int i, j, k;
    for (int i = 0; i < left_length; i++){
        left[i]=film[l + i];
    }
    for (int i = 0; i < right_length; i++){
        right[i]=film[m + 1 + i];
    }
    for (i = 0, j = 0, k = l; k <= r; k++)
    {
    if ((i < left_length) && (j >= right_length || left[i].views >= right[j].views)){
            film[k]=left[i];
            i++;
        }
        else{
            film[k]=right[j];
            j++;
        }
    }
    //mengganti nilai list dengan array yang sudah disorting
    elemen *bantu = (*L).first;
    k=0;
    while(bantu!=NULL){
        strcpy(bantu->kontainer.nama,film[k].nama);
        strcpy(bantu->kontainer.genre,film[k].genre);
        strcpy(bantu->kontainer.kategori,film[k].kategori);
        bantu->kontainer.rating=film[k].rating;
        bantu->kontainer.thn_rilis=film[k].thn_rilis;
        bantu->kontainer.views=film[k].views;
        k++;
        bantu=bantu->next;
    }
}

void cari_nama(list L){
    int i=0;
    char *cari, nama[50];
    elemen *bantu = (L).first;

    printf("Masukkkan Nama Film: ");
    fflush(stdin);
    gets(nama);
    loading1();
    printf("\n");
    while(bantu != NULL){
        cari = strstr(bantu->kontainer.nama,nama);
        if(cari!=NULL){
            print(bantu);
            cari=NULL;
            i++;
        }
        bantu = bantu->next;
    }
    if(i==0){
        printf("\nFilm Tidak ditemukan");
    }else{
        printf("===================================");
    }
}

void cari_genre(int plh_genre[], int j, int n, int high, temporary film[]){
    int i, k, m=0;
    char *cari, gnr;
    char genre[100];
    temporary genres[n];


    if(j==high){
        loading1();
        if(n==0){
            printf("\n  !!FILM YANG ANDA CARI TIDAK DITEMUKAN!!\n");
        }
        else{
            for(i=0; i<n; i++){
                printf("===================================\n");
                printf("Nama Film\t: %s\n", film[i].nama);
                printf("Genre Film\t: %s\n", film[i].genre);
                printf("Kategori Usia\t: %s\n", film[i].kategori);
                printf("Rating\t\t: %.1f/10\n", film[i].rating);
                printf("Tahun Rilis\t: %d\n", film[i].thn_rilis);
                printf("Views\t\t: %d\n", film[i].views);
            }
            printf("===================================\n");
        }
    }
    else{
    //memasukkan data film yang sesudai dengan genre ke dalam array
        if(plh_genre[j]==1){
            strcpy(genre,"Action");
        }
        else if(plh_genre[j]==2){
            strcpy(genre,"Animation");
        }
        else if(plh_genre[j]==3){
            strcpy(genre,"Comedy");
        }
        else if(plh_genre[j]==4){
            strcpy(genre,"Drama");
        }
        else if(plh_genre[j]==5){
            strcpy(genre,"Fantasy");
        }
        else if(plh_genre[j]==6){
            strcpy(genre,"Horror");
        }
        else if(plh_genre[j]==7){
            strcpy(genre,"Musical");
        }
        else if(plh_genre[j]==8){
            strcpy(genre,"Mystery");
        }
        else if(plh_genre[j]==9){
            strcpy(genre,"Romance");
        }
        else if(plh_genre[j]==10){
            strcpy(genre,"Sci-Fi");
        }
        else if(plh_genre[j]==11){
            strcpy(genre,"Thriller");
        }
        for(k=0; k<n; k++)
        {
            cari = strstr(film[k].genre,genre);
            if(cari!=NULL){
                genres[m] = film[k];
                cari = NULL;
                m++;
            }
        }
        //rekursif
        cari_genre(plh_genre, j+1, m, high, genres);
    }
}

void cari_usia(int usia, temporary film[], int n, int *k){
    temporary rekomendasi[n];
    int j, i=0;

        if(usia<13){
           for(j=0; j<n; j++){
                if(strcmp(film[j].kategori, "G (General)") == 0){
                   rekomendasi[i]=film[j];
                   i++;
                }
                else if(strcmp(film[j].kategori, "PG (Parental Guidance)") == 0){
                   rekomendasi[i]=film[j];
                   i++;
                }
            }
        }
        else if(usia<17 && usia>=13){
            for(j=0; j<n; j++){
                if(strcmp(film[j].kategori, "G (General)") == 0){
                   rekomendasi[i]=film[j];
                   i++;
                }
                else if(strcmp(film[j].kategori, "PG (Parental Guidance)") == 0){
                   rekomendasi[i]=film[j];
                   i++;
                }
                else if(strcmp(film[j].kategori, "PG-13 (Parental Guidance Strongly Cautioned)") == 0){
                   rekomendasi[i]=film[j];
                   i++;
                }
            }
        }
        else if(usia>=17){
            for(j=0; j<n; j++){
                rekomendasi[i]=film[j];
                i++;
            }
        }
        film=rekomendasi;
        *k=i;
}

void cari_kategori(char ktgr, list L){
    int i=0;
    char kategori[50];
    elemen *bantu = (L).first;

    if(ktgr=='1'){
        strcpy(kategori,"G (General)");
    }
    else if(ktgr=='2'){
        strcpy(kategori,"PG (Parental Guidance)");
    }
    else if(ktgr=='3'){
        strcpy(kategori,"PG-13 (Parental Guidance Strongly Cautioned)");
    }
    else if(ktgr=='4'){
        strcpy(kategori,"R (Restricted)");
    }
    else if(ktgr=='5'){
        strcpy(kategori,"NC-17 (Adults Only)");
    }
    loading1();
    while(bantu != NULL){
        if(strcmp(bantu->kontainer.kategori, kategori) == 0){
            print(bantu);
            i++;
        }
        bantu = bantu->next;
    }

    if(i==0){
        printf("\n  !!FILM YANG ANDA CARI TIDAK DITEMUKAN!!\n");
    }
    else{
        printf("===================================");
    }
}

void cari_thn_rilis(int thn, list L){
    int i=0;
    elemen *bantu = (L).first;

    loading1();
    while(bantu != NULL){
        if(thn == bantu->kontainer.thn_rilis){
            print(bantu);
            i++;
        }
        bantu = bantu->next;
    }
    if(i==0){
        printf("\n  !!FILM YANG ANDA CARI TIDAK DITEMUKAN!!\n");
    }else{
        printf("===================================");
    }
}

void menu_back(){
    printf("\n1. Back");
    printf("\n2. Back to Main Menu");
    printf("\nPilih Menu:");
}

void menu_genre(){
    printf("1. Action");
    printf("\n2. Animation");
    printf("\n3. Comedy");
    printf("\n4. Drama");
    printf("\n5. Fantasy");
    printf("\n6. Horror");
    printf("\n7. Musical");
    printf("\n8. Mystery");
    printf("\n9. Romance");
    printf("\n10. Sci-Fi");
    printf("\n11. Thriller");
    printf("\n12. Back");
}

int main()
{
    //Membuat list dan input data film
    list L;
    createList(&L);
    input("the avengers", "Action, Sci-Fi", "PG-13 (Parental Guidance Strongly Cautioned)", 8, 2012, 1400000000, &L);
    input("avengers: age of ultron", "Action, Sci-Fi", "PG-13 (Parental Guidance Strongly Cautioned)", 7.3, 2015, 837000000, &L);
    input("avengers: infinity war", "Action, Sci-Fi", "PG-13 (Parental Guidance Strongly Cautioned)", 8.4, 2018, 1000000000, &L);
    input("avengers: endgame", "Action, Sci-Fi", "PG-13 (Parental Guidance Strongly Cautioned)", 8.4, 2019, 1100000000, &L);
    input("the secret life of pets", "Animation, Comedy", "PG (Parental Guidance)", 6.5, 2016, 199000, &L);
    input("the secret life of pets 2", "Animation, Comedy", "PG (Parental Guidance)", 6.4, 2019, 61000, &L);
    input("the hunger games", "Action, Thriller, Sci-Fi", "PG-13 (Parental Guidance Strongly Cautioned)", 7.2, 2012, 900000, &L);
    input("the hunger games: catching fire", "Action, Thriller, Sci-Fi", "PG-13 (Parental Guidance Strongly Cautioned)", 7.5, 2013, 653000, &L);
    input("the hunger games: mockingjay part 1", "Action, Thriller, Sci-Fi", "PG-13 (Parental Guidance Strongly Cautioned)", 6.6, 2014, 447000, &L);
    input("the hunger games: mockingjay part 2", "Action, Thriller, Sci-Fi", "PG-13 (Parental Guidance Strongly Cautioned)", 6.5, 2015, 318000, &L);
    input("nanti kita cerita tentang hari ini", "Drama, Romance", "PG (Parental Guidance)", 7.4, 2020, 1100, &L);
    input("the fault in our stars", "Romance", "PG-13 (Parental Guidance Strongly Cautioned)", 7.7, 2014, 370000, &L);
    input("the nun", "Horror, Thriller, Mystery", "R (Restricted)", 5.3, 2018, 137000, &L);
    input("high school musical", "Musical, Comedy, Drama", "PG (Parental Guidance)", 5.4, 2006, 87000, &L);
    input("high school musical 2", "Musical, Comedy, Drama", "PG (Parental Guidance)", 5.1, 2007, 60000, &L);
    input("high school musical 3", "Musical, Comedy, Drama", "PG (Parental Guidance)", 4.8, 2008, 62000, &L);
    input("men in black: international", "Action, Sci-Fi", "PG-13 (Parental Guidance Strongly Cautioned)", 5.6, 2019, 131000, &L);
    input("encanto", "Animation, Musical, Mystery", "PG (Parental Guidance)", 7.2, 2021, 200000, &L);
    input("coco", "Comedy, Animation", "PG (Parental Guidance)", 8.4, 2017, 480000, &L);
    input("ratatouille", "Comedy, Animation", "G (General)", 8.1, 2007, 707000, &L);
    input("deadpool", "Action", "R (Restricted)", 8, 2016, 1000000000, &L);
    input("johnny english", "Comedy, Action", "PG (Parental Guidance)", 6.2, 2003, 159000, &L);
    input("final destination", "Thriller, Horror", "R (Restricted)", 5.9, 2011, 119000, &L);
    input("jurassic world", "Sci-Fi", "PG-13 (Parental Guidance Strongly Cautioned)", 6.6, 2015, 623000, &L);
    input("jurassic world: fallen kingdom", "Sci-Fi", "PG-13 (Parental Guidance Strongly Cautioned)", 6.1, 20158, 301000, &L);
    input("lucy", "Action, Sci-Fi", "R (Restricted)", 6.4, 2014, 485000, &L);
    input("i am number four", "Sci-Fi, Action", "PG-13 (Parental Guidance Strongly Cautioned)", 6.1, 2011, 237000, &L);
    input("hereditary", "Horror, Drama, Mystery", "R (Restricted)", 7.3, 2018, 295000, &L);
    input("five feet apart", "Drama", "PG-13 (Parental Guidance Strongly Cautioned)", 7.2, 2019, 63000, &L);
    input("black box", "Horror, Sci-Fi", "NC-17 (Adults Only)", 6.2, 2020, 14000, &L);
    input("to all the boys: always and forever", "Drama", "PG-13 (Parental Guidance Strongly Cautioned)", 6.3, 2021, 35000, &L);
    input("despicable me", "Comedy, Animation", "PG (Parental Guidance)", 7.6, 2010, 534000, &L);
    input("despicable me 2", "Comedy, Animation", "PG (Parental Guidance)", 7.3, 2013, 392000, &L);
    input("despicable me 3", "Comedy, Animation", "PG (Parental Guidance)", 6.2, 2017, 130000, &L);
    input("trolls", "Animation, Musical", "PG (Parental Guidance)", 6.4, 2016, 80000, &L);
    input("trolls world tour", "Animation, Musical", "PG (Parental Guidance)", 6, 2020, 23000, &L);
    input("sing", "Animation, Musical", "PG (Parental Guidance)", 7.1, 2016, 163000, &L);
    input("sing 2", "Animation, Musical", "PG (Parental Guidance)", 7.4, 2022, 51000, &L);
    input("those who wish me dead", "Action, Thriller", "R (Restricted)", 6, 2021, 58000, &L);
    input("thor", "Action, Sci-Fi", "PG-13 (Parental Guidance Strongly Cautioned)", 7, 2011, 704000, &L);
    input("thor: the dark world", "Action, Sci-Fi", "PG-13 (Parental Guidance Strongly Cautioned)", 6.8, 2013, 821000, &L);
    input("thor: ragnarok", "Action, Sci-Fi", "PG-13 (Parental Guidance Strongly Cautioned)", 7.9, 2017, 661000, &L);
    input("beauty and the beast", "Musical, Romance, Drama", "PG (Parental Guidance)", 7.1, 2017, 302000, &L);
    input("cruella", "Comedy", "PG-13 (Parental Guidance Strongly Cautioned)", 7.3, 2021, 222000, &L);
    input("harry potter and the philosopher's stone", "Fantasy, Mystery", "PG (Parental Guidance)", 7.6, 2001, 755000, &L);
    input("harry potter and the chamber of secrets", "Fantasy, Mystery", "PG (Parental Guidance)", 7.4, 2002, 617000, &L);
    input("harry potter and the prisoner of azkaban", "Fantasy, Mystery", "PG (Parental Guidance)", 7.9, 2004, 617000, &L);
    input("harry potter and the goblet of fire", "Fantasy, Mystery", "PG (Parental Guidance)", 7.7, 2005, 610000, &L);
    input("harry potter and the order of the phoenix", "Fantasy, Mystery", "PG (Parental Guidance)", 7.5, 2007, 566000, &L);
    input("harry potter and the half-blood prince", "Fantasy, Mystery", "PG (Parental Guidance)", 7.6, 2009, 530000, &L);
    input("harry potter and the deathly hallows", "Fantasy, Mystery", "PG (Parental Guidance)", 7.7, 2010, 534000, &L);
    input("harry potter and the deathly hallows ii", "Fantasy, Mystery", "PG (Parental Guidance)", 8.1, 2011, 850000, &L);
    input("cinderella", "Fantasy, Romance, Drama", "PG (Parental Guidance)", 6.9, 2015, 175000, &L);
    input("knives out", "Mystery", "PG-13 (Parental Guidance Strongly Cautioned)", 7.9, 2019, 593000, &L);
    input("sherlock holmes", "Mystery", "PG-13 (Parental Guidance Strongly Cautioned)", 7.6, 2009, 623000, &L);

    char nama[50], gnr, back, menu, show;
    int z, thn, umr, umur, n, i, plh_genre[11], y, x, a;

    //membuat array yang akan disorting
    n=countElement(L);
    temporary film[n];
    //memasukkan nilai list kedalam array
    array_pass(n,&film,&L);

    //Menu Utama
    mainmenu:
    system("CLS");
    printf("=========================================================");
    printf("\nSELAMAT DATANG DI PROGRAM PENCARIAN DAN REKOMENDASI FILM");
    printf("\n=========================================================");
    printf("\n1. Pencarian Film");
    printf("\n2. Rekomendasi Film");
    printf("\n3. Exit");
    printf("\n=========================================================");
    printf("\nPilih Menu: ");
    scanf("%s", &menu);

    //Case setiap menu
    switch(menu){
        case '1':
            case1:
            system("CLS");
            printf("1. Cari film berdasarkan Nama");
            printf("\n2. Cari film berdasarkan Genre");
            printf("\n3. Cari film berdasarkan Rating");
            printf("\n4. Cari film berdasarkan Tahun Rilis");
            printf("\n5. Cari film berdasarkan Kategori Usia");
            printf("\n6. Cari film berdasarkan Views");
            printf("\n7. Back");
            printf("\nPilih menu: ");
            scanf("%s", &show);
            switch(show)
            {
                    case '1':
                        casenama:
                        system("CLS");
                        printf("1. Cari Berdasarkan Nama");
                        printf("\n2. Tampilkan berdasarkan nama Ascending");
                        printf("\n3. Tampilkan berdasarkan nama Descending");
                        printf("\n4. Back");
                        printf("\nPilih Menu: ");
                        scanf("%s", &show);
                            switch(show){
                                case '1':
                                    cari_nama(L);
                                    while(1){
                                        menu_back();
                                        scanf("%s", &back);
                                        if(back=='1'){
                                            loading2();
                                            goto casenama;
                                        }
                                        else if(back=='2'){
                                            loading2();
                                            goto mainmenu;
                                        }
                                        else{
                                            printf("\n  !!PERINTAH YANG ANDA MASUKKAN SALAH!!\n");
                                        }
                                    }
                                case '2':
                                    merge_sort_nama_asc(0, n-1, film, &L);
                                    printElement(L);
                                    while(1){
                                        menu_back();
                                        scanf("%s", &back);
                                        if(back=='1'){
                                            goto casenama;
                                            loading2();
                                        }
                                        else if(back=='2'){
                                            goto mainmenu;
                                            loading2();
                                        }
                                        else{
                                            printf("\n  !!PERINTAH YANG ANDA MASUKKAN SALAH!!\n");
                                        }
                                    }
                                case '3':
                                    merge_sort_nama_dsc(0, n-1, film, &L);
                                    printElement(L);
                                    while(1){
                                        menu_back();
                                        scanf("%s", &back);
                                        if(back=='1'){
                                            goto casenama;
                                            loading2();
                                        }
                                        else if(back=='2'){
                                            goto mainmenu;
                                            loading2();
                                        }
                                        else{
                                            printf("\n  !!PERINTAH YANG ANDA MASUKKAN SALAH!!\n");
                                        }
                                    }
                                case '4':
                                    loading2();
                                    goto case1;
                                default:
                                    printf("\n  !!PERINTAH YANG ANDA MASUKKAN SALAH!!\n");
                                    loading2();
                                    goto casenama;
                            }
                    case '2':
                        casegenre:
                        system("CLS");
                        menu_genre();
                        for(x=0; x<11; x++){
                            plh_genre[x]=NULL;
                        }
                        i=0;
                        pilih_genre:
                            if(i==11){
                                printf("\n  ANDA TELAH MEMILIH SEMUA GENRE YANG ADA\n");
                                loading2();
                                goto next;
                            }
                            else{
                                printf("\nPilih Menu: ");
                                scanf("%d", &plh_genre[i]);
                                if(plh_genre[i]<1 && plh_genre[i]>12){
                                    printf("\n  !!PERINTAH YANG ANDA MASUKKAN SALAH!!\n");
                                    plh_genre[i]=NULL;
                                    goto pilih_genre;
                                }
                                else if(plh_genre[i]==12){
                                    loading2();
                                    goto case1;
                                }
                                else{
                                    if(i>0){
                                         for(a=0; a<i; a++){
                                            if(plh_genre[a]==plh_genre[i]){
                                                printf("\n  !!ANDA SUDAH MEMILIH GENRE TERSEBUT!!\n");
                                                plh_genre[i]=NULL;
                                                goto pilih_genre;
                                            }
                                        }

                                    }
                                }
                                i++;
                                lagi:
                                printf("\nPilih genre lagi?(y/t) : ");
                                scanf("%s", &gnr);
                                if(gnr == 't'){
                                    loading2();
                                    goto next;
                                }
                                else if(gnr == 'y'){
                                    goto pilih_genre;
                                }
                                else{
                                    printf("\n  !!PERINTAH YANG ANDA MASUKKAN SALAH!!\n");
                                    goto lagi;
                                }
                            }
                        next:
                        system("CLS");
                        printf("1. Tampilkan Menurut Rating Ascending");
                        printf("\n2. Tampilkan Menurut Rating Descending");
                        printf("\n3. Tampilkan Menurut Views Ascending");
                        printf("\n4. Tampilkan Menurut Views Descending");
                        printf("\n5. Back");
                        printf("\nPilih menu: ");
                        scanf("%s", &show);
                            switch(show){
                                case '1':
                                    merge_sort_rtg_asc(0, n-1, film, &L);
                                    array_pass(n,&film,&L);
                                    cari_genre(plh_genre, 0, n, i, film);
                                    while(1){
                                        menu_back();
                                        scanf("%s", &back);
                                        if(back=='1'){
                                            loading2();
                                            goto next;
                                        }
                                        else if(back=='2'){
                                            loading2();
                                            goto mainmenu;
                                        }
                                        else{
                                            printf("\n  !!PERINTAH YANG ANDA MASUKKAN SALAH!!\n");
                                        }
                                    }
                                case '2':
                                    merge_sort_rtg_dsc(0, n-1, film, &L);
                                    array_pass(n,&film,&L);
                                    cari_genre(plh_genre, 0, n, i, film);
                                    while(1){
                                        menu_back();
                                        scanf("%s", &back);
                                        if(back=='1'){
                                            loading2();
                                            goto next;
                                        }
                                        else if(back=='2'){
                                            goto mainmenu;
                                            loading2();
                                        }
                                        else{
                                            printf("\n  !!PERINTAH YANG ANDA MASUKKAN SALAH!!\n");
                                        }
                                    }
                                case '3':
                                    merge_sort_view_asc(0, n-1, film, &L);
                                    array_pass(n,&film,&L);
                                    cari_genre(plh_genre, 0, n, i, film);
                                    while(1){
                                        menu_back();
                                        scanf("%s", &back);
                                        if(back=='1'){
                                            loading2();
                                            goto next;
                                        }
                                        else if(back=='2'){
                                            loading2();
                                            goto mainmenu;
                                        }
                                        else{
                                            printf("\n  !!PERINTAH YANG ANDA MASUKKAN SALAH!!\n");
                                        }
                                    }
                                case '4':
                                    merge_sort_rtg_asc(0, n-1, film, &L);
                                    array_pass(n,&film,&L);
                                    cari_genre(plh_genre, 0, n, i, film);
                                    while(1){
                                        menu_back();
                                        scanf("%s", &back);
                                        if(back=='1'){
                                            loading2();
                                            goto next;
                                        }
                                        else if(back=='2'){
                                            loading2();
                                            goto mainmenu;
                                        }
                                        else{
                                            printf("\n  !!PERINTAH YANG ANDA MASUKKAN SALAH!!\n");
                                        }
                                    }
                                case '5':
                                    loading2();
                                    goto casegenre;
                                default:
                                    printf("\n  !!PERINTAH YANG ANDA MASUKKAN SALAH!!\n");
                                    loading2();
                                    goto next;
                            }
                    case '3':
                        caserating:
                        system("CLS");
                        printf("1. Tampilkan Menurut Rating Ascending");
                        printf("\n2. Tampilkan Menurut Rating Descending");
                        printf("\n3. Back");
                        printf("\nPilih Menu: ");
                        scanf("%s", &show);
                        switch(show){
                            case '1':
                                merge_sort_rtg_asc(0, n-1, film, &L);
                                printElement(L);
                                while(1){
                                        menu_back();
                                        scanf("%s", &back);
                                        if(back=='1'){
                                            loading2();
                                            goto caserating;
                                        }
                                        else if(back=='2'){
                                            loading2();
                                            goto mainmenu;
                                        }
                                        else{
                                            printf("\n  !!PERINTAH YANG ANDA MASUKKAN SALAH!!\n");
                                        }
                                    }
                            case '2':
                                merge_sort_rtg_dsc(0, n-1, film, &L);
                                printElement(L);
                                while(1){
                                        menu_back();
                                        scanf("%s", &back);
                                        if(back=='1'){
                                            loading2();
                                            goto caserating;
                                        }
                                        else if(back=='2'){
                                            loading2();
                                            goto mainmenu;
                                        }
                                        else{
                                            printf("\n  !!PERINTAH YANG ANDA MASUKKAN SALAH!!\n");
                                        }
                                    }
                            case '3':
                                loading2();
                                goto case1;
                            default:
                                printf("\n  !!PERINTAH YANG ANDA MASUKKAN SALAH!!\n");
                                loading2();
                                goto caserating;
                        }
                    case '4':
                        casetahun:
                        system("CLS");
                        printf("\nMasukkan Tahun Rilis: ");
                        scanf("%d", &thn);
                        showtahun:
                        system("CLS");
                        printf("1. Tampilkan Menurut Rating Ascending");
                        printf("\n2. Tampilkan Menurut Rating Descending");
                        printf("\n3. Tampilkan Menurut Views Ascending");
                        printf("\n4. Tampilkan Menurut Views Descending");
                        printf("\n5. Back");
                        printf("\nPilih menu: ");
                        scanf("%s", &show);
                            switch(show){
                                case '1':
                                    merge_sort_rtg_asc(0, n-1, film, &L);
                                    cari_thn_rilis(thn, L);
                                    while(1){
                                        menu_back();
                                        scanf("%s", &back);
                                        if(back=='1'){
                                            loading2();
                                            goto casetahun;
                                        }
                                        else if(back=='2'){
                                            loading2();
                                            goto mainmenu;
                                        }
                                        else{
                                            printf("\n  !!PERINTAH YANG ANDA MASUKKAN SALAH!!\n");
                                        }
                                    }
                                case '2':
                                    merge_sort_rtg_dsc(0, n-1, film, &L);
                                    cari_thn_rilis(thn, L);
                                    while(1){
                                        menu_back();
                                        scanf("%s", &back);
                                        if(back=='1'){
                                            loading2();
                                            goto casetahun;
                                        }
                                        else if(back=='2'){
                                            loading2();
                                            goto mainmenu;
                                        }
                                        else{
                                            printf("\n  !!PERINTAH YANG ANDA MASUKKAN SALAH!!\n");
                                        }
                                    }
                                case '3':
                                    merge_sort_view_asc(0, n-1, film, &L);
                                    cari_thn_rilis(thn, L);
                                    while(1){
                                        menu_back();
                                        scanf("%s", &back);
                                        if(back=='1'){
                                            loading2();
                                            goto casetahun;
                                        }
                                        else if(back=='2'){
                                            loading2();
                                            goto mainmenu;
                                        }
                                        else{
                                            printf("\n  !!PERINTAH YANG ANDA MASUKKAN SALAH!!\n");
                                        }
                                    }
                                case '4':
                                    merge_sort_view_dsc(0, n-1, film, &L);
                                    cari_thn_rilis(thn, L);
                                    while(1){
                                        menu_back();
                                        scanf("%s", &back);
                                        if(back=='1'){
                                            loading2();
                                            goto casetahun;
                                        }
                                        else if(back=='2'){
                                            loading2();
                                            goto mainmenu;
                                        }
                                        else{
                                            printf("\n  !!PERINTAH YANG ANDA MASUKKAN SALAH!!\n");
                                        }
                                    }
                                case '5':
                                    loading2();
                                    goto case1;
                                default:
                                    printf("\n  !!PERINTAH YANG ANDA MASUKKAN SALAH!!\n");
                                    loading2();
                                    goto showtahun;
                            }
                    case '5':
                        casekategori:
                        system("CLS");
                        printf("1. G (General)");
                        printf("\n2. PG (Parental Guidance)");
                        printf("\n3. PG13 (Parental Guidance Strongly Cautioned)");
                        printf("\n4. R (Restricted)");
                        printf("\n5. NC17 (Adults Only)");
                        printf("\n6. Back");
                        printf("\nPilih Menu: ");
                        scanf("%s", &show);
                        switch(show){
                        case '1':
                            cari_kategori('1', L);
                            while(1){
                                menu_back();
                                scanf("%s", &back);
                                if(back=='1'){
                                    loading2();
                                    goto casekategori;
                                }
                                else if(back=='2'){
                                    loading2();
                                    goto mainmenu;
                                }
                                else{
                                    printf("\n  !!PERINTAH YANG ANDA MASUKKAN SALAH!!\n");
                                }
                            }
                        case '2':
                            cari_kategori('2', L);
                            while(1){
                                menu_back();
                                scanf("%s", &back);
                                if(back=='1'){
                                    loading2();
                                    goto casekategori;
                                }
                                else if(back=='2'){
                                    loading2();
                                    goto mainmenu;
                                }
                                else{
                                    printf("\n  !!PERINTAH YANG ANDA MASUKKAN SALAH!!\n");
                                }
                            }
                        case '3':
                            cari_kategori('3', L);
                            while(1){
                                menu_back();
                                scanf("%s", &back);
                                if(back=='1'){
                                    loading2();
                                    goto casekategori;
                                }
                                else if(back=='2'){
                                    loading2();
                                    goto mainmenu;
                                }
                                else{
                                    printf("\n  !!PERINTAH YANG ANDA MASUKKAN SALAH!!\n");
                                }
                            }
                        case '4':
                            cari_kategori('4', L);
                            while(1){
                                menu_back();
                                scanf("%s", &back);
                                if(back=='1'){
                                    loading2();
                                    goto casekategori;
                                }
                                else if(back=='2'){
                                    loading2();
                                    goto mainmenu;
                                }
                                else{
                                    printf("\n  !!PERINTAH YANG ANDA MASUKKAN SALAH!!\n");
                                }
                            }
                        case '5':
                            cari_kategori('5', L);
                            while(1){
                                menu_back();
                                scanf("%s", &back);
                                if(back=='1'){
                                    loading2();
                                    goto casekategori;
                                }
                                else if(back=='2'){
                                    loading2();
                                    goto mainmenu;
                                }
                                else{
                                    printf("\n  !!PERINTAH YANG ANDA MASUKKAN SALAH!!\n");
                                }
                            }
                        case '6':
                            loading2();
                            goto case1;
                        default:
                            printf("\n  !!PERINTAH YANG ANDA MASUKKAN SALAH!!\n");
                            loading2();
                            goto casekategori;
                        }
                    case '6':
                        caseviews:
                        system("CLS");
                        printf("1. Tampilkan Menurut Views Ascending");
                        printf("\n2. Tampilkan Menurut Views Descending");
                        printf("\n3. Back");
                        printf("\nPilih Menu: ");
                        scanf("%s", &show);
                        switch(show){
                            case '1':
                                merge_sort_view_asc(0, n-1, film, &L);
                                printElement(L);
                                while(1){
                                    menu_back();
                                    scanf("%s", &back);
                                    if(back=='1'){
                                        loading2();
                                        goto caseviews;
                                    }
                                    else if(back=='2'){
                                        loading2();
                                        goto mainmenu;
                                    }
                                    else{
                                        printf("\n  !!PERINTAH YANG ANDA MASUKKAN SALAH!!\n");
                                    }
                                }
                            case '2':
                                merge_sort_view_dsc(0, n-1, film, &L);
                                printElement(L);
                                while(1){
                                    menu_back();
                                    scanf("%s", &back);
                                    if(back=='1'){
                                        loading2();
                                        goto caseviews;
                                    }
                                    else if(back=='2'){
                                        loading2();
                                        goto mainmenu;
                                    }
                                    else{
                                        printf("\n  !!PERINTAH YANG ANDA MASUKKAN SALAH!!\n");
                                    }
                                }

                            case '3':
                                loading2();
                                goto case1;

                            default:
                                printf("\n  !!PERINTAH YANG ANDA MASUKKAN SALAH!!\n");
                                loading2();
                                goto caseviews;
                        }

                    case '7':
                        loading2();
                        goto mainmenu;

                    default:
                        printf("\n  !!PERINTAH YANG ANDA MASUKKAN SALAH!!\n");
                        loading2();
                        goto case1;
            }
        case '2':
            case2:
            system("CLS");
            menu_genre();
            for(x=0; x<11; x++){
                plh_genre[x]=NULL;
            }
            i=0;
            rek_genre:
            if(i==11){
                printf("\nAnda telah memilih semua genre yang ada\n");
                loading2();
                goto lanjut;
            }
            else{
                printf("\nPilih Menu: ");
                scanf("%d", &plh_genre[i]);
                if(plh_genre[i]<1 && plh_genre[i]>12){
                    printf("\n  !!PERINTAH YANG ANDA MASUKKAN SALAH!!\n");
                    plh_genre[i]=NULL;
                    goto rek_genre;
                }
                else if(plh_genre[i]==12){
                    loading2();
                    goto mainmenu;
                }
                else{
                    if(i>0){
                        for(a=0; a<i; a++){
                            if(plh_genre[a]==plh_genre[i]){
                                printf("\n  !!ANDA SUDAH MEMILIH GENRE TERSEBUT\n");
                                plh_genre[i]=NULL;
                                goto rek_genre;
                            }
                        }
                    }
                }
                i++;
                lagi2:
                printf("\nPilih genre lagi?(y/t) : ");
                scanf("%s", &gnr);
                if(gnr == 't'){
                    loading2();
                    goto lanjut;
                }
                else if(gnr == 'y'){
                    goto rek_genre;
                }
                else{
                    printf("\n  !!PERINTAH YANG ANDA MASUKKAN SALAH!!\n");
                    goto lagi2;
                }
            }
            lanjut:
            system("CLS");
            printf("Masukkan umur:");
            scanf("%d", &umur);
            lanjut2:
            system("CLS");
            printf("1. Tampilkan Berdasarkan Rating");
            printf("\n2. Tampilkan Berdasarkan Views");
            printf("\n3. Back");
            printf("\nPilih Menu: ");
            scanf("%s", &show);
                switch(show){
                    case '1':
                        merge_sort_rtg_dsc(0, n-1, film, &L);
                        array_pass(n,&film,&L);
                        cari_usia(umur, &film, n, &y);
                        cari_genre(plh_genre, 0, y, i, film);
                        while(1){
                            menu_back();
                            scanf("%s", &back);
                            if(back=='1'){
                                loading2();
                                goto lanjut2;
                            }
                            else if(back=='2'){
                                loading2();
                                goto mainmenu;
                            }
                            else{
                                printf("\n  !!PERINTAH YANG ANDA MASUKKAN SALAH!!\n");
                            }
                        }
                    case '2':
                        merge_sort_view_dsc(0, n-1, film, &L);
                        array_pass(n,&film,&L);
                        cari_usia(umur, &film, n, &y);
                        cari_genre(plh_genre, 0, y, i, film);
                        while(1){
                            menu_back();
                            scanf("%s", &back);
                            if(back=='1'){
                                loading2();
                                goto lanjut2;
                            }
                            else if(back=='2'){
                                loading2();
                                goto mainmenu;
                            }
                            else{
                                printf("\n  !!PERINTAH YANG ANDA MASUKKAN SALAH!!\n");
                            }
                        }
                    case '3':
                        loading2();
                        goto case2;
                    default:
                        printf("\n  !!PERINTAH YANG ANDA MASUKKAN SALAH!!\n");
                        loading2();
                        goto lanjut2;
                }
        case '3':
            break;
        default:
            printf("\n  !!PERINTAH YANG ANDA MASUKKAN SALAH!!\n");
            loading2();
            goto mainmenu;
    }
return 0;
}


