//Juan Alejandro Urueña Serna

#include<iostream>
#include<string>
#include<conio.h>
#include<windows.h>

using namespace std;

struct cuenta{
	long cedula;
	string celular;
	string correo;
	string contrasena;
	float codigo[10];
	float costo[10];
	float pagos;
	double saldo;
};

int guardarPosicion(cuenta datos[],int tam){
	for(int i=0;i<tam;i++){
		if(datos[i].cedula==0 &&datos[i].correo.empty() && datos[i].contrasena.empty() && datos[i].saldo==0){
			return i;
		}
	}
	return 1000;
}

bool verificarCedula(cuenta datos[],long ced,int tam){
	for(int i=0;i<tam;i++){
		if(datos[i].cedula==ced){
			return true;
		}
	}
	return false;
}

bool verificarClave(string clave){
	int claveTam,i;
	bool v=true;
	claveTam=clave.size();
	for(int i=0;i<claveTam;i++){
		if(clave[i]<48 || clave[i]>57){
			v=false;break;
		}
	}
	return v;
}

string clave(cuenta datos[],int tam){
	float contador;
	bool comprobar=true, res;
	char caracter;
	string clave;
	
	cout<<"INGRESE SU CLAVE"<<endl;
	contador=1;
	
	do{
		caracter=getch();
		cout<<"*";
		clave+=caracter;
		contador++;
		if(contador==5){
			comprobar=verificarClave(clave);
			if(comprobar==false){
				contador=1;
				system("cls");
				cout<<"ERROR, INGRESE NUEVAMENTE LA CLAVE"<<endl;
				clave="";
			}
		}
	}while(contador<=4 || comprobar==false);
	return clave;
}

void crearCuenta(cuenta datos[],int tam){
	long ced;
	cout<<"CREACION DE CUENTA"<<endl;
	int posicion=guardarPosicion(datos,tam);
	if(posicion>=0 && posicion<tam){
		cout<<"INGRESE EL NUMERO DE CEDULA"<<endl;
		cin>>ced;
		system("cls");
		if(!verificarCedula(datos,ced,tam)){
			datos[posicion].cedula=ced;
			fflush(stdin);
			cout<<"CREACION DE CUENTA"<<endl;
			cout<<"INGRESE SU CORREO ELECTRONICO"<<endl;
			getline(cin,datos[posicion].correo);
			system("cls");
			cout<<"CREACION DE CUENTA"<<endl;
			cout<<"NUMERO DE CELULAR"<<endl;
			cin>>datos[posicion].celular;
			system("cls");
			datos[posicion].contrasena=clave(datos,tam);
			system("cls");
			cout<<"REGISTRADO EXITOSAMENTE"<<endl;
		}else{
			cout<<"EL NUMERO DE CEDULA YA EXISTE"<<endl;
		}
	}else{
		cout<<"ESPACIO EN MEMORIA INSUFICIENTE"<<endl;
	}
	return;
}

void consignar(cuenta datos[],int tam){
	long ced=0;
	double valor=0;
	string nombre;
	cout<<"ESTA OPERACION USA EL IMPUESTO DEL 4 POR MIL"<<endl;
	cout<<"INGRESE EL NUMERO DE CUENTA"<<endl;
	cin>>ced;
	for(int i=0;i<tam;i++){
		if(ced==datos[i].cedula){
			cout<<"INGRESE EL VALOR A CONSIGNAR"<<endl;
			cin>>valor;
			cout<<endl;
			cout<<"INGRESE EL NOMBRE DE LA PERSONA O EMPRESA QUE DESEA CONSIGNAR"<<endl;
			fflush(stdin);
			getline(cin,nombre);
			datos[i].saldo=datos[i].saldo+valor;
			datos[i].saldo=datos[i].saldo-(4*valor)/1000;
			return;
		}
	}
	cout<<"DATOS INCORRECTOS"<<endl;
	return;
}

void consultaSaldo(cuenta datos[],int tam){
	long ced;
	string cla;
	cout<<"ESTA OPERACION CUENTA CON UN COSTO DE 1500"<<endl;
	cout<<"INGRESE EL NUMERO DE CUENTA(CEDULA)"<<endl;
	cin>>ced;
	cout<<endl;
	cla=clave(datos,tam);
	system("cls");
	for(int i=0;i<tam;i++){
		if(datos[i].cedula==ced && datos[i].contrasena==cla){
			if(datos[i].saldo<1500){
				cout<<"SALDO INSUFICIENTE"<<endl;
				break;
			}else{
				datos[i].saldo=datos[i].saldo-1500;
				cout<<"EL SALDO ACTUAL ES DE "<<datos[i].saldo<<endl;
			}
		}
	}
}

void retiro(cuenta datos[],int tam){
	long ced=0;
	string cla;
	double retiro=0;
	cout<<"ESTA OPERACION TIENE UN COSTO DE 2000"<<endl;
	cout<<"INGRESE EL NUMERO DE CUENTA(CEDULA)"<<endl;
	cin>>ced;
	cla=clave(datos,tam);
	system("cls");
	cout<<"CUANTO DESEA RETIRAR"<<endl;
	cin>>retiro;
	for(int i=0;i<tam;i++){
		if(retiro<datos[i].saldo && datos[i].cedula==ced && datos[i].saldo>2000 && datos[i].contrasena==cla){
			datos[i].saldo=datos[i].saldo-retiro-2000;
			cout<<"OPERACION EXITOSA"<<endl;
			break;
		}else{
			cout<<"SALDO INSUFICIENTE"<<endl;
		}
	}
}

