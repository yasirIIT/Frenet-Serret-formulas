#include<stdlib.h>
#include<stdio.h>
#include<math.h>

FILE *fp,*fpp; double _Ad[9],_Bd[9], s=0,d1,d2,d3,d4,d5,d6,d7,d8,d9,d10;

void _path(double s){	
	_Ad[0]=s*cos(s);	_Ad[1]=s*sin(s);	_Ad[2]=s;	//path1: 
	//_Ad[0]=s;	_Ad[1]=10.0*sin(s);	_Ad[2]=1;	//path2=flagella:
	//_Ad[0]=s;	_Ad[1]=0;	_Ad[2]=11+10*sin(s);	//path2:
	}











double derr1(double s,double ds){
	_path(s+ds); 
	_Bd[0]=_Ad[0];_Bd[1]=_Ad[1];_Bd[2]=_Ad[2]; 
	_path(s-ds); 
	_Ad[3]=(_Bd[0]-_Ad[0])/(2.0*ds);	_Ad[4]=(_Bd[1]-_Ad[1])/(2.0*ds);	_Ad[5]=(_Bd[2]-_Ad[2])/(2.0*ds);
	}
double derr2(double s,double ds){
	_path(s+ds); 
	_Bd[0]=_Ad[0];_Bd[1]=_Ad[1];_Bd[2]=_Ad[2]; 
	_path(s); 
	_Bd[3]=_Ad[0];_Bd[4]=_Ad[1];_Bd[5]=_Ad[2]; 
	_path(s-ds); 
	_Ad[6]=(_Bd[0]-2*_Bd[3] +_Ad[0])/(1.0*ds*ds);	
	_Ad[7]=(_Bd[1]-2*_Bd[4] +_Ad[1])/(1.0*ds*ds);	
	_Ad[8]=(_Bd[2]-2*_Bd[5] +_Ad[2])/(1.0*ds*ds);	
	}

void main(){
	float lengthofvector=5.0;//for visualization:
	int N = 100; //speed will keep on increainf as 
	double total_t = 6*M_PI;
	double ds = 6*M_PI/(1.0*N);
	double R[6][N][3];

	fp=fopen("f_data.txt", "w+");
	fpp=fopen("f_data1.txt", "w+");


	for(int i=0;i<N;i++){
			//calculate values at all grid points::
			_path(s);			R[0][i][0] = _Ad[0];	R[0][i][1] = _Ad[1];	R[0][i][2] = _Ad[2];	//positions
			// Derivatives
			derr1(s,ds);	R[1][i][0] = _Ad[3];	R[1][i][1] = _Ad[4];	R[1][i][2] = _Ad[5];	//first
			derr2(s,ds);	R[2][i][0] = _Ad[6];	R[2][i][1] = _Ad[7];	R[2][i][2] = _Ad[8];	//second
			
			//Calculate T
			d1=R[1][i][0];	d2=R[1][i][1];	d3=R[1][i][2];	d4=sqrt(d1*d1+d2*d2+d3*d3);//norm
			R[3][i][0]=d1/d4;		R[3][i][1]=d2/d4;		R[3][i][2]=d3/d4;
			
			//Calculate B
			d1=R[1][i][0];	d2=R[1][i][1];	d3=R[1][i][2];
			d4=R[2][i][0];	d5=R[2][i][1];	d6=R[2][i][2];
			d7 = d2*d6 -d3*d5;	d8= d3*d4 -d1*d6; d9= d1*d5 -d2*d4;
			d10 = sqrt(d7*d7+d8*d8+d9*d9);
			R[4][i][0]=d7/d10;	R[4][i][1]=d8/d10;		R[4][i][2]=d9/d10;
			
			//Calculate N
			d1=R[4][i][0];	d2=R[4][i][1];	d3=R[4][i][2];
			d4=R[3][i][0];	d5=R[3][i][1];	d6=R[3][i][2];
			d7 = d2*d6 -d3*d5;	d8= d3*d4 -d1*d6; d9= d1*d5 -d2*d4;
			d10 = sqrt(d7*d7+d8*d8+d9*d9);
			R[5][i][0]=d7/d10;	R[5][i][1]=d8/d10;	R[5][i][2]=d9/d10;
			
			/* print R, T, B, N in a file*/
			fprintf(fp,"%lf  %lf  %lf		%lf  %lf  %lf		%lf  %lf  %lf		%lf  %lf  %lf\n\n\n",R[0][i][0],R[0][i][1],R[0][i][2],R[3][i][0]*lengthofvector,R[3][i][1]*lengthofvector,R[3][i][2]*lengthofvector,R[4][i][0]*lengthofvector,R[4][i][1]*lengthofvector,R[4][i][2]*lengthofvector,R[5][i][0]*lengthofvector,R[5][i][1]*lengthofvector,R[5][i][2]*lengthofvector);
			fprintf(fpp,"%lf  %lf  %lf\n",R[0][i][0],R[0][i][1],R[0][i][2]);	

		s+=ds;
		}
	system("rm a");
	fclose(fp);	
	fclose(fpp);	
	
}

