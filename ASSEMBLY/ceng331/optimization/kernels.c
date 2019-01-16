/********************************************************
 * Kernels to be optimized for the CS:APP Performance Lab
 ********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "defs.h"
/*
 * Please fill in the following student struct
 */
team_t team = {
    "e1942317",              /* Student ID */

    "Emrah Kosen",     /* full name */
    "e1942317@ceng.metu.edu.tr",  /* email address */

    "",                   /* leave blank */
    ""                    /* leave blank */
};


/***************
 * CONVOLUTION KERNEL
 ***************/

/******************************************************
 * Your different versions of the convolution functions  go here
 ******************************************************/

/*
 * naive_conv - The naive baseline version of convolution
 */

char naive_conv_descr[] = "naive_conv: Naive baseline implementation";
void naive_conv(int dim,int *src, int *ker,int *dst)
{
    int i,j,k,l;

    for(i = 0; i < dim-8+1; i++)
        for(j = 0; j < dim-8+1; j++) {
            dst[j*dim+i] = 0;
            for(k = 0; k < 8; k++)
                for(l = 0; l < 8; l++) {
                    dst[j*dim+i] = dst[j*dim+i] +src[(j+l)*dim+(i+k)]*ker[l*dim+k];
                }
        }




 }

/*
 * convolution - Your current working version of convolution
 * IMPORTANT: This is the version you will be graded on
 */
char convolution_descr[] = "Dot product: Current working version";
void convolution(int dim,int *src, int *ker,int *dst)
{
  int i=0,j,des,dimijk,kdim,dimi;

  int dim81 = dim-7;
    first:
          dimi = dim*i;
              j =0;
              second:
                  des = 0;
                  dimijk = dimi  +j;
                  kdim = 0;
                  des += src[dimijk ]*ker[kdim];
                  des += src[dimijk +1]*ker[1+kdim];
                  des += src[dimijk +2]*ker[2+kdim];
                  des += src[dimijk +3]*ker[3+kdim];
                  des += src[dimijk +4]*ker[kdim+4];
                  des += src[dimijk +5]*ker[5+kdim];
                  des += src[dimijk +6]*ker[6+kdim];
                  des += src[dimijk +7]*ker[7+kdim];
                dimijk+=dim;
                  kdim += dim;
                  des += src[dimijk ]*ker[kdim];
                  des += src[dimijk +1]*ker[1+kdim];
                  des += src[dimijk +2]*ker[2+kdim];
                  des += src[dimijk +3]*ker[3+kdim];
                  des += src[dimijk +4]*ker[kdim+4];
                  des += src[dimijk +5]*ker[5+kdim];
                  des += src[dimijk +6]*ker[6+kdim];
                  des += src[dimijk +7]*ker[7+kdim];
                  dimijk+=dim;
                    kdim += dim;
                    des += src[dimijk ]*ker[kdim];
                    des += src[dimijk +1]*ker[1+kdim];
                    des += src[dimijk +2]*ker[2+kdim];
                    des += src[dimijk +3]*ker[3+kdim];
                    des += src[dimijk +4]*ker[kdim+4];
                    des += src[dimijk +5]*ker[5+kdim];
                    des += src[dimijk +6]*ker[6+kdim];
                    des += src[dimijk +7]*ker[7+kdim];
                    dimijk+=dim;
                      kdim += dim;
                      des += src[dimijk ]*ker[kdim];
                      des += src[dimijk +1]*ker[1+kdim];
                      des += src[dimijk +2]*ker[2+kdim];
                      des += src[dimijk +3]*ker[3+kdim];
                      des += src[dimijk +4]*ker[kdim+4];
                      des += src[dimijk +5]*ker[5+kdim];
                      des += src[dimijk +6]*ker[6+kdim];
                      des += src[dimijk +7]*ker[7+kdim];
                      dimijk+=dim;
                        kdim += dim;
                        des += src[dimijk ]*ker[kdim];
                        des += src[dimijk +1]*ker[1+kdim];
                        des += src[dimijk +2]*ker[2+kdim];
                        des += src[dimijk +3]*ker[3+kdim];
                        des += src[dimijk +4]*ker[kdim+4];
                        des += src[dimijk +5]*ker[5+kdim];
                        des += src[dimijk +6]*ker[6+kdim];
                        des += src[dimijk +7]*ker[7+kdim];
                        dimijk+=dim;
                          kdim += dim;
                          des += src[dimijk ]*ker[kdim];
                          des += src[dimijk +1]*ker[1+kdim];
                          des += src[dimijk +2]*ker[2+kdim];
                          des += src[dimijk +3]*ker[3+kdim];
                          des += src[dimijk +4]*ker[kdim+4];
                          des += src[dimijk +5]*ker[5+kdim];
                          des += src[dimijk +6]*ker[6+kdim];
                          des += src[dimijk +7]*ker[7+kdim];
                          dimijk+=dim;
                            kdim += dim;
                            des += src[dimijk ]*ker[kdim];
                            des += src[dimijk +1]*ker[1+kdim];
                            des += src[dimijk +2]*ker[2+kdim];
                            des += src[dimijk +3]*ker[3+kdim];
                            des += src[dimijk +4]*ker[kdim+4];
                            des += src[dimijk +5]*ker[5+kdim];
                            des += src[dimijk +6]*ker[6+kdim];
                            des += src[dimijk +7]*ker[7+kdim];
                            dimijk+=dim;
                              kdim += dim;
                              des += src[dimijk ]*ker[kdim];
                              des += src[dimijk +1]*ker[1+kdim];
                              des += src[dimijk +2]*ker[2+kdim];
                              des += src[dimijk +3]*ker[3+kdim];
                              des += src[dimijk +4]*ker[kdim+4];
                              des += src[dimijk +5]*ker[5+kdim];
                              des += src[dimijk +6]*ker[6+kdim];
                              des += src[dimijk +7]*ker[7+kdim];



          dst[dimi+j] = des;

      j+= 1;
      if(j < dim81)
        goto second;
      i += 1;
  if(i<dim81)
    goto first;


}

