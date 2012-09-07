# NDS Toolkit Tests

This is the test code for the NDS Toolkit.

## Build Instructions

### Setup

The NDS Toolkit uses [CxxTest](http://cxxtest.com/) to test its code. To learn
how to use the framework, you may refer to their official documentation
[here](http://cxxtest.com/cxxtest/doc/guide.html).

To install CxxTest on your system, use, for example, one of the following:

```Shell
sudo apt-get install cxxtest
```

```Shell
sudo yum install cxxtest
```

You will also need an environment variable named CXXTEST containing the path
to the cxxtest include directory. If this is not set, the tests will not build.
Try adding the following line to your ```.bashrc```:

```Shell
export CXXTEST=/usr/include
```

If the above does not work, yours is in a different location.

If you are having problems compiling this code, also make sure that it isn't
a problem on your end by checking that this has output:

```Shell
cxxtestgen -v
```

You also need wxWidgets installed in order to run the test code. If you are
able to build this application successfully, that should not be a problem
when it comes to building these tests.

### Running Tests

Running ```make``` will build and run the tests and a fresh copy of all code
that the tests need to use. It will automatically clean up after itself any
generated files or compiled object files, but will keep the executable intact.
To run the tests again without rebuilding them, you can use ```make run```.

If you wish to run the executable directly, your current working directory
must be the the one that the executable is originally built in. If you move
the executable out of that directory or try to run it from elsewhere, it won't
be able to find the external files that it uses for testing. It is recommended
to just use ```make run``` for the purpose of executing the tests.

Also note that if you edit the code that is being tested, ```make run``` will
no longer be up to date! Always rebuild everything with ```make``` if you have
modified the source code to assure that you are testing the latest code.

To delete everything that is built, including the executable, run
```make delete``` or ```make erase```.
