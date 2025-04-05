# simple-pkcs7
a pkcs7 implementation

## Usage
to create a pkcs7 struct

```c
char *data = "hello";
pkcs7_t *pkcs = create_pkcs7(data, strlen(data) + 1, 16);
```

get padded data

```c
uint8_t *data = (uint8_t*) copy_pkcs_data(pkcs);
```

release pkcs7 struct

```c
free_pkcs(pkcs);
```