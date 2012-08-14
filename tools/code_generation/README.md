# Code Generation Tools

The tools in this directory are to aid the process of developing for the NDS
Toolkit, by speeding up automatable coding tasks. This README will be updated
as new tools are added.

## page_generator

This tool will generate the code for a new NDS Toolkit page and place it in
the program's ```pages``` directory for you. To generate a page, you may
supply it command-line arguments, like so:

```
./page_generator pgClassName 'Page Title' v
```

The last argument, either a v or an h, decides whether the main box sizer is
vertical or horizontal, respectively.

If you give no command line arguments, it will ask you for your selections
at runtime.

