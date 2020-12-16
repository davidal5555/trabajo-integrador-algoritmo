#include <stdio.h>
#include <windows.h>
#include <ctype.h>


struct Usuarios{
	char usuario[10];
	char password[32];
	char apynom[60];
};

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
	bool estado=true;
};

//FUNCION QUE VALIDA EL USUARIO ANTES DE GUARDARLO EN EL ARCHIVO
bool validacionUsuario(FILE *archUsuario, Usuarios regUsuario, char usuario[10]);
//FUNCION QUE VALIDA EL PASSWORD
bool validacionPassword(char password[32]);
//FUNCION PARA DAR DE ALTA UN VETERINARIO
void RegistrarVeterinario(FILE *archVeterinario, Veterinario regVeterinario);
//FUNCION PARA DAR DE ALTA UN USUARIO
void RegistrarUsuario(FILE *archUsuario,Usuarios regUsuario);
//FUNCION PARA LISTAR LOS TURNOS ATENDIDOS POR UN VETERINARIO Y UN MES EN ESPECIAL
void AtencionPorVeterinario(FILE *archTurno,Turnos turn);
//FUNCION QUE MUESTRA EL VETERINARIO QUE MAS TURNOS ATENDIO EN UN MES DETERMINADO
void Ranking(FILE *archVeterinario,FILE *archTurno,Turnos turn,Veterinario regVeterinario);

