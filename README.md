# password_generator

``genpasswd`` is a program for generating a password.

### Usage

Clone the repository https://github.com/Anastasiiaq/password_generator.git. Go to the project folder and just do ``make`` to create an executable file.

Run the program as following :

```
./genpasswd [number of characters in the password] [options]
```

By default, the program will generate a password with all the options enabled.

// default photo

The program can generate a password from 1 to 1.000.000 characters.

To read how to use the program, just call ``-help``.

// help photo

### Options

To configure generation, use the following flags:

``-a`` - to use at least 1 lowercase letter

``-A`` - to use at least 1 uppercase letter

``-1`` - to use at least 1 digit

``-@`` - to use at least 1 special symbol

Characters running in a row are not repeated.
