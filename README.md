# password_generator

``genpasswd`` is a program for generating a password.

### Usage

Clone the repository https://github.com/Anastasiiaq/password_generator.git. Go to the project folder and just do ``make`` to create an executable file.

Run the program as following :

```
./genpasswd [number of characters in the password] [options]
```

By default, the program will generate a password with all the options enabled.

<img width="640" alt="default" src="https://github.com/Anastasiiaq/password_generator/blob/master/screenshots/default.png">

The program can generate a password from 1 to 1.000.000 characters.

To read how to use the program, just call ``-help``.

<img width="640" alt="help" src="https://github.com/Anastasiiaq/password_generator/blob/master/screenshots/help.png">

### Options

To configure generation, use the following flags:

``-a`` - to use at least 1 lowercase letter

``-A`` - to use at least 1 uppercase letter

``-1`` - to use at least 1 digit

``-@`` - to use at least 1 special symbol

Characters running in a row are not repeated.

<img width="640" alt="generator" src="https://github.com/Anastasiiaq/password_generator/blob/master/screenshots/generator.png">