main(){
	Veterinario regVeterinario;
	Usuarios regUsuario;
	Turnos turn;
	FILE *archVeterinario,*archUsuario,*archTurno;

	int opcion;
	char salir = 'n';
	do{
		system("CLS");
		printf("\tAdministracion\n");
		printf("==========================\n");
		printf("1.- Registrar Veterinario\n");
		printf("2.- Registrar Usuario Asistente\n");
		printf("3.- Atenciones por Veterinario\n");
		printf("4.- Ranking de Veterinarios por Atenciones\n\n");
		printf("6.- Cerrar Aplicacion.\n\n");
		printf("Elija una opcion: ");
		scanf("%d",&opcion);
		system("CLS");	
		switch(opcion){
			case 1:
				RegistrarVeterinario(archVeterinario,regVeterinario);
				break;
			case 2: 
				RegistrarUsuario(archUsuario,regUsuario);
				break;
			case 3:
				AtencionPorVeterinario(archTurno,turn);
				break;
			case 4:
				Ranking(archVeterinario,archTurno,turn,regVeterinario);
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
	}while(salir=='n' || salir=='N');
	
}

bool validacionUsuario(FILE *archUsuario, Usuarios regUsuario, char usuario[10]){
	archUsuario=fopen("Usuarios.dat","rb");
	bool respuesta = false;
	int existeUsuario=0;
	int cantidadnumeros=0,mayusculas=0;
	if(strlen(usuario)>=6 && strlen(usuario)<=10){
		for(int i=0; i<strlen(usuario); i++){
		//IF QUE VALIDA SI EL PRIMER CARACTER DE LA VARIABLE COMIENZA CON MINUSCULA	
			if(usuario[0]>='a' && usuario[0]<='z'){
				//IF QUE VALIDA SI UN CARACTER DEL USUARIO ES UNA LETRA MAYUSCULA
				if(usuario[i]>='A' && usuario[i]<='Z'){
					mayusculas++;
				}
				//IF QUE VALIDA SI UN CARACTER DEL USUARIO ES UN DIGITO
				if(isdigit(usuario[i])){
					cantidadnumeros++;		
				}
			}
			else{
				printf("EL USUARIO DEBE COMENZAR CON UNA LETRA MINUSCULA.\n\n");
				system("PAUSE");
				break;
			}
		}
		if(cantidadnumeros<=3){
			if(mayusculas>=2){
				fread(&regUsuario,sizeof(Usuarios),1,archUsuario);
				//ALGORITMO PARA CONSULTAR SI EL USUARIO QUE SE VA CREAR YA EXISTE EN EL ARCHIVO
				while(!feof(archUsuario)){
					if(regUsuario.usuario == usuario){
						existeUsuario++;
					}
					fread(&regUsuario,sizeof(Usuarios),1,archUsuario);
				}
				if(existeUsuario==0){
					respuesta=true;
				}
				else{
					printf("YA EXISTE UN USUARIO CON ESE NOMBRE. PORFAVOR INGRESE OTRO\n\n");
					respuesta=false;
				}
			}
			else{
				printf("EL USUARIO DEBE TENER AL MENOS 2 LETRAS MAYUSCULAS.\n\n");
				respuesta=false;
			}
		}
		else{
			printf("EL NOMBRE DE USUARIO NO DEBE TENER MAS DE 3 DIGITOS.\n\n");
			respuesta=false;
		}
	}
	else{
		printf("EL USUARIO DEBE TENER COMO MINIMO 6 CARACTERES Y COMO MAXIMO 10 CARACTERES.\n\n");
		respuesta=false;
	}
	fclose(archUsuario);
	return respuesta;
}

bool validacionPassword(char password[32]){
	bool tieneMayuscula=false;
	bool tieneMinuscula=false;
	bool tieneNumero=false;
	bool tieneSimbolo=false;
	bool respuesta=false;
	char aux[32];
	char abecedario[]="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char numeros[]="123456789";
	int letrasConsecutivas=0;
	int numerosConsecutivos=1;
	// IF QUE VALIDA SI EL PASSWORD ES MAYOR A 6 CARACTERES Y MENOR QUE 32 CARACTERES
	if(strlen(password)>=6 && strlen(password)<=32){
		for(int i=0;i<strlen(password);i++){
			//IF QUE VALIDA SI UN CARACTER DE PASSWORD ES UNA LETRA MINUSCULA
			if(password[i]>='a' && password[i]<='z'){
				tieneMinuscula=true;
			}
			//IF QUE VALIDA SI UN CARACTER DE PASSWORD ES UNA LETRA MAYUSCULA
			if(password[i]>='A' && password[i]<='Z'){
				tieneMayuscula=true;
			}
			//IF QUE VALIDA SI UN CARACTER DE PASSWORD ES UN DIGITO
			if(isdigit(password[i])){
				tieneNumero=true;
			}
			//IF QUE VALIDA SI UN CARACTER DE PASSWORD ES UN SIMBOLO
			if(!isalpha(password[i]) && !isdigit(password[i])){
				tieneSimbolo=true;
			}
		}
		if(tieneSimbolo==false){
			if(tieneMinuscula==true && tieneMayuscula==true && tieneNumero==true){
				strcpy(aux,password);
				strupr(aux);
				//ALGORITMO QUE PERMITE SABER SI EXISTEN LETRAS CONSECUTIVAS
				for(int i=0; i<strlen(aux);i++){
					for(int j=0; j<strlen(abecedario);j++){
						if(aux[i]==abecedario[j] && aux[i+1]==abecedario[j+1]){
							letrasConsecutivas++;
						}		
					}
				}
				//ALGORITMO QUE PERMITE SABER SI EXISTEN NUMEROS CONSECUTIVOS
				for(int i=0;i<strlen(password);i++){
					for(int j=0;j<strlen(numeros);j++){
						if(password[i]==numeros[j] && password[i+1]==numeros[j+1]){
							numerosConsecutivos++;
						}
					}
				}
				if(letrasConsecutivas==0 && numerosConsecutivos<=3){
					respuesta=true;
				}
				else{
					printf("EL PASSWORD NO DEBE TENER NINGUNA LA CONSECUTIVA.\n");
					printf("EL PASSWORD NO DEBE TENER MAS DE 3 DIGITOS CONSECUTIVOS.\n\n");
					respuesta=false;
				}			
			}
			else{
				printf("EL PASSWORD NO CUMPLE CON UNA DE LAS CONDICIONES.\n");
				printf("DEBE TENER AL MENOS 1 MAYUSCULA 1 MINUSCULA Y 1 NUMERO\n\n");
				respuesta=false;
			}
		}
		else{
			printf("EL PASSWORD NO DEBE TENER ESPACIOS NI SIMBOLOS.\n\n");
			respuesta=false;
		}		
	}
	else{
		printf("EL PASSWORD DEBE TENER COMO MINIMO 6 CARACTERES Y 32 COMO MAXIMO.\n");
		respuesta=false;
	}
	system("PAUSE");
	return respuesta;
}
void RegistrarVeterinario(FILE *archVeterinario, Veterinario regVeterinario){
	archVeterinario=fopen("Veterinarios.dat","a+b");
	bool pass=false;
	char password[32];
	system("CLS");
	printf("ALTA DE VETERINARIO.\n\n");
	_flushall();
	printf("Nombre y Apellido: ");
	gets(regVeterinario.apynom);
	_flushall();
	printf("DNI: ");
	scanf("%d",&regVeterinario.dni);
	printf("Matricula: ");
	scanf("%d",&regVeterinario.matricula);
	_flushall();
	printf("Telefono: ");
	gets(regVeterinario.telefono);
	do{
		printf("\n\n Para ingresar un password correcto:\nMin 6 caracteres Max 32\nMinimo 1 Mayuscula,1 numero, 1 Minuscula\nNo letras consecutivas\nNo mas de 3 numeros consecutivos\nNo Simbolos.\n\n");
		printf("Password: ");
		gets(regVeterinario.password);
		pass=validacionPassword(regVeterinario.password);
		if(pass==false){
			system("CLS");
		}
	}while(pass==false);
	fwrite(&regVeterinario,sizeof(Veterinario),1,archVeterinario);
	fclose(archVeterinario);
}

void RegistrarUsuario(FILE *archUsuario,Usuarios regUsuario){
	bool usu = false;
	bool pass = false;
	archUsuario=fopen("usuarios.dat","a+b");
	_flushall();
	printf("ALTA DE ASISTENTE\n\n");
	printf("Nombre y Apellido: ");
	gets(regUsuario.apynom);
	do{
		system("CLS");
		printf("AYUDA PARA CREAR USUARIO\n\n");
		printf("* No se debe repetir\n* Comenzar con una letra minuscula\n* Tener al menos 2 mayusculas\n*Tener como maximo 3 digitos\n\n");
		printf("Usuario: ");
		gets(regUsuario.usuario);
		usu=validacionUsuario(archUsuario,regUsuario,regUsuario.usuario);
	}while(usu==false);
	do{
		system("CLS");
		printf("AYUDA PARA CREAR PASSWORD\n\n");
		printf("* Debe contener al menos: UNA letra mayuscula, UNA letra minuscula y UN numero.\n");
		printf("* No simbolos, No espacios.\n");
		printf("* Min 6 caracteres Max 32.\n");
		printf("* No debe tener mas de 3 numeros consecutivos.\n");
		printf("* No debe tener 2 caracteres consecutivos que refieran al alfabeto.\n\n");
		printf("Por favor ingrese un Password: ");
		gets(regUsuario.password);
		pass=validacionPassword(regUsuario.password);
	}while(pass==false);
	fwrite(&regUsuario,sizeof(Usuarios),1,archUsuario);
	fclose(archUsuario);
}

void AtencionPorVeterinario(FILE *archTurno,Turnos turn){
	int MATRICULA, MES;
	archTurno=fopen("Turnos.dat","rb");
	printf("BUSCAR ATENCION DE VETERINARIO\n\n");
	printf("Ingrese la Matricula: ");
	scanf("%d",&MATRICULA);
	printf("ingrese el mes en numero: ");
	scanf("%d",&MES);
	fread(&turn,sizeof(Turnos),1,archTurno);
	//SE IMPRIMEN LOS TURNOS ATENDIDOS DE UN DETERMINADO VETERINARIO Y UN DETERMINADO MES
	while(!feof(archTurno)){
		if(turn.matriculaVet == MATRICULA && turn.fec.mes==MES && turn.estado==false){
			printf("Matricula: %d\n",turn.matriculaVet);
			printf("Fecha: %d/%d/%d\n",turn.fec.dia,turn.fec.mes,turn.fec.anio);
			printf("DNI del dueño: %d\n",turn.dniDuenio);
			printf("Detalle de Atencion: %s\n",turn.detalleAt);
			printf("\n================================\n");
		}
		fread(&turn,sizeof(Turnos),1,archTurno);
	}
	fclose(archTurno);
	system("PAUSE");
}

void Ranking(FILE *archVeterinario,FILE *archTurno,Turnos turn,Veterinario regVeterinario){
	int MATRICULAS[50];
	int TURNOS[50];
	int canregistros=0;
	int canturnos=0;
	int AUX;
	archVeterinario=fopen("Veterinarios.dat","rb");
	fread(&regVeterinario,sizeof(Veterinario),1,archVeterinario);
	archTurno=fopen("Turnos.dat","rb");
	fread(&turn,sizeof(Turnos),1,archTurno);
	//ESTE WHILE NOS PERMITIRA OBTENER LA CANTDIAD DE VETERINARIOS QUE EXISTEN
	while(!feof(archVeterinario)){
		MATRICULAS[canregistros]= regVeterinario.matricula;
		canregistros++;				
		fread(&regVeterinario,sizeof(Veterinario),1,archVeterinario);
	}
	rewind(archVeterinario);
	//ESTE ALGORITMO PERMITIRA OBTENER LA CANTIDAD DE TURNOS POR VETERINARIO
	for(int i=0; i<canregistros;i++){
		while(!feof(archTurno)){
			if(MATRICULAS[i]==turn.matriculaVet){
				canturnos++;
			}
			fread(&turn,sizeof(Turnos),1,archTurno);
		}
		TURNOS[i]=canturnos;
		canturnos=0;
	}
	//ESTE FOR ORDENARA DE MAYOR A MENOR LOS VETERINARIOS CON LA CANTIDAD DE TURNOS REALIZADOS
	for(int i=0; i<canregistros;i++){
		for(int j=0; j<canregistros;j++){
			if(TURNOS[i]>TURNOS[j]){
				AUX=MATRICULAS[i];
				MATRICULAS[i]=MATRICULAS[j];
				MATRICULAS[j]=AUX;
				AUX=TURNOS[i];
				TURNOS[i]=TURNOS[j];
				TURNOS[j]=AUX;
			}
		}
	}
	printf("RANKING DE VETERINARIOS\n\n");
	//ESTE ALGORITMO PERMITIRA IMPRIMIR LOS DATOS ANTERIORMETE ORDENADOS
	for(int i=0;i<canregistros;i++){
		fread(&regVeterinario,sizeof(Veterinario),1,archVeterinario);
		while(!feof(archVeterinario)){
			if(MATRICULAS[i]== regVeterinario.matricula){
				printf("PUESTO NUMERO (%d)\n",i+1);
				printf("Nombre y Apellido: %s\n",regVeterinario.apynom);
				printf("Matricula: %d\n",regVeterinario.matricula);
				printf("Turnos: %d\n",TURNOS[i]);
				printf("\n======================\n");
			}
			fread(&regVeterinario,sizeof(Veterinario),1,archVeterinario);
		}
		rewind(archVeterinario);
	}
	fclose(archVeterinario);
	fclose(archTurno);
	system("PAUSE");
}
