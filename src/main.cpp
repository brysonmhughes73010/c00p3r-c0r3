---FILEPATH src/SPI.h
---FIND
```
#if defined(__AVR__)
#endif
#define SPI_HAS_TRANSACTION 1
```
---REPLACE
```
#if defined(__AVR__)
#endif // Ensure that this #endif corresponds to an #if
#define SPI_HAS_TRANSACTION 1
```
---COMPLETE

---FILEPATH src/JPEGDecoder.h
---FIND
```
#include "SPI.h"
```
---REPLACE
```
#include <SPI.h> // Ensure proper inclusion of SPI library
```
---COMPLETE

---FILEPATH platformio.ini
---FIND
```
; Add your libraries here
```
---REPLACE
```
lib_deps =
    lvgl
```
---COMPLETE