# Pointer Searcher Results File Format

The format of a Pointer Searcher Results file (```.psr``` file extension) is as
follows.

```
0
F432F
0x02101D40 : 0x0227E17C :: 0x00000090
0x021C0794 : 0x0227E17C :: 0x00000090
```

It simply gives the index of the current selection on the first line and the
contents of the Hex Value input on the second line, followed by each of the
results, listed one per line.

The PSR class handles this file format- it contains methods for reading a file,
verifying the validity of the file, and returning relevant information about
the PSR.

## Class Usage

### Construction

The class can be constructed by passing in a ```wxFFile``` or a ```wxString```
containing the path to the file that is to be read in initially.

### Reading

The currently loaded file may be changed using the ```Read()``` method. Simply
call this as you would the constructor- with either an ```wxFFile``` or a
```wxString``` containing the path to the file.

### Writing

There are static methods to allow the writing of PSR files without constructing
an instance of the PSR class.

To write a PSR file, simply pass the name of the file to be written, the list
of search results, and the currently selected result to this method:

```C++
static void Write(wxString filename,
                  wxArrayString results,
                  int index,
                  wxString hexValue);
```

### Verification

To verify that the file that has been loaded is a valid PSR file, run the
```Verify()``` method. It will return a boolean stating the file's validity.
It is recommended to run this before accessing the file's data, as the
methods for getting that data only offers minimal protection against improperly
formatted files.

### Data Access

To access the data in the currently loaded PSR file, you can use the
```GetResults()``` method to get a wxArrayString containing all of the search
results, or the ```GetIndex()``` method to get the index of the currently
selected result. The ```GetHexValue()``` method gets the contents of the Hex
Value input.
