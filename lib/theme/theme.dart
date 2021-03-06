import 'package:flutter/material.dart';

var appButtonColor = Colors.teal.shade200;
final ThemeData theme = ThemeData(
  textTheme: TextTheme(
    display1: TextStyle(fontSize: 15),
    // subtitle: TextStyle(fontSize: ),
    button: TextStyle(
      color: Colors.white,
    ),
  ),
  appBarTheme: AppBarTheme(
    color: appButtonColor,
  ),
  snackBarTheme: SnackBarThemeData(backgroundColor: Colors.lightBlue.shade100),
  backgroundColor: Colors.teal.shade50,
  errorColor: Colors.red,
  buttonColor: appButtonColor,
);