/*********************************************************************
 * register_conv_functions - Register all of your different versions
 *     of the convolution functions  with the driver by calling the
 *     add_conv_function() for each test function. When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.
 *********************************************************************/

void register_conv_functions() {
    add_conv_function(&naive_conv, naive_conv_descr);
    add_conv_function(&convolution, convolution_descr);
    /* ... Register additional test functions here */
}




/***************
 * MATRIX MULTIP KERNEL
 ***************/

/******************************************************
 * Your different versions of the matrix multiplications  go here
 ******************************************************/

/*
 * naive_matrix_multiplication - The naive baseline version of matrix multiplication
 */
char naive_matrix_multiplication_descr[] = "Naive_matrix_multiplication: Naive baseline implementation";
void naive_matrix_multiplication(int dim,int *src, int *src2,int *dst) {
    int i,j,k;

    for(i = 0; i < dim; i++)
        for(j = 0; j < dim; j++) {
            dst[j*dim+i]=0;
            for(k = 0; k < dim; k++)
                dst[j*dim+i] = dst[j*dim+i] + src[j*dim+k]*src2[i+k*dim];
        }
}


/*
 * matrix_multiplication - Your current working version of matrix_multiplication
 * IMPORTANT: This is the version you will be graded on
 */
char matrix_multiplication_descr[] = "Matrix multiplications: Current working version";
void matrix_multiplication(int dim,int *src, int *src2,int *dst)
{
int i,j,k;






  if(dim%128 == 0)
  {
    int a,x = 0 , y  ,yk,xk;
    int dim2 = dim/2,dim4= dim/4,dim34= dim*3/4;
      for (i = 0; i < dim; i++)
      {  //k = i+(i+1)dim;
          for (j = i+1; j < dim; j++)
          {   k = j*dim+i;
              a = src2[x+j];
              src2[x+j] = src2[k];
              src2[k] = a;
              k+=dim;
          }
        x += dim;
      }

        x =0;
        for(i = 0; i < dim4; i++)
        {

          y = 0;
          for(j = 0; j < dim4; j++)
          {

            a=0;


              for(k = 0; k < dim; k+=64)
              {
                yk = y+k;
                xk = x+k;
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk];

              }

            dst[x+j]=a;
            y += dim;
          }

          for(j = dim4; j < dim2; j++)
          {

            a=0;


              for(k = 0; k < dim; k+=64)
              {
                yk = y+k;
                xk = x+k;
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk];

              }

            dst[x+j]=a;
            y += dim;
          }

          for(j = dim2; j < dim34; j++)
          {

            a=0;


              for(k = 0; k < dim; k+=64)
              {
                yk = y+k;
                xk = x+k;
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk];

              }

            dst[x+j]=a;
            y += dim;
          }

          for(j = dim34; j < dim; j++)
          {

            a=0;


              for(k = 0; k < dim; k+=64)
              {
                yk = y+k;
                xk = x+k;
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk];

              }

            dst[x+j]=a;
            y += dim;
          }
          x += dim;
        }

        for(i = dim4; i < dim2; i++)
        {

          y = 0;
          for(j = 0; j < dim4; j++)
          {

            a=0;


              for(k = 0; k < dim; k+=64)
              {
                yk = y+k;
                xk = x+k;
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk];

              }

            dst[x+j]=a;
            y += dim;
          }

          for(j = dim4; j < dim2; j++)
          {

            a=0;


              for(k = 0; k < dim; k+=64)
              {
                yk = y+k;
                xk = x+k;
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk];

              }

            dst[x+j]=a;
            y += dim;
          }

          for(j = dim2; j < dim34; j++)
          {

            a=0;


              for(k = 0; k < dim; k+=64)
              {
                yk = y+k;
                xk = x+k;
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk];

              }

            dst[x+j]=a;
            y += dim;
          }

          for(j = dim34; j < dim; j++)
          {

            a=0;


              for(k = 0; k < dim; k+=64)
              {
                yk = y+k;
                xk = x+k;
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk];

              }

            dst[x+j]=a;
            y += dim;
          }
          x += dim;
        }

        for(i = dim2; i < dim34; i++)
        {

          y = 0;
          for(j = 0; j < dim4; j++)
          {

            a=0;


              for(k = 0; k < dim; k+=64)
              {
                yk = y+k;
                xk = x+k;
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk];

              }

            dst[x+j]=a;
            y += dim;
          }

          for(j = dim4; j < dim2; j++)
          {

            a=0;


              for(k = 0; k < dim; k+=64)
              {
                yk = y+k;
                xk = x+k;
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk];

              }

            dst[x+j]=a;
            y += dim;
          }

          for(j = dim2; j < dim34; j++)
          {

            a=0;


              for(k = 0; k < dim; k+=64)
              {
                yk = y+k;
                xk = x+k;
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk];

              }

            dst[x+j]=a;
            y += dim;
          }

          for(j = dim34; j < dim; j++)
          {

            a=0;


              for(k = 0; k < dim; k+=64)
              {
                yk = y+k;
                xk = x+k;
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk];

              }

            dst[x+j]=a;
            y += dim;
          }
          x += dim;
        }

        for(i = dim34; i < dim; i++)
        {

          y = 0;
          for(j = 0; j < dim4; j++)
          {

            a=0;


              for(k = 0; k < dim; k+=64)
              {
                yk = y+k;
                xk = x+k;
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk];

              }

            dst[x+j]=a;
            y += dim;
          }

          for(j = dim4; j < dim2; j++)
          {

            a=0;


              for(k = 0; k < dim; k+=64)
              {
                yk = y+k;
                xk = x+k;
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk];

              }

            dst[x+j]=a;
            y += dim;
          }

          for(j = dim2; j < dim34; j++)
          {

            a=0;


              for(k = 0; k < dim; k+=64)
              {
                yk = y+k;
                xk = x+k;
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk];

              }

            dst[x+j]=a;
            y += dim;
          }

          for(j = dim34; j < dim; j++)
          {

            a=0;


              for(k = 0; k < dim; k+=64)
              {
                yk = y+k;
                xk = x+k;
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk++];
                a+=src[xk++]*src2[yk];

              }

            dst[x+j]=a;
            y += dim;
          }
          x += dim;
        }








    x = 0;
    for (i = 0; i < dim; i++)
    {  //k = i+(i+1)dim;
        for (j = i+1; j < dim; j++)
        {   k = j*dim+i;
            a = src2[x+j];
            src2[x+j] = src2[k];
            src2[k] = a;
            k+=dim;
        }
      x += dim;
    }



  }


  else
  {
    int idim;
    for(i = 0; i < dim; i++)
      {
        idim = i*dim;
        for(j = 0; j < dim; j++)
        {
            int des = 0;
            int kdimj = j;
            for(k = 0; k < dim; k+=32)
                {
                  int idimk = idim+k;

                  des +=  src[idimk]*src2[kdimj];
                  des +=  src[++idimk]*src2[kdimj+=dim];
                  des +=  src[++idimk]*src2[kdimj+=dim];
                  des +=  src[++idimk]*src2[kdimj+=dim];
                  des +=  src[++idimk]*src2[kdimj+=dim];
                  des +=  src[++idimk]*src2[kdimj+=dim];
                  des +=  src[++idimk]*src2[kdimj+=dim];
                  des +=  src[++idimk]*src2[kdimj+=dim];
                  des +=  src[++idimk]*src2[kdimj+=dim];
                  des +=  src[++idimk]*src2[kdimj+=dim];
                  des +=  src[++idimk]*src2[kdimj+=dim];
                  des +=  src[++idimk]*src2[kdimj+=dim];
                  des +=  src[++idimk]*src2[kdimj+=dim];
                  des +=  src[++idimk]*src2[kdimj+=dim];
                  des +=  src[++idimk]*src2[kdimj+=dim];
                  des +=  src[++idimk]*src2[kdimj+=dim];
                  des +=  src[++idimk]*src2[kdimj+=dim];
                  des +=  src[++idimk]*src2[kdimj+=dim];
                  des +=  src[++idimk]*src2[kdimj+=dim];
                  des +=  src[++idimk]*src2[kdimj+=dim];
                  des +=  src[++idimk]*src2[kdimj+=dim];
                  des +=  src[++idimk]*src2[kdimj+=dim];
                  des +=  src[++idimk]*src2[kdimj+=dim];
                  des +=  src[++idimk]*src2[kdimj+=dim];
                  des +=  src[++idimk]*src2[kdimj+=dim];
                  des +=  src[++idimk]*src2[kdimj+=dim];
                  des +=  src[++idimk]*src2[kdimj+=dim];
                  des +=  src[++idimk]*src2[kdimj+=dim];
                  des +=  src[++idimk]*src2[kdimj+=dim];
                  des +=  src[++idimk]*src2[kdimj+=dim];
                  des +=  src[++idimk]*src2[kdimj+=dim];
                  des +=  src[++idimk]*src2[kdimj+=dim];
                  kdimj+=dim;
                }
            dst[idim +j]=des;

        }
        idim += dim;
      }
  }



}





/*********************************************************************
 * register_matrix_multiplication_functions - Register all of your different versions
 *     of the matrix multiplication  with the driver by calling the
 *     add_matrix_multiplication_function() for each test function. When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.
 *********************************************************************/

void register_matrix_multiplication_functions() {
    add_matrix_multiplication_function(&naive_matrix_multiplication, naive_matrix_multiplication_descr);
    add_matrix_multiplication_function(&matrix_multiplication, matrix_multiplication_descr);
    /* ... Register additional test functions here */
}
