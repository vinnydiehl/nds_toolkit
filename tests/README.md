# NDS Toolkit Tests

This is the test code for the NDS Toolkit.

## Build Instructions

### Setup

The NDS Toolkit uses [CxxTest](http://cxxtest.com/) to test its code. To learn
how to use the framework, you may refer to their official documentation
[here](http://cxxtest.com/cxxtest/doc/guide.html).

To install CxxTest on your system, try, for example, one of the following:

```
sudo apt-get install cxxtest
```

```
sudo yum install cxxtest
```

If you are having problems compiling this code, first make sure that it isn't
a problem on your end by checking that this has output:

```
cxxtestgen -v
```

### Running Tests

Running ```make``` will build and run the tests and a fresh copy of all code
that the tests need to use. It will automatically clean up after itself, but
to run the tests again without rebuilding them, you can use ```make run```.

To delete everything that is built, including the executable, run
```make delete``` or ```make erase```.

