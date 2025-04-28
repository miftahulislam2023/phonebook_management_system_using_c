# Phonebook Management System

A simple C application to manage contacts with basic CRUD operations.

## File I/O Functions Used

1. **fopen(char* fname, char* mode)** - Opens a file
   - Returns file pointer or NULL on error
2. **fclose(FILE* fp)** - Closes the file stream
   - Returns 0 on success or EOF on error
3. **fread(void* ptr, size_t size, size_t count, FILE* fp)** - Reads binary data
   - Reads `count` elements of `size` bytes into `ptr`
4. **fwrite(void* ptr, size_t size, size_t count, FILE* fp)** - Writes binary data
   - Writes `count` elements of `size` bytes from `ptr`
5. **remove(const char* filename)** - Deletes a file
   - Used when updating/deleting contacts
6. **rename(const char* oldname, const char* newname)** - Renames a file
   - Used when updating the phonebook
7. **int fgetc(FILE* fp);**
   - reads the next byte as an unsigned character from the file stream and return it as an int or EOF on error
8. **int fputc(int ch, FILE* fp);**
   - writes a character to the file stream and returns it as an int or EOF on error
9. **int fputs(const char* str, FILE* fp);**
   - writes a string to the file stream and returns a non-negative number on success or EOF on error
10. **fgets(char* str, int n, FILE* fp);**
    - reads a string from the file stream and stores it in str, returns str on success or NULL on error
11. **int fprintf(FILE* fp, const char* format, ...);**
    - writes formatted data to the file stream and returns the number of characters written or a negative number on error
12. **int fscanf(FILE* fp, const char* format, ...);**
    - reads formatted data from the file stream and returns the number of items successfully read or EOF on error

## Notes

- EOF is a negative integer (usually -1) used to indicate the end of a file or an error in file operations
- The application handles memory allocation and deallocation for dynamic operations
