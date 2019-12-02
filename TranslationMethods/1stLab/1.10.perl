while (<>) {
  print if /\b(\S+)\1\b/;
}
