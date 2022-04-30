#include<stdio.h>

/* Our structure */
struct rec
{
	int x,y,z;
};

int main()
{
	int counter;
	FILE *ptr_myfile;
	struct rec my_record;
	struct rec reading;

	ptr_myfile=fopen("test.bin","r+b");
	if (!ptr_myfile)
	{
		printf("Unable to open file!");
		return 1;
	}
	for ( counter=1; counter <= 10; counter++)
	{
		my_record.x= counter;
		fwrite(&my_record, sizeof(struct rec), 1, ptr_myfile);
	}
	fseek(ptr_myfile, sizeof(struct rec), SEEK_END);
	rewind(ptr_myfile);

	for ( counter=1; counter <= 10; counter++)
	{
		fread(&reading,sizeof(struct rec),1,ptr_myfile);
		printf("%d\n",reading.x);
	}
	fclose(ptr_myfile);
	return 0;
}
