#include <stdio.h>
#include <time.h>
#include <string.h>

typedef struct {
	char contents[100];
   	int length;
	int arah;
	int xAwal;
	int yAwal;
	int xAkhir;
	int yAkhir;
} word;



//KAMUS FILE//
char currentChar;
static FILE * tapeFile;
char puzzle[100][100];
word kata[100];

#define True 1
#define False 0
#define newLine '\n'

void adv(){
	/* KAMUS LOKAL */
	static int * retval;
	
	/* ALGORITMA */
	retval = fscanf(tapeFile,"%c",&currentChar);
}

int startFile(char *fileName){

	/* Algoritma */
	tapeFile = fopen(fileName,"r");
	if (tapeFile == NULL){
        printf("Error: could not open file\n");
		return False;
    }
    else{
		adv();
		return True;
	}
}


void readMatrix(int *row,int *col){
    /* KAMUS LOKAL */
    int i,j;
   
	/* ALGORITMA */
	i = 0;
    while (currentChar != newLine){
        j = 0;
        while (currentChar != newLine){
            puzzle[i][j] = currentChar;
            j++;
            adv();
			if (currentChar == ' ') adv();
        }
        adv();
        i++;
    }
	*row = i;
	*col = j;
}

void readKata(word solusi[100], int *banyakKata){
	/* KAMUS LOKAL */
	int i,j;
	
	/* ALGORITMA */
	adv();
	i = 0;
	while ((!feof(tapeFile))){
		j=0;
		while (currentChar != newLine && (!feof(tapeFile))){
			solusi[i].contents[j] = currentChar;
			adv();
			j++;
		}
		solusi[i].length=j;
		i++;
		adv();
	}
	*banyakKata = i;
}

void tulisKata(word sample){
	/* KAMUS LOKAL */
	int i;

	/* ALGORITMA */
	for (i = 0; i< sample.length; i++){
		printf("%c", sample.contents[i]);
	}
	printf("\n");
}


void tulisMatriks(word sample,int row, int col){
	/* KAMUS LOKAL */
	int i,j,k;
	
	/* ALGORITMA */
	tulisKata(sample);
	
	//vertikal-atas
	if (sample.arah == 1){
		k = sample.length-1;
		for (i = 0; i< row; i++){
			for ( j = 0; j< col; j++){
				if (j == sample.xAwal && i == sample.yAkhir){
					printf("%c ", sample.contents[k]);
					k--;
					if (k >=0) sample.yAkhir++;
				}
				else{
					printf("- ");
				}
			}
			printf("\n");
		}
	}

	//menyamping  atas-kanan
	else if (sample.arah == 2){
		k = sample.length-1;
		for (i = 0; i< row; i++){
			for ( j = 0; j< col; j++){
				if (j == sample.xAkhir && i == sample.yAkhir){
					printf("%c ", sample.contents[k]);
					
					k--;
					if (k >=0){
						sample.yAkhir++;
						sample.xAkhir--;
					}
					
				}
				else{
					printf("- ");
				}
			}
			printf("\n");
		}
	}

	//mendatar kanan
	else if (sample.arah == 3){
		k = 0;
		for (i = 0; i< row; i++){
			for ( j =0; j< col; j++){
				if (j == sample.xAwal && i == sample.yAwal){
					printf("%c ", sample.contents[k]);
					k++;
					if (k < sample.length){
						sample.xAwal++;
					}
				}
				else{
					printf("- ");
				}
			}
			printf("\n");
		}
			
	}
	
	//menyamping kanan-bawah
	else if (sample.arah == 4){
		k = 0;
		for (i = 0; i< row; i++){
			for ( j =0; j< col; j++){
				if (j == sample.xAwal && i == sample.yAwal){
					printf("%c ", sample.contents[k]);
					k++;
					if (k < sample.length){
						sample.xAwal++;
						sample.yAwal++;
					}
				}
				else{
					printf("- ");
				}
			}
			printf("\n");
		}
	}

	//vertikal bawah
	else if (sample.arah == 5){
		k = 0;
		for (i = 0; i< row; i++){
			for ( j =0; j< col; j++){
				if (j == sample.xAwal && i == sample.yAwal){
					printf("%c ", sample.contents[k]);
					k++;
					if (k < sample.length){
						sample.yAwal++;
					}
				}
				else{
					printf("- ");
				}
			}
			printf("\n");
		}
	}

	//menyamping kiri-bawah
	else if (sample.arah == 6){
		k = 0;
		for (i = 0; i< row; i++){
			for ( j =0; j< col; j++){
				if (j == sample.xAwal && i == sample.yAwal){
					printf("%c ", sample.contents[k]);
					k++;
					if (k < sample.length){
						sample.xAwal--;
						sample.yAwal++;
					}
				}
				else{
					printf("- ");
				}
			}
			printf("\n");
		}
	}

	//mendatar kiri
	else if (sample.arah == 7){
		k = sample.length-1;
		for (i = 0; i< row; i++){
			for ( j =0; j< col; j++){
				if (j == sample.xAkhir && i == sample.yAwal){
					printf("%c ", sample.contents[k]);
					k--;
					if (k >=0 ){
						sample.xAkhir++;
					}
				}
				else{
					printf("- ");
				}
			}
			printf("\n");
		}
	}

	//menyamping atas-kiri
	else if (sample.arah == 8){
		k = sample.length-1;
		for (i = 0; i< row; i++){
			for ( j =0; j< col; j++){
				if (j == sample.xAkhir && i == sample.yAkhir){
					printf("%c ", sample.contents[k]);
					k--;
					if (k >=0 ){
						sample.xAkhir++;
						sample.yAkhir++;
					}
				}
				else{
					printf("- ");
				}
			}
			printf("\n");
		}
	}
}


