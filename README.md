# Scaffold-c

## Overview

A simple utility to generate .h and .c files based on the given file name 

## Example

```
./main foo bar
```

foo.h
```
#ifndef FOO_H
#define FOO_H

#endif
```

bar.h
```
#ifndef BAR_H
#define BAR_H

#endif

```

foo.c

```
#include <stdio.h>
#include "foo.h"

int main() {

	return 0;
}
```

bar.c

```
#include <stdio.h>
#include "bar.h"

int main() {

	return 0;
}
```

