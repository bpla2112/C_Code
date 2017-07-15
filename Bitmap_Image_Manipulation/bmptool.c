/*
Author: Bernardo Pla
PID:3885008
COP 4338 Section U05
I affirm that this program is entirely my own work
and none of it is the work of any other person.
<Bernardo Pla>
*/

/*
This program performs operations on a BMP image.
These operations include: enlarge, flip, rotate etc
*/

#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <errno.h>

//constants
#define LOG 1
#define DEFAULT_OFFSET 1078

//structs
typedef struct
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
} pixel;

typedef struct
{
    unsigned short padding;
    unsigned short bfType;
    unsigned int bfSize;
    unsigned short bfReserved1;
    unsigned short bfReserved2;
    unsigned int bfOffBits;
} BITMAPFILEHEADER;

typedef struct
{
    unsigned int biSize;
    int biWidth;
    int biHeight;
    unsigned short biPlanes;
    unsigned short biBitCount;
    unsigned int biCompression;
    unsigned int biSizeImage;
    unsigned int biXPelsPerMeter;
    unsigned int biYPelsPerMeter;
    unsigned int biClrUsed;
    unsigned int biClrImportant;
} BITMAPINFOHEADER;


//function declaration
int readFile (char *filename, int *rows, int *cols, pixel** image);
int readHeader(int fd, int *rows, int *cols, unsigned int *start);
int readBits (int fd, pixel *image, int rows, int cols, unsigned int start);
int writeFile (char *filename, int rows, int cols, pixel *image);
int writeHeader(int fd, unsigned int rows, unsigned int cols, unsigned int start);
int writeBits(int fd, int rows, int cols, pixel *image, unsigned int start);
int flippic(pixel *origin, pixel **edited, int row, int column);
int enlarge(pixel *origin, int row, int column, int scale, pixel **edited, int *edrows, int *edcolumn);
int rotate (pixel *original, pixel **newImage, int rotation, int rows, int cols);
void run(int flip, int enlarge, int rotate, char *outfile, char *infile);

int main(int argc, char *argv[])
{
    int command;
    opterr = 0; //used for error checking
    int occurs[4] = {0};
    char *outfile = NULL;

    while((command = getopt(argc, argv, "s:r:fo:")) != -1)
    {
        switch (command)
        {
            case 's': //scale the BMP image
                if (occurs[0] >= 2)
                {
                    fprintf(stderr, "ERROR: Cannot pass multiple scale ops\n");
                    exit(1);
                }
                if(sscanf(optarg, "%d", &occurs[0]) != 1)
                {
                    fprintf(stderr, "ERROR: Number required\n");
                    exit(1);
                }
                if(occurs[0] < 0)
                {
                    fprintf(stderr, "ERROR: Positive number required\n");
                    exit(1);
                }
                if(LOG)
                {
                    printf("Success\n");
                }
                break;

            case 'r': //rotate image by interval of 90 degrees
                if(occurs[1] >= 2 || occurs[1] < 0)
                {
                    fprintf(stderr, "ERROR: Cannot pass multiple rotate ops\n");
                    exit(1);
                }
                if(scanf(optarg, " %d", &occurs[0]) != 1)
                {
                    fprintf(stderr, "ERROR: Number Required\n");
                    exit(1);
                }
                if(occurs[1] % 90 != 0 || occurs[1] == 0)
                {
                    fprintf(stderr, "ERROR: Multiple of 90 required");
                    exit(1);
                }
                if(LOG)
                {
                    printf("Success\n");
                }
                break;

            case 'f': //flip image
                occurs[2]++;
                if(occurs[2] >= 2)
                {
                    fprintf(stderr, "ERROR: Cannot pass multiple flip ops");
                    exit(1);
                }
                if(LOG)
                {
                    printf("Success\n");
                }
                break;

            case 'o': //output file
                occurs[3]++;
                if(occurs[3] >= 2)
                {
                    fprintf(stderr, "ERROR: Cannot pass multiple output file ops");
                    exit(1);
                }
                outfile = optarg;
                if(LOG)
                {
                    printf("Success\n");
                }
                break;

            case '?':
                if(optopt == 's' || optopt == 'r' || optopt == 'o')
                {
                    fprintf(stderr, "Unknown argument: -%c requires an argument! \n", optopt);
                }
                else if(isprint(optopt))
                {
                    fprintf(stderr, "ERROR: Invalid option");
                }
                else
                {
                    fprintf(stderr, "ERROR: Unknown Option");
                }
                exit(1);

            default:
                abort();
        }
    }

    char *infile = NULL;
    if(argv[optind])
    {
        infile = argv[optind];
    }

    run(occurs[2], occurs[0], occurs[1], outfile, infile);
    return 0; //end of main
}

