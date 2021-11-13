#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define max 400
int strxor[max];
void chuyenint(char s1[],int s2[],int s3[]){
    for(int i=0;i<strlen(s1);i++){
        if (s1[i]>='a' && s1[i]<='f')
            s2[i]=s1[i]-87;
        if (s1[i]>='0' && s1[i]<='9')
            s2[i]=int(s1[i])-48;
    }
    for (int l=0;l<strlen(s1);l=l+2){
        s3[l/2]=s2[l]*2*2*2*2 + s2[l+1];
    }
}
void Xor(char s1[],char s2[], int s1x[], int s2x[],int s1i[],int s2i[]){
    // s1,s2 là 2 bản mã hệ hexa ban đầu
    // s1x,s2x là 2 bản mã chuyển các chữ trong chuỗi về dạng số nguyên 
    // s1i,s2i là 2 bản mã được chuyển về thành số nguyên để xor
    int i;
    chuyenint(s1,s1x,s1i);
    chuyenint(s2,s2x,s2i);
    for (int i=0;i<200;i++){// in ra các số của chuỗi số sau khi xor s1i và s2i
        strxor[i]=s1i[i]^s2i[i];
 //       if ( strxor[i]>=65 && strxor[i]<=90 || strxor[i]>=97 && strxor[i]<=122)
  //          printf("%d - %d || ",strxor[i],i);
    }
}
int main(){
    int key[250]={0};
    char s1[max],s2[max];
    int s1x[max]={0},s2x[max]={0},s1i[max]={0},s2i[max]={0};
    int mang[10][max]={0};
    int lap;
   // for (lap =0;lap <10; lap ++){// Nhập lần lượt từ 1 đến 10 là bản mã s1 
        printf("Nhap s1:");
    fflush(stdin);
    gets(s1);
    for (int j=0;j<9;j++){//Nhập 9 bản mã còn lại để Xor với bản mã s1 ban đầu ( s1 là bản mã bất kì trong 10 bản ban đầu nhập từ bàn phím)
        printf("Nhap s2:");
        fflush(stdin);
        gets(s2);
        Xor(s1,s2,s1x,s2x,s1i,s2i);
        for (int i=0;i<200;i++){
            if ( strxor[i]>=65 && strxor[i]<=90 || strxor[i]>=97 && strxor[i]<=122){
                mang[j][i]=strxor[i];
                //printf("%d - %d || ",mang[j][i],i);
            }   
        }
        printf("\n");
    }
    for (int j=0;j<200;j++){
        int i;
        //printf("Cot thu %d : ",j);
        int m1[9]={0},dem=2,x1;
        for ( i=0;i<9;i++){
            if ( mang[i][j]>=65 && mang[i][j]<=90 || mang[i][j]>=97 && mang[i][j]<=122){
                //printf("%d - %d || ",mang[i][j],i+1);
                m1[i]=mang[i][j];
             }
            
        }
    for (int i1=0;i1<9;i1++){
            if (m1[i1] > 0){
                x1=m1[i1];
                break;
                }
            }
        for (int i1=0;i1<9;i1++){
            if (m1[i1] > 0 && m1[i1] != x1)  dem++;
        }
        if (dem > 2 ){
            key[j]=32^s1i[j];
        }
    }
    /*for (int i1=0;i1<250;i1++){
        if (key[i1] > 0) printf("%d - %d ||",key[i1],i1);
    }*/
    //}
    char s10[max];
    int s10i[max]={0},s10x[max]={0};// s10 là chuỗi cần giải mã
    printf("Nhap chuoi can giai ma:");
    fflush(stdin);
    gets(s10);
    chuyenint(s10,s10x,s10i);// chuyển thành int để xor cùng bản key( các kí tự key tìm được)
    for (int i1=0;i1<250;i1++){
        if (key[i1] > 0) printf("%c - %d ||",key[i1]^s10i[i1],i1); // Khi xor ta sẽ tìm được gần hết bản rõ :The secuet-mes*age*is: Wh** usi|g **str*am cipher, nev***use th* k*y *ore than onc*
        }// từ đó suy ra bản rõ là: The secret message is: When using a stream cipher, never use the key more than once
    return 0;
}
// Ý tưởng thuật toán: Xor lần lượt các bản mã với nhau theo thứ tự rồi cập nhật vào mảng key, thực hiện quá trình này 10 lần chạy thì ta
// lại nhập tiếp bản mã tiếp theo để xor và điền vào mảng key. Khi xor các bản với nhau, ta sẽ giả sử xor s1 với 10 bản còn lại được các kí tự 
// ở cùng dòng ( giả sử cột 2 - nghĩa là kí tự thứ 2 ở mỗi bản mã), xor với kí tự thứ 2 của s1 được các chữ cái a-z hoặc A-Z mà thu được các bản xor
// khác nhau nên kí tự thứ 2 của bản rõ của s1 là dấu space (" "); từ đó xor lại với s1 để tìm ra key và đem xor với bản mã cần giải, cứ như thế đến hết 10 bản thì tìm được