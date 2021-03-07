# Changelog


Version 1.6
-----------

Minor changes (reverting to 2 files for get_time).


Version 1.5
-----------

Added an SSE/AVX version of the approximation function.


Version 1.4
-----------

Added another value in excess, but at the array' start, in order to return images
of the preset interval's boundaries when given input values outside of said interval.


Version 1.3
-----------

Change in the precomputation struct, in order to have a unified runtime environment accross versions.


Version 1.2
-----------

Added a value in excess at the end of the precomputed values array, which is the same as
the previous last value, in order to speed up the interpolation computation.


Version 1.1
-----------

Fixed an accuracy error. Changed the approximation function as to be branchless, resulting in far
greater speed when input values are often out of the preset range.


Version 1.0
-----------

Dynamically allocated version chosen. It feels cleaner, has no risk of user created memory leak,
and seems to have better performances when the Precomputation is declared as a static variable, which
in and on itself is quite natural for this utility.
