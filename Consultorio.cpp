#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <string.h>
#include<conio.h>
struct Veterinario{
	char apynom[60];
	int matricula;
	int dni;
	char telefono[25];
	char password[32];
};

struct fecha
{
	int dia;
	int mes;
	int anio;
};

struct Turnos
{
	int matriculaVet;
	fecha fec;
	int dniDuenio;
	char detalleAt[380];
	bool estado;
};

struct Mascota
{
	char apeNom[60];
	char domicilio[60];
	int  dniDuenio;
	char localidad [60];
	fecha  fechaNacimiento;
	float   peso;
	char  telefono[25];
};
//FUNCION PARA INICIAR SESION 
int IniciarSesion(FILE *archVeterinario, Veterinario regVeterinario);
//FUNCION PARA CALCULAR LA EDAD DE LA MASCOTA
int Edad(int year,int month,int day);
//FUNCION PARA LISTAR LOS TURNOS REGISTRADOS POR EL ASISTENTE
void ListaDeTurnos(int sesion,FILE *archTurno, FILE *archMascota,Turnos turn,Mascota datoMascota);
//FUNCION PARA CARGAR LA EVOLUCION DE LA MASCOTA "DETALLE DE ATENCION"
void RegistrarEvolucion(int sesion,FILE *archTurno,Turnos turn);

main(){
	//DECLARACION DE ARCHIVOS
	FILE *archVeterinario,*archTurno,*archMascota;
	//DECLARACION DE REGISTROS
	Veterinario regVeterinario;
	Turnos turn;
	Mascota datoMascota;
	//DECLARACION DE VARIABLES PARA EL USO DEL MENU
	char salir='n';
	int opcion;
	int sesion=0;
	do{
		system("CLS");
		printf("\tConsultorio Veterinario\n");
		printf("==========================\n");
		printf("1.- Iniciar Sesion\n");
		printf("2.- Visualizar Lista de Espera de Turnos\n");
		printf("3.- Registrar Evolucion de la Mascota\n\n");
		printf("6.- Cerrar Aplicacion.\n\n");
		printf("Elija una opcion: ");
		scanf("%d",&opcion);
		system("CLS");	
		switch(opcion){
			case 1:
				//SOLO HACE EL LLAMADO A LA FUNCION SI LA VARIABLE sesion==0(ESTO QUIERE DECIR QUE NO SE ENCUENTRA NINGUNA MATRICULA CARGADO)
				if(sesion==0){
					sesion=IniciarSesion(archVeterinario,regVeterinario);
				}
				else{
					printf("YA SE ENCUENTRA UNA SESION INICIADA!\n\n");
					system("PAUSE");
				}
				break;
			case 2:
				//EN ES IF SE CONSULTA SI SESION ES DISTINTA DE 0, EN EL CASO QUE SEA VERDADERO, QUIERE DECIR QUE SESION YA TIENE UNA MATRICULA.
				if(sesion!=0){
					ListaDeTurnos(sesion,archTurno,archMascota,turn,datoMascota);
				}
				else{
					printf("PARA INGRESAR A ESTA OPCION DEBE INICIAR SESION.\n\n");
					system("PAUSE");
				}
				break;
			case 3:
				if(sesion!=0){
					RegistrarEvolucion(sesion,archTurno,turn);
				}
				else{
					printf("PARA INGRESAR A ESTA OPCION DEBE INICIAR SESION.\n\n");
					system("PAUSE");
				}
				break;
			case 6:
				_flushall();
				printf("ESTA SEGURO QUE DESEA SALIR --> SI=S / NO=N: ");
				scanf("%c",&salir);
				break;
			default:
				printf("LA OPCION INGRESADA ES INCORRECTA.\n\n");
				system("PAUSE");
				break;
		}
	}while(salir=='n' || salir =='N');
}

int IniciarSesion(FILE *archVeterinario, Veterinario regVeterinario){
	int existeUsuario=0;//VARIABLE QUE GUARDARA LA MATRICULA SE ES ENCONTRADO EL NUMERO DE MATRICULA
	int mat,i=0;
	char pass[32],c;
	archVeterinario=fopen("Veterinarios.dat","rb");
	printf("\t INICIO DE SESION\n\n");
	printf("Matricula: ");
	scanf("%d",&mat);
	_flushall();
	printf("Password: ");
	while((i<32 )and (c!=13))
	{
		c=getch();
		
	  	if(c==13|| i==31)
	  	{
	  		pass[i]='\0';
	  	}
	  	else
	  	{
	  		pass[i]=c;
	  	}
	  	printf("#");
	  	i++;
	}
	
	fread(&regVeterinario,sizeof(Veterinario),1,archVeterinario);
	while(!feof(archVeterinario)){
		//ESTE IF CONSULTA SI LOS TADOS INGRESADOS SON IGUALES A LOS DATOS QUE EXISTEN EN EL ARCHIVO "Veterinarios.dat"
		if(regVeterinario.matricula==mat && strcmp(regVeterinario.password,pass)==0){
			existeUsuario=mat;
		}
		fread(&regVeterinario,sizeof(Veterinario),1,archVeterinario);
	}
	if(existeUsuario==0){
		printf("EL USUARIO NO FUE ENCONTRADO O NO EXISTE.\n\n");
		system("PAUSE");
	}
	return existeUsuario; //RETORNA EL NUMERO DE MATRICULA
}

