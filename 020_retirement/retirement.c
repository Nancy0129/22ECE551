#include <stdio.h>
#include <stdlib.h>

struct _account_info {
  int age;
  double balance;
};
typedef struct _account_info account_info;

struct _retire_info {
  int months;
  double contribution;
  double rate_of_return;
};
typedef struct _retire_info retire_info;

account_info monthly_balance(retire_info S, account_info P) {
  for (int m = 0; m < S.months; m++) {
    printf("Age %3d month %2d you have $%.2f\n", P.age / 12, P.age % 12, P.balance);
    P.balance += P.balance * S.rate_of_return + S.contribution;
    P.age++;
  }
  return P;
}

void retirement(int startAge, double initial, retire_info working, retire_info retired) {
  account_info person;
  person.balance = initial;
  person.age = startAge;
  person = monthly_balance(working, person);
  person = monthly_balance(retired, person);
}

int main(void) {
  retire_info working;
  retire_info retired;
  working.months = 489;
  working.contribution = 1000;
  working.rate_of_return = 0.045 / 12;

  retired.months = 384;
  retired.contribution = -4000;
  retired.rate_of_return = 0.01 / 12;

  retirement(327, 21345, working, retired);

  return EXIT_SUCCESS;
}
