while (<>) {
  print if /^(0|((11)+0*)|(((11)*|0*)*(10)(1*|(00)*)*(01)0*))+$/;
}
