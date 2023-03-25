/*  assignment 2
 *  DANIEL CHASTAIN
 *
 *
 */

#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>

/*
 * See instructions on how to do this part.
 * See the web site:
 *  http://www.ibiblio.org/gferg/ldp/GCC-Inline-Assembly-HOWTO.html#s4
 * for information on how to write gcc inline
 * assembly.
 */
int regular_pay_asm(int payrate, int hours) {
  // remember to put any register names
  // you are directly using in the
  // clobber list.
  // gpay - %0  hours - %1  payrate - %2
  int gpay = 0;
  asm(""
      : "=r"(gpay), "+r"(hours) /* output */
      : "r"(payrate)            /* input */
      :                         /* clobbered register */
  );

  return gpay;
}
// Operands are specified as a comma-separated list of constraints and C
// expressions, enclosed in parentheses. The constraints define the types of
// registers or memory locations the operands can use. r: Any general-purpose
// register
//  a: The eax/ax/al register
//  b: The ebx/bx/bl register
//  c: The ecx/cx/cl register
//  d: The edx/dx/dl register
//  m: A memory operand
//  i: An immediate integer operand (constant)
// EAX IS A TEMPORY POINT OF MEMORY
int regular_pay_c(int pay_rate, int hours) {
  int pay;               // this is now in memory ?
  asm("movl %1, %%eax\n" // eax = hours to the second input into EAX mov is how
                         // you move data into the structure
      "sarl $31, %%eax\n"   // shift arithmetic right, Hours > 40 line
      "andl $40, %%eax\n"   // eax = (hours > 40) ? 40 : 0
      "addl %1, %%eax\n"    // eax = (hours > 40)
      "andl $0x3F, %%eax\n" // eax = (hours > 40) ? 40 : hours
      "imull %2, %%eax\n"   // eax = eax * pay_rate
      "movl %%eax, %0\n"    // pay = eax
      : "=r"(pay)
      : "r"(hours), "r"(pay_rate)
      : "%eax");

  return pay;
}

int main() {
  int pay_rate = 15;
  int hours = 30;

  printf("enter pay rate: ");
  scanf("%d", &pay_rate);
  printf("enter hours: ");
  scanf("%d", &hours);

  int rpay_c = regular_pay_c(pay_rate, hours);
  int rpay_asm = regular_pay_asm(pay_rate, hours);
  printf("regular pay (C) is: %d \n", rpay_c);
  printf("regular pay (asm) is: %d \n", rpay_asm);

  return 0;
}