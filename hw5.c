#include<stdio.h>
#include<stdlib.h>


unsigned long long int pascal_valued_of(int row, int column);
unsigned long long int p_v[64][64] = {0};
void print_pascall_triangle(int row);
void xpm(int row);


int main(int argc, char **argv)
{
    int row, column, mode;
    if (argc != 4)
    {
        printf("invalid call.\n'%s' takes 3 argument [row, column, mode].\n",argv[0]);
        exit(1);
    }
    row = atoi(argv[1]) - 1;
    column = atoi(argv[2]) - 1;
    mode = atoi(argv[3]);
    if ( !(row >= 0 && row <= 63) || !(column >= 0 && column <= row) || !(mode >= 0 && mode <= 2) )
    {
        printf("Input (%d, %d, %d) is wrong. row, col must be in 1...64, col <= row and mode 0, 1 or 2.\n", row + 1, column + 1, mode);
        exit(2);
    }
    if (mode == 0)
    {
        printf("%llu\n", pascal_valued_of(row, column));
    }else if (mode == 1)
    {
        print_pascall_triangle(row);
    }else{
        xpm(row);
    }

    return 0;
}


unsigned long long int pascal_valued_of(int row, int column)
{
    if (column == 0 || row == column )
    {
        return 1;
    }
    if (p_v[row][column] != 0)
    {
       return p_v[row][column];
    }
    p_v[row][column] = pascal_valued_of(row - 1, column - 1) + pascal_valued_of(row - 1, column);
    return p_v[row][column]; 
}


void print_pascall_triangle(int row)
{
    int  digits = 0;
    long long int bigest_number;
    bigest_number = pascal_valued_of(row, (row) / 2);
        while (bigest_number != 0)
        {
            digits++;
            bigest_number /= 10;
        }
        if (digits % 2 == 0 ) digits++;
    int i, j, k;
    for (i = 0; i <= row; i++)
    {
        for (j = 0; j < row - i; j++)
        {
            for (k = 0; k < digits/2 + 1; k++)
            {
                printf(" ");
            }
        } 
        for (j = 0; j <= i; j++)
        {
            printf("%0*llu",digits,pascal_valued_of(i,j));
            if (i != j) printf(" ");
        }
        printf("\n");
    }
    return;
}


void xpm(int row)
{
    row++;
    char file_name[14];
    int i, column, c, k, h, y,j;
    sprintf(file_name, "pascal_%d.xpm",row);
    FILE *file;
    file = fopen(("%s",file_name),"w");
    if (file == (FILE *) NULL)
    {
        printf("can not open file");
        exit(1);
    }
    fprintf(file,"/* XPM */\nstatic char * XFACE[] = {\n\"%d %d %d %d\",\n\"b c #000000\",\n\"e c #0000ff\",\n",row * 10, row * 10, 2, 1);
    for (i = 1; i <= row; i++){
        for ( c = 0; c < 10; c++){
            fprintf(file,"\"");
            for (k = 0; k < ((row * 5) - (i * 5)) ; k++){
                fprintf(file,"b");
            }
            for (column = 1; column <= i; column++){
               for (h = 0; h < 10; h++){
                   if (pascal_valued_of(i - 1,column - 1) % 2 == 1){
                       fprintf(file,"e");
                   }else{
                       fprintf(file,"b");
                   }
               }
            }
            for (k = 0; k < ((row * 5) - (i * 5)) ; k++){
                fprintf(file,"b");
            }
            if (i == row && c == 9){
                fprintf(file,"\"\n");
            }else{
                fprintf(file,"\",\n");
            }
        }
    }
    fprintf(file,"};\n");
    fclose(file);

    return;
}
