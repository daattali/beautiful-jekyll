To create a conforming program, you need to test for overflow **before** generating said overflow. The method can be used with unsigned integers too:

```
// For addition
#include <limits.h>

int a = <something>;
int x = <something>;
if ((x > 0) && (a > INT_MAX - x)) /* `a + x` would overflow */;
if ((x < 0) && (a < INT_MIN - x)) /* `a + x` would underflow */;
```

---

```
// For subtraction
#include <limits.h>
int a = <something>;
int x = <something>;
if ((x < 0) && (a > INT_MAX + x)) /* `a - x` would overflow */;
if ((x > 0) && (a < INT_MIN + x)) /* `a - x` would underflow */;
```

---

```
// For multiplication
#include <limits.h>

int a = <something>;
int x = <something>;
// There may be a need to check for -1 for two's complement machines.
// If one number is -1 and another is INT_MIN, multiplying them we get abs(INT_MIN) which is 1 higher than INT_MAX
if ((a == -1) && (x == INT_MIN)) /* `a * x` can overflow */
if ((x == -1) && (a == INT_MIN)) /* `a * x` (or `a / x`) can overflow */
// general case
if (a > INT_MAX / x) /* `a * x` would overflow */;
if ((a < INT_MIN / x)) /* `a * x` would underflow */;
```

---

For division (except for the `INT_MIN` and `-1` special case), there isn't any possibility of going over `INT_MIN` or `INT_MAX`.