int solver(word sample, int row, int col){
	/* KAMUS LOKAL */
	int i, j, k,ii,jj,found,temp,counter;
	
	/* ALGORITMA */
	//pengecekan searah jarum jam dimulai dari atas-kanan 
	found = False;
	i = 0;
	counter = 0;
	while ((!found) && (i < row || j <col)){
		j = 0;
		
		while (j<col && !found){
			temp = sample.contents[0] == puzzle[i][j];
			counter++;
			if (temp){
				
				sample.xAwal = j;
				sample.yAwal = i;
				
				k = 1;
				if (i>=sample.length-1){
					ii = i-1;
					while (temp && !found){
						counter++;
						temp = (sample.contents[k] == puzzle[ii][j]);
						k++;
						if (k == sample.length && temp){
								found = True;
								sample.xAkhir = j;
								sample.yAkhir = ii;
								sample.arah = 1;
						}
						ii--;
					}
					
					//menyamping atas-kanan
					if (!temp){			//apabila pencarian menurun sudah dilakukan dan gagal mendapatkan solusi
						ii = i-1;
						k = 1;

						if (j<= col -sample.length-1){
							temp = True;
							// printf("hello %d", j);
							jj = j+1;

							while (temp && !found){
								counter++;
								temp = (sample.contents[k] == puzzle[ii][jj]);
								k++;
								if (k == sample.length && temp){
									found = True;
									sample.xAkhir = jj;
									sample.yAkhir = ii;
									sample.arah = 2;
								}
								ii--;
								jj++;
							}
						}
					}

					//menyamping atas-kiri
					if (!temp){			//apabila pencarian menurun sudah dilakukan dan gagal mendapatkan solusi
						ii = i-1;
						k = 1;
						
						if (j>= sample.length-1){
							
							temp = True;
							jj = j-1;
							
							while (temp && !found){
								counter++;
								temp = (sample.contents[k] == puzzle[ii][jj]);
								k++;
								
								if (k == sample.length && temp){
									found = True;
									sample.xAkhir = jj;
									sample.yAkhir = ii;
									sample.arah = 8;
								}
								ii--;
								jj--;
							}
						}
					}
					
				}
				
				//cek datar kanan
				if (!found && (j<= col -sample.length))
				{	
					jj = j+1;	
					k = 1;
					temp = True;
					while (temp && !found){	
						counter++;
						temp = (sample.contents[k] == puzzle[i][jj]);
						k++;
						
						if (k == sample.length && temp){
							found = True;
							sample.xAkhir = jj;
							sample.yAkhir = i;
							sample.arah = 3;
						}
						jj++;
					}
					
				}	
				
				
				//cek datar kiri
				if (!found && (j>=sample.length-1))
				{	
					temp = True;
					jj = j-1;
					k = 1;	
					
					while (temp && !found){	
						counter++;
						temp = (sample.contents[k] == puzzle[i][jj]);
						k++;
						
						if (k == sample.length && temp){
							found = True;
							sample.xAkhir = jj;
							sample.yAkhir = i;
							sample.arah = 7;
						}
						jj--;
					}
					
				}

				//cek menurun-bawah, menyamping bawah-kanan, menyamping bawah-kiri
				if (!found && i<=row - sample.length){
					ii = i+1;
					k = 1;
					temp = True;
					//menurun-bawah
					while (temp && !found){
						counter++;
						temp = (sample.contents[k] == puzzle[ii][j]);
						k++;
						
						if (k == sample.length && temp){
								found = True;
								sample.xAkhir = j;
								sample.yAkhir = ii;
								sample.arah = 5;
						}
						ii++;
					}
					
					//menyamping bawah-kanan
					if (!temp){			//apabila pencarian menurun sudah dilakukan dan gagal mendapatkan solusi
						ii = i+1;
						k = 1;
						if (j<= col -sample.length-1){
							temp = True;
							jj = j+1;
						
							while (temp && !found){
								counter++;
								temp = (sample.contents[k] == puzzle[ii][jj]);
								k++;
								
								if (k == sample.length && temp){
									found = True;
									sample.xAkhir = jj;
									sample.yAkhir = ii;
									sample.arah = 4;
								}
								ii++;
								jj++;
							}
						}
					}

					//menyamping bawah-kiri
					if (!temp){			//apabila pencarian menurun sudah dilakukan dan gagal mendapatkan solusi
						
						ii = i+1;
						k = 1;
						
						if (j>= sample.length-1){
							
							temp = True;
							jj = j-1;
							
							while (temp && !found){
								counter++;
								temp = (sample.contents[k] == puzzle[ii][jj]);
								k++;
								
								if (k == sample.length && temp){
									found = True;
									sample.xAkhir = jj;
									sample.yAkhir = ii;
									sample.arah = 6;
								}
								ii++;
								jj--;
							}
						}
					}
				}
			}
			j++;
		}
		i++;
	
	}
	if (found){
		tulisMatriks(sample,row,col);
	}
	else{
		printf("Kata tidak ditemukan\n");
	}
	printf("Banyak perbandingan huruf : %d\n", counter);
	return counter;
}




int main(){
	/* KAMUS  */
	int i,j;
    char filename[50]; 
     
	int row,col;
	int banyakKata ;
	int sumPerbandingan;
    double cpu_time_used;
	clock_t start, end;
	
	/* ALGORITMA */
	
	scanf("%s", filename);
	char dir[] = "../test/";
	strcat(dir,filename);
	printf("%s", dir);
	
    if (startFile(dir)){
		readMatrix(&row,&col);
		
		readKata(kata, &banyakKata);
		
    	start = clock();
		sumPerbandingan = 0;
		for ( i = 0; i <banyakKata; i++){
			sumPerbandingan += solver(kata[i], row,col);
			printf("\n\n");
		}
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("Waktu Eksekusi program : %lf (s)\n", cpu_time_used);
		printf("Total Perbandingan : %d\n", sumPerbandingan);
			
	}
	else{
		// do nothing
	}
	
	
	
}