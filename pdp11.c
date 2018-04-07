#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

typedef unsigned char byte;
typedef unsigned short int word;
typedef word adr;

word mem [64 * 1024];

# define LO(x) ((x) & 0xFF)
# define HI(x) (((x) >> 8) & 0xFF)

byte b_read (adr a); // читает из "старой памяти" mem байт с "адресом" a.
void b_write (adr a, byte val); // пишет значение val в "старую память" mem в байт с "адресом" a.
word w_read (adr a); // читает из "старой памяти" mem слово с "адресом" a.
void w_write (adr a, word val); // пишет значение val в "старую память" mem в слово с "адресом" a.
void load_file( );

void do_halt()
{
	printf("THE END!!!!");
	exit(0);
}

void do_mov()
{
	printf("THAT'S MOVE");
	//exit(0);
}

void do_add()
{
	printf("THAT'S ADD");
	//exit(0);
}

void do_unknown()
{
	printf("WHAT is it?");
	//exit(0);
}

struct Command
{
	word opcode;
	word mask;
	char* name;
	void (*func)();
}commands[] = {
	{0, 0xFFFF, "halt", do_halt},
	{0010000, 0170000, "mov", do_mov},
	{0060000, 0170000, "add", do_add},
	{0070000, 0170000,"unknown", do_unknown },
};

void run(adr pc0)
{
	adr pc = pc0;
	int i;
	while(1)
	{
		word w = w_read(pc);
		printf("%06o : %06o", pc, w);
		pc += 2;
		for(i = 0; i < 4;i++)
		{
			struct Command cmd = commands[i];
			if((w & cmd.mask) ==  cmd.opcode)
			{
				printf(" %s ", cmd.name);
				cmd.func();
			}
		}
		printf("\n");
	}

}

byte b_read(adr a)
{
	byte res;
	if((a % 2) == 0)
		res = (LO(mem[a]));
	else if((a % 2) != 0)
		res = (HI(mem[a - 1]));
		a -= 1;
	return res;	
}

word w_read(adr a)
{
	return mem[a];
}

void w_write(adr a, word val)
{
	mem[a] = val;
}

void b_write(adr a, byte val)
{
	word b =0;
	if((a % 2) == 0)
		mem[a] |= val;
	else if((a % 2) != 0)
		b = val;
		b <<= 8;
		mem[a - 1] = mem[a-1] | b;
}

void load_file(char* FileName)
{
	int size = strlen(FileName);
	if(size == 0)
		exit(0);

	unsigned int a, b, val;
	int i = 0;
	FILE * f;
	f = fopen(FileName, "r");
	if (f == NULL) {
		perror(FileName);
		exit(1);
	}
	while(fscanf(f, "%x%x", &a, &b) == 2)
	{
		for(i = a; i < (a + b); i++)
		{
			fscanf(f, "%x", &val);
			b_write(i, val);
		}
	}
	fclose(f);
}

void mem_dump(adr start, word n)
{
	assert (start % 2 == 0);
	int i = 0;
	for(i = 0; i < n; i = i + 2)
	{
		printf("%06o : %06o\n", (start + i), mem[start + i]);
	}
}

int main(int argc, char* argv[])
{
	//char* FileName = (char*)calloc(100, sizeof(char))
	load_file(argv[1]);//         load_file(argv[1]);
	//mem_dump(0x40, 8);
	run(0x40);
	return 0;
}

