# The 8th NSTT:
Implement a hierarchy `for reading/writing` data from/to some source.
* `Base class`: IO; Should provide some basic information: if source is still open or not (can be closed manually by close() method), was eof reached or not.
* `1st level` of derived classes: Reader and Writer; They provide functions for reading/writing primitive types (and std::strings).
* `2nd level` of derived classes: ReaderWriter. It provides functions for reading and writing at the same time.
* `3rd level`: specific implementation for different sources:
  1. std::string as a source
  2. FILE* as a source.
* `4th level`: implementation for both string and FILE* sources with buffer.
  * Operations firstly read/write from/to the preallocated buffer of fixed size.
  * If buffer is empty/full, classes should read/write to the real source (string or file).