int flippic(pixel *origin, pixel **edited, int row, int column)
{
    if(LOG)
    {
        printf("\t\tFlip Function\n");
    }

    if(row <= 0 || column <= 0)
    {
        return -1;
    }

    *edited = (pixel *) malloc(row * column * sizeof(pixel));
    int rindex = 0;
    int cindex = 0;

    for(rindex = 0; rindex < row; rindex++)
    {
        for (cindex = 0; cindex < column ; cindex++)
        {
            *((*edited) + ((((row - 1) - rindex) *column) + cindex)) = *(origin + rindex * column + cindex);
        }
    }
    if(LOG)
    {
        printf("\t\tFlip Complete\n");
    }
    return 0;
}

int enlarge(pixel *origin, int row, int column, int scale, pixel **edited, int *edrows, int *edcolumn)
{
    if(LOG)
    {
        printf("\t\tBegin Scaling\n");
    }

    *edrows = row * scale;
    *edcolumn = column * scale;
    int rindex = 0;
    int cindex = 0;
    int srindex = 0;
    int scindex = 0;

    *edited = (pixel *) malloc((row * column) * (scale * scale) * sizeof(int));

    for (rindex = 0; rindex < *edrows; rindex += scale)
    {
        for (cindex = 0; cindex < *edcolumn ; cindex += scale)
        {
            for (srindex = 0; srindex < scale; srindex++)
            {
                int edindex = ((rindex + scale) * (*edcolumn) + cindex);
                int oindex = ((rindex / scale) * ((*edcolumn) / scale) + (cindex / scale));
                *((*edited) + edindex) = *(origin + oindex);

                for (scindex = 0; scindex < scale; scindex++)
                {
                    *((*edited) + (edindex + scindex)) = *(origin + oindex);
                }
            }
        }
    }

    if(LOG)
    {
        printf("\t\tScaling Complete\n");
    }

    return 0;
}

int rotate (pixel *original,pixel **newImage, int rotation, int rows, int cols)
{
    if(LOG)
        

    if((rows <=0 || cols <= 0))
    {
        return -1;
    }

    *newImage = (pixel *)malloc(rows*cols*sizeof(pixel));
    pixel *tempImage = (pixel *)malloc(rows*cols*sizeof(pixel));

    int rowIndex = 0, colIndex = 0;
    int rotateAmount = rotation / 90;
    if(rotateAmount > 0) {

        if(LOG) 
        {
            
        }
        for(rowIndex = 0; rowIndex < rows; rowIndex++) 
        {
            for(colIndex = 0; colIndex < cols; colIndex++) 
            {
                int newIndex = ((rows*cols) - (rows + rows*colIndex)) + rowIndex;
                int oldIndex = rowIndex*cols + colIndex;
                *((*newImage) + newIndex) = *(original + oldIndex);
            }
        }

        while(rotateAmount > 1) 
        {

            for(rowIndex = 0; rowIndex < rows; rowIndex++) 
            {
                for(colIndex = 0; colIndex < cols; colIndex++) 
                {
                    int newIndex = ((rows*cols) - (rows + rows*colIndex)) + rowIndex;
                    int oldIndex = rowIndex*cols + colIndex;
                    *(tempImage + newIndex) = *((*newImage) + oldIndex);
                }
            }

            if(LOG)
                
            free(*newImage);
            *newImage = (pixel *)malloc(rows*cols*sizeof(pixel));

            for(rowIndex = 0; rowIndex < rows; rowIndex++) 
            {
                for(colIndex = 0; colIndex < cols; colIndex++) 
                {
                    if(rowIndex == 0) 
                    {
                        *((*newImage) + colIndex) = *(tempImage + colIndex);
                    }
                    else
                    {
                        int normalIndex = ((rowIndex)*cols + colIndex);
                        *((*newImage) + normalIndex) = *(tempImage + normalIndex);
                    }
                }
            }
            if(LOG)
                
            free(tempImage);
            tempImage = (pixel *)malloc(rows*cols*sizeof(pixel));
            rotateAmount--;
        }
    }

    return 0;
}
void run(int flip, int scale, int rotatedegree, char *outfile, char *infile)
{
    int row = 0;
    int column = 0;
    pixel *origin;
    pixel *edited;
    int morethanone = 0;

    if(infile == NULL)
    {

    }
    else
    {
        readFile(infile, &row, &column, &origin);
    }

    if(scale)
    {
        morethanone++;
        enlarge(origin, row, column, scale, &edited, &row, &column);
    }

    if(rotatedegree)
    {
        morethanone++;
        if(morethanone > 1)
        {
            origin = edited;
        }
        rotate(origin, &edited, rotatedegree, row, column);
    }

    if(flip)
    {
        morethanone++;
        if(morethanone > 1)
        {
            origin = edited;
        }
        flippic(origin, &edited, row, column);
    }

    if(outfile == NULL)
    {

    }
    else
    {
        writeFile(outfile, row, column, edited);
    }
}