int Edad(int year,int month,int day){
	int anioActual,mesActual,diaActual,edad;
	time_t t= time(NULL);
	struct tm tiempolocal=*localtime(&t);
	char anioCad[5],mesCad[3],diaCad[3];
	char *formatoAnio="%Y";//EN ESTA VARIABLE SE GUARDA EL AÑO ACTUAL
	char *formatomes="%m";//EN ESTA BARIABLE SE GUARDA EL MES ACTUAL
	char *formatodia="%d";//EN ESTA VARIABLE SE GUARDA EL DIA ACTUAL
	//EN ESTAS TRES FUNCIONES LE DAMOS FORMATO A LA FECHA ACTUAL
	strftime(anioCad,sizeof(anioCad),formatoAnio,&tiempolocal);
	strftime(mesCad,sizeof(mesCad),formatomes,&tiempolocal);
	strftime(diaCad,sizeof(diaCad),formatodia,&tiempolocal);
	//AQUI SE CONVIERTE LAS TRES VARIABLES A FORMATO INT
	anioActual=atoi(anioCad);
	mesActual=atoi(mesCad);
	diaActual=atoi(diaCad);
	if(mesActual>=month && diaActual>=day){
		edad=anioActual-year;
	}
	else{
		edad=anioActual-year-1;
	}
	return edad;
}

void ListaDeTurnos(int sesion,FILE *archTurno, FILE *archMascota,Turnos turn,Mascota datoMascota){
	int anio;
	archMascota=fopen("Mascotas.dat","rb");
	archTurno=fopen("Turnos.dat","rb");
	fread(&datoMascota,sizeof(Mascota),1,archMascota);
	fread(&turn,sizeof(Turnos),1,archTurno);
	//ESTE WHILE LO UTILIZAMOS PARA OBTENER LOS DATOS DEL TURNO
	while(!feof(archTurno)){		
		if(sesion==turn.matriculaVet && turn.estado==true){		
		//ESTE WHILE SE UTILIZA PARA OBTENER LOS DATOS DE LA MASCOTA Y PODER IMPRIMIR LOS DATOS CORRESPONDIENTES	
			while(!feof(archMascota)){
				if(turn.dniDuenio==datoMascota.dniDuenio){
					printf("Nombre y Apellido: %s\n",datoMascota.apeNom);
					printf("DNI: %d\n",datoMascota.dniDuenio);
					printf("Localidad: %s\n",datoMascota.localidad);
					anio=Edad(datoMascota.fechaNacimiento.anio,datoMascota.fechaNacimiento.mes,datoMascota.fechaNacimiento.dia);
					printf("Edad: %d\n",anio);
					printf("Peso: %.2f",datoMascota.peso);
					printf("\n================\n\n");
				}
				fread(&datoMascota,sizeof(Mascota),1,archMascota);					
			}
			rewind(archMascota);			
		}
		fread(&turn,sizeof(Turnos),1,archTurno);
	}
	fclose(archMascota);
	fclose(archTurno);
	system("PAUSE");
}

void RegistrarEvolucion(int sesion,FILE *archTurno,Turnos turn){
	FILE *auxiliar;
	int dni;
	archTurno=fopen("Turnos.dat","a+b");
	auxiliar=fopen("auxiliar.dat","wb");
	_flushall();
	printf("REGISTRO DE EVOLUCION\n\n");
	printf("Ingrese el DNI del titular: ");
	scanf("%d",&dni);
	_flushall();
	fread(&turn,sizeof(Turnos),1,archTurno);
	//EN ESTE WHILE SE BUSCARA LOS DATOS DE LA MASCOTA QUE ESTA POR SER ATENDIDA POR EL VETERINARIO
	while(!feof(archTurno)){
		//EL IF SOLO MOSTRARA LOS DATOS QUE CUMPLAN CON LAS SENTICIAS PARA LUEGO PODER GUARDAR EL DETALLE DE ATENCION
		if(turn.dniDuenio==dni && sesion==turn.matriculaVet && turn.estado==true){
			if(strlen(turn.detalleAt)==0){
				printf("\nMatricula del Veterinario: %d\n",turn.matriculaVet);
				printf("Fecha: %d/%d/%d\n",turn.fec.dia,turn.fec.mes,turn.fec.anio);
				printf("DNI: %d\n",turn.dniDuenio);
				do{
					_flushall();
					printf("Ingrese el detalle de la Atencion No mas de 380 Caracteres\n\n");
					gets(turn.detalleAt);
				}while(strlen(turn.detalleAt)>=380);
				turn.estado=false;
				fwrite(&turn,sizeof(Turnos),1,auxiliar);
				break;
			}
		}
		if(turn.dniDuenio!=dni){
			fwrite(&turn,sizeof(Turnos),1,auxiliar);
		}
		fread(&turn,sizeof(Turnos),1,archTurno);
	}
	fclose(archTurno);
	fclose(auxiliar);
	remove("Turnos.dat");
	rename("auxiliar.dat","Turnos.dat");
}

