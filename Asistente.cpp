#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include<conio.h>

struct fecha
{
	int dia;
	int mes;
	int anio;
};

struct Usuarios{
	char usuario[10];
	char password[32];
	char apynom[60];
};

struct veterinario
{
	char apynom[60];
	int matricula;
	int dni;
	char telefono[25];
	char password[32];
};

struct mascota
{
	char apeNom[60];
	char domicilio[60];
	int  dniDuenio;
	char localidad [60];
	fecha  fechaNacimiento;
	float   peso;
	char  telefono[25];
};

struct Turnos
{
	int matriculaVet;
	fecha fec;
	int dniDuenio;
	char detalleAt[380];
	bool estado;
};

int menu(int h);
void carga();
void cargaTurno();
void informe();
int IniciarSesion();
main()
{
	int op,b,h=0;
	do
	{
		op=menu(h);
		switch(op)
		{
			case 1:
				if(h==0)
				{
					system("cls");
					b=IniciarSesion();
					system("cls");
					h=b;
				}
				break;
			case 2:
			   if(b==1)
			   {
			   	h=1;
			   	system("cls");
			   	carga();
			   }
			   else
			   {
			   	 system("cls");
			   	 printf("PRIMERO DEBE INICIAR SESION");
			   }
				break;
			case 3:
			if(b==1)
				{
					system("cls");
					h=0;
					cargaTurno();
				}
				else
			   {
			   	 system("cls");
			   	 printf("PRIMERO DEBE INICIAR SESION");
			   }
				break;
			case 4:
			if(b==1)
			{
				system("cls");
				h=0;
				informe();
			}
			else
			   {
			   	 system("cls");
			   	 printf("PRIMERO DEBE INICIAR SESION ");
			   }		
				break;	
		}
	}while(op!=5);
}
int menu(int h)
{
	int x;

	printf("\n ============================================\n");
	if(h==0)
	{
		printf("\n 1-> Iniciar Sesion \n");
	}
	printf("2->Registrar Mascotas\n");
	printf("3->Registrar Turnos\n");
	printf("4->Listado de Atenciones por Veterinario y fecha\n");
	printf("5->Salir \n");
	printf("============================================\n");
	printf("ingrese la opcion:");
	scanf("%d",&x);
	if(x==1 || x>5)
	{
		system("cls");
		printf("ELIJA LA OPCION QUE MUESTRA EL MENU!!");
	}
	
	return x;
}