int readFile (char *filename, int *rows, int *cols, pixel** image) {
    int fd;
    unsigned int start;

    if ((fd = open (filename, O_RDONLY)) < 0) {
        perror("Problem with input file");
        return -1;
    }

    readHeader (fd, rows, cols, &start);
    *image = (pixel *) malloc (sizeof(pixel) * (*rows) * (*cols));
    if (NULL == *image) {
        perror("Unable to allocate memory for image");
        close(fd);
        return -2;
    }
    readBits (fd, *image, *rows, *cols, start);

    close (fd);

    return 0;

}

int readHeader(int fd, int *rows, int *cols, unsigned int *start) {

    BITMAPFILEHEADER bmfh;
    BITMAPINFOHEADER bmih;

    read (fd, (BITMAPFILEHEADER *)((unsigned long)(&bmfh) + 2), sizeof(bmfh)-2);
    read (fd, &bmih, sizeof(bmih));

    *rows = bmih.biHeight;
    *cols = bmih.biWidth;
    *start = bmfh.bfOffBits;

    return 0;

}

int readBits (int fd, pixel *image, int rows, int cols,
              unsigned int start) {

    int row;
    char padding[3];
    int padAmount;

    padAmount = cols*sizeof(pixel)%4 ? 4-(cols*sizeof(pixel)%4) : 0;

    lseek (fd, start, SEEK_SET);

    for (row=0; row < rows; row++) {
        read (fd, image + (row*cols), cols*sizeof(pixel));
        read (fd, padding, padAmount);
    }

    return 0;
}

int writeFile (char *filename, int rows, int cols, pixel *image)
{
    int fd;
    unsigned int start = DEFAULT_OFFSET;

    if ((fd = open (filename, O_RDWR | O_CREAT | O_TRUNC, 0666)) < 0)
    {
        perror("Problem with output file");
        return -1;
    }

    writeHeader (fd, rows, cols, start);
    writeBits(fd, rows, cols, image, start);

    close (fd);
    return 0;
}

int writeHeader(int fd, unsigned int rows, unsigned int cols,
                unsigned int start)
{

    unsigned int fileSize;
    unsigned int headerSize;
    unsigned int paddedCols;

    int count;

    BITMAPFILEHEADER bmfh;
    BITMAPINFOHEADER bmih;

    memset (&bmfh, 0, sizeof(bmfh));
    memset (&bmih, 0, sizeof(bmih));

    paddedCols = ((cols/4)*4 !=cols ? ((cols+4)/4)*4 : cols);

    headerSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
    fileSize = rows*paddedCols*sizeof(pixel)+headerSize;

    bmfh.bfType = 0x4D42;
    bmfh.bfSize = fileSize;
    bmfh.bfReserved1 = 0;
    bmfh.bfReserved2 = 0;
    bmfh.bfOffBits = start;
    bmih.biSize = 40;
    bmih.biWidth  = cols;
    bmih.biHeight = rows;
    bmih.biPlanes = 1;
    bmih.biBitCount = 24;
    bmih.biCompression = 0;
    bmih.biSizeImage = 0;
    bmih.biXPelsPerMeter  = 0;
    bmih.biYPelsPerMeter = 0;
    bmih.biClrUsed = 0;
    bmih.biClrImportant = 0;

    write (fd, (BITMAPFILEHEADER *)((unsigned long)(&bmfh) + 2), sizeof(bmfh)-2);
    count = write (fd, &bmih, sizeof(bmih));

    return 0;

}

int writeBits(int fd, int rows, int cols,
              pixel *image, unsigned int start)
{
    int row;

    char padding[3];
    int padAmount;

    padAmount = cols*sizeof(pixel)%4 ? 4-(cols*sizeof(pixel)%4) : 0;

    memset(padding, 0, padAmount);

    lseek (fd, start, SEEK_SET);

    fflush (stdout);

    for (row=0; row < rows; row++) {
        write (fd, image + (row*cols), cols*sizeof(pixel));
        write (fd, padding, padAmount);
    }

    return 0;
}