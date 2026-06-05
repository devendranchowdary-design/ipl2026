#include <stdio.h>

union decision {
  unsigned char flags;
  struct field {
    int your_choice : 1; /* tobe computed */
    int your_mothers_choice : 1;
    int your_fathers_choice : 1;
    int socially_acceptable : 1;
    int financially_viable : 1;
    int do_you_aptitude : 1;
    int do_you_likeit : 1;
    int decision : 1; /* to be computed */
  } field;
};

// Function Prototypes
union decision input();
void make_decision(union decision *d);
void print_decsion(union decision d);
void print_conclusion_based_on_flags(union decision d);

// 1. Input gathering
union decision input() {
  union decision d;
  d.flags = 0; // Clear all bits

  // Sample inputs: 1 for Yes, 0 for No
  d.field.your_mothers_choice = 1;
  d.field.your_fathers_choice = 1;
  d.field.socially_acceptable = 0;
  d.field.financially_viable = 1;
  d.field.do_you_aptitude = 1;
  d.field.do_you_likeit = 0;

  return d;
}

// 2. Decision expression
void make_decision(union decision *d) {
  // Core logic: You choose it if you like it and have the aptitude.
  d->field.your_choice = d->field.do_you_likeit && d->field.do_you_aptitude;

  // Final decision: Your choice matters, but parental approval and financial
  // viability can override or sustain it.
  d->field.decision =
      (d->field.your_choice && d->field.financially_viable) ||
      (d->field.your_mothers_choice && d->field.your_fathers_choice);
}

// 3. Narrative
void print_decsion(union decision d) {
  printf("--- Decision Narrative ---\n");
  printf("You %s what you do, and you %s the skills for it.\n",
         d.field.do_you_likeit ? "love" : "dislike",
         d.field.do_you_aptitude ? "have" : "lack");
  printf("Parents' approval status: Mother (%s), Father (%s).\n",
         d.field.your_mothers_choice ? "Yes" : "No",
         d.field.your_fathers_choice ? "Yes" : "No");
  printf("Final Verdict: %s\n\n", d.field.decision ? "PROCEED" : "HALT");
}

// 4. Conclusion based on raw flag integer value
void print_conclusion_based_on_flags(union decision d) {
  printf("--- Chaos Index (Flags Value: %d) ---\n", d.flags);

  if (d.flags == 0xFF) {
    printf("Absolute Harmony: Everything aligns perfectly.\n");
  } else if (d.flags == 0x00) {
    printf("Absolute Paralysis: Total existential standstill.\n");
  } else if (d.flags % 2 == 1) {
    printf(
        "Rebel Energy: The final decision is YES despite structural chaos.\n");
  } else {
    printf(
        "Internal Friction: Standard human condition. Proceed with caution.\n");
  }
}

int main() {
  union decision d = input();
  make_decision(&d);
  print_decsion(d);
  print_conclusion_based_on_flags(d);
  return 0;
}