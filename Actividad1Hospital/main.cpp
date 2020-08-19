#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 5

 struct paciente {
    char nombre[30];
    char apellido[30];
    char telefono[30];
    int id;
    int cama_id;
};


typedef void (*opcion_t) (int);

void agregar(int); //void append();
void buscar(int); //void buscar();
void listaPacientes(int); //void listaPacientes();
void alta(int); //void alta();
void vaciarMemoria(int);

char fname[]={"mydb.dat"};

int main(int argc, const char * argv[]) {
	
	while(1){
		
	
    
    opcion_t * menu = (opcion_t *) malloc( N * sizeof(opcion_t));
    
    *menu = agregar;
    *(menu+1) = buscar;//buscar por nombre
    *(menu+2) = listaPacientes;
    *(menu+3) = alta;
    *(menu+4) = vaciarMemoria;
    
	//*(menu+4) = salir;
    
    
    printf("--- Opciones --- \n1-AGREGAR\n2-BUSCAR\n3-LISTA DE PACIENTES\n4-ALTA\n5-VACIAR MEMORIA\nEscoge tu opcion: ");
    
    int opcion;
    
    scanf("%d", &opcion);
    

    (*(menu+opcion-1))(opcion);
    
    
}
    return 0;
	}
	
void agregar(int opcion)
{
FILE *fp;
struct paciente p1;

fp=fopen(fname,"ab");

printf("\nAsignar ID paciente:");
scanf("%d",&p1.id);
printf("\nIngresa nombre:");
scanf("%s",&p1.nombre);
printf("\nIngresa apellido:");
scanf("%s",&p1.apellido);
printf("\nIngresa telefono:");
scanf("%s",&p1.telefono);
printf("\nAsignar cama:");
scanf("%d",&p1.cama_id);
fwrite(&p1,sizeof(p1),1,fp);

fclose(fp);
}
void alta(int opcion)
{
FILE *fp,*fp1;
struct paciente p,p1;
int id,found=0,count=0;

fp=fopen(fname,"rb");
fp1=fopen("temp.dat","wb");

printf("\nIngresa el id de la cama que quieres dar de alta:");
scanf("%d",&id);

while(1)
{
fread(&p,sizeof(p),1,fp);

if(feof(fp))
{
break;
}
if(p.id==id)
{
found=1;
}
else
{
fwrite(&p,sizeof(p),1,fp1);
}
}
fclose(fp);
fclose(fp1);

if(found==0)
{
printf("Sorry No Record Found\n\n");
}
else
{
fp=fopen(fname,"wb");
fp1=fopen("temp.dat","rb");

while(1)
{
fread(&p,sizeof(p),1,fp1);

if(feof(fp1))
{
break;
}
fwrite(&p,sizeof(p),1,fp);
}
}
fclose(fp);
fclose(fp1);
}

void buscar(int opcion)
{
FILE *fp;
struct paciente p;
int found=0;
char nombre[30];

fp=fopen(fname,"rb");

printf("\nIngresa el nombre del paciente:");
scanf("%s",&nombre);

while(1)
{
fread(&p,sizeof(p),1,fp);

if(feof(fp))
{
break;
}
if(strcmp(nombre,p.nombre)==0)
{
printf("\n========================================================\n\n");
printf("\t\t Detalles %d\n\n",p.id);
printf("========================================================\n\n");

printf("Name\tid\n\n");

printf("%s\t",p.nombre);
printf("%d\t\n\n",p.cama_id);

printf("========================================================\n\n");

}
}
if(found==0)
{
	printf("\nNO EXISTE");
printf("\nSorry No Record Found");
}
fclose(fp);
}
void listaPacientes(int opcion)
{
FILE *fp;
struct paciente p;

fp=fopen(fname,"rb");

printf("\n========================================================\n\n");
printf("\t\t Lista de pacientes\n\n");
printf("========================================================\n\n");

printf("Nombre\tApellido\tTelefono\tCama_ID\n");

while(1)
{
fread(&p,sizeof(p),1,fp);

if(feof(fp))
{
break;
}
printf("%s\t\t%s\t\t%s\t\t%d\n", p.nombre, p.apellido, p.telefono, p.cama_id);


}
printf("========================================================\n\n");

fclose(fp);
}
void vaciarMemoria(int opcion)
{
	FILE *fp,*fp1;
struct paciente p;

char nombre[30];
char val[20];

printf("\nQuieres una copía de esta lista ?  (Y/N):");
scanf("%s",val);

if(strcmp(val,"Y")==0)
{

printf("\nEnter the New File Name:");
fflush(stdin);
scanf("%[^\n]",nombre);

fp=fopen(nombre,"wb");
fp1=fopen(fname,"rb");

while(1)
{
fread(&p,sizeof(p),1,fp1);

if(feof(fp1))
{
break;
}
fwrite(&p,sizeof(p),1,fp);
}

fclose(fp);
fclose(fp1);

remove(fname);

strcpy(fname,nombre);
}
else
{
remove(fname);
}
}


