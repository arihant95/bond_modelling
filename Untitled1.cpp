#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include<math.h>
int main()
{
    float fv,cpn,nc,nd;
    int f,i=0;
    printf("Please enter face value of coupon\n");
    scanf("%f",&fv);
    printf("Please enter the coupon rate\n");
    scanf("%f",&cpn);
    printf("Please enter no of days till next coupon\n");
    scanf("%f",&nd);
    printf("Please enter no of coupon\n");
    scanf("%f",&nc);
    printf("Please enter frequency\n");
    scanf("%d",&f);
    float y[2000];
    FILE*ff=fopen("Book2.txt","r");
    while (!feof(ff)){
        fscanf(ff,"%f",&y[i]);
     
        i++;
        
    }
   /* fv =100;
    cpn=0.0883;
    nc=16;
    nd=119;
    f=2;*/
    fclose(ff);
    float w=nd/(360/f);
    int a=52/f;
    int m=nd/7;
    float price=0,yi;
    float c=cpn*fv/f;
    for(i=1;i<nc;i++)
    {
    	yi=y[(m+(i-1)*a)]/(100*f);
    	price=price+(c/pow((1+yi),(w+i-1)));
    }
    price=price+((fv)/pow((1+yi),(w+i-1)));
	printf("\nPrice:%f",price);
	
	float error=1000;
	float diff=0.001;
	float yld=1/f;
	float fr=price,fdr=0;
	do 
	{
		float fr=price,fdr=0;
		for(i=1;i<nc;i++)
		{
			fr= fr - c/pow((1+yld),w+i-1);
			fdr= fdr+ (w+i-1)*c/pow((1+yld),w+i);
		}
		fr = fr -fv/pow((1+yld),(w+nc-1));
		fdr=(fdr + (fv * (w+nc-1)/pow((1+yld),(w+nc))))/f;
		yld = yld - (fr/(fdr*f));
	} while(abs(fr/fdr)>0.00001);
    
    printf("\nYield= %f",yld);
    
    
    /*code to find dp/dy*/
    float pdy=0;
    for(i=1;i<nc;i++)
    {
    	pdy= pdy- (w+i-1)*c/pow((1+yld),w+i);
	}
	pdy=(pdy - (fv * (w+nc-1)/pow((1+yld),(w+nc))))/f;
	printf("\ndp/dy = %f",pdy);
	
	/*code to find d^2p/dy^2*/
	float pddy=0;
	for(i=1;i<nc;i++)
    {
    	pddy= pddy + (w+i-1)*(w+i)*c/pow((1+yld),w+i+1);
	}
	pddy=(pddy + (fv * (w+nc-1)*(w+nc)/pow((1+yld),(w+nc+1))))/(f*f);
	printf("\nd^2p/dy^2 = %f",pddy);
	
	/*code to find DURATION AND CONVEXITY*/
	float dur;
	float com;
	dur=-((1+(yld/f))*pdy)/price;
	com=pddy/price;
	printf("\nDuration : %f",dur);
	printf("\nConvexity : %f",com);
    
    return (0);
}
