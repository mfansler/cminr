Team: Merv Fansler

Notes
=====

When checking for externally defined methods (e.g., "input"), identifier and
nestLevel info are checked.  Technically, nestLevel could be omitted since all
C- function declarations must happen at global level.  However, including it now
should future-proof it should functions ever become full class citizens.