void inscribirPagos(cuenta datos[],int tam){
	cout<<"INSCRIBIR PAGOS"<<endl;
	float ced=0;
	string cla;
	int x=0,y=0,z=0;
	
	cout<<"INGRESE EL NUMERO DE CUENTA"<<endl;
	cin>>ced;
	cla=clave(datos,tam);
	for(int i=0;z<1;i++){
		if(datos[i].cedula==ced && datos[i].contrasena==cla){
			system("cls");
			y++;
			cout<<"INGRESE EL CODIGO DEL NUMERO DE PAGO"<<endl;
			cin>>x;
			for(int e=0;e<10;e++){
				if(datos[i].codigo[e]==x){
					cout<<"NUMERO DE PAGO EXISTENTE"<<endl;
					break;
				}
				if(datos[i].codigo[e]==0){
					datos[i].codigo[e]=x;
					cout<<"INGRESE EL PRECIO "<<endl;
					cin>>datos[i].costo[e];
					cout<<"PAGO INSCRITO"<<endl;
					z++;
					break;
				}
			}
		}
	}
	if(y==0){
		cout<<"DATOS INCORRECTOS"<<endl;
	}
	return;
}

void pagos(cuenta datos[],int tam){
	float ced;
	string cla;
	int x=0,y=0,z=0;
	
	cout<<"INGRESE EL NUMERO DE CUENTA(CEDULA)"<<endl;
	cin>>ced;
	cla=clave(datos,tam);
	for(int i=0;i<5;i++){
		if(datos[i].cedula==ced && datos[i].contrasena==cla){
			system("cls");
			
			for(int e=0;e<10;e++){
				if(datos[i].codigo[e]!=0){
					z++;
					cout<<datos[i].codigo[e]<<" "<<datos[i].costo[e];
					cout<<endl;
				}
			}
			cout<<"INGRESE EL NUMERO DE PAGO"<<endl;
			cin>>x;
			for(int a=0;a<10;a++){
				if(x==datos[i].codigo[a]){
					if(datos[i].saldo>datos[i].costo[a]){
						datos[i].saldo=datos[i].saldo-datos[i].costo[a];
						cout<<"PAGO EXITOSO"<<endl;
						datos[i].codigo[a]=0;
					}else{
						cout<<"SALDO INSUFICIENTE"<<endl;
					}
				}
			}
		}
	}
	return;
}

void cerrarCuenta(cuenta datos[],int tam){
	
	float ced=0;
	string cla;
	
	cout<<"DIGITE SU NUMERO DE CUENTA "<<endl;
	cin>>ced;
	cla=clave(datos,tam);
	system("cls");
	for(int i=0; i<tam;i++){
		for(int j=0; j<tam; j++){
			if(datos[i].cedula==ced && datos[i].contrasena==cla){
				   if(datos[i].saldo==0 && datos[i].costo[j]==0){
				 	   cout<<"LA CEUNTA "<<datos[i].cedula<<" HA SIDO CERRADA CORRECTAMENTE"<<endl;
				 	   datos[i].cedula=0;
                       datos[i].correo="";
                       datos[i].celular="";
                       datos[i].contrasena="";
                       datos[i].codigo[j]=0;
                       datos[i].costo[j]=0;
                       datos[i].pagos=0; 
                       datos[i].saldo=0;
                       break;
				    } 
				    
			   else{
				cout<<"SU CUENTA "<<datos[i].cedula<<" PETICION RECHAZADA "<<endl;
				break;
			}
		}
		}
	}
	return;
}

int main(){
	int menu=0;
	int tam=1000;
	cuenta datos[tam];
	
	for(int i=0;i<tam;i++){
		datos[i].cedula=0;
		datos[i].correo="";
		datos[i].celular="";
		datos[i].contrasena="";
		datos[i].saldo=0;
		for(int e=0;e<10;e++){
			datos[i].codigo[e]=0;
			datos[i].costo[e]=0;	
		}
	}
	
	do{
		system("cls");
		cout<<"BIENVENIDO AL MENU PRINCIPAL DEL BANCO PORTAL DEL CERRO"<<endl;
		cout<<endl;
		
		system("color 3E");
		cout<<"CREAR CUENTA--------->(1)"<<endl;
		cout<<"CONSIGNACIONES------->(2)"<<endl;
		cout<<"CONSULTA TU SALDO---->(3)"<<endl;
		cout<<"RETIROS-------------->(4)"<<endl;
		cout<<"INSCRIBIR PAGOS------>(5)"<<endl;
		cout<<"PAGOS---------------->(6)"<<endl;
		cout<<"CANCELAR CUENTA------>(7)"<<endl;
		cout<<"SALIDA--------------->(8)"<<endl;
		cout<<"DIGITE UNA OPCION"<<endl;
		cin>>menu;
		fflush(stdin);
		
		switch(menu){
			case 1:{
				system("cls");
				crearCuenta(datos,tam);
				system("pause");
				break;
			}
			case 2:{
				system("cls");
				consignar(datos,tam);
				system("pause");
				break;
			}
			case 3:{
				system("cls");
				consultaSaldo(datos,tam);
				system("pause");
				break;
			}
			case 4:{
				system("cls");
				retiro(datos,tam);
				system("pause");
				break;
			}
			case 5:{
				system("cls");
				inscribirPagos(datos,tam);
				system("pause");
				break;
			}
			case 6:{
				system("cls");
				pagos(datos,tam);
				system("pause");
				break;
			}
			case 7:{
				system("cls");
				cerrarCuenta(datos,tam);
				system("pause");
				break;
			}
			case 8:{
				system("cls");
				
				cout<<"DE NADA, VUELVA PRONTO"<<endl;
				return 0;
				system("pause");
				break;
			}
		}
	}while(menu>=1 && menu<=8);
}