int IniciarSesion()
{
	FILE *arch;
	 Usuarios usua, us;
	int existeUsuario=0,i=0;
	char palabras[32],c;
	arch=fopen("usuarios.dat","rb");
	printf("\t INICIO DE SESION\n\n");
	printf("Usuario: ");
	_flushall();
	gets(us.usuario);
	printf("Password: ");
	_flushall();
	while((i<32 )and (c!=13))
	{
		c=getch();
		
	  	if(c==13|| i==31)
	  	{
	  		palabras[i]='\0';
	  	}
	  	else
	  	{
	  		palabras[i]=c;
	  	}
	  	printf("#");
	  	i++;
	}
	strcpy(us.password,palabras);
	
	fread(&usua,sizeof(Usuarios),1,arch);
	
	
	while(!feof(arch)){
		
		if( strcmp (us.usuario,usua.usuario)==0 && strcmp (us.password,usua.password)==0)
		{
			existeUsuario=1;
		}
		fread(&usua,sizeof(Usuarios),1,arch);
	}
	if(existeUsuario==0){
		printf("EL USUARIO NO FUE ENCONTRADO O NO EXISTE.\n\n");
		system("PAUSE");
	}
	return existeUsuario;
	fclose(arch);
}
void carga()
{
	FILE *arch;
	mascota masc;
	arch=fopen("Mascotas.dat","a+b");
	char op='S';
	while(op=='S')
	{
		printf("\n ingrese el nombre de la mascota:\n");
		_flushall();
		gets(masc.apeNom);
		strlwr(masc.apeNom);
		printf(" Ingrese el Domicilio:\n");
		_flushall();
		gets(masc.domicilio);
		strlwr(masc.domicilio);		
		printf("ingrese el DNI del duenio");
		scanf("%d",&masc.dniDuenio);
		printf("ingrese la localidad \n ");
		_flushall();
		gets(masc.localidad);
		printf("ingrese la fecha de Nacimiento:\n");
		printf("dia:  ");
		scanf("%d",&masc.fechaNacimiento.dia);
		printf("\n mes:  ");
		scanf("%d",&masc.fechaNacimiento.mes);
		printf("\n anio(4 digitos):  ");
		scanf("%04d",&masc.fechaNacimiento.anio);
		printf("ingrese el peso de la mascota:\n");
		scanf("%f",&masc.peso);
		printf("ingrese el numero de telefono del duenio:\n");
		_flushall();
		gets(masc.telefono);
		fwrite(&masc,sizeof(mascota),1,arch);
		printf("desea agregar mas S/N");
		op=getch();
		op=toupper(op);	
		system("CLS");
		
	}
	fclose(arch);
}
void cargaTurno()
{
	FILE *arch, *arch1, *arch2;
	Turnos turn;
	mascota masc;
	veterinario veter;
	arch=fopen("Turnos.dat","a+b");
	arch1=fopen("Mascotas.dat","rb");
	arch2=fopen("Veterinarios.dat","a+b");
	char nomasc[50];
	int n,b;
	b=0;
	printf("ingrese el nombre de la mascota: \n");
	_flushall();
	gets(nomasc);
	strlwr(nomasc);
	printf("ingrese la matricula del veterinario:\n");
	scanf("%d",&n);
	if(fread(&masc,sizeof(mascota),1,arch1)==NULL)
	{
		printf("no hay nada guardado en el archivo");
	}
	else
	{
			while(!feof(arch1))
		{
			if(strcmp(nomasc,masc.apeNom)==0)
			{
				if(fread(&veter,sizeof(veterinario),1,arch2)==NULL)
				{
					printf("no hay nada guardado en el archivo");
				}
				else
				{
					while(!feof(arch2))
					{
						if(n==veter.matricula)
						{
							b=1;
							turn.matriculaVet=n;
							printf("Ingrese la fecha del turno:\n");
							printf("Dia:  ");
							scanf("%d",&turn.fec.dia);
							printf("\n Mes:  ");
							scanf("%d",&turn.fec.mes);
							printf("\n Anio(4 digitos):  ");
							scanf("%04d",&turn.fec.anio);
							printf("Ingrese el DNI del duenio:\n");
							scanf("%d",&turn.dniDuenio);
							turn.estado=true;
						
							fwrite(&turn,sizeof(Turnos),1,arch);
						}
						fread(&veter,sizeof(veterinario),1,arch2);
					}
				}
			
			}
				fread(&masc,sizeof(mascota),1,arch1);
		}
			if(b==0)
			{
				printf("LA MASCOTA Y/O LA MATRICULA DEL VETERINARIO NO EXISTE!!");
			}
			fclose(arch);
			fclose(arch1);
			fclose(arch2);
	}
}
void informe()
{
	FILE *arch, *arch1;
	Turnos turn;
	arch=fopen("Turnos.dat","rb");
	int n, d, m, a,b=0;
	if(fread(&turn,sizeof(Turnos),1,arch)==NULL)
	{
		printf("no hay nada guardado en el archivo");
	}
	else
	{
		printf("ingrese el numero de matricula del Veterinario:\n");
		scanf("%d",&n);
		printf("ingrese la fecha del turno:\n");
		printf("dia: \t");
		scanf("%d",&d);
		printf("mes: \t");
		scanf("%d",&m);
		printf("anio: \t");
		scanf("%d",&a);

		printf("MATRICULA VETERINARIO \t FECHA DEL TURNO \t DNI DEL DUENIO \t DETALLE DE ATENCION\n");
		while(!feof(arch))
		{
			if(turn.estado==false && n==turn.matriculaVet && d==turn.fec.dia && m==turn.fec.mes && a==turn.fec.anio )
			{
				b=1;
				printf("| %d |",turn.matriculaVet);
				printf("\t\t\t");
				printf("| %d/%d/%d |",turn.fec.dia,turn.fec.mes,turn.fec.anio);
				printf("\t\t");
				printf("|%d|",turn.dniDuenio);
				printf("\t\t");
				printf("| %s |",turn.detalleAt);
				printf("\n");
			}
			fread(&turn,sizeof(Turnos),1,arch);
		}
		if(b==0)
		{
			printf("no se atendio ningun turno todavia!!");
		}
	}
	fclose(arch);
}
